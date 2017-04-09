#version 330 core

#include <../util/packing.glsl>
#include <../../../standard/include/stdMaterial.glsl>
#include <../../../standard/include/light/stdPointLight.glsl>

in vec3 out_vs_pos; // Take in the world position outputted by VS

uniform PointLight pointLight; // The point light
uniform Camera camera;

uniform sampler2D gBufferPosition;
uniform sampler2D gBufferAlbedoAmbientDiffuse;
uniform sampler2D gBufferNormal;
uniform sampler2D gBufferSpecular;

out vec4 fragColor;

void main() {
    vec2 screenCoord = vec2(gl_FragCoord.x / camera.width,
							gl_FragCoord.y / camera.height);
    
    vec3 pos = texture2D(gBufferPosition, screenCoord).xyz;
    vec3 norm = normalize(texture2D(gBufferNormal, screenCoord).xyz);
	vec3 spec = texture2D(gBufferSpecular, screenCoord).xyz;
	float shine = texture2D(gBufferSpecular, screenCoord).w;

	vec3 aad = texture2D(gBufferAlbedoAmbientDiffuse, screenCoord).xyz;
	vec3 albedo = unpackColor(aad.r);
	vec3 ambient = unpackColor(aad.g);
	vec3 diffuse = unpackColor(aad.b);

	fragColor = vec4(calculatePointLight(pointLight, camera, pos, norm, shine,
        spec, diffuse), 1.0F);
}