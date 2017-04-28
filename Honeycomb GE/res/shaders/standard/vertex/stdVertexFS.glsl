#ifndef STD_VERTEX_GLSL
#define STD_VERTEX_GLSL

///
/// Standard Structure defining the vertex structure which is used as input 
/// inside all standard Fragment Shaders.
///

in STD_VERTEX_OUT {
	vec3 position;
	vec3 normal;
	vec3 tangent;
	vec3 bitangent;
	
	vec2 texCoords0;

	mat3 tbnMatrix;
} vertexIn;

#endif