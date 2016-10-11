#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

namespace Honeycomb::Math { class Vector2f; }
namespace Honeycomb::Math { class Vector3f; }

namespace Honeycomb::Mesh::Importer {
	class Model {
	public:
		/// Default Destructor.
		~Model();

		/// Gets a reference to the normal indices of the model.
		/// return : The references to the normal indices.
		virtual std::vector<int>& getNormalIndices();

		/// Gets a reference to the normals of the model.
		/// return : The references to the normals.
		virtual std::vector<Honeycomb::Math::Vector3f>& getNormals();

		/// Gets a reference to the UV indices of the model.
		/// return : The references to the UV indices.
		virtual std::vector<int>& getUVIndices();

		/// Gets a reference to the 2D texture coordinates of the model.
		/// return : The references to the coordinates.
		virtual std::vector<Honeycomb::Math::Vector2f>& getUVs();

		/// Gets a reference to the vertex indices of the model.
		/// return : The references to the vertex indices.
		virtual std::vector<int>& getVertexIndices();

		/// Gets a reference to the verticies of the model.
		/// return : The references to the verticies.
		virtual std::vector<Honeycomb::Math::Vector3f>& getVerticies();
	
		/// Loads in the model from the specified file.
		/// std::string : The file from which to load in the model.
		/// return : The loaded in model.
		virtual Model* loadModel(std::string file);
	protected:
		/// Initializes an Empty Model.
		Model();

		/// Creates a Model instance initialized to the specified faces, 
		/// normals, texture coordinates and verticies.
		/// vector<int> normIndx : The normal indices.
		/// vector<int> uvIndx : The UV indices.
		/// vector<int> vertIndx : The vertex indices.
		/// vector<Vector3f> norms: The normals.
		/// vector<Vector2f> texCrds : The texture coordinates.
		/// vector<Vector3f> verts : The verticies.
		Model(std::vector<int> normIndx, std::vector<int> uvIndx, 
			std::vector<int> vertIndx, 
			std::vector<Honeycomb::Math::Vector3f> norms,
			std::vector<Honeycomb::Math::Vector2f> uvs,
			std::vector<Honeycomb::Math::Vector3f> verts);
	private:
		std::vector<int> normalIndices;
		std::vector<Honeycomb::Math::Vector3f> normals;

		std::vector<int> uvIndices;
		std::vector<Honeycomb::Math::Vector2f> uvs;

		std::vector<int> vertexIndices;
		std::vector<Honeycomb::Math::Vector3f> verticies;
	};
}

#endif