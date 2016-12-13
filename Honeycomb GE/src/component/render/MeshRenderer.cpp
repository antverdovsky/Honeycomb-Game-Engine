#include "..\..\..\include\component\render\MeshRenderer.h";

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>

#include "..\..\..\include\file\FileIO.h"
#include "..\..\..\include\component\physics\Transform.h"
#include "..\..\..\include\component\render\CameraController.h"
#include "..\..\..\include\object\GameObject.h"

using Honeycomb::Component::Render::CameraController;
using Honeycomb::Component::Physics::Transform;
using Honeycomb::Geometry::Mesh;
using Honeycomb::Graphics::Material;
using Honeycomb::Shader::ShaderProgram;

using namespace Honeycomb::File;

namespace Honeycomb::Component::Render {
	MeshRenderer::MeshRenderer(const Material &mat, const Mesh &mes) : 
			GameComponent("MeshRenderer"), material(&mat), mesh(&mes) {

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

		// Render the mesh using the shader and material provided.
		if (this->material != nullptr) this->material->use(shader);
		if (this->mesh != nullptr) this->mesh->draw(shader);
	}

	void MeshRenderer::setMaterial(const Honeycomb::Graphics::Material &mat) {
		this->material = &mat;
	}

	void MeshRenderer::setMesh(const Honeycomb::Geometry::Mesh &mes) {
		this->mesh = &mes;
	}

	void MeshRenderer::start() {
		this->transform = this->getAttached()->
			getComponentOfType<Transform>("Transform");
	}
}