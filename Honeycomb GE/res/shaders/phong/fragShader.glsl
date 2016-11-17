///
/// Phong Fragment Shader.
///
/// Calculates the lighting on a fragment, and shades it to emulate lighting.
///

#version 330 core

uniform sampler2D textureSampler; // Texture Sampler

///
/// The material structure.
///
struct Material {
    vec3 ambientColor; // Color under ambient light
    vec3 diffuseColor; // Color under diffuse light
};

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
in vec3 out_vs_norm; // Take in the normal outputted by VS
in vec3 out_vs_pos; // Take in the world position outputted by VS

uniform AmbientLight ambientLight; // The ambient light
uniform DirectionalLight directionalLight; // The directional light (TODO: ARRAY of many lights)
uniform Material material; // The material

/// Calculates the diffuse light which should be applied to this fragment, given
/// some base light which shines on it.
/// BaseLight bL : The base light which should be calculated.
/// vec3 dir : The direction with which the BaseLight shines upon the surface.
/// vec3 norm : The normal of the surface on which the BaseLight shines upon.
///             This should be normalized, prior to being passed in.
/// return : The vector which can be used to add or detract lighting from the
///          fragment.
vec4 calculateDiffuseLight(BaseLight bL, vec3 dir, vec3 norm) {
    float diff = max(dot(norm, -dir), 0.0F);
    
    return diff * bL.color * bL.intensity;
}

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
    return calculateDiffuseLight(dL.base, dL.direction, norm);
}

void main() {
    vec4 ambientComponent = calculateAmbientLight(ambientLight) *
        vec4(material.ambientColor, 1.0F);
    vec4 directionalComponent = calculateDirectionalLight(directionalLight,
        out_vs_norm) * vec4(material.diffuseColor, 1.0F);

    vec4 totalLight = ambientComponent + directionalComponent;

	// Set the color to the color provided by the Texture, mixed with the
    // lighting for this fragment.
	gl_FragColor = totalLight * texture2D(textureSampler, out_vs_texCoord);
}