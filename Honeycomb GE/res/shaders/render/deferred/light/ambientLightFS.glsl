#version 330 core

#include <../../../standard/include/stdMaterial.glsl>
#include <../../../standard/include/light/stdAmbientLight.glsl>

in vec3 out_vs_pos; // Take in the world position outputted by VS

uniform sampler2D gBufferDiffuse;

uniform AmbientLight ambientLight; // The Ambient Light
uniform Camera camera;

out vec4 fragColor;

void main() {
	vec2 screenCoord = vec2(gl_FragCoord.x / camera.width,
							gl_FragCoord.y / camera.height);

	vec3 dif = texture2D(gBufferDiffuse, screenCoord).xyz;

	fragColor = vec4(calculateAmbientLight(ambientLight) * dif, 1.0F);
}