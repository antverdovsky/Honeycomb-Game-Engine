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
	MeshRenderer::MeshRenderer() : GameComponent("MeshRenderer") {

	}

	MeshRenderer::MeshRenderer(Mesh *mes, ShaderProgram *shad, Material *mat)
			: GameComponent("MeshRenderer") {
		this->mesh = mes;
		this->shader = shad;
		this->material = mat;
	}

	MeshRenderer::~MeshRenderer() {

	}

	MeshRenderer* MeshRenderer::clone() {
		return new MeshRenderer(*this);
	}

	Mesh* MeshRenderer::getMesh() {
		return this->mesh;
	}

	ShaderProgram* MeshRenderer::getShader() {
		return this->shader;
	}

	Material* MeshRenderer::getMaterial() {
		return this->material;
	}

	void MeshRenderer::render() {
		// Bind the shader & texture and then draw the Mesh.
		Transform& objTrans = // TODO
			*(this->getAttached()->getComponentOfType<Transform>("Transform"));
		this->shader->setUniform_mat4("objTransform",
			objTrans.getTransformationMatrix());

		// Draw what you can (what isn't NULL).
		if (this->shader != nullptr) this->shader->bindShaderProgram();
		if (this->material != nullptr) this->material->use();
		if (this->mesh != nullptr) this->mesh->draw();
	}

	void MeshRenderer::setMaterial(Material *mat) {
		this->material = mat;
	}

	void MeshRenderer::setMesh(Mesh *mes) {
		this->mesh = mes;
	}

	void MeshRenderer::setShader(ShaderProgram *shad) {
		this->shader = shad;
	}

	void MeshRenderer::update() {

	}
}