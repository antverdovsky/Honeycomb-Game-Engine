#version 330 core

#include <../../../../util/packing.glsl>
#include <../../../../standard/structs/stdMaterial.glsl>
#include <../../../../standard/light/blinn-phong/blinnPhongAmbient.glsl>

in vec3 out_vs_pos; // Take in the world position outputted by VS

uniform sampler2D gBufferMaterial;

uniform AmbientLight ambientLight; // The Ambient Light
uniform Camera camera;

out vec4 fragColor;

void main() {
	vec2 screenCoord = vec2(gl_FragCoord.x / camera.width,
							gl_FragCoord.y / camera.height);

	vec4 mat = texture2D(gBufferMaterial, screenCoord);
	vec3 ambient = unpackRGB(mat.g);

    fragColor = vec4(calculateAmbientLight(ambientLight) * ambient, 1.0F);
}