#version 410 core

#include <../../../standard/include/stdCamera.glsl>

layout (location = 0) in vec4 in_vs_pos;

uniform Camera camera;
uniform mat4 objTransform;

out vec3 out_vs_pos;

void main() {
    gl_Position = camera.projection * objTransform * in_vs_pos;
    
    out_vs_pos = (objTransform * in_vs_pos).xyz;
}