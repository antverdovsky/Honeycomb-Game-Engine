#include "..\..\include\mesh\MeshRenderer.h"


#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>

#include "..\..\include\file\FileIO.h"

using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Graphics::Texture2D;
using namespace Honeycomb::File;

namespace Honeycomb::Mesh {
	MeshRenderer::MeshRenderer(Mesh &mesh, ShaderProgram &shad, Texture2D &tex)
			: Component("MeshRenderer") {
		this->mesh = &mesh;
		this->shader = &shad;
		this->texture = &tex;
	}

	MeshRenderer::~MeshRenderer() {

	}

	Mesh& MeshRenderer::getMesh() {
		return *this->mesh;
	}

	ShaderProgram& MeshRenderer::getShader() {
		return *this->shader;
	}

	Texture2D& MeshRenderer::getTexture() {
		return *this->texture;
	}

	void MeshRenderer::render() {
		// Bind the shader & texture and then draw the Mesh.
		this->shader->bindShaderProgram();
		this->texture->bind();
		this->mesh->draw();
		//this->texture.unbind();
		//this->shader.unbindShaderProgram(); Won't be able to write to uniforms then... TODO
	}
}