#include "..\..\..\include\mesh\importer\Model.h"

#include "..\..\..\include\math\Vector2f.h"
#include "..\..\..\include\math\Vector3f.h"
#include "..\..\..\include\mesh\Vertex.h"

using Honeycomb::Math::Vector2f;
using Honeycomb::Math::Vector3f;

namespace Honeycomb::Mesh::Importer {
	Model::~Model() {

	}

	std::vector<int>& Model::getIndicies() {
		return this->indicies;
	}

	std::vector<Vector3f>& Model::getNormals() {
		return this->normals;
	}

	std::vector<Vector2f>& Model::getTextureCoords() {
		return this->textureCoords;
	}

	std::vector<Vertex>& Model::getVerticies() {
		return this->verticies;
	}

	Model* Model::loadModel(std::string file) {
		return new Model();
	}

	Model::Model() {

	}

	Model::Model(std::vector<int> indx, std::vector<Honeycomb::Math::Vector3f>
			norms, std::vector<Honeycomb::Math::Vector2f> texCrds,
			std::vector<Honeycomb::Mesh::Vertex> verts) {
		this->indicies = indx;
		this->normals = norms;
		this->textureCoords = texCrds;
		this->verticies = verts;
	}
}