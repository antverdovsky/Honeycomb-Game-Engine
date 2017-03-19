///
/// The material structure.
///
struct Material {
    vec4 ambientColor; // Color under ambient light
    vec4 diffuseColor; // Color under diffuse light
    vec4 specularColor; // Color under specular light (XYZ) & Shininess (W)

	float refIndexFrom; // The refractive index from which a light ray goes
	float refIndexTo;   // The refractive index to which a light ray goes
	float reflectionStrength; // The strength of the Reflection [0, 1] (TODO, clamp)

	sampler2D albedoTexture; // Texture under any light
};