#version 410 core

#include <../../../standard/include/stdCamera.glsl>

layout (location = 0) in vec3 in_vs_pos;

uniform Camera camera;
uniform mat4 objTransform;

out vec3 out_vs_pos;

void main() {
    gl_Position = camera.projection * objTransform * vec4(in_vs_pos, 1.0);
    
    out_vs_pos = (objTransform * vec4(in_vs_pos, 1.0)).xyz;
}