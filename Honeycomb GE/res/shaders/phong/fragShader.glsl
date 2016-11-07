//
// Sets the color of the fragment to the color indicated by the Texture.
//

#version 330 core

in vec2 out_vs_texCoord; // Take in texture coordinate outputted by VS
uniform sampler2D textureSampler; // Texture Sampler2D

uniform float ambientLightStrength; // The strength of the light
uniform vec3 ambientLightColor; // The color of the light

void main() {
    // Calculate the Ambient Light for this fragment
    vec3 ambientLight = ambientLightStrength * ambientLightColor;
    
    // TODO: OTHER LIGHTS...
    
    vec4 totalLight = vec4(ambientLight, 1); // + ... TODO

	// Set the color to the color provided by the Texture, mixed with the
    // lighting for this fragment.
	gl_FragColor = totalLight * texture2D(textureSampler, out_vs_texCoord);
}