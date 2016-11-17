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
	MeshRenderer::MeshRenderer(Mesh &mes, ShaderProgram &shad, Material &mat)
			: GameComponent("MeshRenderer"), mesh(mes), shader(shad),
			  material(mat) {

	}

	MeshRenderer::~MeshRenderer() {

	}

	Mesh& MeshRenderer::getMesh() {
		return this->mesh;
	}

	ShaderProgram& MeshRenderer::getShader() {
		return this->shader;
	}

	Material& MeshRenderer::getMaterial() {
		return this->material;
	}

	void MeshRenderer::render() {
		// Bind the shader & texture and then draw the Mesh.
		Transform& objTrans = // TODO
			*(this->getAttached()->getComponentOfType<Transform>("Transform"));
		this->shader.setUniform_mat4("objTransform",
			objTrans.getTransformationMatrix());

		this->shader.bindShaderProgram();
		this->material.use();
		this->mesh.draw();
	}

	void MeshRenderer::update() {

	}
}