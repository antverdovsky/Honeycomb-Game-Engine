#include "../../include/geometry/Model.h"

#include <iostream>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "../../include/component/physics/Transform.h"
#include "../../include/component/render/MeshRenderer.h"
#include "../../include/debug/Logger.h"
#include "../../include/geometry/Vertex.h"
#include "../../include/graphics/Material.h"
#include "../../include/graphics/Texture2D.h"
#include "../../include/math/Vector2f.h"
#include "../../include/math/Vector3f.h"
#include "../../include/math/Vector4f.h"
#include "../../include/math/Quaternion.h"

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

namespace Honeycomb { namespace Geometry {
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

	float Model::fetchMaterialProperty(const aiMaterial &mat, const char *pKey,
			unsigned int type, unsigned int idx, const float &def, bool err) {
		// Fetch the property from the material
		float prop;
		aiReturn result = mat.Get(pKey, type, idx, prop);

		if (result == aiReturn::aiReturn_SUCCESS) {
			return prop; // Return the property
		} else {
			if (err) { // Print a warning message if applicable
				Logger::getLogger().logWarning(__FUNCTION__, __LINE__,
					"Unable to retrieve property " + std::string(pKey) +
					" from material for object " + this->path);
			}

			return def; // Return the default value
		}
	}

	Vector3f Model::fetchMaterialProperty(const aiMaterial &mat,
		const char *pKey, unsigned int type, unsigned int idx, const
		Vector3f &def, bool err) {
		// Fetch the property from the material
		aiColor3D vec3;
		aiReturn result = mat.Get(pKey, type, idx, vec3);

		if (result == aiReturn::aiReturn_SUCCESS) {
			return Vector3f(vec3.r, vec3.g, vec3.b); // Return the property
		} else {
			if (err) { // Print a warning message if applicable
				Logger::getLogger().logWarning(__FUNCTION__, __LINE__,
					"Unable to retrieve property " + std::string(pKey) +
					" from material for object " + this->path);
			}

			return def; // Return the default value
		}
	}

	Texture2D* Model::fetchMaterialTexture(const aiMaterial &mat,
		const int &tT, const int &r, const int &g, const int &b) {
		// Create and initialize the texture
		Texture2D *texture = new Texture2D();
		texture->initialize();

		aiTextureType aTT = (aiTextureType)(tT);
		if (mat.GetTextureCount(aTT)) { // If material has the texture we want
			// Get the texture directory
			aiString dir;
			mat.GetTexture(aTT, 0, &dir);

			// Set the previously initialized texture to contain the data
			texture->setImageData(dir.C_Str());
		} else {
			// Set the previously initialized texture to empty texture
			texture->setImageData(r, g, b);
		}

		return texture; // Return the texture
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
		// Retrieve all of the Material properties from ASSIMP
		Vector3f diffuse = this->fetchMaterialProperty(*aMat,
			AI_MATKEY_COLOR_DIFFUSE, Vector3f(1.0F, 1.0F, 1.0F));
		Vector3f specular = this->fetchMaterialProperty(*aMat,
			AI_MATKEY_COLOR_SPECULAR, Vector3f(1.0F, 1.0F, 1.0F));
		float shininess = this->fetchMaterialProperty(*aMat,
			AI_MATKEY_SHININESS, 0.0F);
		float refIndex = this->fetchMaterialProperty(*aMat,
			AI_MATKEY_REFRACTI, 1.0F);
		float refStrength = this->fetchMaterialProperty(*aMat,
			AI_MATKEY_REFLECTIVITY, 0.0F);

		// Retrieve the Textures from ASSIMP.
		Texture2D *diffuseTexture = this->fetchMaterialTexture(*aMat,
			aiTextureType::aiTextureType_DIFFUSE, 255, 255, 255);
		Texture2D *specularTexture = this->fetchMaterialTexture(*aMat,
			aiTextureType::aiTextureType_SPECULAR, 255, 255, 255);
		Texture2D *normalsTexture = this->fetchMaterialTexture(*aMat,
			aiTextureType::aiTextureType_NORMALS, 0, 0, 0);
		Texture2D *displacementTexture = this->fetchMaterialTexture(*aMat,
			aiTextureType::aiTextureType_DISPLACEMENT, 0, 0, 0);

		// Create the material.
		Material *mat = new Material();
		mat->glVector3fs.setValue("diffuseColor", diffuse);
		mat->glVector3fs.setValue("specularColor", specular);
		mat->glFloats.setValue("shininess", shininess);
		mat->glFloats.setValue("refractiveIndex", refIndex);
		mat->glFloats.setValue("reflectionStrength", refStrength);
		mat->glSampler2Ds.setValue("diffuseTexture.sampler", *diffuseTexture);
		mat->glVector2fs.setValue("diffuseTexture.tiling",
			Vector2f(1.0F, 1.0F));
		mat->glVector2fs.setValue("diffuseTexture.offset",
			Vector2f(0.0F, 0.0F));
		mat->glSampler2Ds.setValue("specularTexture.sampler",
			*specularTexture);
		mat->glVector2fs.setValue("specularTexture.tiling",
			Vector2f(1.0F, 1.0F));
		mat->glVector2fs.setValue("specularTexture.offset",
			Vector2f(0.0F, 0.0F));
		mat->glSampler2Ds.setValue("normalsTexture.sampler",
			*normalsTexture);
		mat->glVector2fs.setValue("normalsTexture.tiling",
			Vector2f(1.0F, 1.0F));
		mat->glVector2fs.setValue("normalsTexture.offset",
			Vector2f(0.0F, 0.0F));
		mat->glSampler2Ds.setValue("displacementTexture.sampler",
			*displacementTexture);
		mat->glVector2fs.setValue("displacementTexture.tiling",
			Vector2f(1.0F, 1.0F));
		mat->glVector2fs.setValue("displacementTexture.offset",
			Vector2f(0.0F, 0.0F));
		mat->glVector2fs.setValue("globalTiling", Vector2f(1.0F, 1.0F));
		mat->glVector2fs.setValue("globalOffset", Vector2f(0.0F, 0.0F));

		// Save the texture and material
		this->textures.push_back(diffuseTexture);
		this->textures.push_back(specularTexture);
		this->textures.push_back(normalsTexture);
		this->materials.push_back(mat);

		return mat;
	}

	Honeycomb::Geometry::Mesh* Model::processAiMeshGeometry(aiMesh *aMesh) {
		std::vector<Vertex> vertices; // Vertices Data
		std::vector<int> indices; // Indices Data

		// Go through all the vertices of the Mesh (for the tangents, if the
		// Mesh has no tangents, we should not use a default Vector3 of values
		// { 0, 0, 0 } since this can cause some division by zero errors in the
		// Shaders).
		for (unsigned int i = 0; i < aMesh->mNumVertices; i++) {
			// Get all of the needed properties of the vertex
			aiVector3D vertNorms = aMesh->HasNormals() ?
				aMesh->mNormals[i] : aiVector3D();
			aiVector3D vertPos = aMesh->HasPositions() ?
				aMesh->mVertices[i] : aiVector3D();
			aiVector3D vertUV = aMesh->HasTextureCoords(0) ?
				aMesh->mTextureCoords[0][i] : aiVector3D();
			aiVector3D vertTan = aMesh->HasTangentsAndBitangents() ?
				aMesh->mTangents[i] : aiVector3D(1.0F, 1.0F, 1.0F);

			// Generate a Vertex using the fetched Vertex information
			Vertex vertex = Vertex(
				Vector3f(vertNorms.x, vertNorms.y, vertNorms.z),
				Vector3f(vertPos.x, vertPos.y, vertPos.z),
				Vector2f(vertUV.x, vertUV.y),
				Vector3f(vertTan.x, vertTan.y, vertTan.z)
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
			} else { // Otherwise, create a default Material
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
} }
