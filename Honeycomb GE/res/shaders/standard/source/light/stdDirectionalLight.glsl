#version 330 core

#include <..\..\include\stdLight.glsl>

///
/// The directional light structure.
///
struct DirectionalLight {
    BaseLight base; // The base component of the light
    
    vec3 direction; // The direction of the light
};

in vec2 out_vs_texCoord; // Take in texture coordinate outputted by VS
in vec3 out_vs_norm; // Take in the normal outputted by VS
in vec3 out_vs_pos; // Take in the world position outputted by VS

uniform DirectionalLight directionalLight; // The directional light
uniform Material material; // The material

uniform Camera camera;

/// Forward Declarations
vec4 calculateDirectionalLight(DirectionalLight dL, Material mat, Camera cam,
        vec3 wP, vec3 norm);

/// Calculates the light which should be applied to this fragment, given the
/// directional light which shines on it and the normal of the surface.
/// DirectionLight dL : The directional light which will be used to calculate
///                     the effect of the light.
/// Material mat : The material for which the light should be calculated.
/// Camera cam : The camera with which the light is calculated.
/// vec3 wP : The world position of the fragment.
/// vec3 norm : The normal vector of the surface. This should be normalized,
///             prior to being passed in.
/// return : The vector which can be used to add or detract lighting from the
///          fragment.
vec4 calculateDirectionalLight(DirectionalLight dL, Material mat, Camera cam, 
        vec3 wP, vec3 norm) {
    // Calculate the Diffuse and Specular Light components of the Directional
    // Light.
    vec4 diffuse = calculateDiffuseLight(dL.base, mat, dL.direction, norm);
    vec4 specular = calculateSpecularReflection(dL.base, mat, cam, wP, 
        dL.direction, norm);
    
    // Return the blend of the Diffuse and Specular lighting
    return diffuse + specular;
}

void main() {
    // Calculate the contributions of the Light sources
    vec4 directionalComponent = calculateDirectionalLight(directionalLight,
        material, camera, out_vs_pos, out_vs_norm);
        
    // Sum up the contributions of the Light sources
    vec4 totalLight = directionalComponent;
    
	// Set the color to the color provided by the Texture, mixed with the
    // lighting for this fragment.
	gl_FragColor = vec4(totalLight.xyz, 1.0F) * 
		texture2D(material.albedoTexture, out_vs_texCoord);
}