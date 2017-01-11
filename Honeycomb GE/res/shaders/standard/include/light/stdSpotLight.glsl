#include <stdBaseLight.glsl>

///
/// The spot light structure
///
struct SpotLight {
    BaseLight base; // The base component of the light
    Attenuation attenuation; // The attenuation of the light

    vec3 position; // The 3D position of the light in the world
    vec3 direction; // The direction of the light in the world
    
    float range; // The range of the light (height of the cone formed by the 
                 // light point and light ray).
    float angle; // The spot angle of the light.
};

/// Calculates the light which should be applied to this fragment given the
/// spot light which shines upon it, the camera position, the world position of
/// the fragment and the normal of the surface normal.
/// SpotLight sL : The spot light which shines on this fragment.
/// Material mat : The material of the surface on this fragment.
/// Camera cam : The camera with which to render the scene.
/// vec3 wP : The world position of this fragment.
/// vec3 norm : The normalized normal of the surface.
/// float shine : The shiness of the reflection (for specular reflection).
vec4 calculateSpotLight(SpotLight sL, Camera cam, vec3 wP, vec3 norm, 
        float shine) {
    // Calculate the displacement vector between the world position of the
    // fragment and the spot light position.
    vec3 displacement = wP - sL.position;
    
    // Calculate the distance between the fragment and the point light. If the
    // distance exceeds the range of the point light, return a zero vector 
    // since the point light can't affect this fragment.
    float dispMag = length(displacement);
    if (dispMag > sL.range) return vec4(0.0F, 0.0F, 0.0F, 0.0F);
    
    // Calculate the angle between the fragment and the spot light. If the 
    // angle exceeds the angle of the spot light, return a zero vector since
    // the spot light can't affect this fragment.
    vec3 direction = normalize(displacement);
    float cosAngle = dot(direction, normalize(sL.direction));
    if (cosAngle < cos(sL.angle)) return vec4(0.0F, 0.0F, 0.0F, 0.0F);
    
    // Calculate the Attenuation of the Point Light, and the adjusted
    // attenuation which will make the attenuation zero at the range of the
    // spot light and zero at the edge of the angle of the spot light to allow 
    // for a smoother light transition.
    float atten = calculateAttenuation(sL.attenuation, dispMag);
    float intensity = (1.0F / atten) * sL.base.intensity * 
        (1.0F - (1.0F - cosAngle) / (1.0F - cos(sL.angle))) * 
        ((sL.range - dispMag) / sL.range);
    
    // Calculate the Diffuse and Specular Light components of the Spot Light 
    // and scale by the attenuation to adjust the light with distance.
    vec4 diffuse = calculateDiffuseLight(sL.base, direction, norm);
    vec4 specular = calculateSpecularReflection(sL.base,  cam, wP, direction,
        norm, shine);
    diffuse = vec4(diffuse.xyz * intensity, diffuse.w);
    specular = vec4(specular.xyz * intensity, specular.w);
    
    // Return the blend of the Diffuse and Specular lighting
    return diffuse + specular;
}