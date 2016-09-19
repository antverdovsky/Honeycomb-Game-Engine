//
// Test Fragment Shader 1
//
// Sets the color of each fragment to red (R: 1, G: 0, B: 0).
// 

#version 330 core

out vec3 color; // The output color

void main() {
    color = vec3(1, 0, 0); // Set the color to Red.
}