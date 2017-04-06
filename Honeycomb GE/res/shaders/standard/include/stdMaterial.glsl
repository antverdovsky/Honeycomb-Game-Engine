///
/// The Texture structure.
///
struct Texture2D {
	sampler2D sampler;			// The sampler2D used to sample the texture
	vec2 tiling;				// The tiling of the texture on X, Y axes
	vec2 offset;				// The offset of the texture on X, Y axes
};

///
/// The Material structure.
///
struct Material {
    vec3 diffuseColor;				// Diffuse color of the Material
	Texture2D diffuseTexture;		// Diffuse texture of the Material

    vec3 specularColor;				// Color of the specular reflection
	Texture2D specularTexture;		// Specular texture of the Material
	float shininess;				// The shininess of the specular reflection

	Texture2D normalsTexture;		// Normal/Bump Map
	Texture2D displacementTexture;	// Displacement/Height Map

	float refractiveIndex;			// Index of refraction
	float reflectionStrength;		// The strength of the Reflection [0, 1]
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
vec4 applyGammaSRGB(vec4 inColor, float gamma) {
	vec3 gammaVec3 = vec3(gamma);
	vec3 outColor = pow(inColor.rgb, gammaVec3);

	return vec4(outColor, inColor.a);
}

/// Fetches a fragment of the specified texture at the specified texture
/// coordinates. The texture's fragment will be gamma corrected (or not)
/// depending on the gamma parameter.
/// sampler2D texture : The sampler containing the texture.
/// vec2 coord : The coordinates of the fragment on the texture.
/// float gamma : The gamma value. If the gamma value is equal to 1.0F, the
///			      image is not gamma corrected in anyway and its raw RGB values
///				  are returned instead.
/// return : The gamma corrected fragment color (alpha is returned raw).
vec4 texture2DSRGB(sampler2D texture, vec2 coord, float gamma) {
	vec4 texColor = texture2D(texture, coord);
	return applyGammaSRGB(texColor, gamma);
}

/// Fetches a fragment of the specified cubemap at the specified cube
/// coordinates. The cube's fragment will be gamma corrected (or not) depending
/// on the gamma parameter.
/// samplerCube cube : The sampler containing the cubemap.
/// vec3 coord : The coordinates of the fragment on the cubemap.
/// float gamma : The gamma value. If the gamma value is equal to 1.0F, the
///			      image is not gamma corrected in anyway and its raw RGB values
///				  are returned instead.
/// return : The gamma corrected fragment color (alpha is returned raw).
vec4 textureCubeSRGB(samplerCube cube, vec3 coord, float gamma) {
	vec4 texColor = texture(cube, coord);
	return applyGammaSRGB(texColor, gamma);
}