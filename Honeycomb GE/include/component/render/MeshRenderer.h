#pragma once
#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

/// TODO: Maybe have the mesh renderer store an array of shader programs for
/// multirendering passes instead, though that will probably be more difficult
/// to understand.

#include "..\GameComponent.h"
#include "..\physics\Transform.h"
#include "..\..\..\include\geometry\Mesh.h"
#include "..\..\..\include\graphics\Material.h"
#include "..\..\..\include\shader\ShaderProgram.h"

namespace Honeycomb::Component::Render {
	class MeshRenderer : public GameComponent {
	public:
		/// Creates a Mesh Renderer component given the specified mesh and
		/// material.
		/// const Material &mat : The material to be used when rendering.
		/// const Mesh &mesh : The mesh to be rendered.
		MeshRenderer(const Honeycomb::Graphics::Material &mat,
			const Honeycomb::Geometry::Mesh &mesh);

		/// Deletes this Mesh Renderer component.
		~MeshRenderer();

		/// Clones this Mesh Renderer into a new, dynamically allocated 
		/// Mesh Renderer. This function should be used instead of the copy 
		/// constructor to prevent object slicing. Note that the new Mesh
		/// Renderer will still reference the material, mesh and shader of this
		/// instance.
		/// return : The cloned Mesh Renderer.
		MeshRenderer* clone() const;

		/// Returns the constant reference to the mesh of this Mesh Renderer.
		/// return : The constant reference to the mesh.
		const Honeycomb::Geometry::Mesh& getMesh() const;

		/// Returns the constant reference to the material of this Mesh 
		///	Renderer.
		/// return : The constant reference to the material.
		const Honeycomb::Graphics::Material& getMaterial() const;

		/// Renders the referenced mesh to the game screen using the referenced
		/// material and shader.
		/// ShaderProgram &shader : The shader to be used to render the mesh.
		void render(Honeycomb::Shader::ShaderProgram &shader);

		/// Sets the material of this Mesh Renderer.
		/// const Material &mat : The material.
		void setMaterial(const Honeycomb::Graphics::Material &mat);

		/// Sets the mesh of this Mesh Renderer.
		/// const Mesh &mes : The mesh.
		void setMesh(const Honeycomb::Geometry::Mesh &mes);

		/// Starts this Mesh Renderer instance.
		void start();
	private:
		// The referenced material and mesh.
		const Honeycomb::Graphics::Material *material;
		const Honeycomb::Geometry::Mesh *mesh;

		// Reference to the transform of the mesh
		Honeycomb::Component::Physics::Transform *transform;
	};
}

#endif