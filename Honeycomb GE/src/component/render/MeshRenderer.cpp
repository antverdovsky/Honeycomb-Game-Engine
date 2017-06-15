#include "../../../include/component/render/MeshRenderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
	MeshRenderer::MeshRenderer(const Material &mat, const Mesh &mes) : 
			material(&mat), mesh(&mes) {

	}

	MeshRenderer::~MeshRenderer() {

	}

	MeshRenderer* MeshRenderer::clone() const {
		return new MeshRenderer(*this->material, *this->mesh);
	}

	const Mesh& MeshRenderer::getMesh() const {
		return *this->mesh;
	}

	const Material& MeshRenderer::getMaterial() const {
		return *this->material;
	}

	void MeshRenderer::render(ShaderProgram &shader) {
		shader.setUniform_mat4("objTransform",
			this->transform->getTransformationMatrix());

		// If the current Transform is negatively scaled on an odd number of
		// axes, then flip the winding order for the front face.
		Renderer::WindingOrder frontFace = Renderer::getRenderer()->frontFace;
		if (this->transform->isOddNegativelyScaled()) {
			if (frontFace == Renderer::WindingOrder::CLOCKWISE)
				glFrontFace(Renderer::WindingOrder::COUNTER_CLOCKWISE);
			else
				glFrontFace(Renderer::WindingOrder::CLOCKWISE);
		}

		// Render the mesh using the shader and material provided.
		if (this->material != nullptr) this->material->toShader(shader, "material"); // todo
		if (this->mesh != nullptr) this->mesh->render(shader);

		// Undo the winding order flip for the front face, if necessary.
		if (this->transform->isOddNegativelyScaled()) {
			glFrontFace(frontFace);
		}
	}

	void MeshRenderer::setMaterial(const Honeycomb::Graphics::Material *mat) {
		this->material = mat;
	}

	void MeshRenderer::setMaterial(const Honeycomb::Graphics::Material &mat) {
		this->material = &mat;
	}

	void MeshRenderer::setMesh(const Honeycomb::Geometry::Mesh &mes) {
		this->mesh = &mes;
	}

	void MeshRenderer::start() {
		this->transform = &this->getAttached()->getComponent<Transform>();
	}
} } }
