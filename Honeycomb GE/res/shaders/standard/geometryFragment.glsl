#version 330

struct Material {
    vec4 ambientColor; // Color under ambient light
    vec4 diffuseColor; // Color under diffuse light.
    vec4 specularColor; // Color under specular light
    float shininess; // Shininess for the Specular Spread
};

in vec2 ovs_TexturePosition; // Texture Position from Vertex Shader

uniform Material ufs_Material; // The material for this Fragment
uniform sampler2D ufs_Texture; // Texture Sampler [todo]

void main() {
    // Set the color of the fragment to the diffuse of material multiplied
    // by the texture color. 
    
    // TODO: The 0.25F is the ambient light, very temporary,
    // move this to a ambient light structure later!
	gl_FragColor = texture2D(ufs_Texture, ovs_TexturePosition) *
        ufs_Material.ambientColor * 0.25F;
}