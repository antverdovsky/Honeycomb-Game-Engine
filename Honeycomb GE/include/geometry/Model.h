#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "Mesh.h"
#include "..\object\GameObject.h"

struct aiMesh;
struct aiNode;
struct aiScene;

namespace Honeycomb::Geometry {
	class Model {
	public:
		/// Initializes a new Model from the specified file path.
		/// string path : The system file path to the model.
		Model(std::string path);

		/// Returns the game object... todo
		Honeycomb::Object::GameObject* getGameObject();
	private:
		/// Loads the model object from the specified file path.
		/// string path : The system path to the model.
		void loadFromFile(std::string path);

		/// Processes the specified ASSIMP node. The meshes of the node will be
		/// processed, and then the node's children will be processed
		/// recursively.
		/// GameObject *par : The object to which this node belongs. The node's
		///					  object will be parented to this object.
		/// aiNode *aNode : The ASSIMP node to be processed.
		/// bool isRoot : Boolean indicating whether this is the root object,
		///				  and if it is then the 
		void processAiNode(Honeycomb::Object::GameObject *par, aiNode *node, 
			bool isRoot);

		/// Processes the specified ASSIMP mesh.
		/// GameObject *obj : The object to which this mesh belongs. A mesh
		///				 	  renderer will be added to the object, so that it
		///				 	  may render the processed Mesh.
		/// aiMesh *aMesh : The ASSIMP mesh to be processed.
		void processAiMesh(Honeycomb::Object::GameObject *obj, aiMesh *mesh);

		const aiScene* scene; // The ASSIMP Scene for this model
		Honeycomb::Object::GameObject *modelObject; // The built model object
	};
}

#endif