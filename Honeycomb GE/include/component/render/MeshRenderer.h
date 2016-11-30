#pragma once
#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include "..\GameComponent.h"
#include "..\physics\Transform.h"
#include "..\..\..\include\geometry\Mesh.h"
#include "..\..\..\include\graphics\Material.h"
#include "..\..\..\include\shader\ShaderProgram.h"

namespace Honeycomb::Component::Render {
	class MeshRenderer : public GameComponent {
	public:
		/// Creates a Mesh Renderer component given the specified mesh, shader
		/// and texture.
		/// Mesh *mesh : The mesh to be rendered.
		/// ShaderProgram *shad : The shader to be used when rendering.
		/// Material *mat : The material to be used when rendering.
		MeshRenderer(const Honeycomb::Graphics::Material &mat,
			const Honeycomb::Geometry::Mesh &mesh,
			Honeycomb::Shader::ShaderProgram &shad);

		/// Deletes this Mesh Renderer component.
		~MeshRenderer();

		/// Clones this Mesh Renderer into a new, dynamically allocated 
		/// Mesh Renderer. This function should be used instead of the copy 
		/// constructor to prevent object slicing. Note that the new Mesh
		/// Renderer will still reference the material, mesh and shader of this
		/// instance.
		/// return : The cloned Mesh Renderer.
		MeshRenderer* clone() const;

		/// Returns the pointer to the mesh of this Mesh Renderer.
		/// return : The mesh pointer.
		const Honeycomb::Geometry::Mesh& getMesh() const;

		/// Returns the pointer to the shader of this Mesh Renderer.
		/// return : The shader pointer.
		const Honeycomb::Shader::ShaderProgram& getShader() const;

		/// Returns the pointer to the material of this Mesh Renderer.
		/// return : The material pointer.
		const Honeycomb::Graphics::Material& getMaterial() const;

		/// Renders the mesh stored to the screen.
		void render();

		/// Sets the material of this Mesh Renderer.
		/// Material mat : The material.
		void setMaterial(const Honeycomb::Graphics::Material &mat);

		/// Sets the mesh of this Mesh Renderer.
		/// Mesh mes : The mesh.
		void setMesh(const Honeycomb::Geometry::Mesh &mes);

		/// Sets the shader of this Mesh Renderer.
		/// ShaderProgram shad : The shader.
		void setShader(Honeycomb::Shader::ShaderProgram &shad);
		
		/// Starts this Mesh Renderer instance.
		void start();
	private:
		const Honeycomb::Graphics::Material *material;
		const Honeycomb::Geometry::Mesh *mesh;
		Honeycomb::Shader::ShaderProgram *shader; // const? todo

		Honeycomb::Component::Physics::Transform *transform;
	};
}

#endif