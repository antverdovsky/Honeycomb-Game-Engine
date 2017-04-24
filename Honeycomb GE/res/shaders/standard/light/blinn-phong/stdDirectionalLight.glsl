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
/// vec3 specColor : The color of the reflection (for specular reflection).
/// vec3 dif : The diffuse material color of this fragment before applying the
///			   lighting.
/// sampler2D shadowMap : The shadow map texture.
/// vec4 shadowCoords : The light projection transformed coordinates for
///						reading from the shadow map.
/// return : The directional light color.
vec3 calculateDirectionalLight(DirectionalLight dL, Camera cam, vec3 wP, 
        vec3 norm, float shine, vec3 specColor, vec3 dif, sampler2D shadowMap,
		vec4 shadowCoords) {
    // Calculate the Diffuse and Specular Light components of the Directional
    // Light.
    vec3 diffuse = calculateDiffuseLight(dL.base, dL.direction, norm);
    vec3 specular = calculateSpecularReflection(dL.base, cam, wP, 
		dL.direction, norm, shine, specColor);

	float inShadow = isInShadow(shadowMap, shadowCoords, dL.direction, norm,
		dL.base.shadowType);

    // Return the blend of the Diffuse and Specular lighting
    return (1.0F - inShadow) * ((dif * diffuse) + specular);
}