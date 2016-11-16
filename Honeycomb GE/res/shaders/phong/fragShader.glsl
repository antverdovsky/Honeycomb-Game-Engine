///
/// Phong Fragment Shader.
///
/// Calculates the lighting on a fragment, and shades it to emulate lighting.
///

#version 330 core

///
/// The basic structure for all lights.
/// 
struct BaseLight {
    float intensity; // The intensity of the light
    vec3 color; // The color of the light
};

///
/// The ambient light strcture.
///
struct AmbientLight {
    BaseLight base; // The base components of the light
};

///
/// The directional light structure.
///
struct DirectionalLight {
    BaseLight base; // The base components of the light
    vec3 direction; // The direction of the light
};

in vec2 out_vs_texCoord; // Take in texture coordinate outputted by VS
uniform sampler2D textureSampler; // Texture Sampler2D
uniform vec3 albedoColor = vec3(0.0, 1.0F, 1.0F);

in vec3 out_vs_norm; // Take in the normal outputted by VS

uniform AmbientLight ambientLight; // The ambient light
uniform DirectionalLight directionalLight; // The directional light (TODO: ARRAY of many lights)

/// Calculates the light which should be applied to this fragment, given the
/// ambient light which shines on it.
/// AmbientLight aL : The ambient light which should be calculated.
/// return : The vector which can be used to add or detract lighting from the 
///          fragment.
vec4 calculateAmbientLight(AmbientLight aL) {
    return vec4(aL.base.intensity * aL.base.color, 1);
}

///
/// Calculates the light which should be applied to this fragment, given the
/// directional light which shines on it and the normal of the surface.
/// DirectionLight dL : The directional light which will be used to calculate
///                     the effect of the light.
/// vec3 norm : The normal vector of the surface. This should be normalized,
///             prior to being passed in.
///
vec4 calculateDirectionalLight(DirectionalLight dL, vec3 norm) {
    // Get the diffuse effect of the light, but if it less than 0, ignore it
    return max(dot(norm, -dL.direction), 0.0F) * dL.base.color * 
        dL.base.intensity;
}

void main() {
    vec4 totalLight = calculateAmbientLight(ambientLight) + 
        calculateDirectionalLight(directionalLight, out_vs_norm);

	// Set the color to the color provided by the Texture, mixed with the
    // lighting for this fragment.
	gl_FragColor = vec4(albedoColor, 1.0F) * totalLight * 
		texture2D(textureSampler, out_vs_texCoord);
}