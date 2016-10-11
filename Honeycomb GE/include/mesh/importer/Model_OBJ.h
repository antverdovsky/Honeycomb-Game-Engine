#pragma once
#ifndef MODEL_OBJ_H
#define MODEL_OBJ_H

#include "Model.h"

namespace Honeycomb::Mesh::Importer {
	class Model_OBJ : public Model {
	public:
		/// Loads in a Wavefront (.obj) Model from the specified file. The 
		/// "Model" object will be allocated dynamically and should therefore 
		/// be removed after being used.
		/// std::string file : The file pointing to the Wavefront Model.
		/// return : The initialized Wavefront Model.
		static Model_OBJ* loadModel(std::string file);
	private:
		/// Creates a Wavefront (.obj) Model using the specified indices,
		/// normals, texture coordinates and verticies.
		/// vector<Face> fcs : The indices.
		/// vector<Vector3f> norms: The normals.
		/// vector<Vector2f> texCrds : The texture coordinates.
		/// vector<verts> verts : The verticies.
		Model_OBJ(std::vector<int> normIndx, std::vector<int> uvIndx,
				std::vector<int> vertIndx,
				std::vector<Honeycomb::Math::Vector3f> norms,
				std::vector<Honeycomb::Math::Vector2f> uvs,
				std::vector<Honeycomb::Math::Vector3f> verts);

		/// Default Destructor.
		~Model_OBJ();
	};
}

#endif