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
	}

	bool Model::fetchMaterialProperty(const aiMaterial &aMat, Material &mat,
			const std::string &prop, const float &def,
			const char *pKey, unsigned int type, unsigned int idx) {
		float fetched;
		aiReturn result = aMat.Get(pKey, type, idx, fetched);
		bool success = result == aiReturn::aiReturn_SUCCESS;

		if (success) {
			mat.getFloats().setValue(prop, fetched);
		} else {
			mat.getFloats().setValue(prop, def);
		}

		return success;
	}

	bool Model::fetchMaterialProperty(const aiMaterial &aMat, Material &mat,
			const std::string &prop, const Vector3f &def,
			const char *pKey, unsigned int type, unsigned int idx) {
		aiColor3D fetched;
		aiReturn result = aMat.Get(pKey, type, idx, fetched);
		bool success = result == aiReturn::aiReturn_SUCCESS;

		if (success) {
			mat.getVector3fs().setValue(
				prop, Vector3f(fetched.r, fetched.g, fetched.b));
		} else {
			mat.getVector3fs().setValue(prop, def);
		}

		return success;
	}

	bool Model::fetchMaterialTexture(const aiMaterial &aMat, Material &mat,
			const std::string &prop,
			const Honeycomb::Graphics::Texture2DCommonFillColor &def,
			const int &type) {
		bool success = false;
		aiTextureType aTT = (aiTextureType)(type); // Cast to ASSIMP type

		// If the material has the texture of this type
		if (aMat.GetTextureCount(aTT)) {
			// Fetch the directory of the texture
			aiString dir;
			aMat.GetTexture(aTT, 0, &dir);

			// If the image can be loaded, set the texture to the image data
			try {
				ImageIO image = ImageIO(dir.C_Str());
				auto texture = Texture2D::newTexture2DShared();
				texture->setImageDataIO(image);
				mat.getSampler2Ds().setValue(prop + ".sampler", texture);
				success = true;
			} 
			// Otherwise set the texture to the default common fill color
			catch (ImageIOLoadException e) {
				auto texture = Texture2D::getTextureCommonFill(def);
				mat.getSampler2Ds().setValue(prop + ".sampler", texture);
			}
		} 
		// If the material does not have the texture 
		else {
			// Set the previously initialized texture to default value
			auto texture = Texture2D::getTextureCommonFill(def);
			mat.getSampler2Ds().setValue(prop + ".sampler", texture);
		}

		// By default, set the intensity of the texture to 1.0F
		mat.getFloats().setValue(prop + ".intensity", 1.0F);
		return success;
	}

	void Model::loadFromPath() {
		// Import the Scene from ASSIMP and Check for Errors
		Importer aImp = Importer();
		this->scene = aImp.ReadFile(path, settings.toPFlags());
		if (this->scene == nullptr ||
				this->scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE ||
				this->scene->mRootNode == nullptr) {
			throw ModelLoadException(this->path, aImp.GetErrorString());
		}

		// Initialize the Model Game Object from the Scene Root node
		this->gameObject = this->processAiNode(this->scene->mRootNode);
	}

	std::shared_ptr<Material> Model::processAiMeshMaterial(aiMaterial* aMat) {
		std::shared_ptr<Material> material = std::make_shared<Material>();

		// Retrieve all of the Material properties from ASSIMP
		this->fetchMaterialProperty(*aMat, *material, "albedoColor",
				Vector3f(1.0F, 1.0F, 1.0F), AI_MATKEY_COLOR_DIFFUSE);
		this->fetchMaterialProperty(*aMat, *material, "ambientColor",
			Vector3f(1.0F, 1.0F, 1.0F), AI_MATKEY_COLOR_AMBIENT);
		this->fetchMaterialProperty(*aMat, *material, "specularColor",
			Vector3f(1.0F, 1.0F, 1.0F), AI_MATKEY_COLOR_SPECULAR);
		this->fetchMaterialProperty(*aMat, *material, "shininess",
			0.0F, AI_MATKEY_SHININESS);
		this->fetchMaterialProperty(*aMat, *material, "refractiveIndex",
			1.0F, AI_MATKEY_REFRACTI);
		this->fetchMaterialProperty(*aMat, *material, "reflectionStrength",
			0.0F, AI_MATKEY_REFRACTI);

		// Retrieve the Textures from ASSIMP
		this->fetchMaterialTexture(*aMat, *material, "albedoTexture",
			Texture2DCommonFillColor::COLOR_WHITE, 
			aiTextureType::aiTextureType_DIFFUSE);
		this->fetchMaterialTexture(*aMat, *material, "ambientTexture",
			Texture2DCommonFillColor::COLOR_WHITE,
			aiTextureType::aiTextureType_AMBIENT);
		this->fetchMaterialTexture(*aMat, *material, "specularTexture",
			Texture2DCommonFillColor::COLOR_WHITE,
			aiTextureType::aiTextureType_SPECULAR);
		this->fetchMaterialTexture(*aMat, *material, "normalsTexture",
			Texture2DCommonFillColor::COLOR_BLACK,
			aiTextureType::aiTextureType_NORMALS);
		this->fetchMaterialTexture(*aMat, *material, "displacementTexture",
			Texture2DCommonFillColor::COLOR_BLACK,
			aiTextureType::aiTextureType_DISPLACEMENT);

		// Special default value for diffuse map, this is always white by
		// default.
		auto diffuse = Texture2D::getTextureWhite();
		material->getSampler2Ds().setValue("diffuseTexture.sampler", diffuse);
		material->getFloats().setValue("diffuseTexture.intensity", 1.0F);
		material->getVector3fs().setValue("diffuseColor",
			Vector3f(1.0F, 1.0F, 1.0F));

		// Set global tiling and offset for all Material Textures
		material->getVector2fs().setValue("globalTiling", 
			Vector2f(1.0F, 1.0F));
		material->getVector2fs().setValue("globalOffset", 
			Vector2f(0.0F, 0.0F));

		return material;
	}

	std::shared_ptr<Mesh> Model::processAiMeshGeometry(aiMesh *aMesh) {
		std::vector<Vertex> vertices;            // Vertices Data
		std::vector<unsigned int> indices;       // Indices Data

		// Go through all the vertices of the Mesh
		for (unsigned int i = 0; i < aMesh->mNumVertices; i++) {
			// Get all of the needed properties of the vertex. If the vertex is
			// missing some property, give it a default constructed vector.
			// Note, for the tangents, if the Mesh is missing them, we should 
			// not use a default Vector3 of values { 0, 0, 0 } since this can 
			// cause some division by zero errors in the Shaders.
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

			// Go through all the indices of the Face and add them to the Mesh
			for (unsigned int j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}

		// Create a new Honeycomb Mesh with the fetched vertex and index data.
		std::unique_ptr<Mesh> mesh = Mesh::newMeshUnique();
		mesh->setVertexData(vertices);
		mesh->setIndexData(indices);
		return mesh;
	}

	std::unique_ptr<GameObject> Model::processAiNode(aiNode *aNode) {
		// If this is a child of the scene's RootNode, then scale it according
		// to the settings' scaling factor since its position is global. Else,
		// the position is local and the local scale is fetched from Transform.
		float lclSclFactor = (aNode->mParent == this->scene->mRootNode) ?
			this->settings.scaleFactor : 1.0F;

		// Create the GameObject representing this node
		std::unique_ptr<GameObject> object = std::make_unique<GameObject>(
				aNode->mName.C_Str());

		// Fetch the Transformation of the Object and write to the Transform.
		// Note that the scale is unused since ASSIMP scales the vertex 
		// positions.
		aiQuaterniont<float> rotation;
		aiVector3D position;
		aiVector3D scale;
		auto &transf = object->getComponent<Transform>();
		aNode->mTransformation.Decompose(scale, rotation, position);
		transf.setRotation(Quaternion(rotation.x, rotation.y, rotation.z,
			rotation.w));
		transf.setTranslation(Vector3f(position.x, position.y, position.z) *
			lclSclFactor, Space::LOCAL);

		// Create a Mesh Renderer for the Game Object and add all of the meshes
		// and materials of the ASSIMP node. As long as we had at least one
		// mesh, add the MeshRenderer component to the Game Object.
		auto meshRen = std::make_unique<MeshRenderer>();
		for (unsigned int i = 0; i < aNode->mNumMeshes; i++) {
			// Convert the ASSIMP Mesh Geometry into Honeycomb Mesh Geometry
			aiMesh *aMesh = this->scene->mMeshes[aNode->mMeshes[i]];
			std::shared_ptr<Mesh> mesh = this->processAiMeshGeometry(aMesh);
			
			// Convert the ASSIMP Mesh Material into Honeycomb Mesh Material
			aiMaterial *aMat;
			std::shared_ptr<Material> mat;
			if (aMesh->mMaterialIndex >= 0) { // Get Material, if it exists
				aMat = this->scene->mMaterials[aMesh->mMaterialIndex];
				mat = this->processAiMeshMaterial(aMat);
			} else {                          // Else, use a default Material
				mat = std::shared_ptr<Material>(new Material());
			}

			meshRen->addMaterial(mat);
			meshRen->addMesh(mesh);
		}
		if (aNode->mNumMeshes > 0) object->addComponent(std::move(meshRen));

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

	const char* ModelLoadException::what() const noexcept {
		std::ostringstream oss("");
		oss << std::runtime_error::what() << " from directory " <<
			this->directory << " | " << this->assimpError;
		return oss.str().c_str();
	}
} }
