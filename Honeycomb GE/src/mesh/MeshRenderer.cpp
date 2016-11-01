#include "..\..\include\mesh\MeshRenderer.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>

#include "..\..\include\file\FileIO.h"
#include "..\..\include\object\Transform.h"
#include "..\..\include\object\Object.h"
#include "..\..\include\render\Camera.h"

using Honeycomb::Graphics::Texture2D;
using Honeycomb::Object::Transform;
using Honeycomb::Render::Camera;
using Honeycomb::Shader::ShaderProgram;
using namespace Honeycomb::File;

namespace Honeycomb::Mesh {
	MeshRenderer::MeshRenderer(Mesh &mes, ShaderProgram &shad, Texture2D &tex)
			: Component("MeshRenderer"), mesh(mes), shader(shad), 
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