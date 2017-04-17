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

	void Model::fetchMaterialProperty(const aiMaterial &aMat, const char *pKey,
			unsigned int type, unsigned int idx, Material &mat, 
			const std::string &matUni, const float &def, bool err) {
		// Fetch the property from the material
		float prop;
		aiReturn result = aMat.Get(pKey, type, idx, prop);

		if (result == aiReturn::aiReturn_SUCCESS) {
			mat.glFloats.setValue(matUni, prop);
		} else {
			if (err) { // Print a warning message if applicable
				Logger::getLogger().logWarning(__FUNCTION__, __LINE__,
					"Unable to retrieve property " + std::string(pKey) +
					" from material for object " + this->path);
			}

			mat.glFloats.setValue(matUni, def);
		}
	}

	void Model::fetchMaterialProperty(const aiMaterial &aMat, const char *pKey,
			unsigned int type, unsigned int idx, Material &mat, const 
			std::string &matUni, const Vector3f &def, bool err) {
		// Fetch the property from the material
		aiColor3D vec3;
		aiReturn result = aMat.Get(pKey, type, idx, vec3);

		if (result == aiReturn::aiReturn_SUCCESS) {
			mat.glVector3fs.setValue(matUni, Vector3f(vec3.r, vec3.g, vec3.b));
		} else {
			if (err) { // Print a warning message if applicable
				Logger::getLogger().logWarning(__FUNCTION__, __LINE__,
					"Unable to retrieve property " + std::string(pKey) +
					" from material for object " + this->path);
			}

			mat.glVector3fs.setValue(matUni, def);
		}
	}

	void Model::fetchMaterialTexture(const aiMaterial &aMat, const int &tT, 
			Material &mat, const std::string &matUni, const int &r, 
			const int &g, const int &b) {
		// Create and initialize the texture
		Texture2D *texture = new Texture2D();
		texture->initialize();

		aiTextureType aTT = (aiTextureType)(tT);
		if (aMat.GetTextureCount(aTT)) { // If material has the texture we want
			// Get the texture directory
			aiString dir;
			aMat.GetTexture(aTT, 0, &dir);

			// Set the previously initialized texture to contain the data
			texture->setImageData(dir.C_Str(), r, g, b);
		} else {
			// Set the previously initialized texture to default value
			texture->setImageData(r, g, b);
		}

		mat.glSampler2Ds.setValue(matUni + ".sampler", *texture);
		mat.glFloats.setValue(matUni + ".intensity", 1.0F);

		this->textures.push_back(texture);
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
		Material *material = new Material();

		// Retrieve all of the Material properties from ASSIMP
		this->fetchMaterialProperty(*aMat, AI_MATKEY_COLOR_DIFFUSE, *material,
			"albedoColor", Vector3f(1.0F, 1.0F, 1.0F));
		this->fetchMaterialProperty(*aMat, AI_MATKEY_COLOR_AMBIENT, *material,
			"ambientColor", Vector3f(1.0F, 1.0F, 1.0F));
		this->fetchMaterialProperty(*aMat, AI_MATKEY_COLOR_SPECULAR, *material,
			"specularColor", Vector3f(1.0F, 1.0F, 1.0F));
		this->fetchMaterialProperty(*aMat, AI_MATKEY_SHININESS, *material,
			"shininess", 0.0F);
		this->fetchMaterialProperty(*aMat, AI_MATKEY_REFRACTI, *material,
			"refractiveIndex", 1.0F);
		this->fetchMaterialProperty(*aMat, AI_MATKEY_REFLECTIVITY, *material,
			"reflectionStrength", 0.0F);

		// Retrieve the Textures from ASSIMP.
		this->fetchMaterialTexture(*aMat, 
			aiTextureType::aiTextureType_DIFFUSE, *material, 
			"albedoTexture", 255, 255, 255);
		this->fetchMaterialTexture(*aMat,
			aiTextureType::aiTextureType_AMBIENT, *material,
			"ambientTexture", 255, 255, 255);
		this->fetchMaterialTexture(*aMat, 
			aiTextureType::aiTextureType_SPECULAR, *material, 
			"specularTexture", 255, 255, 255);
		this->fetchMaterialTexture(*aMat, 
			aiTextureType::aiTextureType_NORMALS, *material,
			"normalsTexture", 0, 0, 0);
		this->fetchMaterialTexture(*aMat,
			aiTextureType::aiTextureType_DISPLACEMENT, *material,
			"displacementTexture", 0, 0, 0);

		// Special default value for diffuse map (TODO: Method for this?)
		Texture2D *diffuse = new Texture2D();
		diffuse->initialize();
		diffuse->setImageData(255, 255, 255);
		material->glSampler2Ds.setValue("diffuseTexture.sampler", *diffuse);
		material->glFloats.setValue("diffuseTexture.intensity", 1.0F);
		material->glVector3fs.setValue("diffuseColor",
			Vector3f(1.0F, 1.0F, 1.0F));

		// Set global tiling and offset for all Material Textures
		material->glVector2fs.setValue("globalTiling", Vector2f(1.0F, 1.0F));
		material->glVector2fs.setValue("globalOffset", Vector2f(0.0F, 0.0F));

		// Save the material
		this->materials.push_back(material);

		return material;
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
				Vector3f(vertPos.x, vertPos.y, vertPos.z),
				Vector3f(vertNorms.x, vertNorms.y, vertNorms.z),
				Vector3f(vertTan.x, vertTan.y, vertTan.z),
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
