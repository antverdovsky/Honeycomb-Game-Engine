#include "..\..\..\include\mesh\importer\Model_OBJ.h"

#include <sstream>

#include "..\..\..\include\file\FileIO.h"
#include "..\..\..\include\math\Vector2f.h"
#include "..\..\..\include\math\Vector3f.h"
#include "..\..\..\include\mesh\Vertex.h"

using namespace Honeycomb::File;
using Honeycomb::Math::Vector2f;
using Honeycomb::Math::Vector3f;
using Honeycomb::Mesh::Vertex;

namespace Honeycomb::Mesh::Importer {
	Model_OBJ* Model_OBJ::loadModel(std::string file) {
		// Create variables to store the contents and stream each line
		std::string contents = File::readFileToStr(file);
		std::stringstream lineStream(contents);
		std::string line = "";

		// Create variables to store the verticies, indicies, normals, etc.
		std::vector<int> indx;
		std::vector<Vertex> verts;
		std::vector<Vector3f> norms;
		std::vector<Vector2f> texCoords;

		while (std::getline(lineStream, line, '\n')) { // Get the line
			std::vector<std::string> tokens; // Line contents
			std::stringstream tokenStream(line); // Stream each token in line
			std::string token = "";

			while (std::getline(tokenStream, token, ' ')) { // Get each token
				tokens.push_back(token);
			}

			// If this is an empty line or its a comment -> Go to next line
			if (line.empty() || tokens.at(0) == "#") {
				continue;
			}
			else if (tokens.at(0) == "v") { // If this is a vertex
				// Get the vector position of the vertex from the file
				Vector3f pos = Vector3f(std::stof(tokens.at(1)),
					std::stof(tokens.at(2)),
					std::stof(tokens.at(3)));

				// Create a vertex with the vector position
				verts.push_back(Vertex(pos));
			}
			else if (tokens.at(0) == "f") { // If this is a face
				// Get the indicies from the file (and subtract 1 since OBJ
				// files count indicies from 1, but Honeycomb GE counts from 0.
				indx.push_back(std::stoi(tokens.at(1)) - 1);
				indx.push_back(std::stoi(tokens.at(2)) - 1);
				indx.push_back(std::stoi(tokens.at(3)) - 1);
			}
		}

		Model_OBJ *model = new Model_OBJ(indx, norms, texCoords, verts);

		return model;
	}

	Model_OBJ::Model_OBJ(std::vector<int> indx, 
			std::vector<Honeycomb::Math::Vector3f> norms, 
			std::vector<Honeycomb::Math::Vector2f> texCrds,
			std::vector<Honeycomb::Mesh::Vertex> verts) 
				: Model(indx, norms, texCrds, verts) {
			
	}

	Model_OBJ::~Model_OBJ() {

	}
}