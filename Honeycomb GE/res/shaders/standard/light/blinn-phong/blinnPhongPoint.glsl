#ifndef BLINN_PHONG_POINT_GLSL
#define BLINN_PHONG_POINT_GLSL

#include <blinnPhongBase.glsl>
#include <../../structs/light/stdPointLight.glsl>

/// Calculates the light which should be applied to this fragment, given the
/// point light which shines on it, the coordinates of the fragment position 
/// and the surface normal.
/// PointLight pL : The point light which shines on the surface.
/// Camera cam : The camera with which the scene is rendered.
/// vec3 wP : The world position of the fragment.
/// vec3 norm : The normal of the surface.
/// float shine : The shininess of the reflection (for specular reflection).
/// vec3 specColor : The color of the reflection (for specular reflection).
/// vec3 dif : The diffuse material color of this fragment before applying the
///			   lighting.
/// return : The point light color.
vec3 calculatePointLight(PointLight pL, Camera cam, vec3 wP, vec3 norm, 
        float shine, vec3 specColor, vec3 dif) {
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
	float atten = 1.0F / calculateAttenuation(pL.attenuation, dispMag) - 
		1.0F / calculateAttenuation(pL.attenuation, pL.range);
	float intensity = atten * pL.base.intensity;
    
    // Calculate the Diffuse and Specular Light components of the Point Light 
    // and scale by the attenuation to adjust the light with distance.
    vec3 diffuse = calculateDiffuseLight(pL.base, direction, norm);
    vec3 specular = calculateSpecularReflection(pL.base, cam, wP, 
		direction, norm, shine, specColor);
	
    // Return the blend of the Diffuse and Specular lighting
	return ((dif * diffuse) + specular) * intensity;
}

#endif