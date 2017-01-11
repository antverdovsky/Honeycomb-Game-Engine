#include <stdBaseLight.glsl>

///
/// The directional light structure.
///
struct DirectionalLight {
    BaseLight base; // The base component of the light
    
    vec3 direction; // The direction of the light
};

/// Calculates the light which should be applied to this fragment, given the
/// directional light which shines on it and the normal of the surface.
/// DirectionLight dL : The directional light which will be used to calculate
///                     the effect of the light.
/// Camera cam : The camera with which the light is calculated.
/// vec3 wP : The world position of the fragment.
/// vec3 norm : The normal vector of the surface. This should be normalized,
///             prior to being passed in.
/// float shine : The shininess of the reflection (for specular reflection).
/// return : The vector which can be used to add or detract lighting from the
///          fragment.
vec4 calculateDirectionalLight(DirectionalLight dL, Camera cam, vec3 wP, 
        vec3 norm, float shine) {
    // Calculate the Diffuse and Specular Light components of the Directional
    // Light.
    vec4 diffuse = calculateDiffuseLight(dL.base, dL.direction, norm);
    vec4 specular = calculateSpecularReflection(dL.base, cam, wP, dL.direction,
        norm, shine);
    
    // Return the blend of the Diffuse and Specular lighting
    return diffuse + specular;
}