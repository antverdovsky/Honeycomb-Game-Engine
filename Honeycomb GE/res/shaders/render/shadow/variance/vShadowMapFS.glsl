#version 330 core

out vec4 color;

void main() {
	color = vec4(gl_FragCoord.z, gl_FragCoord.z * gl_FragCoord.z, 0.0F, 0.0F);
}