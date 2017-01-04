#version 330 core

#include <..\..\include\stdLight.glsl>

///
/// The ambient light strcture.
///
struct AmbientLight {
    BaseLight base; // The base component of the light
};

in vec2 out_vs_texCoord; // Take in texture coordinate outputted by VS
in vec3 out_vs_norm; // Take in the normal outputted by VS
in vec3 out_vs_pos; // Take in the world position outputted by VS

uniform AmbientLight ambientLight; // The ambient light
uniform Material material; // The material

uniform vec3 cameraPos;

/// Forward Declarations
vec4 calculateAmbientLight(AmbientLight aL, Material mat);

/// Calculates the light which should be applied to this fragment, given the
/// ambient light which shines on it.
/// AmbientLight aL : The ambient light which should be calculated.
/// Material mat : The material for which the light should be calculated.
/// return : The vector which can be used to add or detract lighting from the 
///          fragment.
vec4 calculateAmbientLight(AmbientLight aL, Material mat) {
    // Calculate the ambient light but do NOT apply the intensity to the W
    // component, so that the surface does not become transparent if the
    // intensity is less than 1.0F.
    return vec4(
        vec3(aL.base.intensity * aL.base.color.xyz * mat.ambientColor.xyz *
            aL.base.color.w * mat.ambientColor.w),
        aL.base.color.w * mat.ambientColor.w);
}


void main() {
    // Calculate the contributions of the Light sources
    vec4 ambientComponent = calculateAmbientLight(ambientLight, material);
        
    // Sum up the contributions of the Light sources
    vec4 totalLight = ambientComponent;
    
	vec3 amsd = cameraPos; // TODO: JUST SO IT ISNT OPTIMIZED AWAY FROM SHADER FOR NOW

	// Set the color to the color provided by the Texture, mixed with the
    // lighting for this fragment.
	gl_FragColor = vec4(totalLight.xyz, 1.0F) * 
		texture2D(material.albedoTexture, out_vs_texCoord);
}