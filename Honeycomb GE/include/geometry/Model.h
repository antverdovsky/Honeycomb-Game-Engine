#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "Mesh.h"
#include "../object/GameObject.h"
#include "../component/render/MeshRenderer.h"
#include "../graphics/Material.h"
#include "../graphics/Texture2D.h"

struct aiMaterial;
struct aiMesh;
struct aiNode;
struct aiScene;

namespace Honeycomb { namespace Geometry {
	/// <summary>
	/// Simple struct which stores all of the the different settings using
	/// which a Model can be loaded.
	/// </summary>
	struct ModelSettings {
		friend class Model;
	public:
		float scaleFactor;             // The scale factor of the Model

		bool calcTangentSpace;         // Calculate tangent space?
		bool joinDuplicateVertices;    // Should duplicate vertices be joined?
		bool makeLeftHanded;           // Should coord. system be left-handed?
		bool triangulate;              // Should the model be triangulated?
		bool genNormals;               // Should normals be generated?
		bool genSmoothNormals;         // Should smooth normals be generated?
		bool splitLargeMeshes;         // Should large meshes be split?
		bool preTransformVertices;     // Should vertices be pretransformed?
		bool delUnusedMaterials;       // Remove redundant materials?
		bool fixInfacingNormals;       // Fix normals facing inwards?
		bool genUVCoords;              // Generate UV coordinates?
		bool transformUVCoords;        // Transform UV Coordinates?
		bool optimizeMesh;             // Optimize the mesh?
		bool optimizeGraph;            // Optimize the scene graph?
		bool flipUVs;                  // Flip the UV coordinates along y-axis?
		bool flipWindingOrder;         // Flip Face Winding Order to CW?

		/// <summary>
		/// Creates a model settings structure with the following default
		/// settings:
		/// 
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
		/// </summary>
		ModelSettings();
	private:
		/// <summary>
		/// Converts the Model Settings to PFlags which can be used by ASSIMP.
		/// </summary>
		/// <returns></returns>
		unsigned int toPFlags() const;
	};

	/// <summary>
	/// Class representing a 3D model which was loaded in from file.
	/// </summary>
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
/*
		/// Returns the Game Object loaded in from the Model. This game object
		/// is directly linked to the Model and IS NOT independent of the
		/// Model. Modifying this object will result in the modification of all
		/// future clones of this Game Object.
		/// return : The loaded Game Object.
		Honeycomb::Object::GameObject* getGameObject();
*/
		/// Returns a Clone of the loaded Game Object. The game object will be
		/// completely independent, with its own unique children and 
		/// components, and it does not depend on the Model in any way.
		/// return : A clone of the loaded Game Object.
		std::unique_ptr<Honeycomb::Object::GameObject> getGameObjectClone() const;

		/// Gets the system path to the file from which the Model was loaded.
		/// return : The string containing the system path.
		const std::string& getPath() const;

		/// TO BE IMPLEMENTED:
		/// void reloadModel(const ModelSettings &settings);
	private:
		static std::vector<Model*> imports; // All imported models

		const aiScene* scene; // The ASSIMP Scene for this model
		std::string path; // The system path to the model
		std::unique_ptr<Honeycomb::Object::GameObject> gameObject; // The built model object

		// These refer to the initialized components from the imported data.
		// All game objects built from this model will reference these in some
		// form.
		std::vector<std::shared_ptr<const Honeycomb::Geometry::Mesh>> meshes;
		std::vector<std::shared_ptr<const Honeycomb::Graphics::Texture2D>> textures;
		std::vector<std::shared_ptr<const Honeycomb::Graphics::Material>> materials;

		ModelSettings settings; // The settings used to import this model

		/// Initializes a new Model from the specified file path.
		/// const std::string &path : The system file path to the model.
		/// const ModelSettings &settings : The settings to be used when
		///									importing the model.
		Model(const std::string &path, const ModelSettings &settings);

		/// Fetches the specified float property from the given material and
		/// writes it to the material. For the three parameters "pKey", "type",
		///	"idx", it is suggested that they are passed via 
		/// AI_MATKEY_<PROPERTY>.
		/// const aiMaterial &mat : The ASSIMP Material.
		/// const char *pKey : The string containing the name of the material
		///					   property.
		/// unsigned int type : The property type.
		/// unsigned int idx : The property index.
		/// Material &mat : The material to which the fetched property should
		///					be written to.
		/// const string &matUni : The name of the uniform in the Material.
		/// const float &def : If an error occurs, this will be the written to
		///					   the material.
		/// bool err : Logs a warning to the Honeycomb Logger if an error
		///			   occurs and this is true. No log otherwise.
		void fetchMaterialProperty(const aiMaterial &aMat, const char *pKey,
			unsigned int type, unsigned int idx, Honeycomb::Graphics::Material 
			&mat, const std::string &matUni, const float &def = 0.0F, 
			bool err = true);

		/// Fetches the specified Vector3 property from the given material and
		/// writes it to the specified material. For the three parameters 
		/// "pKey", "type", "idx", it is suggested that they are passed via 
		/// AI_MATKEY_<PROPERTY>.
		/// const aiMaterial &aMat : The ASSIMP Material.
		/// const char *pKey : The string containing the name of the material
		///					   property.
		/// unsigned int type : The property type.
		/// unsigned int idx : The property index.
		/// Material &mat : The material to write the texture to.
		/// const string &matUni : The name of the texture uniform in the
		///						   Material.
		/// const Vector3f &def : If an error occurs, this will be the value
		///						  written.
		/// bool err : Logs a warning to the Honeycomb Logger if an error
		///			   occurs and this is true. No log otherwise.
		void fetchMaterialProperty(const aiMaterial &aMat, const char *pKey, 
			unsigned int type, unsigned int idx, Honeycomb::Graphics::Material
			&mat, const std::string &matUni, const Honeycomb::Math::Vector3f 
			&def = Honeycomb::Math::Vector3f(), bool err = true);

		/// Fetches the texture of the specified texture type from the 
		///	specified ASSIMP material and writes it to the standard material.
		/// const aiMaterial &mat : The ASSIMP Material.
		/// const int &tT : The texture type we want to fetch.
		/// Material &mat : The material to which to write the texture.
		/// const string &matUni : The name of the texture uniform in the
		///						   Material.
		/// const int &r : The red component of the texture to be set to
		///				   the color of the texture IF the texture does
		///				   cannot be imported. Bounded to [0, 255].
		/// const int &g : The green component of the texture to be set to
		///				   the color of the texture IF the texture does
		///				   cannot be imported. Bounded to [0, 255].
		/// const int &b : The blue component of the texture to be set to
		///				   the color of the texture IF the texture does
		///				   cannot be imported. Bounded to [0, 255].
		void fetchMaterialTexture(const aiMaterial &aMat, const int &tT, 
			Honeycomb::Graphics::Material &mat, const std::string &matUni,
			const Honeycomb::Graphics::Texture2DCommonFillColor &defColor);

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
		std::unique_ptr<Honeycomb::Object::GameObject> processAiNode(aiNode *aNode);

		/// Converts the ASSIMP Material into a Honeycomb Material, and returns
		/// the Material instance.
		/// aiMaterial *aMat : The ASSIMP Material to be converted into a
		///					   Honeycomb Material.
		/// return : The dynamically allocated Honeycomb Material instance,
		///			 containing the information extracted from the ASSIMP 
		///			 Material.
		std::shared_ptr<Honeycomb::Graphics::Material> processAiMeshMaterial(aiMaterial *aMat);

		/// Converts the ASSIMP Mesh into a Honeycomb Mesh, and returns the 
		/// Mesh instance.
		/// aiMesh *aMesh : The ASSIMP Mesh to be converted into a Honeycomb 
		///					Mesh.
		/// return : The dynamically allocated Honeycomb Mesh instance,
		///			 containing the information extracted from the ASSIMP 
		///			 Mesh.
		std::shared_ptr<Honeycomb::Geometry::Mesh> processAiMeshGeometry(aiMesh *aMesh);
	};

	/// <summary>
	/// Represents an exception which is thrown when a Model cannot be loaded
	/// from the system directory.
	/// </summary>
	class ModelLoadException : public std::runtime_error {
	public:
		/// <summary>
		/// Creates a new Model Load Exception for the model which could not be
		/// loaded from the specified path.
		/// </summary>
		/// <param name="path">
		/// The path from which the model could not be loaded.
		/// </param>
		/// <param name="err">
		/// The error returned by ASSIMP which occured while the model was
		/// being loaded.
		/// </param>
		ModelLoadException(const std::string &path, const std::string &err);

		/// <summary>
		/// Returns a constant character string containing the description of
		/// the exception.
		/// </summary>
		/// <returns>
		/// The constant character string exception info containing the
		/// directory of the model which could not be loaded and the error
		/// returned by the ASSIMP library.
		/// </returns>
		virtual const char* what() const throw();
	private:
		std::string directory;
		std::string assimpError;
	};
} }

#endif
