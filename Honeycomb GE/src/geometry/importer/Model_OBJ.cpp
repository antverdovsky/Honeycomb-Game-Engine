#include "..\..\..\include\geometry\importer\Model_OBJ.h"

#include <sstream>
#include <cstdio>

#include <iostream>

#include "..\..\..\include\file\FileIO.h"
#include "..\..\..\include\math\Vector2f.h"
#include "..\..\..\include\math\Vector3f.h"
#include "..\..\..\include\geometry\Vertex.h"

using namespace Honeycomb::File;
using Honeycomb::Math::Vector2f;
using Honeycomb::Math::Vector3f;
using Honeycomb::Mesh::Vertex;

namespace Honeycomb::Geometry::Importer {
	Model* Model_OBJ::loadModel(std::string file) {
		// Create variables to store the contents and stream each line
		std::string contents = File::readFileToStr(file);
		std::stringstream lineStream(contents);
		std::string line = "";

		// Create variables to store the verticies, indices, normals, etc.
		// These are only temporary, the actual vertices, UVs, and normals will
		// be seeded to the model according to the indices.
		std::vector<int> tmpPosIndx;
		std::vector<int> tmpUVIndx;
		std::vector<int> tmpNormIndx;
		std::vector<Vector3f> tmpPos;
		std::vector<Vector3f> tmpNorms;
		std::vector<Vector2f> tmpUVs;

		while (std::getline(lineStream, line, '\n')) { // Get the line
			// If this is an empty line or its a comment -> Go to next line
			if (line.empty() || line.at(0) == '#') {
				continue;
			}
			else if (line.substr(0, 2) == "v ") { // If a vertex
				// Create an empty position vector and push the vertex coords
				// into it.
				Vector3f vert = Vector3f();
				sscanf_s(line.c_str(), "v %f %f %f", 
					&vert.getX(), &vert.getY(), &vert.getZ());

				tmpPos.push_back(vert); // Create a vertex with the position
			}
			else if (line.substr(0, 3) == "vt ") { // If texture coordinate
				// Create an empty UV vector and push the texture coords
				// into it.
				Vector2f uv = Vector2f();
				sscanf_s(line.c_str(), "vt %f %f",
					&uv.getX(), &uv.getY());

				tmpUVs.push_back(uv); // Create a UV with the position
			}
			else if (line.substr(0, 3) == "vn ") { // If vertex normal
				// Create an empty normal vector and push the normal coords
				// into it.
				Vector3f norm = Vector3f();
				sscanf_s(line.c_str(), "vn %f %f %f",
					&norm.getX(), &norm.getY(), &norm.getZ());

				tmpNorms.push_back(norm); // Create a normal for the vertex 
			}
			else if (line.substr(0, 2) == "f ") { // If this is a face
				// Temporary arrays to store the indices of the vertex, UV,
				// and normal components.
				int vert[3], uv[3], norm[3];

				// Get the indices from the line. Since the faces are supposed
				// to be triangulated, we expect a vertex, UV and normal index 
				// from each group of 3 indices on the line.
				sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
					&vert[0], &uv[0], &norm[0],
					&vert[1], &uv[1], &norm[1],
					&vert[2], &uv[2], &norm[2]);

				// Copy the data from the temporary arrays to the vectors which
				// will actually store all of the data. 
				for (int i = 0; i < 3; i++) {
					tmpPosIndx.push_back(vert[i] - 1);
					tmpUVIndx.push_back(uv[i] - 1);
					tmpNormIndx.push_back(norm[i] - 1);
				}
			}
		}

		Model *model = new Model(); // Create an empty model

		// Go through all the "faces" of the imported model. (Each face has 1
		// index for vertex, texture and normal, so the loop could iterate
		// through tmpUVIndx or tmpNormIndx instead).
		for (int i = 0; i < tmpPosIndx.size(); i++) {
			// Get the position, UV and normal for the current face index.
			Vector3f curNorm = tmpNorms.at(tmpNormIndx.at(i));
			Vector3f curPos = tmpPos.at(tmpPosIndx.at(i));
			Vector2f curUV = tmpUVs.at(tmpUVIndx.at(i));

			// Add all the Vertices, UVs and Normals which are associated with
			// this face index.
			Vertex vertex = Vertex(curNorm, curPos, curUV);
			model->getVerticies().push_back(vertex);
			model->getIndices().push_back(i);
		}

		return model;
	}

	Model_OBJ::Model_OBJ(std::vector<int> indx, std::vector<Vertex> vert)
				: Model(indx, vert) {
			
	}

	Model_OBJ::~Model_OBJ() {

	}
}