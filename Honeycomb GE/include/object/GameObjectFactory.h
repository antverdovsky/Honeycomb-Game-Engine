#pragma once
#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H

#include "GameObject.h"
#include "../geometry/Model.h"

namespace Honeycomb { namespace Object {
	class GameObjectFactory {
	public:
		/// <summary>
		/// Gets the singleton instance of the Game Object Factory.
		/// </summary>
		/// <returns>
		/// The reference to the instance of the Game Object Factory.
		/// </returns>
		static GameObjectFactory& getFactory();

		/// <summary>
		/// Builds a new Ambient Light Game Object. The Game Object will have
		/// the name "Ambient Light" and will have Transform and Ambient Light
		/// components attached to it.
		/// </summary>
		/// <returns>
		/// The pointer to the new Ambient Light Object.
		/// </returns>
		std::unique_ptr<GameObject> newAmbientLight();

		/// <summary>
		/// Builds a new Camera Game Object. The Game Object will have the name
		/// "Camera" and will have Transform and Camera Controller components
		/// attached to it.
		/// </summary>
		/// <returns>
		/// The pointer to the new Camera Object.
		/// </returns>
		std::unique_ptr<GameObject> newCamera();

		/// <summary>
		/// Builds a new Cone Game Object. The Game Object will have the name
		/// "Cone" and will have the Transform and Mesh Renderer components
		/// attached to it. The mesh and material data for the Cone will come
		/// from the cone model file.
		/// </summary>
		/// <returns>
		/// The pointer to the Cone Object.
		/// </returns>
		std::unique_ptr<GameObject> newCone();

		/// <summary>
		/// Builds a new Directional Light Game Object. The Game Object will
		/// have the name "Directional Light" and will have the Transform and
		/// Directional Light components attached to it.
		/// </summary>
		/// <returns>
		/// The pointer to the Directional Light Object.
		/// </returns>
		std::unique_ptr<GameObject> newDirectionalLight();

		/// <summary>
		/// Builds a new Cube Game Object. The Game Object will have the name
		/// "Cube" and will have the Transform and Mesh Renderer components
		/// attached to it. The mesh and material data for the Cube will come
		/// from the cube model file.
		/// </summary>
		/// <returns>
		/// The pointer to the Cube Object.
		/// </returns>
		std::unique_ptr<GameObject> newCube();

		/// <summary>
		/// Builds a new Icosphere Game Object. The Game Object will have the 
		/// name "Icosphere" and will have the Transform and Mesh Renderer 
		/// components attached to it. The mesh and material data for the 
		/// Icosphere will come from the icosphere model file.
		/// </summary>
		/// <returns>
		/// The pointer to the Icosphere Object.
		/// </returns>
		std::unique_ptr<GameObject> newIcosphere();

//TODO
		/// Imports a new model from the specified path and constructs a game
		/// object from it. The game object will be the the root node of the
		/// model, with all the individual objects parented to the root node.
		/// Each object in the hierarchy will receive the Transform component,
		/// and all meshes in the hierarchy will receive the Mesh Renderer
		/// component, initialized to the data extracted from the Model file.
		/// If the model has been previously imported, a copy of the game obj.
		/// from that model will be returned, rather than re-importing the 
		/// entire model again. If the model has not been previously imported,
		/// it will be imported and the settings specified will be used when
		/// importing.
		/// const std::string &path : The path of the Model.
		/// const ModelSettings &settings : The settings to be used for
		///								    importing the model.
		/// return : The constructed Game Object.
		std::unique_ptr<GameObject> newModel(const std::string &path,
			const Honeycomb::Geometry::ModelSettings &settings = 
			Honeycomb::Geometry::ModelSettings());
//TODO

		/// <summary>
		/// Builds a new Plane Game Object. The Game Object will have the 
		/// name "Plane" and will have the Transform and Mesh Renderer 
		/// components attached to it. The mesh and material data for the 
		/// Plane will come from the plane model file.
		/// </summary>
		/// <returns>
		/// The pointer to the Plane Object.
		/// </returns>
		std::unique_ptr<GameObject> newPlane();

		/// <summary>
		/// Builds a new Point Light Game Object. The Game Object will have the
		/// name "Point Light" and will have the Transform and Point Light 
		/// components attached to it.
		/// </summary>
		/// <returns>
		/// The pointer to the Point Light Object.
		/// </returns>
		std::unique_ptr<GameObject> newPointLight();

		/// <summary>
		/// Builds a new Sphere Game Object. The Game Object will have the 
		/// name "Sphere" and will have the Transform and Mesh Renderer 
		/// components attached to it. The mesh and material data for the 
		/// Sphere will come from the sphere model file.
		/// </summary>
		/// <returns>
		/// The pointer to the Sphere Object.
		/// </returns>
		std::unique_ptr<GameObject> newSphere();

		/// <summary>
		/// Builds a new Spot Light Game Object. The Game Object will have the
		/// name "Spot Light" and will have the Transform and Spot Light 
		/// components attached to it.
		/// </summary>
		/// <returns>
		/// The pointer to the Spot Light Object.
		/// </returns>
		std::unique_ptr<GameObject> newSpotLight();

		/// <summary>
		/// Builds a new Suzanne Game Object. The Game Object will have the 
		/// name "Suzanne" and will have the Transform and Mesh Renderer 
		/// components attached to it. The mesh and material data for the 
		/// Suzanne will come from the suzanne model file.
		/// </summary>
		/// <returns>
		/// The pointer to the Sphere Object.
		/// </returns>
		std::unique_ptr<GameObject> newSuzanne();
	private:
		// File Location of all of the Default Models
		const static std::string CONE_LOCATION;
		const static std::string CUBE_LOCATION;
		const static std::string ICOSPHERE_LOCATION;
		const static std::string PLANE_LOCATION;
		const static std::string SPHERE_LOCATION;
		const static std::string SUZANNE_LOCATION;
		
		/// <summary>
		/// Helper method for loading in default models. For the model path and
		/// name specified, this method will clone the model's game object and
		/// return a copy of the child game object containing the default model
		/// (i.e. stripping the root and returning only the child).
		/// </summary>
		/// <param name="name">
		/// The name of the model (this must be equivalent to the name of the
		/// child of the Game Object).
		/// </param>
		/// <param name="path">
		/// The path from which the model should be loaded.
		/// </param>
		/// <returns></returns>
		std::unique_ptr<GameObject> newDefaultImport(const std::string &name,
				const std::string &path);
	};
} }

#endif
