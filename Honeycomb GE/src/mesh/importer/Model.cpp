#include "..\..\..\include\mesh\importer\Model.h"

#include "..\..\..\include\math\Vector2f.h"
#include "..\..\..\include\math\Vector3f.h"
#include "..\..\..\include\mesh\Vertex.h"

using Honeycomb::Math::Vector2f;
using Honeycomb::Math::Vector3f;
using Honeycomb::Mesh::Vertex;

namespace Honeycomb::Mesh::Importer {
	Model::~Model() {

	}
	
	std::vector<int>& Model::getIndices() {
		return this->indices;
	}

	std::vector<Vertex>& Model::getVerticies() {
		return this->vertices;
	}

	Model* Model::loadModel(std::string file) {
		return new Model();
	}

	Model::Model() {

	}

	Model::Model(std::vector<int> indx, std::vector<Vertex> vert) {
		this->indices = indx;
		this->vertices = vert;
	}
}