#include "..\..\..\include\mesh\importer\Model.h"

#include "..\..\..\include\math\Vector2f.h"
#include "..\..\..\include\math\Vector3f.h"

using Honeycomb::Math::Vector2f;
using Honeycomb::Math::Vector3f;

namespace Honeycomb::Mesh::Importer {
	Model::~Model() {

	}
	
	std::vector<int>& Model::getNormalIndices() {
		return this->normalIndices;
	}

	std::vector<Vector3f>& Model::getNormals() {
		return this->normals;
	}

	std::vector<int>& Model::getUVIndices() {
		return this->uvIndices;
	}

	std::vector<Vector2f>& Model::getUVs() {
		return this->uvs;
	}

	std::vector<int>& Model::getVertexIndices() {
		return this->vertexIndices;
	}

	std::vector<Vector3f>& Model::getVerticies() {
		return this->verticies;
	}

	Model* Model::loadModel(std::string file) {
		return new Model();
	}

	Model::Model() {

	}

	Model::Model(std::vector<int> normIndx, std::vector<int> uvIndx,
			std::vector<int> vertIndx,
			std::vector<Honeycomb::Math::Vector3f> norms,
			std::vector<Honeycomb::Math::Vector2f> uvs,
			std::vector<Honeycomb::Math::Vector3f> verts) {
		this->normalIndices = normIndx;
		this->uvIndices = uvIndx;
		this->vertexIndices = vertIndx;

		this->normals = norms;
		this->uvs = uvs;
		this->verticies = verts;
	}
}