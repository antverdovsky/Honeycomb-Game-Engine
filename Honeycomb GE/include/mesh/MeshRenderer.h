#pragma once

#include "Mesh.h"
#include "..\graphics\Texture2D.h"
#include "..\object\Component.h"
#include "..\shader\ShaderProgram.h"

namespace Honeycomb::Mesh {
	class MeshRenderer : public Honeycomb::Object::Component {
	public:
		/// Creates a Mesh Renderer component given the specified mesh, shader
		/// and texture.
		MeshRenderer(Mesh mesh, Honeycomb::Shader::ShaderProgram shad, 
			Honeycomb::Graphics::Texture2D *tex);

		/// Deletes this Mesh Renderer component.
		~MeshRenderer();

		/// Returns the reference to the shader of this Mesh Renderer.
		/// return : The shader reference.
		Honeycomb::Shader::ShaderProgram& getShader();

		/// Returns the reference to the texture of this Mesh Renderer.
		/// return : The texture reference.
		Honeycomb::Graphics::Texture2D* getTexture();

		/// Renders the mesh stored to the screen.
		void render();
	private:
		Mesh mesh;
		Honeycomb::Shader::ShaderProgram shader;
		Honeycomb::Graphics::Texture2D *texture; // TODO : Should not be ptr!!
	};
}