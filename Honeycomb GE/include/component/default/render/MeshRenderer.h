#pragma once
#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include "..\..\..\..\include\geometry\Mesh.h"
#include "..\..\..\..\include\graphics\Texture2D.h"
#include "..\..\..\..\include\component\GameComponent.h"
#include "..\..\..\..\include\shader\ShaderProgram.h"

namespace Honeycomb::Geometry { class Mesh; }
namespace Honeycomb::Shader { class ShaderProgram; }
namespace Honeycomb::Graphics { class Texture2D; }

namespace Honeycomb::Component::Default::Render {
	class MeshRenderer : public GameComponent {
	public:
		/// Creates a Mesh Renderer component given the specified mesh, shader
		/// and texture.
		MeshRenderer(Honeycomb::Geometry::Mesh &mesh, 
			Honeycomb::Shader::ShaderProgram &shad, 
			Honeycomb::Graphics::Texture2D &tex);

		/// Deletes this Mesh Renderer component.
		~MeshRenderer();

		/// Returns the reference to the mesh of this Mesh Renderer.
		/// return : The mesh reference.
		Honeycomb::Geometry::Mesh& getMesh();

		/// Returns the reference to the shader of this Mesh Renderer.
		/// return : The shader reference.
		Honeycomb::Shader::ShaderProgram& getShader();

		/// Returns the reference to the texture of this Mesh Renderer.
		/// return : The texture reference.
		Honeycomb::Graphics::Texture2D& getTexture();

		/// Renders the mesh stored to the screen.
		void render();

		/// Updates the mesh transformation for the Shader.
		void update();
	private:
		// All objects are declared with pointers, for lazy initialization.
		Honeycomb::Geometry::Mesh mesh;
		Honeycomb::Shader::ShaderProgram shader;
		Honeycomb::Graphics::Texture2D texture;
	};
}

#endif