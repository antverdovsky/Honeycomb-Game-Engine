#version 410 core

#include <../../../standard/structs/stdCamera.glsl>
#include <../../../standard/vertex/stdVertexVS.glsl>

uniform Camera camera;
uniform mat4 objTransform;

void main() {
    gl_Position = camera.projection * objTransform * vertexIn.position;
    
    vertexOut.position = (objTransform * vertexIn.position).xyz;
}