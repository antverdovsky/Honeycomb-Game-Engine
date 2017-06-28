#include "../../include/geometry/Model.h"

#include <iostream>
#include <sstream>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "../../include/component/physics/Transform.h"
#include "../../include/component/render/MeshRenderer.h"
#include "../../include/debug/Logger.h"
#include "../../include/file/ImageIO.h"
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
using Honeycomb::File::ImageIO;
using Honeycomb::File::ImageIOLoadException;
using Honeycomb::Debug::Logger;
using Honeycomb::Graphics::Material;
using Honeycomb::Graphics::Texture2D;
using Honeycomb::Graphics::Texture2DCommonFillColor;
using Honeycomb::Object::GameObject;
using Honeycomb::Math::Vector2f;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector4f;
using Honeycomb::Math::Quaternion;

namespace Honeycomb { namespace Geometry {
	std::vector<Model*> Model::imports = std::vector<Model*>();

	ModelSettings::ModelSettings() {
		this->scaleFactor           = 0.01F;

		this->calcTangentSpace      = true;
		this->joinDuplicateVertices = true;
		this->makeLeftHanded        = false;
		this->triangulate           = true;
		this->genNormals            = false;
		this->genSmoothNormals      = true;
		this->splitLargeMeshes      = true;
		this->preTransformVertices  = false;
		this->delUnusedMaterials    = false;
		this->fixInfacingNormals    = false;
		this->genUVCoords           = false;
		this->transformUVCoords     = false;
		this->optimizeMesh          = true;
		this->optimizeGraph         = false;
		this->flipUVs               = true;
		this->flipWindingOrder      = false;
	}

	unsigned int ModelSettings::toPFlags() const {
		unsigned int pF = 0;

		pF |= calcTangentSpace      ? aiProcess_CalcTangentSpace         : 0;
		pF |= joinDuplicateVertices ? aiProcess_JoinIdenticalVertices    : 0;
		pF |= makeLeftHanded        ? aiProcess_MakeLeftHanded           : 0;
		pF |= triangulate           ? aiProcess_Triangulate              : 0;
		pF |= genNormals            ? aiProcess_GenNormals               : 0;
		pF |= genSmoothNormals      ? aiProcess_GenSmoothNormals         : 0;
		pF |= splitLargeMeshes      ? aiProcess_SplitLargeMeshes         : 0;
		pF |= preTransformVertices  ? aiProcess_PreTransformVertices     : 0;
		pF |= delUnusedMaterials    ? aiProcess_RemoveRedundantMaterials : 0;
		pF |= fixInfacingNormals    ? aiProcess_FixInfacingNormals       : 0;
		pF |= genUVCoords           ? aiProcess_GenUVCoords              : 0;
		pF |= transformUVCoords     ? aiProcess_TransformUVCoords        : 0;
		pF |= optimizeMesh          ? aiProcess_OptimizeMeshes           : 0;
		pF |= optimizeGraph         ? aiProcess_OptimizeGraph            : 0;
		pF |= flipUVs               ? aiProcess_FlipUVs                  : 0;
		pF |= flipWindingOrder      ? aiProcess_FlipWindingOrder         : 0;

		return pF;
	}

	Model::~Model() {
		for (const Material *mat : this->materials)
			delete mat;
//		for (const Mesh *mesh : this->meshes)
//			delete mesh;

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
/*
	std::unique_ptr<GameObject> Model::getGameObject() {
		return this->gameObject;
	}
*/
	std::unique_ptr<GameObject> Model::getGameObjectClone() const {
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
			Material &mat, const std::string &matUni, 
			const Texture2DCommonFillColor &defColor) {
		Texture2D texture;
		
		aiTextureType aTT = (aiTextureType)(tT);
		if (aMat.GetTextureCount(aTT)) { // If material has the texture we want
			// Get the texture directory
			aiString dir;
			aMat.GetTexture(aTT, 0, &dir);

			// If the image can be loaded, set the texture to the image data;
			// otherwise set the texture to the R, G, B values.
			try {
				ImageIO image = ImageIO(dir.C_Str());
				texture.initialize();
				texture.setImageDataIO(image);
			} catch (ImageIOLoadException e) {
				texture = Texture2D::getTextureCommonFill(defColor);
				return;
			}
		} else {
			// Set the previously initialized texture to default value
			texture = Texture2D::getTextureCommonFill(defColor);
		}

		mat.glSampler2Ds.setValue(matUni + ".sampler", texture);
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
			"albedoTexture", Texture2DCommonFillColor::COLOR_WHITE);
		this->fetchMaterialTexture(*aMat,
			aiTextureType::aiTextureType_AMBIENT, *material,
			"ambientTexture", Texture2DCommonFillColor::COLOR_WHITE);
		this->fetchMaterialTexture(*aMat, 
			aiTextureType::aiTextureType_SPECULAR, *material, 
			"specularTexture", Texture2DCommonFillColor::COLOR_WHITE);
		this->fetchMaterialTexture(*aMat, 
			aiTextureType::aiTextureType_NORMALS, *material,
			"normalsTexture", Texture2DCommonFillColor::COLOR_BLACK);
		this->fetchMaterialTexture(*aMat,
			aiTextureType::aiTextureType_DISPLACEMENT, *material,
			"displacementTexture", Texture2DCommonFillColor::COLOR_BLACK);

		// Special default value for diffuse map (TODO: Method for this?)
		Texture2D diffuse = Texture2D::getTextureWhite();
		material->glSampler2Ds.setValue("diffuseTexture.sampler", diffuse);
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

	std::unique_ptr<Honeycomb::Geometry::Mesh> Model::processAiMeshGeometry(aiMesh *aMesh) {
		std::vector<Vertex> vertices; // Vertices Data
		std::vector<unsigned int> indices; // Indices Data

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
				unsigned int indx = face.mIndices[j]; // Get the index
				indices.push_back(indx); // Add the index to Mesh data
			}
		}

		// Create a new Honeycomb Mesh with the fetched vertex and index data.
		std::unique_ptr<Mesh> mesh = Mesh::newMeshUnique();
		mesh->setIndexData(indices);
		mesh->setVertexData(vertices);
		return mesh;
	}

	std::unique_ptr<GameObject> Model::processAiNode(aiNode *aNode) {
		// If this is a child of the scene's RootNode, then scale it according
		// to the settings' scaling factor since its position is global. Else,
		// the position is local and should not be scaled by anything!
		float lclSclFactor = (aNode->mParent == this->scene->mRootNode) ?
			this->settings.scaleFactor : 1.0F;

		// Create the GameObject representing this node, and give it a
		// Transform, since all Objects get one.
		std::unique_ptr<GameObject> object = std::make_unique<GameObject>(
				aNode->mName.C_Str());
		auto &transf = object->getComponent<Transform>();

		// Fetch the Transformation of the Object and write to the Transform
		// (Scaling may be ignored since the position vector itself is scaled
		// by the import scale factor).
		aiQuaterniont<float> rotation;
		aiVector3D position;
		aiVector3D scale;
		aNode->mTransformation.Decompose(scale, rotation, position);
		transf.setRotation(Quaternion(rotation.x, rotation.y, rotation.z,
			rotation.w));
		transf.setTranslation(Vector3f(position.x, position.y, position.z) *
			lclSclFactor, Space::LOCAL);

		// Process all of the Meshes of the Object
		std::unique_ptr<MeshRenderer> meshRen =
			std::make_unique<MeshRenderer>();
		for (unsigned int i = 0; i < aNode->mNumMeshes; i++) {
			// Convert the ASSIMP Mesh Geometry into Honeycomb Mesh Geometry
			aiMesh *aMesh = this->scene->mMeshes[aNode->mMeshes[i]];
			std::unique_ptr<Mesh> mesh = this->processAiMeshGeometry(aMesh);
			
			// Convert the ASSIMP Mesh Material into Honeycomb Mesh Material
			aiMaterial *aMat;
			Material *mat;
			if (aMesh->mMaterialIndex >= 0) { // Get Material, if it exists
				aMat = this->scene->mMaterials[aMesh->mMaterialIndex];
				mat = this->processAiMeshMaterial(aMat);
			} else { // Otherwise, create a default Material
				mat = new Material();
			}

			meshRen->addMaterial(mat);
			meshRen->addMesh(mesh.get());

			this->meshes.push_back(std::move(mesh));
		}
		object->addComponent(std::move(meshRen));

		// Process all of the Children of the Object
		for (unsigned int i = 0; i < aNode->mNumChildren; i++) {
			// Convert each child into a new Game Object.
			aiNode *childNode = aNode->mChildren[i];
			std::unique_ptr<GameObject> childObj = 
					this->processAiNode(childNode);

			// Add each fetched child as a child to this Game Object.
			object->addChild(std::move(childObj));
		}

		return object; // Return the instantiated object
	}

	ModelLoadException::ModelLoadException(const std::string &path,
			const std::string &err) : 
			std::runtime_error("Model could not be loaded") {
		this->directory = path;
		this->assimpError = err;
	}

	const char* ModelLoadException::what() const {
		std::ostringstream oss("");
		oss << std::runtime_error::what() << " from directory " <<
			this->directory << " | " << this->assimpError;
		return oss.str().c_str();
	}
} }
