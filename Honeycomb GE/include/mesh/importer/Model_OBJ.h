#pragma once
#ifndef MODEL_OBJ_H
#define MODEL_OBJ_H

#include "Model.h"

namespace Honeycomb::Mesh::Importer {
	class Model_OBJ : public Model {
	public:
		/// Loads in a Wavefront (.obj) Model from the specified file.
		/// std::string file : The file pointing to the Wavefront Model.
		/// return : The initialized Wavefront Model.
		static Model_OBJ* loadModel(std::string file);
	private:
		/// Creates a Wavefront (.obj) Model using the specified indicies,
		/// normals, texture coordinates and verticies.
		/// vector<int> indx : The indicies.
		/// vector<Vector3f> norms: The normals.
		/// vector<Vector2f> texCrds : The texture coordinates.
		/// vector<verts> verts : The verticies.
		Model_OBJ(std::vector<int> indx, std::vector<Honeycomb::Math::Vector3f>
			norms, std::vector<Honeycomb::Math::Vector2f> texCrds,
			std::vector<Honeycomb::Mesh::Vertex> verts);

		/// Default Destructor.
		~Model_OBJ();
	};
}

#endif