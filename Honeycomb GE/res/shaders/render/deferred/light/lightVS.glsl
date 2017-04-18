#version 410 core

#include <../../../standard/include/stdCamera.glsl>
#include <../../../standard/include/vertex/stdVertexAttrib.glsl>
#include <../../../standard/include/vertex/stdVertexOut.glsl>

uniform Camera camera;
uniform mat4 objTransform;

void main() {
    gl_Position = camera.projection * objTransform * in_vs_position;
    
    vertexOut.position = (objTransform * in_vs_position).xyz;
}