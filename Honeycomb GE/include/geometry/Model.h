#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "Mesh.h"
#include "..\object\GameObject.h"
#include "..\component\render\MeshRenderer.h"

struct aiMaterial;
struct aiMesh;
struct aiNode;
struct aiScene;

namespace Honeycomb::Geometry {
	class Model {
	public:
		/// Initializes a new Model from the specified file path.
		/// string path : The system file path to the model.
		Model(std::string path);

		/// Returns the Game Object loaded in from the Model. This game object
		/// is directly linked to the Model and IS NOT independent of the
		/// Model. Modifying this object will result in the modification of all
		/// future clones of this Game Object.
		/// return : The loaded Game Object.
		Honeycomb::Object::GameObject* getGameObject();

		/// Returns a Clone of the loaded Game Object. The game object will be
		/// completely independent, with its own unique children and 
		/// components, and it does not depend on the Model in any way.
		/// return : A clone of the loaded Game Object.
		Honeycomb::Object::GameObject* getGameObjectClone();

		/// Gets the system path to the file from which the Model was loaded.
		/// return : The string containing the system path.
		std::string getPath();
	private:
		std::string path; // The system path to the model
		const aiScene* scene; // The ASSIMP Scene for this model
		Honeycomb::Object::GameObject *gameObject; // The built model object

		/// Loads the model object from the file path stored in this Model.
		void loadFromPath();

		/// Converts the ASSIMP Node into a Honeycomb GameObject, and returns
		/// the GameObject instance. Each child node of the ASSIMP node will
		/// also be converted into a GameObject, and parented to the returned
		/// instance, recursively. All Objects will be equipped with a
		/// Transform, and those which contain Mesh data will be equipped with
		/// a MeshRenderer component.
		/// aiNode *aNode : The ASSIMP node to be processed into a Honeycomb
		///					GameObject.
		/// return : The dynamically allocated Honeycomb GameObject instance,
		///			 containing the information extracted from the ASSIMP node.
		Honeycomb::Object::GameObject* processAiNode(aiNode *aNode);

		/// Converts the ASSIMP Material into a Honeycomb Material, and returns
		/// the Material instance.
		/// aiMaterial *aMat : The ASSIMP Material to be converted into a
		///					   Honeycomb Material.
		/// return : The dynamically allocated Honeycomb Material instance,
		///			 containing the information extracted from the ASSIMP 
		///			 Material.
		Honeycomb::Graphics::Material* processAiMeshMaterial(aiMaterial *aMat);

		/// Converts the ASSIMP Mesh into a Honeycomb Mesh, and returns the 
		/// Mesh instance.
		/// aiMesh *aMesh : The ASSIMP Mesh to be converted into a Honeycomb 
		///					Mesh.
		/// return : The dynamically allocated Honeycomb Mesh instance,
		///			 containing the information extracted from the ASSIMP 
		///			 Mesh.
		Honeycomb::Geometry::Mesh* processAiMeshGeometry(aiMesh *aMesh);
	};
}

#endif