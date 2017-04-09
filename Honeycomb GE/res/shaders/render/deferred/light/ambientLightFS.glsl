#version 330 core

#include <../util/packing.glsl>
#include <../../../standard/include/stdMaterial.glsl>
#include <../../../standard/include/light/stdAmbientLight.glsl>

in vec3 out_vs_pos; // Take in the world position outputted by VS

uniform sampler2D gBufferAlbedoAmbientDiffuse;

uniform AmbientLight ambientLight; // The Ambient Light
uniform Camera camera;

out vec4 fragColor;

void main() {
	vec2 screenCoord = vec2(gl_FragCoord.x / camera.width,
							gl_FragCoord.y / camera.height);

	vec3 aad = texture2D(gBufferAlbedoAmbientDiffuse, screenCoord).xyz;
	vec3 albedo = unpackColor(aad.r);
	vec3 ambient = unpackColor(aad.g);
	vec3 diffuse = unpackColor(aad.b);

	fragColor = vec4(calculateAmbientLight(ambientLight) * diffuse, 1.0F);
}