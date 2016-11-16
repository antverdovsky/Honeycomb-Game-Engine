#pragma once
#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include "..\GameComponent.h"
#include "..\..\..\include\geometry\Mesh.h"
#include "..\..\..\include\graphics\Material.h"
#include "..\..\..\include\shader\ShaderProgram.h"

namespace Honeycomb::Component::Render {
	class MeshRenderer : public GameComponent {
	public:
		/// Creates a Mesh Renderer component given the specified mesh, shader
		/// and texture.
		MeshRenderer(Honeycomb::Geometry::Mesh &mesh, 
			Honeycomb::Shader::ShaderProgram &shad, 
			Honeycomb::Graphics::Material &mat);

		/// Deletes this Mesh Renderer component.
		~MeshRenderer();

		/// Returns the reference to the mesh of this Mesh Renderer.
		/// return : The mesh reference.
		Honeycomb::Geometry::Mesh& getMesh();

		/// Returns the reference to the shader of this Mesh Renderer.
		/// return : The shader reference.
		Honeycomb::Shader::ShaderProgram& getShader();

		/// Returns the reference to the material of this Mesh Renderer.
		/// return : The material reference.
		Honeycomb::Graphics::Material& getMaterial();

		/// Renders the mesh stored to the screen.
		void render();

		/// Updates the mesh transformation for the Shader.
		void update();
	private:
		Honeycomb::Geometry::Mesh mesh;
		Honeycomb::Shader::ShaderProgram shader;
		Honeycomb::Graphics::Material material;

		/// Sends the information from the material to the Shader.
		void useMaterial();
	};
}

#endif