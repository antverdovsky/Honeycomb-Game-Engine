#include <..\stdCamera.glsl>

///
/// The basic structure for all lights.
/// 
struct BaseLight {
    vec4 color; // The color of the light
    float intensity; // The intensity of the light
};

///
/// The attenuation structure for non-uniform lights.
///
struct Attenuation {
	float constant; // The constant coefficient in the attenuation equation
	float linear; // The linear coefficient in the attenuation equation
	float quadratic; // The quadratic coefficient in the attenuation equation
};

/// Calculates the attenuation of the specified attenuation component at the
/// specified distance.
/// Attenuation atten : The attenuation component.
/// float d : The distance of the fragment from the light.
/// return : The value of the attenuation at the fragment distance given.
float calculateAttenuation(Attenuation atten, float d) {
	return (atten.constant + atten.linear * d + atten.quadratic * d * d);
}

/// Calculates the diffuse light which should be applied to this fragment, 
/// given some base light which shines on it.
/// BaseLight bL : The base light which should be calculated.
/// vec3 dir : The direction with which the BaseLight shines upon the surface.
/// vec3 norm : The normal of the surface on which the BaseLight shines upon.
///             This should be normalized, prior to being passed in.
/// return : The vector which can be used to add or detract lighting from the
///          fragment.
vec4 calculateDiffuseLight(BaseLight bL, vec3 dir, vec3 norm) {
    float diff = max(dot(-dir, norm), 0.0F);
    
    // Calculate the diffuse light but do NOT apply the intensity to the W
    // component, so that the surface does not become transparent if the
    // intensity is less than 1.0F.
    return vec4(vec3(diff * bL.intensity * bL.color.xyz), bL.color.w);
}

/// Calculates the specular reflection for this fragment given the light for
/// which the reflection is being computed, and the coordinates of the camera 
/// and the fragment.
/// BaseLight bL : The light for which the reflection is being computed.
/// Camera cam : The camera with which the scene is rendered.
/// vec3 wP : The position of the fragment in the world.
/// vec3 dir : The direction with which the light hits the surface.
/// vec3 norm : The normal to the surface.
/// float shine : The shininess of the specular reflection.
/// vec3 color : The color of the specular reflection.
/// return : The specular reflection.
vec4 calculateSpecularReflection(BaseLight bL, Camera cam, vec3 wP, vec3 dir, 
        vec3 norm, float shine, vec3 color) {
    vec3 cP = cam.translation; // Camera Position
        
    vec3 direction = normalize(cP - wP); // Direction from Cam to Frag
    vec3 reflection = normalize(reflect(dir, norm)); // Get the reflection
    
    // Calculate the specular reflection factor
    float spec = pow(max(dot(direction, reflection), 0.0F), shine);
    
    // Calculate the specular light but do NOT apply the intensity to the W
    // component, so that the surface does not become transparent if the
    // intensity is less than 1.0F.
    return vec4(vec3(spec * bL.intensity * bL.color.xyz * color), bL.color.w);
}