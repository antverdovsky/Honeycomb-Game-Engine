#pragma once
#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include "../GameComponent.h"
#include "../physics/Transform.h"
#include "../../../include/geometry/Mesh.h"
#include "../../../include/graphics/Material.h"
#include "../../../include/shader/ShaderProgram.h"

namespace Honeycomb { namespace Component { namespace Render {
	class MeshRenderer : public GameComponent {
	public:
		/// <summary>
		/// Creates a new Mesh Renderer component. The Mesh Renderer will have
		/// no mesh or material attached to it.
		/// </summary>
		MeshRenderer();

		/// <summary>
		/// Adds the specified Material to this Mesh Renderer.
		/// 
		/// An assertion makes sure that the material is not null.
		/// </summary>
		/// <param name="material">
		/// The Material to be added.
		/// </param>
		void addMaterial(const std::shared_ptr<Honeycomb::Graphics::Material> 
				&material);

		/// <summary>
		/// Adds the specified Mesh to this Mesh Renderer. 
		/// 
		/// An assertion makes sure that the mesh is not null.
		/// </summary>
		/// <param name="mesh">
		/// The Mesh to be added.
		/// </param>
		void addMesh(const std::shared_ptr<Honeycomb::Geometry::Mesh> &mesh);

		/// <summary>
		/// Clones this Mesh Renderer into a new Mesh Renderer. Each mesh and
		/// material of this Mesh Renderer will be re-added to the cloned
		/// Mesh Renderer.
		/// </summary>
		/// <returns>
		/// The unique pointer to the clone of this.
		/// </returns>
		std::unique_ptr<MeshRenderer> clone() const;

		/// <summary>
		/// Returns the Component ID integer representation of the Mesh
		/// Renderer.
		/// </summary>
		/// <returns>
		/// The Component ID of the Mesh Renderer Component.
		/// </returns>
		virtual GameComponentID getGameComponentID() const noexcept override;

		/// <summary>
		/// Returns the materials of this Mesh Renderer.
		/// </summary>
		/// <returns>
		/// The materials list, returned by reference.
		/// </returns>
		std::vector<std::shared_ptr<Honeycomb::Graphics::Material>>& 
				getMaterials();

		/// <summary>
		/// Returns the materials of this Mesh Renderer.
		/// </summary>
		/// <returns>
		/// The materials list, returned by constant reference.
		/// </returns>
		const std::vector<std::shared_ptr<Honeycomb::Graphics::Material>>& 
				getMaterials() const;

		/// <summary>
		/// Returns the meshes of this Mesh Renderer.
		/// </summary>
		/// <returns>
		/// The meshes list, returned by reference.
		/// </returns>
		std::vector<std::shared_ptr<Honeycomb::Geometry::Mesh>>& getMeshes();

		/// <summary>
		/// Returns the meshes of this Mesh Renderer.
		/// </summary>
		/// <returns>
		/// The meshes list, returned by constant reference.
		/// </returns>
		const std::vector<std::shared_ptr<Honeycomb::Geometry::Mesh>>& 
				getMeshes() const;

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
		/// 
		/// If there is only one mesh and one material attached, the mesh is
		/// rendered using that material.
		/// 
		/// If there are multiple meshes and one material attached, the meshes
		/// are rendered using that material.
		/// 
		/// If there are multiple meshes and multiple materials attached: if
		/// the number of meshes equals the number of materials, each mesh is
		/// rendered with its corresponding material; else a runtime assertion
		/// will be raised.
		/// </summary>
		/// <param name="shader">
		/// The Shader to be used when rendering the Mesh. The material data
		/// of the shader will be overwritten with the material data of this
		/// Mesh Renderer.
		/// </param>
		void onRender(Honeycomb::Shader::ShaderProgram &shader) override;

		/// <summary>
		/// Removes the specified Material from this Mesh Renderer. If the
		/// material is not attached to this Mesh Renderer, no further action
		/// is taken.
		/// </summary>
		/// <param name="material">
		/// The Material to be removed.
		/// </param>
		void removeMaterial(const 
				std::shared_ptr<Honeycomb::Graphics::Material> &material);

		/// <summary>
		/// Removes the specified Mesh from this Mesh Renderer. If the mesh is
		/// not attached to this Mesh Renderer, no further action is taken.
		/// </summary>
		/// <param name="mesh">
		/// The Mesh to be removed.
		/// </param>
		void removeMesh(const std::shared_ptr<Honeycomb::Geometry::Mesh> 
				&mesh);
	private:
		// The list of meshes and materials of this Mesh Renderer.
		std::vector<std::shared_ptr<Honeycomb::Geometry::Mesh>> meshes;
		std::vector<std::shared_ptr<Honeycomb::Graphics::Material>> materials;

		// Reference to the transform of the mesh
		Honeycomb::Component::Physics::Transform *transform;

		/// <summary>
		/// Clones this Mesh Renderer component.
		/// </summary>
		/// <returns>
		/// The new Mesh Renderer component.
		/// </returns>
		virtual MeshRenderer* cloneInternal() const override;
	};
} } }

#endif
