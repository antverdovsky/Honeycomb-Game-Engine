///
/// The material structure.
///
struct Material {
    vec3 diffuseColor;  // Diffuse color of the Material

    vec3 specularColor; // Color of the specular reflection
	float shininess;	// The shininess of the specular reflection

	float refIndexFrom;		  // The refractive index of the from material
	float refIndexTo;		  // The refractive index of the to material (this)
	float reflectionStrength; // The strength of the Reflection [0, 1] (TODO, clamp)

	sampler2D albedoTexture; // Texture under any light
};