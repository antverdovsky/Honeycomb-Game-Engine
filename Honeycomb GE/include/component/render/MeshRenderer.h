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
		/// Creates a Mesh Renderer component with no mesh, shader, or texture.
		MeshRenderer();

		/// Creates a Mesh Renderer component given the specified mesh, shader
		/// and texture.
		/// Mesh *mesh : The mesh to be rendered.
		/// ShaderProgram *shad : The shader to be used when rendering.
		/// Material *mat : The material to be used when rendering.
		MeshRenderer(Honeycomb::Geometry::Mesh *mesh, 
			Honeycomb::Shader::ShaderProgram *shad, 
			Honeycomb::Graphics::Material *mat);

		/// Deletes this Mesh Renderer component.
		~MeshRenderer();

		/// Clones this Mesh Renderer into a new, dynamically allocated 
		/// Mesh Renderer. This function should be used instead of the copy 
		/// constructor to prevent object slicing.
		/// return : The cloned Mesh Renderer.
		MeshRenderer* clone();

		/// Returns the pointer to the mesh of this Mesh Renderer.
		/// return : The mesh pointer.
		Honeycomb::Geometry::Mesh* getMesh();

		/// Returns the pointer to the shader of this Mesh Renderer.
		/// return : The shader pointer.
		Honeycomb::Shader::ShaderProgram* getShader();

		/// Returns the pointer to the material of this Mesh Renderer.
		/// return : The material pointer.
		Honeycomb::Graphics::Material* getMaterial();

		/// Renders the mesh stored to the screen.
		void render();

		/// Sets the pointer to the material of this Mesh Renderer.
		/// Material *mat : The new material of this Mesh Renderer.
		void setMaterial(Honeycomb::Graphics::Material *mat);

		/// Sets the pointer to the mesh of this Mesh Renderer.
		/// Mesh *mes : The new mesh of this Mesh Renderer.
		void setMesh(Honeycomb::Geometry::Mesh *mes);

		/// Sets the pointer to the shader of this Mesh Renderer.
		/// ShaderProgram *shad : The new shader of this Mesh Renderer.
		void setShader(Honeycomb::Shader::ShaderProgram *shad);

		/// Updates the mesh transformation for the Shader.
		void update();
	private:
		Honeycomb::Geometry::Mesh *mesh;
		Honeycomb::Shader::ShaderProgram *shader;
		Honeycomb::Graphics::Material *material;
	};
}

#endif