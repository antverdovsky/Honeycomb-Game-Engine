#include "..\..\..\include\mesh\importer\Model_OBJ.h"

#include <sstream>
#include <cstdio>

#include <iostream>

#include "..\..\..\include\file\FileIO.h"
#include "..\..\..\include\math\Vector2f.h"
#include "..\..\..\include\math\Vector3f.h"

using namespace Honeycomb::File;
using Honeycomb::Math::Vector2f;
using Honeycomb::Math::Vector3f;

namespace Honeycomb::Mesh::Importer {
	Model_OBJ* Model_OBJ::loadModel(std::string file) {
		// Create variables to store the contents and stream each line
		std::string contents = File::readFileToStr(file);
		std::stringstream lineStream(contents);
		std::string line = "";

		// Create variables to store the verticies, indices, normals, etc.
		std::vector<int> vertIndx;
		std::vector<int> uvIndx;
		std::vector<int> normIndx;
		std::vector<Vector3f> verts;
		std::vector<Vector3f> norms;
		std::vector<Vector2f> uvs;

		while (std::getline(lineStream, line, '\n')) { // Get the line
			// If this is an empty line or its a comment -> Go to next line
			if (line.empty() || line.at(0) == '#') {
				continue;
			}
			else if (line.substr(0, 2) == "v ") { // If a vertex
				// Create an empty position vector and push the vertex coords
				// into it.
				Vector3f pos = Vector3f();
				sscanf_s(line.c_str(), "v %f %f %f", 
					&pos.getX(), &pos.getY(), &pos.getZ());

				// Create a vertex with the vector position
				verts.push_back(pos);
			}
			else if (line.at(0) == 'f') { // If this is a face
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
					vertIndx.push_back(vert[i] - 1);
					uvIndx.push_back(uv[i] - 1);
					normIndx.push_back(norm[i] - 1);
				}
			}
		}

		Model_OBJ *model = new Model_OBJ(normIndx, uvIndx, vertIndx,
			norms, uvs, verts); 

		return model;
	}

	Model_OBJ::Model_OBJ(std::vector<int> normIndx, std::vector<int> uvIndx,
			std::vector<int> vertIndx,
			std::vector<Honeycomb::Math::Vector3f> norms,
			std::vector<Honeycomb::Math::Vector2f> uvs,
			std::vector<Honeycomb::Math::Vector3f> verts)
				: Model(normIndx, uvIndx, vertIndx, norms, uvs, verts) {
			
	}

	Model_OBJ::~Model_OBJ() {

	}
}