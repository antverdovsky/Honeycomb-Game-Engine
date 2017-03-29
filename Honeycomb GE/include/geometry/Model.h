#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "Mesh.h"
#include "..\object\GameObject.h"
#include "..\component\render\MeshRenderer.h"
#include "..\graphics\Material.h"
#include "..\graphics\Texture2D.h"

struct aiMaterial;
struct aiMesh;
struct aiNode;
struct aiScene;

enum aiTextureType;

namespace Honeycomb::Geometry {
	struct ModelSettings {
		friend class Model;
	public:
		float scaleFactor; // The scale factor of the Model

		bool calcTangentSpace; // Calculate tangent space for imported models?
		bool joinDuplicateVertices; // Should duplicate vertices be joined?
		bool makeLeftHanded; // Should the coordinate system be left-handed?
		bool triangulate; // Should the model be triangulated?
		bool genNormals; // Should normals be generated?
		bool genSmoothNormals; // Should smooth normals be generated?
		bool splitLargeMeshes; // Should large meshes be split?
		bool preTransformVertices; // Should all vertices be pretransformed?
		bool delUnusedMaterials; // Remove redundant materials?
		bool fixInfacingNormals; // Fix normals facing inwards?
		bool genUVCoords; // Generate UV coordinates for non-UV mappings?
		bool transformUVCoords; // Transform UV Coordinates?
		bool optimizeMesh; // Optimize the mesh?
		bool optimizeGraph; // Optimize the scene graph?
		bool flipUVs; // Flip the UV coordinates along y-axis?
		bool flipWindingOrder; // Flip Face Winding Order to CW?

		/// Sets the Model Settings to their Default Settings:
		/// scaleFactor = 0.01F;
		/// calcTangentSpace = true;
		/// joinDuplicateVertices = true;
		/// makeLeftHanded = false;
		/// triangulate = true;
		/// genNormals = false;
		/// genSmoothNormals = true;
		/// splitLargeMeshes = true;
		/// preTransformVertices = false;
		/// delUnusedMaterials = false;
		/// fixInfacingNormals = false;
		/// genUVCoords = false;
		/// transformUVCoords = false;
		/// optimizeMesh = true;
		/// optimizeGraph = false;
		/// flipUVs = true;
		/// flipWindingOrder = false;
		ModelSettings() {
			this->scaleFactor = 0.01F;

			this->calcTangentSpace = true;
			this->joinDuplicateVertices = true;
			this->makeLeftHanded = false;
			this->triangulate = true;
			this->genNormals = false;
			this->genSmoothNormals = true;
			this->splitLargeMeshes = true;
			this->preTransformVertices = false;
			this->delUnusedMaterials = false;
			this->fixInfacingNormals = false;
			this->genUVCoords = false;
			this->transformUVCoords = false;
			this->optimizeMesh = true;
			this->optimizeGraph = false;
			this->flipUVs = true;
			this->flipWindingOrder = false;
		}

		/// Checks if these model settings are equal to the specified model
		/// settings.
		/// const ModelSettings &that : The model settings which are to be
		///							    compared to these model settings.
		/// return : True if the model settings are equal; False otherwise.
		bool operator== (const ModelSettings &that);
	private:
		/// Converts the Model Settings to PFlags which may be used by ASSIMP.
		/// return : The PFlags.
		unsigned int toPFlags() const;
	};

	class Model {
	public:
		/// Deletes this model, and the materials / textures imported from it.
		~Model();

		/// Loads a model from the specified path and returns it. If the model
		/// has previously been imported, the model will be returned but not 
		/// re-imported to prevent duplication. The settings will only be used
		/// if the model has not been previously imported.
		/// const std::string &path : The path to the model.
		static const Model& loadModel(const std::string &path, 
				const ModelSettings &settings = ModelSettings());

		/// Returns the Game Object loaded in from the Model. This game object
		/// is directly linked to the Model and IS NOT independent of the
		/// Model. Modifying this object will result in the modification of all
		/// future clones of this Game Object.
		/// return : The loaded Game Object.
		Honeycomb::Object::GameObject* getGameObject();

		/// Returns a Clone of the loaded Game Object. The game object will be
		/// completely independent, with its own unique children and 
		/// components, and it does not depend on the Model in any way.
		/// return : A clone of the loaded Game Object.
		Honeycomb::Object::GameObject* getGameObjectClone() const;

		/// Gets the system path to the file from which the Model was loaded.
		/// return : The string containing the system path.
		const std::string& getPath() const;

		/// TO BE IMPLEMENTED:
		/// void reloadModel(const ModelSettings &settings);
	private:
		static std::vector<Model*> imports; // All imported models

		const aiScene* scene; // The ASSIMP Scene for this model
		std::string path; // The system path to the model
		Honeycomb::Object::GameObject *gameObject; // The built model object

		// These refer to the initialized components from the imported data.
		// All game objects built from this model will reference these in some
		// form.
		std::vector<const Honeycomb::Geometry::Mesh*> meshes;
		std::vector<const Honeycomb::Graphics::Texture2D*> textures;
		std::vector<const Honeycomb::Graphics::Material*> materials;

		ModelSettings settings; // The settings used to import this model

		/// Initializes a new Model from the specified file path.
		/// const std::string &path : The system file path to the model.
		/// const ModelSettings &settings : The settings to be used when
		///									importing the model.
		Model(const std::string &path, const ModelSettings &settings);

		/// Fetches the texture of the specified texture type from the 
		///	specified ASSIMP material.
		/// const aiMaterial &mat : The ASSIMP Material.
		/// aiTextureType tT : The texture type.
		/// const int &r : The red component of the texture to be set to
		///				   the color of the texture IF the texture does
		///				   cannot be imported. Bounded to [0, 255].
		/// const int &g : The green component of the texture to be set to
		///				   the color of the texture IF the texture does
		///				   cannot be imported. Bounded to [0, 255].
		/// const int &b : The blue component of the texture to be set to
		///				   the color of the texture IF the texture does
		///				   cannot be imported. Bounded to [0, 255].
		/// return : The initialized and ready to be used Texture. If the
		///			 material does not contain the texture of the specified
		///			 type, a 1x1 pixel set to the specified color (white by
		///			 default) is returned instead.
		Honeycomb::Graphics::Texture2D* fetchTexture(const aiMaterial &mat, 
				aiTextureType tT, const int &r = 255, const int &g = 255,
				const int &b = 255);

		/// Loads the model object from the file path and using settings stored
		/// in this Model.
		void loadFromPath();

		/// Converts the ASSIMP Node into a Honeycomb GameObject, and returns
		/// the GameObject instance. Each child node of the ASSIMP node will
		/// also be converted into a GameObject, and parented to the returned
		/// instance, recursively. All Objects will be equipped with a
		/// Transform, and those which contain Mesh data will be equipped with
		/// a MeshRenderer component.
		/// aiNode *aNode : The ASSIMP node to be processed into a Honeycomb
		///					GameObject.
		/// return : The dynamically allocated Honeycomb GameObject instance,
		///			 containing the information extracted from the ASSIMP node.
		Honeycomb::Object::GameObject* processAiNode(aiNode *aNode);

		/// Converts the ASSIMP Material into a Honeycomb Material, and returns
		/// the Material instance.
		/// aiMaterial *aMat : The ASSIMP Material to be converted into a
		///					   Honeycomb Material.
		/// return : The dynamically allocated Honeycomb Material instance,
		///			 containing the information extracted from the ASSIMP 
		///			 Material.
		Honeycomb::Graphics::Material* processAiMeshMaterial(aiMaterial *aMat);

		/// Converts the ASSIMP Mesh into a Honeycomb Mesh, and returns the 
		/// Mesh instance.
		/// aiMesh *aMesh : The ASSIMP Mesh to be converted into a Honeycomb 
		///					Mesh.
		/// return : The dynamically allocated Honeycomb Mesh instance,
		///			 containing the information extracted from the ASSIMP 
		///			 Mesh.
		Honeycomb::Geometry::Mesh* processAiMeshGeometry(aiMesh *aMesh);
	};
}

#endif