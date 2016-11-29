#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "Mesh.h"
#include "..\object\GameObject.h"
#include "..\component\render\MeshRenderer.h"
#include "..\graphics\Material.h"
#include "..\graphics\Texture2D.h"

struct aiMaterial;
struct aiMesh;
struct aiNode;
struct aiScene;

namespace Honeycomb::Geometry {
	class Model {
	public:
		/// Deletes this model, and the materials / textures imported from it.
		~Model();

		/// Loads a model from the specified path and returns it. If the model
		/// has previously been loaded, it will be returned instead, to prevent.
		/// string path : The path to the model.
		static const Model& loadModel(std::string path);

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
		Honeycomb::Object::GameObject* getGameObjectClone() const;

		/// Gets the system path to the file from which the Model was loaded.
		/// return : The string containing the system path.
		const std::string& getPath() const;
	private:
		static std::vector<Model*> imports; // All imported models

		const aiScene* scene; // The ASSIMP Scene for this model
		std::string path; // The system path to the model
		Honeycomb::Object::GameObject *gameObject; // The built model object

		std::vector<Honeycomb::Graphics::Texture2D*> textures; // Textures
		std::vector<Honeycomb::Graphics::Material*> materials; // Materials

		/// Initializes a new Model from the specified file path.
		/// string path : The system file path to the model.
		Model(std::string path);

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