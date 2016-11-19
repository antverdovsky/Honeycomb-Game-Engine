#include "..\..\include\geometry\Model.h"

#include <iostream>

#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"

#include "..\..\include\component\physics\Transform.h"
#include "..\..\include\component\render\MeshRenderer.h"
#include "..\..\include\geometry\Vertex.h"
#include "..\..\include\graphics\Material.h"
#include "..\..\include\math\Vector2f.h"
#include "..\..\include\math\Vector3f.h"
#include "..\..\include\shader\phong\PhongShader.h"

using Assimp::Importer;

using Honeycomb::Component::Physics::Transform;
using Honeycomb::Component::Render::MeshRenderer;
using Honeycomb::Graphics::Material;
using Honeycomb::Object::GameObject;
using Honeycomb::Math::Vector2f;
using Honeycomb::Math::Vector3f;
using Honeycomb::Shader::Phong::PhongShader;

namespace Honeycomb::Geometry {
	Model::Model(std::string path) {
		this->loadFromFile(path);
	}

	GameObject* Model::getGameObject() {
		return this->modelObject;
	}

	void Model::loadFromFile(std::string path) {
		Importer aImp = Importer(); // Initialize the Importer

		this->scene = aImp.ReadFile(path, aiProcess_Triangulate);

		if (this->scene == nullptr ||
				this->scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE ||
				this->scene->mRootNode == nullptr) {
			std::cout << "ASSIMP Error: " << aImp.GetErrorString() << std::endl; // todo

			return;
		}
		
		this->modelObject = // Initialize the Model Object
			new GameObject(this->scene->mRootNode->mName.C_Str());

		// Process the root node, passing in the model object so that all
		// recursively added children are parented to the model object.
		this->processAiNode(this->modelObject, this->scene->mRootNode, true);
	}

	/// TODO: a lot of things...
	///
	///
	void Model::processAiMesh(GameObject *obj, aiMesh *aMesh) {
		Mesh *mesh = new Mesh();

		std::vector<Vertex> vertices; // Vertices Data
		std::vector<int> indices; // Indices Data

		// Go through all the vertices of the Mesh
		for (int i = 0; i < aMesh->mNumVertices; i++) {
			// Get all of the normals, positions and UV coordinates for this
			// vertex.
			// TODO: Worry about the other 7 texture coordinates of the vertex?
			aiVector3D vertNorms = aMesh->mNormals[i];
			aiVector3D vertPos = aMesh->mVertices[i];
			aiVector3D vertUV = aMesh->HasTextureCoords(0) ? 
				aMesh->mTextureCoords[0][i] : // TODO?
				aiVector3D(0.0F, 0.0F, 0.0F);
			
			// Generate a Vertex using the fetched Vertex information
			Vertex vertex = Vertex(
				Vector3f(vertNorms.x, vertNorms.y, vertNorms.z),
				Vector3f(vertPos.x, vertPos.y, vertPos.z),
				Vector2f(vertUV.x, vertUV.y)
			);

			vertices.push_back(vertex); // Add the vertex to Mesh data
		}

		// Go through all the faces of the Mesh
		for (int i = 0; i < aMesh->mNumFaces; i++) {
			aiFace face = aMesh->mFaces[i]; // Get the face

			// Go through all the indices of the Face
			for (int j = 0; j < face.mNumIndices; j++) {
				int indx = face.mIndices[j]; // Get the index
				indices.push_back(indx); // Add the index to Mesh data
			}
		}

		// Send the vertex and index data of the Mesh to the Mesh
		mesh->addVertexData(&vertices[0], vertices.size(), 
			&indices[0], indices.size());

		// Create a Mesh Renderer component and add it to the Object
		MeshRenderer *meshRenderer = new MeshRenderer(*mesh,
			*PhongShader::getPhongShader(), /// TODO, Other shader support!!!
			*(new Material())); // TODO: materials... TODO: dynamic memory alloc...
		obj->addComponent(*meshRenderer);
	}

	void Model::processAiNode(GameObject *par, aiNode *aNode, bool isRoot) {
		// If this is a root object, then the node object is simply the passed
		// in parent object. Otherwise create a new object, since this will be
		// processing the child.
		GameObject *nodeObject = isRoot ?
			par :
			new GameObject(aNode->mName.C_Str());

		// Go through all the meshes of the node object, process their meshes,
		// specifying the node object, so that the meshes are added to the node
		// object.
		for (int i = 0; i < aNode->mNumMeshes; i++) {
			aiMesh *mesh = this->scene->mMeshes[aNode->mMeshes[i]];
			this->processAiMesh(nodeObject, mesh);
		}

		// Go through all the children of the node object, process the children
		// nodes, specify this node object as the new parent so that all the
		// children nodes are parented to this node object.
		for (int i = 0; i < aNode->mNumChildren; i++) {
			// TODO: Child Transformation
			aiNode *childNode = aNode->mChildren[i];
			this->processAiNode(nodeObject, childNode, false);
		}

		nodeObject->addComponent(*(new Transform()));

		// If this is not the root object, parent this node object to the 
		// original specified parent object.
		if (!isRoot) par->addChild(*nodeObject);
	}
}