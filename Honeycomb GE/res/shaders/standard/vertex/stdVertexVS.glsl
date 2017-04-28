#ifndef STD_VERTEX_GLSL
#define STD_VERTEX_GLSL

///
/// Defines the layouts of all of the Vertex attributes used in all standard
/// Vertex Shaders.
///

layout (location = 0) in vec4 in_vs_position;
layout (location = 1) in vec4 in_vs_normal;
layout (location = 2) in vec4 in_vs_tangent;
layout (location = 3) in vec4 in_vs_texCoords0;

///
/// Standard Structure defining the vertex structure which is used as the 
/// input of all standard Vertex Shaders.
///

struct STD_VERTEX_IN {
	vec4 position;
	vec4 normal;
	vec4 tangent;
	vec2 texCoords0;
} vertexIn = STD_VERTEX_IN(
	in_vs_position,
	in_vs_normal, 
	in_vs_tangent,
	in_vs_texCoords0.xy);

///
/// Standard Structure defining the vertex structure whichc is used as the 
/// output of all standard Vertex Shaders.
///

out STD_VERTEX_OUT {
	vec3 position;
	vec3 normal;
	vec3 tangent;
	vec3 bitangent;
	
	vec2 texCoords0;

	mat3 tbnMatrix;
} vertexOut;

#endif