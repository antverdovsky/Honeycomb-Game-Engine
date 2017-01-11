#version 330 core

#include <..\..\standard\include\stdMaterial.glsl>
#include <..\..\standard\include\light\stdPointLight.glsl>

in vec2 out_vs_texCoord; // Take in texture coordinate outputted by VS
in vec3 out_vs_norm; // Take in the normal outputted by VS
in vec3 out_vs_pos; // Take in the world position outputted by VS

uniform PointLight pointLight; // The point light
uniform Material material; // The material
uniform Camera camera;

uniform sampler2D gBufferPosition;
uniform sampler2D gBufferDiffuse;
uniform sampler2D gBufferNormal;

out vec4 fragColor;

void main() {
    vec2 screenCoord = vec2(gl_FragCoord.x / camera.width,
							gl_FragCoord.y / camera.height);
    
    vec3 pos = texture2D(gBufferPosition, screenCoord).xyz;
    vec3 dif = texture2D(gBufferDiffuse, screenCoord).xyz;
    vec3 norm = texture2D(gBufferNormal, screenCoord).xyz;
  fragColor = calculatePointLight(pointLight, camera, pos, norm, 
        material.shininess);
    //fragColor = texture2D(gBufferPosition, screenCoord);
    
}