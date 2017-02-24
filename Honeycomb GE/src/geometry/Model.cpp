#include "..\..\include\geometry\Model.h"

#include <iostream>

#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"

#include "..\..\include\component\physics\Transform.h"
#include "..\..\include\component\render\MeshRenderer.h"
#include "..\..\include\debug\Logger.h"
#include "..\..\include\geometry\Vertex.h"
#include "..\..\include\graphics\Material.h"
#include "..\..\include\graphics\Texture2D.h"
#include "..\..\include\math\Vector2f.h"
#include "..\..\include\math\Vector3f.h"
#include "..\..\include\math\Vector4f.h"
#include "..\..\include\math\Quaternion.h"

using Assimp::Importer;

using Honeycomb::Component::Physics::Transform;
using Honeycomb::Component::Physics::Space;
using Honeycomb::Component::Render::MeshRenderer;
using Honeycomb::Debug::Logger;
using Honeycomb::Graphics::Material;
using Honeycomb::Graphics::Texture2D;
using Honeycomb::Object::GameObject;
using Honeycomb::Math::Vector2f;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector4f;
using Honeycomb::Math::Quaternion;

namespace Honeycomb::Geometry {
	std::vector<Model*> Model::imports = std::vector<Model*>();

	unsigned int ModelSettings::toPFlags() const {
		unsigned int pF = 0;

		pF |= calcTangentSpace ? aiProcess_CalcTangentSpace : 0;
		pF |= joinDuplicateVertices ? aiProcess_JoinIdenticalVertices : 0;
		pF |= makeLeftHanded ? aiProcess_MakeLeftHanded : 0;
		pF |= triangulate ? aiProcess_Triangulate : 0;
		pF |= genNormals ? aiProcess_GenNormals : 0;
		pF |= genSmoothNormals ? aiProcess_GenSmoothNormals : 0;
		pF |= splitLargeMeshes ? aiProcess_SplitLargeMeshes : 0;
		pF |= preTransformVertices ? aiProcess_PreTransformVertices : 0;
		pF |= delUnusedMaterials ? aiProcess_RemoveRedundantMaterials : 0;
		pF |= fixInfacingNormals ? aiProcess_FixInfacingNormals : 0;
		pF |= genUVCoords ? aiProcess_GenUVCoords : 0;
		pF |= transformUVCoords ? aiProcess_TransformUVCoords : 0;
		pF |= optimizeMesh ? aiProcess_OptimizeMeshes : 0;
		pF |= optimizeGraph ? aiProcess_OptimizeGraph : 0;
		pF |= flipUVs ? aiProcess_FlipUVs : 0;
		pF |= flipWindingOrder ? aiProcess_FlipWindingOrder : 0;

		return pF;
	}

	bool ModelSettings::operator== (const ModelSettings &that) {
		return
			this->calcTangentSpace == that.calcTangentSpace &&
			this->joinDuplicateVertices == that.joinDuplicateVertices &&
			this->makeLeftHanded == that.makeLeftHanded &&
			this->triangulate == that.triangulate &&
			this->genNormals == that.genNormals &&
			this->genSmoothNormals == that.genSmoothNormals &&
			this->splitLargeMeshes == that.splitLargeMeshes &&
			this->preTransformVertices == that.preTransformVertices &&
			this->delUnusedMaterials == that.delUnusedMaterials &&
			this->fixInfacingNormals == that.fixInfacingNormals &&
			this->genUVCoords == that.genUVCoords &&
			this->transformUVCoords == that.transformUVCoords &&
			this->optimizeMesh == that.optimizeMesh &&
			this->optimizeGraph == that.optimizeGraph &&
			this->flipUVs == that.flipUVs &&
			this->flipWindingOrder == that.flipWindingOrder;
	}

	Model::~Model() {
		for (const Texture2D *tex : this->textures)
			delete tex;
		for (const Material *mat : this->materials)
			delete mat;
		for (const Mesh *mesh : this->meshes)
			delete mesh;

		this->textures.clear();
		this->materials.clear();
		this->meshes.clear();
	}

	const Model& Model::loadModel(const std::string &path, 
			const ModelSettings &settings) {
		for (const Model *model : Model::imports) {
			if (model->path == path)
				return *model;
		}

		return *(new Model(path, settings));
	}

	GameObject* Model::getGameObject() {
		return this->gameObject;
	}

	GameObject* Model::getGameObjectClone() const {
		return this->gameObject->clone();
	}

	const std::string& Model::getPath() const {
		return this->path;
	}

	Model::Model(const std::string &path, const ModelSettings &settings) {
		this->path = path;
		this->settings = settings;
		
		this->loadFromPath();
		this->imports.push_back(this);
	}

	void Model::loadFromPath() {
		// Import the Scene from ASSIMP and Check for Errors.
		Importer aImp = Importer();
		this->scene = aImp.ReadFile(path, settings.toPFlags());
		if (this->scene == nullptr ||
			this->scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE ||
			this->scene->mRootNode == nullptr) {

			Logger::getLogger().logError(__FUNCTION__, __LINE__,
				aImp.GetErrorString());

			return;
		}

		// Initialize the Model Object from the Scene Root node
		this->gameObject = this->processAiNode(this->scene->mRootNode);
	}

	Material* Model::processAiMeshMaterial(aiMaterial* aMat) {
		aiString matName; // Name of the Material
		Texture2D *texture = new Texture2D(); // Albedo Texture of the Material
		aiColor3D matAmbient; // Ambient Property of the Material
		aiColor3D matDiffuse; // Diffuse Property of the Material
		aiColor3D matSpecular; // Specular Property of the Material
		float matShininess; // Shininess Property of the Material

		// Retrieve all of the Material properties from ASSIMP
		aMat->Get(AI_MATKEY_NAME, matName);
		aMat->Get(AI_MATKEY_COLOR_AMBIENT, matAmbient);
		aMat->Get(AI_MATKEY_COLOR_DIFFUSE, matDiffuse);
		aMat->Get(AI_MATKEY_COLOR_SPECULAR, matSpecular);
		aMat->Get(AI_MATKEY_SHININESS, matShininess);

		texture->initialize();
		if (aMat->GetTextureCount(aiTextureType_DIFFUSE)) {
			///
			/// TODO: SUPPORT FOR MORE TEXTURES.
			/// [will need to change the material class first]
			aiString dir;
			aMat->GetTexture(aiTextureType_DIFFUSE, 0, &dir);

			texture->setImageData(dir.C_Str());
		} else {
			texture->setImageData();
		}

		// Build the Material and return it [TODO, use material name not sub!]
		Material *mat = new Material();
		mat->glVector4fs.setValue("ambientColor", 
			Vector4f(matAmbient.r, matAmbient.g, matAmbient.b, 1.0F));
		mat->glVector4fs.setValue("diffuseColor",
			Vector4f(matDiffuse.r, matDiffuse.g, matDiffuse.b, 1.0F));
		mat->glVector4fs.setValue("specularColor",
			Vector4f(matSpecular.r, matSpecular.g, matSpecular.b, 
				matShininess));
		mat->glSampler2Ds.setValue("albedoTexture", *texture);

		// Save the texture and material
		this->textures.push_back(texture);
		this->materials.push_back(mat);

		return mat;
	}

	Honeycomb::Geometry::Mesh* Model::processAiMeshGeometry(aiMesh *aMesh) {
		std::vector<Vertex> vertices; // Vertices Data
		std::vector<int> indices; // Indices Data

		// Go through all the vertices of the Mesh
		for (unsigned int i = 0; i < aMesh->mNumVertices; i++) {
			// Get all of the normals, positions and UV coordinates for this
			// vertex.
			// TODO: Worry about the other 7 texture coordinates of the vertex?
			aiVector3D vertNorms = aMesh->mNormals[i];
			aiVector3D vertPos = aMesh->mVertices[i];
			aiVector3D vertUV = aMesh->HasTextureCoords(0) ?
				aMesh->mTextureCoords[0][i] : // TODO: Multiple Texture Support
				aiVector3D(0.0F, 0.0F, 0.0F);

			// Generate a Vertex using the fetched Vertex information
			Vertex vertex = Vertex(
				Vector3f(vertNorms.x, vertNorms.y, vertNorms.z),
				Vector3f(vertPos.x, vertPos.y, vertPos.z),
				Vector2f(vertUV.x, vertUV.y)
			);

			vertices.push_back(vertex); // Add the vertex to Mesh data
		}

		// Go through all the faces of the Mesh
		for (unsigned int i = 0; i < aMesh->mNumFaces; i++) {
			aiFace face = aMesh->mFaces[i]; // Get the face

			// Go through all the indices of the Face
			for (unsigned int j = 0; j < face.mNumIndices; j++) {
				int indx = face.mIndices[j]; // Get the index
				indices.push_back(indx); // Add the index to Mesh data
			}
		}

		// Create a new Honeycomb Mesh with the fetched vertex and index data.
		Mesh *mesh = new Mesh();
		mesh->initialize();
		mesh->setIndexData(&indices[0], indices.size());
		mesh->setVertexData(&vertices[0], vertices.size());
		this->meshes.push_back(mesh);

		return mesh;
	}

	GameObject* Model::processAiNode(aiNode *aNode) {
		// If this is a child of the scene's RootNode, then scale it according
		// to the settings' scaling factor since its position is global. Else,
		// the position is local and should not be scaled by anything!
		float lclSclFactor = (aNode->mParent == this->scene->mRootNode) ?
			this->settings.scaleFactor : 1.0F;

		// Create the GameObject representing this node, and give it a
		// Transform, since all Objects get one.
		GameObject* object = new GameObject(aNode->mName.C_Str());
		Transform* transf = new Transform();

		// Fetch the Transformation of the Object and write to the Transform
		// (Scaling may be ignored since the position vector itself is scaled
		// by the import scale factor).
		aiQuaterniont<float> rotation;
		aiVector3D position;
		aiVector3D scale;
		aNode->mTransformation.Decompose(scale, rotation, position);
		transf->setRotation(Quaternion(rotation.x, rotation.y, rotation.z,
			rotation.w));
		transf->setTranslation(Vector3f(position.x, position.y, position.z) *
			lclSclFactor, Space::LOCAL);
		object->addComponent(*transf);

		// Process all of the Meshes of the Object
		for (unsigned int i = 0; i < aNode->mNumMeshes; i++) {
			// Convert the ASSIMP Mesh Geometry into Honeycomb Mesh Geometry
			aiMesh *aMesh = this->scene->mMeshes[aNode->mMeshes[i]];
			Mesh *mesh = this->processAiMeshGeometry(aMesh);

			// Convert the ASSIMP Mesh Material into Honeycomb Mesh Material
			aiMaterial *aMat;
			Material *mat;
			if (aMesh->mMaterialIndex >= 0) { // Get Material, if it exists
				aMat = this->scene->mMaterials[aMesh->mMaterialIndex];
				mat = this->processAiMeshMaterial(aMat);
			}
			else { // Otherwise, create a default Material
				mat = new Material();
			}

			// Create a Mesh Renderer with the mesh and material extracted.
			MeshRenderer *meshRen = new MeshRenderer(*mat, *mesh);
			object->addComponent(*meshRen);
		}

		// Process all of the Children of the Object
		for (unsigned int i = 0; i < aNode->mNumChildren; i++) {
			// Convert each child into a new Game Object.
			aiNode *childNode = aNode->mChildren[i];
			GameObject *childObj = this->processAiNode(childNode);

			// Add each fetched child as a child to this Game Object.
			object->addChild(*childObj);
		}

		return object; // Return the instantiated object
	}
}