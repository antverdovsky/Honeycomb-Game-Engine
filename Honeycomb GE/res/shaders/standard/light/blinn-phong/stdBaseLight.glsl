#include <../../structs/stdCamera.glsl>
#include <../../../util/math.glsl>

// Shadow Type "enumeration"
const int SHADOW_TYPE_NONE						= 0;
const int SHADOW_TYPE_CLASSIC					= 1;
const int SHADOW_TYPE_PCF						= 2;
const int SHADOW_TYPE_VARIANCE					= 3;

///
/// The basic structure for all lights.
/// 
struct BaseLight {
    vec3 color;		 // The color of the light
    float intensity; // The intensity of the light
};

///
/// The attenuation structure for non-uniform lights.
///
struct Attenuation {
	float constant;  // The constant coefficient in the attenuation equation
	float linear;	 // The linear coefficient in the attenuation equation
	float quadratic; // The quadratic coefficient in the attenuation equation
};

///
/// The structure for a shadow.
/// 
struct Shadow {
	int shadowType;	 // The type of shadow cast by this Light
	mat4 projection; // The projection of the Shadow

	float intensity; // The intensity of the Shadow

	float minBias;	 // Minimum Bias (if light is parallel to surface)
	float maxBias;	 // Maximum Bias (if light is perpendicular to surface)
};

/// Samples the specified shadow map at the specified coordinates using
/// percentage-closer filtering (PCF).
/// sampler2D map : The shadow map rendered from the perspective of the light.
/// vec2 coords : The coordnates at which to sample the shadow map.
/// float bias : The shadow bias value.
/// float curDepth : The current depth from the projection coordinates.
/// return : The shadow value.
float sampleShadowPCF(sampler2D map, vec2 coords, float bias, 
		float curDepth);

/// Samples the specified shadow map at the specified coordinates with no
/// antialiasing or special filtering.
/// sampler2D map : The shadow map rendered from the perspective of the light.
/// vec2 coords : The coordnates at which to sample the shadow map.
/// float bias : The shadow bias value.
/// float curDepth : The current depth from the projection coordinates.
/// return : The shadow value.
float sampleShadowClassic(sampler2D map, vec2 coords, float bias,
		float curDepth);

/// Samples the specified shadow map at the specified coordinates using the
/// variance shadow mapping technique.
/// sampler2D map : The shadow map rendered from the perspective of the light.
/// vec2 coords : The coordnates at which to sample the shadow map.
/// float bias : The shadow bias value.
/// float curDepth : The current depth from the projection coordinates.
/// return : The shadow value.
float sampleShadowVariance(sampler2D map, vec2 coords, float bias,
		float curDepth);

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
/// return : The diffuse lighting color.
vec3 calculateDiffuseLight(BaseLight bL, vec3 dir, vec3 norm) {
    float diff = max(dot(-dir, norm), 0.0F);
    return clamp(diff * bL.intensity * bL.color, 0.0F, 1.0F);
}

/// Calculates the specular reflection for this fragment given the light for
/// which the reflection is being computed, and the coordinates of the camera 
/// and the fragment, using the Blinn-Phong lighting model.
/// BaseLight bL : The light for which the reflection is being computed.
/// Camera cam : The camera with which the scene is rendered.
/// vec3 wP : The position of the fragment in the world.
/// vec3 dirLight : The direction with which the light hits the surface.
/// vec3 norm : The normal to the surface.
/// float shine : The shininess of the specular reflection.
/// vec3 color : The color of the specular reflection.
/// return : The specular reflection color.
vec3 calculateSpecularReflection(BaseLight bL, Camera cam, vec3 wP, 
		vec3 dirLight, vec3 norm, float shine, vec3 color) {
    vec3 cP = cam.translation; // Camera Position
        
    vec3 dirView = normalize(cP - wP); // Direction from Cam to Frag
	vec3 dirHalf = normalize(dirView - dirLight); // Get the halfway direction
    
    // Calculate the specular reflection factor and multiply by the specular
	// diffuse factor (one for keep, zero for discard).
	float spec = pow(max(dot(dirHalf, norm), 0.0F), shine);

    // Calculate the specular light
	return clamp(spec * bL.intensity * bL.color * color, 0.0F, 1.0F);
}

/// Checks if the fragment is in shadow.
/// sampler2D map : The shadow map rendered from the perspective of the light.
/// vec4 coords : The light projection transformed coordinates which correspond
///				  to the shadow map texture.
/// vec3 dir : The direction of the light ray.
/// vec3 norm : The normal of the surface of the fragment.
/// Shadow shdw : The shadow of the light.
/// return : 1.0F if the fragment is in shadow; 0.0F otherwise.
float isInShadow(sampler2D map, vec4 coords, vec3 dir, vec3 norm, 
		Shadow shdw) {
	// If the light uses no shadows, all fragments are outside of the shadow so
	// always return 0.0F.
	if (shdw.shadowType == SHADOW_TYPE_NONE) {
		return 0.0F;
	} 
	
	// Calculate the bias using the diffuse component to reduce shadow acne
	float diffuse = 1.0F - max(dot(-dir, norm), 0.0F);
	float bias = max(shdw.maxBias * diffuse, shdw.minBias);

	// Convert the coordinates from light coordinates to texture coordinates.
	vec3 texCoords = coords.xyz / coords.w;		// to [-1,  1]
	texCoords = texCoords * 0.5F + 0.5;			// to [ 0,  1]

	// Get the current depth value of the fragment in relation to the light.
	float currentDepth = texCoords.z;

	// Information fetched from the texture is only valid if the Z component of
	// the the texture coordinates is in range [0, 1]. Otherwise, this fragment
	// is not in the texture map so any shadow calculation is unreliable.
	float isValidShadow = float(currentDepth >= 0.0F && currentDepth <= 1.0F);

	float shadow = 0.0F; // Stores the Shadow Value

	if (shdw.shadowType == SHADOW_TYPE_CLASSIC) {			// Classic Shadows
		shadow = sampleShadowClassic(map, texCoords.xy, bias, currentDepth);
	} else if (shdw.shadowType == SHADOW_TYPE_PCF) {		// PCF Shadows	
		shadow = sampleShadowPCF(map, texCoords.xy, bias, currentDepth);
	} else if (shdw.shadowType == SHADOW_TYPE_VARIANCE) {   // Variance Shadows
		shadow = sampleShadowVariance(map, texCoords.xy, bias, currentDepth);
	}

	// Return the Shadow Value multiplied by the validity factor
	return (1.0F - shadow) * isValidShadow;
}

float sampleShadowClassic(sampler2D map, vec2 coords, float bias,
		float curDepth) {
	// Get the depth value of the fragment from the shadow map
	float textureDepth = texture2D(map, coords).r;

	// If the current depth is greater than the shadow depth then the fragment
	// is currently farther away from the light than according to the shadow.
	// This implies the fragment is in shadow.
	return step(curDepth - bias, textureDepth);
}

float sampleShadowPCF(sampler2D map, vec2 coords, float bias, 
		float curDepth) {
	// The number of samples used for PCF.
	const int SAMPLE_COUNT = 1 * 3;	// DO NOT modify the value 3
	const int SAMPLE_COUNT_SQRD = SAMPLE_COUNT * SAMPLE_COUNT;

	// Get the texel size (inverse of the pixel size of the shadow map)
	vec2 offset = 1.0F / textureSize(map, 0);
	
	// Stores the final shadow map depth value
	float shadow = 0.0F;

	// Loop through all of the surrounding pixels and the current pixel
	for (int i = 0; i < SAMPLE_COUNT_SQRD; ++i) {
		// Get the x and y offsets from the current pixel ([-1, 1])
		int x = i / SAMPLE_COUNT - 1;
		int y = i % SAMPLE_COUNT - 1;

		// Fetch the depth from the shadow texture map at the current pixel
		vec2 offsetCoord = coords + vec2(x, y) * offset;
		float textureDepth = texture2D(map, offsetCoord).r;

		// If the current depth is greater than the shadow depth then the 
		// fragment is currently farther away from the light than according to 
		// the shadow map. This implies the fragment is in shadow, therefore,
		// increment the shadow value.
		shadow += step(curDepth - bias, textureDepth);
	}

	// Since we sampled 9 pixels in total (8 surrounding + 1 center), we divide
	// the shadow value by 9 to get the average shadow value.
	return shadow / SAMPLE_COUNT_SQRD;
}

float sampleShadowVariance(sampler2D map, vec2 coords, float bias,
		float curDepth) {
	// Fetch the RG channels of the texture and use them to get the depth and
	// depth ^ 2 values.
	vec2 mapRG = texture2D(map, coords).rg;
	float textureDepth = mapRG.r;
	float textureDepth2 = mapRG.g;
	
	// The probability the texture is in shadow, according to classic shadow
	// mapping. Bias is not really necessary anymore but it's left in for more
	// user control.
	float p = smoothstep(curDepth - bias, curDepth, textureDepth);

	// Calculate the Variance value for Chebyshev's Inequality
	float variance = max(textureDepth2 - textureDepth * textureDepth, 0.0002F);

	// Calculate the distance from the mean (standard deviation) and use it to 
	// compute the maximum P value (maximum probability the pixel is lit).
	float d = curDepth - textureDepth;
	float pMax = variance / (variance + d * d);

	// Clamp the probability such that any values below MIN_P_MAX go to 0.0F 
	// and any values greater than MAX_P_MAX go to 1.0F, using linear stepping.
	// This helps lower the light bleeding artifact of VSM.
	const float MIN_P_MAX = 0.2F;
	const float MAX_P_MAX = 1.0F;
	pMax = linstep(0.2F, 1.0F, pMax);

	// Return the probability that the pixel is lit (which should be such that
	// pMax > p is bounded between [0.0F, 1.0F])
	return clamp(max(p, pMax), 0.0F, 1.0F);
}