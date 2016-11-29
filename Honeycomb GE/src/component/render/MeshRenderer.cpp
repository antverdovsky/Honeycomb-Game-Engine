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
	MeshRenderer::MeshRenderer(const Material &mat, const Mesh &mes, 
			ShaderProgram &shad) 
			: GameComponent("MeshRenderer"), material(&mat), mesh(&mes), 
			  shader(&shad) {

	}

	MeshRenderer::~MeshRenderer() {

	}

	MeshRenderer* MeshRenderer::clone() {
		return new MeshRenderer(*this);
	}

	const Mesh& MeshRenderer::getMesh() const {
		return *this->mesh;
	}

	const ShaderProgram& MeshRenderer::getShader() const {
		return *this->shader;
	}

	const Material& MeshRenderer::getMaterial() const {
		return *this->material;
	}

	void MeshRenderer::render() {
		this->shader->setUniform_mat4("objTransform",
			this->transform->getTransformationMatrix());

		// Render the mesh using the shader and material provided.
		this->shader->bindShaderProgram();
		this->material->use();
		this->mesh->draw();
	}

	void MeshRenderer::setMaterial(const Honeycomb::Graphics::Material &mat) {
		this->material = &mat;
	}

	void MeshRenderer::setMesh(const Honeycomb::Geometry::Mesh &mes) {
		this->mesh = &mes;
	}

	void MeshRenderer::setShader(Honeycomb::Shader::ShaderProgram &shad) {
		this->shader = &shad;
	}

	void MeshRenderer::start() {
		this->transform = this->getAttached()->
			getComponentOfType<Transform>("Transform");
	}
}