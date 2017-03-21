#include <stdBaseLight.glsl>

///
/// The point light structure.
///
struct PointLight {
    BaseLight base; // The base component of the light
	Attenuation attenuation; // The attenuation of the light
	
	vec3 position; // The 3D position of the light in the world
    float range; // The sphere-like radius of the light (the higher this value
                 // the more accurate the attenuation of the light).
};

/// Calculates the light which should be applied to this fragment, given the
/// point light which shines on it, the coordinates of the fragment position 
/// and the surface normal.
/// PointLight pL : The point light which shines on the surface.
/// Camera cam : The camera with which the scene is rendered.
/// vec3 wP : The world position of the fragment.
/// vec3 norm : The normal of the surface.
/// float shine : The shininess of the reflection (for specular reflection).
/// vec3 specColor : The color of the reflection (for specular reflection).
/// return : The vector which can be used to add or detract lighting from the
///          fragment.
vec4 calculatePointLight(PointLight pL, Camera cam, vec3 wP, vec3 norm, 
        float shine, vec3 specColor) {
    // Calculate the displacement vector between the world position of the
    // fragment and the point light position.
    vec3 displacement = wP - pL.position;
    
    // Calculate the distance between the fragment and the point light. If the
    // distance exceeds the range of the point light, return a zero vector 
    // since the point light can't affect this fragment.
    float dispMag = length(displacement);
 
	// Get the unit vector pointing in the direction of the displacement
    vec3 direction  = normalize(displacement);
    
    // Calculate the Attenuation of the Point Light, and the adjusted
    // attenuation which will make the attenuation zero at the range of the
    // point light to allow for a smoother light transition.
	float atten = calculateAttenuation(pL.attenuation, dispMag);
	float intensity = (1.0F / atten) * pL.base.intensity * 
		((pL.range - dispMag) / pL.range);
    
    // Calculate the Diffuse and Specular Light components of the Point Light 
    // and scale by the attenuation to adjust the light with distance.
    vec4 diffuse = calculateDiffuseLight(pL.base, direction, norm);
    vec4 specular = calculateSpecularReflection(pL.base, cam, wP, direction, 
        norm, shine, specColor);
    diffuse = vec4(diffuse.xyz * intensity, diffuse.w);
    specular = vec4(specular.xyz * intensity, specular.w);
    
    // Return the blend of the Diffuse and Specular lighting
    return diffuse + specular;
}