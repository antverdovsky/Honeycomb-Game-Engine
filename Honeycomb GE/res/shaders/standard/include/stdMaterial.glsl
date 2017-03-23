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
    vec3 diffuseColor;			// Diffuse color of the Material
	Texture2D diffuseTexture;	// Diffuse texture of the Material

    vec3 specularColor;			// Color of the specular reflection
	Texture2D specularTexture;	// Specular texture of the Material
	float shininess;			// The shininess of the specular reflection

	float refractiveIndex;		// Index of refraction
	float reflectionStrength;	// The strength of the Reflection [0, 1]
};