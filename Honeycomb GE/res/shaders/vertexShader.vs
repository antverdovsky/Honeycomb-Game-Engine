//
// Basic Vertex Shader.
//
// Takes in the transform and projection matricies to allow for the projection
// of game objects in the OpenGL world.
// 

#version 330 core

// Tells OpenGL to look for the position in the 0th index of the vertex
// attribute array (see Mesh.cpp).
layout(location = 0) in vec3 pos;

uniform mat4 objTransform = mat4(1.0); // Transform Matrix (pos, rot, scl)

uniform mat4 camProjection = mat4(1.0); // Projection Matrix (camera)
uniform mat4 camOrientation = mat4(1.0); // Orientation Matrix (camera)
uniform mat4 camTranslation = mat4(1.0); // Translation Matrix (camera)

void main() {
    // The position of each vertex equals to the transformation matrix
    // mutliplied with the vector representing the original position.
    gl_Position = camProjection * camOrientation * camTranslation * 
		objTransform * vec4(pos, 1.0);
}