#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

namespace Honeycomb::Math { class Vector2f; }
namespace Honeycomb::Math { class Vector3f; }
namespace Honeycomb::Mesh { class Vertex; }

namespace Honeycomb::Mesh::Importer {
	class Model {
	public:
		/// Default Destructor.
		~Model();

		/// Gets a reference to the indicies of the model.
		/// return : The reference to the indicies.
		virtual std::vector<int>& getIndicies();

		/// Gets a reference to the normals of the model.
		/// return : The references to the normals.
		virtual std::vector<Honeycomb::Math::Vector3f>& getNormals();

		/// Gets a reference to the 2D texture coordinates of the model.
		/// return : The references to the coordinates.
		virtual std::vector<Honeycomb::Math::Vector2f>& getTextureCoords();

		/// Gets a reference to the verticies of the model.
		/// return : The references to the verticies.
		virtual std::vector<Honeycomb::Mesh::Vertex>& getVerticies();
	
		/// Loads in the model from the specified file.
		/// std::string : The file from which to load in the model.
		/// return : The loaded in model.
		virtual Model* loadModel(std::string file);
	protected:
		/// Initializes an Empty Model.
		Model();

		/// Creates a Model instance initialized to the specified indicies, 
		/// normals, texture coordinates and verticies.
		/// vector<int> indx : The indicies.
		/// vector<Vector3f> norms: The normals.
		/// vector<Vector2f> texCrds : The texture coordinates.
		/// vector<verts> verts : The verticies.
		Model(std::vector<int> indx, std::vector<Honeycomb::Math::Vector3f>
			norms, std::vector<Honeycomb::Math::Vector2f> texCrds,
			std::vector<Honeycomb::Mesh::Vertex> verts);
	private:
		std::vector<int> indicies;
		std::vector<Honeycomb::Math::Vector3f> normals;
		std::vector<Honeycomb::Math::Vector2f> textureCoords;
		std::vector<Honeycomb::Mesh::Vertex> verticies;
	};
}

#endif