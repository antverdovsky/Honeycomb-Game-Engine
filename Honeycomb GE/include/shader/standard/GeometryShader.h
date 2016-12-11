#pragma once
#ifndef DEFERRED_GEOMETRY_SHADER
#define DEFERRED_GEOMETRY_SHADER

#include "..\ShaderProgram.h"
#include "..\..\math\Matrix4f.h"

namespace Honeycomb::Shader::Standard {
	class GeometryShader : public ShaderProgram {
	public:
		/// Returns the singleton instance of this Deferred Geometry Shader
		/// class.
		/// return : The pointer to the singleton instance.
		static GeometryShader* getGeometryShader();

		/// Sets the projection matrix of the Deferred Rendering Geometry
		/// Shader to the specified matrix.
		/// const Matrix4f &proj : The projection matrix.
		void setProjection(const Honeycomb::Math::Matrix4f &proj);

		/// Sets the transformation matrix of the Deferred Rendering Geometry
		/// Shader to the specified matrix.
		/// const Matrix4f &trans : The transformation matrix.
		void setTransformation(const Honeycomb::Math::Matrix4f &trans);
	private:
		static GeometryShader *geometryShader; // Singleton instance
		
		// Locations of the vertex & fragment shader files.
		const static std::string FRAG_FILE_LOC;
		const static std::string VERT_FILE_LOC;

		/// Initializes a new instance of the Deferred Rendering Geometry 
		/// Shader.
		GeometryShader();

		/// Deletes this instance of the Deferred Rendering Geometry Shader.
		~GeometryShader();
	};
}

#endif