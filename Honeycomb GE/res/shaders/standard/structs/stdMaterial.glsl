#ifndef STD_MATERIAL_GLSL
#define STD_MATERIAL_GLSL

///
/// The Texture structure.
///
struct Texture2D {
	sampler2D sampler;			// The sampler2D used to sample the texture
	float intensity;			// Scales the RGB colors of the texture
};

///
/// The Material structure.
///
struct Material {
	vec3 albedoColor;				// Albedo color of the Material
	Texture2D albedoTexture;		// Albedo texture of the Material

	vec3 ambientColor;				// Color under ambient light
	Texture2D ambientTexture;		// Texture under ambient light

    vec3 diffuseColor;				// Color under diffuse light
	Texture2D diffuseTexture;		// Texture under diffuse light

    vec3 specularColor;				// Color of the specular reflection
	Texture2D specularTexture;		// Specular texture of the Material
	float shininess;				// Shininess of the specular reflection

	Texture2D normalsTexture;		// Normal/Bump Map
	Texture2D displacementTexture;	// Displacement/Height Map

	float refractiveIndex;			// Index of refraction
	float reflectionStrength;		// The strength of the Reflection [0, 1]

	vec2 globalTiling;				// Tiling for all textures
	vec2 globalOffset;				// Offset for all textures
};

/// Constant values for the minimum and maximum number of layers when using
/// Steep Parallax Mapping.
const float MIN_DISPLACEMENT_LAYERS = 8.0F;
const float MAX_DISPLACEMENT_LAYERS = 32.0F;

/// Applies the specified gamma to the specified RGB texture color.
/// vec4 inColor : The inputted RGB texture color, which is to be gamma 
///				   corrected into SRGB.
/// float gamma : The gamma to be applied.
/// return : The gamma corrected SRGB texture color.
vec4 applyGammaSRGB(vec4 inColor, float gamma);

/// Converts the specified coordinates to texture coordinates for the
/// specified material.
/// Material mat : The material for which the coordinates are to be computed.
/// vec2 coords : The coordinates which are to be transformed.
/// return : The transformed coordinates.
vec2 getTextureCoordinates(Material mat, vec2 coords);

/// Samples the specified 2D texture at the specified coordinates. The
/// coordinates will be automatically adjusted according to the tiling and
/// offsets of the Texture struct as well as according to the parallax map.
/// Material mat : The material in which the textures are located.
/// Texture2D tex : The texture which is to be sampled.
/// Texture2D par : The displacement map to be used to adjust the coordinates.
/// vec2 coord : The original texture coordinates.
/// float gamma : The gamma to be used when sampling (1.0F for linear space).
/// return : The RGBA value of the texture at the adjusted coordinates.
vec4 parallaxSampleTexture2D(Material mat, Texture2D tex, Texture2D par, 
		vec2 coord, vec3 eye, mat3 tbn, float gamma);

/// Transforms the specified texture coordinates according to the Material's
/// parallax mapping texture.
/// Texture2D par : The parallax displacement map.
/// vec2 original : The original texture coordinates, which are to be
///					transformed.
/// vec3 eye : The eye view vector.
/// return : The transformed texture coordinates.
vec2 parallaxTransform(Texture2D par, vec2 original, vec3 eye, mat3 tbn);

/// Samples the specified 2D texture at the specified coordinates. The 
/// coordinates will be automatically adjusted according to the tiling and
/// offsets of the Texture structure.
/// Material mat : The material in which the texture is located.
/// Texture2D tex : The texture which is to be sampled.
/// vec2 coord : The original texture coordinates.
/// float gamma : The gamma to be used when sampling (1.0F for linear space).
/// return : The RGBA value of the texture at the adjusted coordinates.
vec4 sampleTexture2D(Material mat, Texture2D tex, vec2 coord, float gamma);

/// Fetches a fragment of the specified texture at the specified texture
/// coordinates. The texture's fragment will be gamma corrected (or not)
/// depending on the gamma parameter.
/// sampler2D texture : The sampler containing the texture.
/// vec2 coord : The coordinates of the fragment on the texture.
/// float gamma : The gamma value. If the gamma value is equal to 1.0F, the
///			      image is not gamma corrected in anyway and its raw RGB values
///				  are returned instead.
/// return : The gamma corrected fragment color (alpha is returned raw).
vec4 texture2DSRGB(sampler2D texture, vec2 coord, float gamma);

/// Fetches a fragment of the specified cubemap at the specified cube
/// coordinates. The cube's fragment will be gamma corrected (or not) depending
/// on the gamma parameter.
/// samplerCube cube : The sampler containing the cubemap.
/// vec3 coord : The coordinates of the fragment on the cubemap.
/// float gamma : The gamma value. If the gamma value is equal to 1.0F, the
///			      image is not gamma corrected in anyway and its raw RGB values
///				  are returned instead.
/// return : The gamma corrected fragment color (alpha is returned raw).
vec4 textureCubeSRGB(samplerCube cube, vec3 coord, float gamma);

vec4 applyGammaSRGB(vec4 inColor, float gamma) {
	vec3 gammaVec3 = vec3(gamma);
	vec3 outColor = pow(inColor.rgb, gammaVec3);

	return vec4(outColor, inColor.a);
}

vec2 getTextureCoordinates(Material mat, vec2 coords) {
	return coords * mat.globalTiling + mat.globalOffset;
}

vec4 parallaxSampleTexture2D(Material mat, Texture2D tex, Texture2D par, 
		vec2 coord, vec3 eye, mat3 tbn, float gamma) {
	// Adjust the texture coordinates according to the tiling and offset of 
	// the Texture2D struct.
	vec2 adjCoord = getTextureCoordinates(mat, coord);
	vec2 parallaxCoord = parallaxTransform(par, adjCoord, eye, tbn);
	vec4 texColor = texture2D(tex.sampler, parallaxCoord) * 
		vec4(vec3(tex.intensity), 1.0F);

	return applyGammaSRGB(texColor, gamma);
}

vec2 parallaxTransform(Texture2D par, vec2 original, vec3 eye, mat3 tbn) {
	// Fetch the view (eye) vector
	vec3 viewTBN = normalize(-eye * tbn);
	
	// Get the number of layers and the depth of each layer (equal to inverse
	// the number of layers). Calculate the number of layers by lerping 
	// between the minimum and maximum number of layers, with the "t" arugment
	// being the steepness of the surface, where the less steep the surface, 
	// the less displacement layers we use, for performance considerations.
	float steepness = abs(dot(vec3(0.0F, 0.0F, 1.0F), viewTBN));
	float layerCount = mix(
		MAX_DISPLACEMENT_LAYERS, MIN_DISPLACEMENT_LAYERS, steepness);
	float eachLayerDepth = 1.0F / layerCount;
	float currentLayerDepth = 0.0F;
	
	// Calculate the initial displacement value
	vec2 parallaxValue = viewTBN.xy * (par.intensity / 10.0F);
	vec2 deltaTexCoords = parallaxValue / layerCount;

	// Calculate the initial height and texture coordinate values
	vec2 currentTexCoords = original;
	float currentTextureDepth = texture2D(par.sampler, currentTexCoords).r;

	// Sample all of the layers until we hit the depth of the texture, and 
	// adjust the texture coordinates and depth as necessary.
	while (currentLayerDepth < currentTextureDepth) {
		// Displace the texture coordinates according to the parallax vector
		currentTexCoords -= deltaTexCoords;

		// Get the new depth value from the displacement texture
		currentTextureDepth = texture2D(par.sampler, currentTexCoords).r;

		// Increment the layer depth counter
		currentLayerDepth += eachLayerDepth;
	}

	// Get the texture coordinates as they were before the last iteration of
	// the loop.
	vec2 previousTexCoords = currentTexCoords + deltaTexCoords;

	// Calculate the depth at the current and previous texture coordinates
	float afterDepth = currentTextureDepth - currentLayerDepth;
	float beforeDepth = texture2D(par.sampler, previousTexCoords).r - 
		currentLayerDepth + eachLayerDepth;

	// Perform an interpolation to find the medium point between the before 
	// and after depths.
	float interpolation = afterDepth / (afterDepth - beforeDepth);
	currentTexCoords = previousTexCoords * interpolation +
		currentTexCoords * (1.0F - interpolation);

	return currentTexCoords;
}

vec4 sampleTexture2D(Material mat, Texture2D tex, vec2 coord, float gamma) {
	// Adjust the texture coordinates according to the tiling and offset of 
	// the Texture2D struct.
	vec2 adjCoord = getTextureCoordinates(mat, coord);
	vec4 texColor = texture2D(tex.sampler, adjCoord) *
		vec4(vec3(tex.intensity), 1.0F);

	return applyGammaSRGB(texColor, gamma);
}

vec4 texture2DSRGB(sampler2D texture, vec2 coord, float gamma) {
	vec4 texColor = texture2D(texture, coord);
	return applyGammaSRGB(texColor, gamma);
}

vec4 textureCubeSRGB(samplerCube cube, vec3 coord, float gamma) {
	vec4 texColor = texture(cube, coord);
	return applyGammaSRGB(texColor, gamma);
}

#endif