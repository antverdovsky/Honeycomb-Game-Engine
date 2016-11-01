#include "..\..\..\..\include\component\default\render\MeshRenderer.h";

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>

#include "..\..\..\..\include\file\FileIO.h"
#include "..\..\..\..\include\component\default\physics\Transform.h"
#include "..\..\..\..\include\component\default\render\CameraController.h"
#include "..\..\..\..\include\object\GameObject.h"

using Honeycomb::Component::Default::Render::CameraController;
using Honeycomb::Component::Default::Physics::Transform;
using Honeycomb::Geometry::Mesh;
using Honeycomb::Graphics::Texture2D;
using Honeycomb::Shader::ShaderProgram;
using namespace Honeycomb::File;

namespace Honeycomb::Component::Default::Render {
	MeshRenderer::MeshRenderer(Mesh &mes, ShaderProgram &shad, Texture2D &tex)
			: GameComponent("MeshRenderer"), mesh(mes), shader(shad),
			  texture(tex) {

	}

	MeshRenderer::~MeshRenderer() {

	}

	Mesh& MeshRenderer::getMesh() {
		return this->mesh;
	}

	ShaderProgram& MeshRenderer::getShader() {
		return this->shader;
	}

	Texture2D& MeshRenderer::getTexture() {
		return this->texture;
	}

	void MeshRenderer::render() {
		// Bind the shader & texture and then draw the Mesh.
		Transform& objTrans = // TODO TODO TODO
			*(this->getAttached()->getComponentOfType<Transform>("Transform"));
		this->shader.setUniform_mat4("objTransform",
			objTrans.getTransformationMatrix());

		this->shader.bindShaderProgram();
		this->texture.bind();
		this->mesh.draw();
		this->texture.unbind();
		this->shader.unbindShaderProgram();
	}

	void MeshRenderer::update() {

	}
}