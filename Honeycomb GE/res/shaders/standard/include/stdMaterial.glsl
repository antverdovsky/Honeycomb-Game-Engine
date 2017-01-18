///
/// The material structure.
///
struct Material {
    vec4 ambientColor; // Color under ambient light
    vec4 diffuseColor; // Color under diffuse light
    vec4 specularColor; // Color under specular light (XYZ) & Shininess (W)

	sampler2D albedoTexture; // Texture under any light
};