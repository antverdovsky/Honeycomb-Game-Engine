#ifndef BLINN_PHONG_SPOT_GLSL
#define BLINN_PHONG_SPOT_GLSL

#include <blinnPhongBase.glsl>
#include <../../structs/light/stdSpotLight.glsl>

/// Calculates the light which should be applied to this fragment given the
/// spot light which shines upon it, the camera position, the world position of
/// the fragment and the normal of the surface normal.
/// SpotLight sL : The spot light which shines on this fragment.
/// Material mat : The material of the surface on this fragment.
/// Camera cam : The camera with which to render the scene.
/// vec3 wP : The world position of this fragment.
/// vec3 norm : The normalized normal of the surface.
/// float shine : The shiness of the reflection (for specular reflection).
/// vec3 specColor : The color of the reflection (for specular reflection).
/// vec3 dif : The diffuse material color of this fragment before applying the
///			   lighting.
/// sampler2D shadowMap : The shadow map texture.
/// vec4 shadowCoords : The light projection transformed coordinates for
///						reading from the shadow map.
/// return : The spot light color.
vec3 calculateSpotLight(SpotLight sL, Camera cam, vec3 wP, vec3 norm, 
        float shine, vec3 specColor, vec3 dif, sampler2D shadowMap,
		vec4 shadowCoords) {
    // Calculate the displacement vector between the world position of the
    // fragment and the spot light position.
    vec3 displacement = wP - sL.position;
    
    // Calculate the distance between the fragment and the point light. If the
    // distance exceeds the range of the point light, return a zero vector 
    // since the point light can't affect this fragment.
    float dispMag = length(displacement);
    
    // Calculate the angle between the fragment and the spot light. If the 
    // angle exceeds the angle of the spot light, return a zero vector since
    // the spot light can't affect this fragment.
    vec3 direction = normalize(displacement);
    float cosAngle = dot(direction, normalize(sL.direction));
   
    // Calculate the Attenuation of the Point Light. Subtract the attenuation 
	// at the range of the light to assure the attenuation at the range is 
	// zero. This makes the falloff less natural at low ranges, but fixes the
	// sudden falloff which can occur if the intensity >> range.
    float attenuation = 1.0F / calculateAttenuation(sL.attenuation, dispMag)
		- 1.0F / calculateAttenuation(sL.attenuation, sL.range);
	attenuation *= float(attenuation >= 0);

	// Calculate the angle factor using the cosine angle and the cosine of the
	// half angle. This factor will gradually fall off as the light angle
	// approaches the the hypotenuse of the spot light cone. This allows for
	// a smooth transition from light to darkness at the light's edges.
	float cosHalfAngle = cos(sL.angle / 2.0F);
	float angleFactor = 1.0F - (1.0F - cosAngle) / (1.0F - cosHalfAngle);

	// Calculate the final intensity using the base intensity, attenuation
	// and the angle factor.
	float intensity = sL.base.intensity * attenuation * angleFactor;
    
    // Calculate the Diffuse and Specular Light components of the Spot Light 
    // and scale by the attenuation to adjust the light with distance.
    vec3 diffuse = calculateDiffuseLight(sL.base, direction, norm);
    vec3 specular = calculateSpecularReflection(sL.base, cam, wP, direction, 
		norm, shine, specColor);

	// Calculate the shadow value which will determine how much diffuse and
	// specular lighting we should apply.
	float inShadow = isInShadow(shadowMap, shadowCoords, sL, norm, wP);
	float shadowValue = (1.0F - inShadow) + (1.0F - sL.shadow.intensity);
	shadowValue = clamp(shadowValue, 0.0F, 1.0F);

    // Return the blend of the Diffuse and Specular lighting
    return shadowValue * (((dif * diffuse) + specular) * intensity);
}

#endif