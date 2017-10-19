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
		/// <summary>
		/// Initializes a new Model instance and loads the model from the
		/// specified file. The model is loaded in using the default settings,
		/// using the default instance of the Model Settings class.
		/// 
		/// If the model could not be loaded for some reason, a 
		/// ModelLoadException is thrown.
		/// </summary>
		/// <param name="path">
		/// The path to the file.
		/// </param>
		/// <param name="settings">
		/// The settings to be used when loading in the Model. By default, the
		/// default instance of the Model is used.
		/// </param>
		/// <exception cref="ModelLoadException">
		/// Thrown if the model could not be loaded.
		/// </exception>
		Model(const std::string &path, const ModelSettings &settings = 
				ModelSettings());

		/// <summary>
		/// Returns a clone of the loaded in model Game Object. The clone will
		/// be independent and not attached to any scene or parent.
		/// </summary>
		/// <returns>
		/// The unique pointer to the clone.
		/// </returns>
		std::unique_ptr<Honeycomb::Object::GameObject> getGameObjectClone() 
				const;

		/// <summary>
		/// Gets the path from which this Model was loaded in from.
		/// </summary>
		/// <returns>
		/// The path string.
		/// </returns>
		const std::string& getPath() const;
	private:
		std::string path;           // The system path to the model
		ModelSettings settings;     // The settings used to import this model

		const aiScene* scene;       // Pointer to ASSIMP scene

		// The constructed Game Object. All Game Object clones returned from
		// this instance are clones of this Game Object.
		std::unique_ptr<Honeycomb::Object::GameObject> gameObject;

		/// <summary>
		/// Fetches the specified float material property from the given
		/// ASSIMP material and writes it to the specified Honeycomb material.
		/// 
		/// Note that the "pKey", "type", and "idx" arguments should be passed
		/// via then AI_MATKEY_&lt__PROPERTY__&gt value.
		/// </summary>
		/// <param name="aMat">
		/// The ASSIMP material from which the property should be extracted 
		/// from.
		/// </param>
		/// <param name="mat">
		/// The Honeycomb material, passed by reference, to which the material
		/// property should be written to.
		/// </param>
		/// <param name="prop">
		/// The name of the property, as it appears in the material's variable
		/// maps, for which the fetched property value is to be written for.
		/// </param>
		/// <param name="def">
		/// The default value to be written to the material property if the
		/// material does not contain the property requested.
		/// </param>
		/// <param name="pKey">
		/// The ASSIMP property key (use AI_MATKEY_&lt__PROPERTY__&gt).
		/// </param>
		/// <param name="type">
		/// The ASSIMP property type.
		/// </param>
		/// <param name="idx">
		/// The ASSIMP property index.
		/// </param>
		/// <returns>
		/// True if the property was successfully fetched and written to the
		/// material. False if the property could not be fetched and the 
		/// default value was written to the material instead.
		/// </returns>
		bool fetchMaterialProperty(
				const aiMaterial &aMat, Honeycomb::Graphics::Material &mat,
				const std::string &prop, const float &def,
				const char *pKey, unsigned int type, unsigned int idx);

		/// <summary>
		/// Fetches the specified Vector3f material property from the given
		/// ASSIMP material and writes it to the specified Honeycomb material.
		/// 
		/// Note that the "pKey", "type", and "idx" arguments should be passed
		/// via then AI_MATKEY_&lt__PROPERTY__&gt value.
		/// </summary>
		/// <param name="aMat">
		/// The ASSIMP material from which the property should be extracted 
		/// from.
		/// </param>
		/// <param name="mat">
		/// The Honeycomb material, passed by reference, to which the material
		/// property should be written to.
		/// </param>
		/// <param name="prop">
		/// The name of the property, as it appears in the material's variable
		/// maps, for which the fetched property value is to be written for.
		/// </param>
		/// <param name="def">
		/// The default value to be written to the material property if the
		/// material does not contain the property requested.
		/// </param>
		/// <param name="pKey">
		/// The ASSIMP property key (use AI_MATKEY_&lt__PROPERTY__&gt).
		/// </param>
		/// <param name="type">
		/// The ASSIMP property type.
		/// </param>
		/// <param name="idx">
		/// The ASSIMP property index.
		/// </param>
		/// <returns>
		/// True if the property was successfully fetched and written to the
		/// material. False if the property could not be fetched and the 
		/// default value was written to the material instead.
		/// </returns>
		bool fetchMaterialProperty(
				const aiMaterial &aMat, Honeycomb::Graphics::Material &mat,
				const std::string &prop, const Honeycomb::Math::Vector3f &def,
				const char *pKey, unsigned int type, unsigned int idx);

		/// <summary>
		/// Fetches the specified material texture from the given ASSIMP
		/// material and writes it to the specified Honeycomb material.
		/// </summary>
		/// <param name="aMat">
		/// The ASSIMP material from which the property should be extracted
		/// from.
		/// </param>
		/// <param name="mat">
		/// The Honeycomb material, passed by reference to which the material
		/// texture should be written to.
		/// </param>
		/// <param name="prop">
		/// The name of the texture, as it appears in the material's variable
		/// map, for which the fetched texture is to be written for.
		/// </param>
		/// <param name="def">
		/// If the material texture could not be fetched, this default color
		/// will be written to the material instead.
		/// </param>
		/// <param name="type">
		/// The ASSIMP type of texture to be fetched.
		/// </param>
		/// <returns>
		/// True if the texture was successfully fetched and written to the
		/// material. False if the texture could not be fetched and the
		/// default value was written to the material instead.
		/// </returns>
		bool fetchMaterialTexture(
				const aiMaterial &aMat, Honeycomb::Graphics::Material &mat,
				const std::string &prop,
				const Honeycomb::Graphics::Texture2DCommonFillColor &def,
				const int &type);

		/// <summary>
		/// Loads this model from the path stored in this instance using the
		/// model settings stored in this instance.
		/// </summary>
		/// <exception cref="ModelLoadException">
		/// Thrown if the Model could not be loaded from the path.
		/// </exception>
		void loadFromPath();

		/// <summary>
		/// Creates a Honeycomb Mesh from the specified ASSIMP Mesh. The mesh
		/// will contain the vertex positions, normals, tangents and index zero
		/// texture coordinates for each vertex of the ASSIMP mesh.
		/// </summary>
		/// <param name="aMesh">
		/// The ASSIMP mesh which is to be converted to a Game Object.
		/// </param>
		/// <returns>
		/// The shared pointer to the Honeycomb Mesh.
		/// </returns>
		std::shared_ptr<Honeycomb::Geometry::Mesh> processAiMeshGeometry(
				aiMesh *aMesh);

		/// <summary>
		/// Creates a Honeycomb Material from the specified ASSIMP material.
		/// The Honeycomb Material will be initialized using the Standard
		/// Honeycomb Material and will have all of its properties initialized
		/// to the ASSIMP material's values, if possible. If a particular value
		/// cannot be fetched from the ASSIMP material, it will be default
		/// constructed.
		/// </summary>
		/// <param name="aMat">
		/// The ASSIMP material which is to be converted to a Game Object.
		/// </param>
		/// <returns>
		/// The shared pointer to the Honeycomb Material.
		/// </returns>
		std::shared_ptr<Honeycomb::Graphics::Material> processAiMeshMaterial(
			aiMaterial *aMat);

		/// <summary>
		/// Creates a Honeycomb Game Object from the specified ASSIMP node. 
		/// The Game Object will contain a Transform component containing the
		/// imported transformation of the ASSIMP node. If the ASSIMP node has
		/// a Mesh attached to it, a MeshRenderer component will also be
		/// attached, containing the Meshes and Materials of the ASSIMP node.
		/// For any children ASSIMP nodes of the specified node, they will be
		/// converted to Game Objects as well (recursively) and be added as
		/// children to this Game Object.
		/// </summary>
		/// <param name="aNode">
		/// The ASSIMP node who is to be converted to a Game Object.
		/// </param>
		/// <returns>
		/// The unique pointer to the Honeycomb Game Object.
		/// </returns>
		std::unique_ptr<Honeycomb::Object::GameObject> processAiNode(
				aiNode *aNode);
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
		virtual const char* what() const noexcept;
	private:
		std::string directory;
		std::string assimpError;
	};
} }

#endif
