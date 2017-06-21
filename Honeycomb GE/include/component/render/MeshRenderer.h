#pragma once
#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

/// TODO: Maybe have the mesh renderer store an array of shader programs for
/// multirendering passes instead, though that will probably be more difficult
/// to understand.

#include "../GameComponent.h"
#include "../physics/Transform.h"
#include "../../../include/geometry/Mesh.h"
#include "../../../include/graphics/Material.h"
#include "../../../include/shader/ShaderProgram.h"

namespace Honeycomb { namespace Component { namespace Render {
	class MeshRenderer : public GameComponent {
	public:
		/// Creates a Mesh Renderer component given the specified mesh and
		/// material.
		/// const Material &mat : The material to be used when rendering.
		/// const Mesh &mesh : The mesh to be rendered.
		MeshRenderer(const Honeycomb::Graphics::Material &mat,
			const Honeycomb::Geometry::Mesh &mesh);

		/// Deletes this Mesh Renderer component.
		~MeshRenderer() override;

		/// Clones this Mesh Renderer into a new, dynamically allocated 
		/// Mesh Renderer. This function should be used instead of the copy 
		/// constructor to prevent object slicing. Note that the new Mesh
		/// Renderer will still reference the material, mesh and shader of this
		/// instance.
		/// return : The cloned Mesh Renderer.
		std::unique_ptr<MeshRenderer> clone() const;

		/// <summary>
		/// Returns the Component ID integer representation of the Mesh
		/// Renderer.
		/// </summary>
		/// <returns>
		/// The Component ID of the Mesh Renderer Component.
		/// </returns>
		virtual GameComponentID getGameComponentID() const noexcept override;

		/// Returns the constant reference to the mesh of this Mesh Renderer.
		/// return : The constant reference to the mesh.
		const Honeycomb::Geometry::Mesh& getMesh() const;

		/// Returns the constant reference to the material of this Mesh 
		///	Renderer.
		/// return : The constant reference to the material.
		const Honeycomb::Graphics::Material& getMaterial() const;

		/// <summary>
		/// When attached, the Mesh Renderer gets a reference to the transform
		/// to which this is attached to.
		/// </summary>
		void onAttach() override;

		/// <summary>
		/// When detached, the Mesh Renderer loses a reference to the transform
		/// to which it was attached to.
		/// </summary>
		void onDetach() override;

		/// <summary>
		/// Renders the Mesh using the specified Shader.
		/// </summary>
		/// <param name="shader">
		/// The Shader to be used when rendering the Mesh.
		/// </param>
		void onRender(Honeycomb::Shader::ShaderProgram &shader) override;

		/// Sets the material of this Mesh Renderer.
		/// const Material *mat : The material.
		void setMaterial(const Honeycomb::Graphics::Material *mat);

		/// Sets the material of this Mesh Renderer.
		/// const Material &mat : The material.
		void setMaterial(const Honeycomb::Graphics::Material &mat);

		/// Sets the mesh of this Mesh Renderer.
		/// const Mesh &mes : The mesh.
		void setMesh(const Honeycomb::Geometry::Mesh &mes);
	private:
		// The referenced material and mesh.
		const Honeycomb::Graphics::Material *material;
		const Honeycomb::Geometry::Mesh *mesh;

		// Reference to the transform of the mesh
		Honeycomb::Component::Physics::Transform *transform;

		virtual MeshRenderer* cloneInternal() const override;
	};
} } }

#endif
