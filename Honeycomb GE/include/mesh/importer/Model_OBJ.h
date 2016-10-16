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
		static Model* loadModel(std::string file);
	private:
		/// Creates a Wavefront (.obj) Model using the specified indices,
		/// and vertices.
		/// vector<int> indx : The indices.
		/// vector<Vertex> vert : The vertices.
		Model_OBJ(std::vector<int> indx, std::vector<Vertex> vert);

		/// Default Destructor.
		~Model_OBJ();
	};
}

#endif