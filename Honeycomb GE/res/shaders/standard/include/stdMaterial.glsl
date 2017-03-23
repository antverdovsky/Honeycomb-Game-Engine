///
/// The material structure.
///
struct Material {
    vec3 diffuseColor;			// Diffuse color of the Material

    vec3 specularColor;			// Color of the specular reflection
	float shininess;			// The shininess of the specular reflection

	float refractiveIndex;		// Index of refraction
	float reflectionStrength;	// The strength of the Reflection [0, 1]

	sampler2D diffuseTexture;	// Texture under diffuse light
	vec2 diffuseTextureTiling;	// Tiling of the albedo texture on X, Y axes
	vec2 diffuseTextureOffset;  // Offset of the albedo texture on X, Y axes
};