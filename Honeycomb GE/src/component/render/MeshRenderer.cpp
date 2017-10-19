#include "../../../include/component/render/MeshRenderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cassert>
#include <iostream>

#include "../../../include/file/FileIO.h"
#include "../../../include/component/physics/Transform.h"
#include "../../../include/component/render/CameraController.h"
#include "../../../include/object/GameObject.h"
#include "../../../include/render/Renderer.h"

using Honeycomb::Component::Render::CameraController;
using Honeycomb::Component::Physics::Transform;
using Honeycomb::Geometry::Mesh;
using Honeycomb::Graphics::Material;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Render::Renderer;

using namespace Honeycomb::File;

namespace Honeycomb { namespace Component { namespace Render {
	MeshRenderer::MeshRenderer() {

	}

	void MeshRenderer::addMaterial(const std::shared_ptr<Material> &material) {
		assert(material != nullptr);

		this->materials.push_back(material);
	}

	void MeshRenderer::addMesh(const std::shared_ptr<Mesh> &mesh) {
		assert(mesh != nullptr);

		this->meshes.push_back(mesh);
	}

	std::unique_ptr<MeshRenderer> MeshRenderer::clone() const {
		return std::unique_ptr<MeshRenderer>(this->cloneInternal());
	}

	GameComponentID MeshRenderer::getGameComponentID() const noexcept {
		return GameComponent::getGameComponentTypeID<MeshRenderer>();
	}

	std::vector<std::shared_ptr<Material>>& MeshRenderer::getMaterials() {
		return this->materials;
	}

	const std::vector<std::shared_ptr<Material>>& MeshRenderer::getMaterials() 
			const {
		return this->materials;
	}

	std::vector<std::shared_ptr<Mesh>>& MeshRenderer::getMeshes() {
		return this->meshes;
	}

	const std::vector<std::shared_ptr<Mesh>>& MeshRenderer::getMeshes() const {
		return this->meshes;
	}

	void MeshRenderer::onAttach() {
		this->transform = &this->getAttached()->getComponent<Transform>();
	}

	void MeshRenderer::onDetach() {
		this->transform = nullptr;
	}

	void MeshRenderer::onRender(ShaderProgram &shader) {
		// Write the Transformation Matrix to the Shader
		shader.setUniform_mat4("objTransform",
			this->transform->getMatrixTransformation());

		// If the current Transform is negatively scaled on an odd number of
		// axes, then flip the winding order for the front face.
		Renderer::WindingOrder frontFace = Renderer::getRenderer()->frontFace;
		if (this->transform->isOddNegativelyScaled()) {
			if (frontFace == Renderer::WindingOrder::CLOCKWISE)
				glFrontFace(Renderer::WindingOrder::COUNTER_CLOCKWISE);
			else
				glFrontFace(Renderer::WindingOrder::CLOCKWISE);
		}

		// Assert meshes == materials if materials > 1
		if (this->materials.size() > 1)
			assert(this->meshes.size() == this->materials.size());

		// If meshes == materials == 1 -> Render the Mesh using the Material
		if (this->meshes.size() == 1 && this->materials.size() == 1) {
			this->materials[0]->toShader(shader, "material");
			this->meshes[0]->render(shader);
		} 
		// If meshes > 1, materials == 1 -> Render each Mesh using the Material
		else if (this->meshes.size() > 1 && this->materials.size() == 1) {
			this->materials[0]->toShader(shader, "material");
			for (auto &mesh : this->meshes) mesh->render(shader);
		}
		// If meshes == materials > 1 -> Render each Mesh using each Material
		else {
			for (std::size_t i = 0; i < this->meshes.size(); ++i) {
				this->materials[i]->toShader(shader, "material");
				this->meshes[i]->render(shader);
			}
		}

		// Undo the winding order flip for the front face, if necessary.
		if (this->transform->isOddNegativelyScaled()) {
			glFrontFace(frontFace);
		}
	}

	void MeshRenderer::removeMaterial(const std::shared_ptr<Material> 
			&material) {
		auto materialFind = std::find_if(
			this->materials.begin(), this->materials.end(),
			[&](auto &m) {
				return m == material;
		});
		if (materialFind == this->materials.end()) return;

		this->materials.erase(materialFind);
	}

	void MeshRenderer::removeMesh(const std::shared_ptr<Mesh> &mesh) {
		auto meshFind = std::find_if(
			this->meshes.begin(), this->meshes.end(),
			[&](auto &m) {
				return m == mesh;
		});
		if (meshFind == this->meshes.end()) return;

		this->meshes.erase(meshFind);
	}

	MeshRenderer* MeshRenderer::cloneInternal() const {
		MeshRenderer* mR = new MeshRenderer();

		for (auto &m : this->meshes) mR->addMesh(m);
		for (auto &m : this->materials) mR->addMaterial(m);

		return mR;
	}
} } }
