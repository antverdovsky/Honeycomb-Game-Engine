#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include "..\..\geometry\Vertex.h"

namespace Honeycomb::Geometry::Importer {
	class Model {
	public:
		/// Initializes an Empty Model.
		Model();

		/// Default Destructor.
		~Model();

		/// Gets a reference to the indices of the model.
		/// return : The references to the indices.
		virtual std::vector<int>& getIndices();

		/// Gets a reference to the verticies of the model.
		/// return : The references to the verticies.
		virtual std::vector<Honeycomb::Geometry::Vertex>& getVerticies();
	
		/// Loads in the model from the specified file.
		/// std::string : The file from which to load in the model.
		/// return : The loaded in model.
		virtual Model* loadModel(std::string file);
	protected:
		/// Creates a Model instance initialized to the indices and vertices.
		/// std::vector<int> indx : The list of indices for the model.
		/// std::vector<Vertex> vert : The list of vertices for the model.
		Model(std::vector<int> indx, 
			std::vector<Honeycomb::Geometry::Vertex> vert);
	private:
		std::vector<int> indices;
		std::vector<Honeycomb::Geometry::Vertex> vertices;
	};
}

#endif