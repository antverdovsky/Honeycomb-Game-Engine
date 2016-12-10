#include "..\..\include\geometry\Model.h"

#include <iostream>

#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"

#include "..\..\include\component\physics\Transform.h"
#include "..\..\include\component\render\MeshRenderer.h"
#include "..\..\include\debug\Logger.h"
#include "..\..\include\geometry\Vertex.h"
#include "..\..\include\graphics\Material.h"
#include "..\..\include\graphics\Texture2D.h"
#include "..\..\include\math\Vector2f.h"
#include "..\..\include\math\Vector3f.h"
#include "..\..\include\math\Vector4f.h"
#include "..\..\include\shader\phong\PhongShader.h"

using Assimp::Importer;

using Honeycomb::Component::Physics::Transform;
using Honeycomb::Component::Render::MeshRenderer;
using Honeycomb::Debug::Logger;
using Honeycomb::Graphics::Material;
using Honeycomb::Graphics::Texture2D;
using Honeycomb::Object::GameObject;
using Honeycomb::Math::Vector2f;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector4f;
using Honeycomb::Shader::Phong::PhongShader;

namespace Honeycomb::Geometry {
	std::vector<Model*> Model::imports = std::vector<Model*>();

	Model::~Model() {
		for (int i = 0; i < this->textures.size(); i++)
			delete this->textures.at(i);
		for (int i = 0; i < this->materials.size(); i++)
			delete this->materials.at(i);
		for (int i = 0; i < this->meshes.size(); i++)
			delete this->meshes.at(i);
	}

	const Model& Model::loadModel(const std::string &path) {
		for (int i = 0; i < imports.size(); i++)
			if (imports.at(i)->path == path)
				return *imports.at(i);

		return *(new Model(path));
	}

	GameObject* Model::getGameObject() {
		return this->gameObject;
	}

	GameObject* Model::getGameObjectClone() const {
		return this->gameObject->clone();
	}

	const std::string& Model::getPath() const {
		return this->path;
	}

	Model::Model(const std::string &path) {
		this->path = path;
		this->loadFromPath();

		this->imports.push_back(this);
	}

	void Model::loadFromPath() {
		// Import the Scene from ASSIMP and Check for Errors.
		Importer aImp = Importer();
		this->scene = aImp.ReadFile(path, aiProcess_Triangulate |
			aiProcess_GenNormals);
		if (this->scene == nullptr ||
			this->scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE ||
			this->scene->mRootNode == nullptr) {

			Logger::getLogger().logError(__FUNCTION__, __LINE__,
				aImp.GetErrorString());

			return;
		}

		// Initialize the Model Object from the Scene Root node
		this->gameObject = this->processAiNode(this->scene->mRootNode);
	}

	Material* Model::processAiMeshMaterial(aiMaterial* aMat) {
		aiString matName; // Name of the Material
		const Texture2D *texture = nullptr; // Albedo Texture of the Material
		aiColor3D matAmbient; // Ambient Property of the Material
		aiColor3D matDiffuse; // Diffuse Property of the Material
		aiColor3D matSpecular; // Specular Property of the Material
		float matShininess; // Shininess Property of the Material

		// Retrieve all of the Material properties from ASSIMP
		aMat->Get(AI_MATKEY_NAME, matName);
		aMat->Get(AI_MATKEY_COLOR_AMBIENT, matAmbient);
		aMat->Get(AI_MATKEY_COLOR_DIFFUSE, matDiffuse);
		aMat->Get(AI_MATKEY_COLOR_SPECULAR, matSpecular);
		aMat->Get(AI_MATKEY_SHININESS, matShininess);

		if (aMat->GetTextureCount(aiTextureType_DIFFUSE)) {
			///
			/// TODO: SUPPORT FOR MORE TEXTURES.
			/// [will need to change the material class first]
			aiString dir;
			aMat->GetTexture(aiTextureType_DIFFUSE, 0, &dir);

			texture = new Texture2D(dir.C_Str());
		}
		else {
			texture = &Texture2D::getNonTexture();
		}

		// Build the Material and return it [TODO, use material name not sub!]
		Material *mat = new Material("ufs_Material", *texture,
			Vector4f(matAmbient.r, matAmbient.g, matAmbient.b, 1.0F),
			Vector4f(matDiffuse.r, matDiffuse.g, matDiffuse.b, 1.0F),
			Vector4f(matSpecular.r, matSpecular.g, matSpecular.b, 1.0F),
			matShininess);

		// Save the texture and material
		this->textures.push_back(texture);
		this->materials.push_back(mat);

		return mat;
	}

	Honeycomb::Geometry::Mesh* Model::processAiMeshGeometry(aiMesh *aMesh) {
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
				aMesh->mTextureCoords[0][i] : // TODO: Multiple Texture Support
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

		// Create a new Honeycomb Mesh with the fetched vertex and index data.
		Mesh *mes = new Mesh(&vertices[0], vertices.size(),
			&indices[0], indices.size());
		this->meshes.push_back(mes);

		return mes;
	}

	GameObject* Model::processAiNode(aiNode *aNode) {
		// Create the GameObject representing this node, and give it a
		// Transform, since all Objects get one. (DO NOT parent the object to
		// root, or else it will become an instantiated Game Object once the
		// game starts).
		GameObject* object = new GameObject(aNode->mName.C_Str());
		Transform* transf = new Transform();
		object->addComponent(*transf); // TODO: Child Transformation

		// Process all of the Meshes of the Object
		for (int i = 0; i < aNode->mNumMeshes; i++) {
			// Convert the ASSIMP Mesh Geometry into Honeycomb Mesh Geometry
			aiMesh *aMesh = this->scene->mMeshes[aNode->mMeshes[i]];
			Mesh *mesh = this->processAiMeshGeometry(aMesh);

			// Convert the ASSIMP Mesh Material into Honeycomb Mesh Material
			aiMaterial *aMat;
			Material *mat;
			if (aMesh->mMaterialIndex >= 0) { // Get Material, if it exists
				aMat = this->scene->mMaterials[aMesh->mMaterialIndex];
				mat = this->processAiMeshMaterial(aMat);
			}
			else { // Otherwise, create a default Material
				mat = new Material();
			}

			// Create a Mesh Renderer with the mesh and material extracted.
			// TODO: Shader???
			MeshRenderer *meshRen = new MeshRenderer(*mat, *mesh);
			object->addComponent(*meshRen);
		}

		// Process all of the Children of the Object
		for (int i = 0; i < aNode->mNumChildren; i++) {
			// Convert each child into a new Game Object.
			aiNode *childNode = aNode->mChildren[i];
			GameObject *childObj = this->processAiNode(childNode);

			// Add each fetched child as a child to this Game Object.
			object->addChild(*childObj);
		}

		return object; // Return the instantiated object
	}
}