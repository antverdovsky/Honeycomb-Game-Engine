///
/// Standard Structure for the input of a Fragment Shader from a Vertex 
/// Shader.
///

in STD_VERTEX_OUT {
	vec3 position;
	vec3 normal;
	vec3 tangent;
	vec3 bitangent;
	
	vec2 texCoords0;

	mat3 tbnMatrix;
} vertexIn;