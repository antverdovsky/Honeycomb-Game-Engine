///
/// Standard Structure for the output of a Vertex Shader to a Fragment Shader.
///

out STD_VERTEX_OUT {
	vec3 position;
	vec3 normal;
	vec3 tangent;
	vec3 bitangent;
	
	vec2 texCoords0;

	mat3 tbnMatrix;
} vertexOut;