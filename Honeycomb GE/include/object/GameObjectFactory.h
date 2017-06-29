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
		std::unique_ptr<Honeycomb::Object::GameObject> newAmbientLight();

		/// <summary>
		/// Builds a new Camera Game Object. The Game Object will have the name
		/// "Camera" and will have Transform and Camera Controller components
		/// attached to it.
		/// </summary>
		/// <returns>
		/// The pointer to the new Camera Object.
		/// </returns>
		std::unique_ptr<Honeycomb::Object::GameObject> newCamera();

		/// <summary>
		/// Builds a new Cone Game Object. The Game Object will have the name
		/// "Cone" and will have the Transform and Mesh Renderer components
		/// attached to it. The mesh and material data for the Cone will come
		/// from the cone model file.
		/// </summary>
		/// <returns>
		/// The pointer to the Cone Object.
		/// </returns>
		std::unique_ptr<Honeycomb::Object::GameObject> newCone();

		/// <summary>
		/// Builds a new Directional Light Game Object. The Game Object will
		/// have the name "Directional Light" and will have the Transform and
		/// Directional Light components attached to it.
		/// </summary>
		/// <returns>
		/// The pointer to the Directional Light Object.
		/// </returns>
		std::unique_ptr<Honeycomb::Object::GameObject> newDirectionalLight();

		/// <summary>
		/// Builds a new Cube Game Object. The Game Object will have the name
		/// "Cube" and will have the Transform and Mesh Renderer components
		/// attached to it. The mesh and material data for the Cube will come
		/// from the cube model file.
		/// </summary>
		/// <returns>
		/// The pointer to the Cube Object.
		/// </returns>
		std::unique_ptr<Honeycomb::Object::GameObject> newCube();

		/// <summary>
		/// Creates a new Game Object from the specified Model.
		/// </summary>
		/// <param name="model">
		/// The model, from which the Game Object should be made.
		/// </param>
		/// <returns>
		/// The unique pointer to the cloned Game Object of the model.
		/// </returns>
		std::unique_ptr<Honeycomb::Object::GameObject> newGameObject(const 
				Honeycomb::Geometry::Model &model);

		/// <summary>
		/// Builds a new Icosphere Game Object. The Game Object will have the 
		/// name "Icosphere" and will have the Transform and Mesh Renderer 
		/// components attached to it. The mesh and material data for the 
		/// Icosphere will come from the icosphere model file.
		/// </summary>
		/// <returns>
		/// The pointer to the Icosphere Object.
		/// </returns>
		std::unique_ptr<Honeycomb::Object::GameObject> newIcosphere();

		/// <summary>
		/// Builds a new Plane Game Object. The Game Object will have the 
		/// name "Plane" and will have the Transform and Mesh Renderer 
		/// components attached to it. The mesh and material data for the 
		/// Plane will come from the plane model file.
		/// </summary>
		/// <returns>
		/// The pointer to the Plane Object.
		/// </returns>
		std::unique_ptr<Honeycomb::Object::GameObject> newPlane();

		/// <summary>
		/// Builds a new Point Light Game Object. The Game Object will have the
		/// name "Point Light" and will have the Transform and Point Light 
		/// components attached to it.
		/// </summary>
		/// <returns>
		/// The pointer to the Point Light Object.
		/// </returns>
		std::unique_ptr<Honeycomb::Object::GameObject> newPointLight();

		/// <summary>
		/// Builds a new Sphere Game Object. The Game Object will have the 
		/// name "Sphere" and will have the Transform and Mesh Renderer 
		/// components attached to it. The mesh and material data for the 
		/// Sphere will come from the sphere model file.
		/// </summary>
		/// <returns>
		/// The pointer to the Sphere Object.
		/// </returns>
		std::unique_ptr<Honeycomb::Object::GameObject> newSphere();

		/// <summary>
		/// Builds a new Spot Light Game Object. The Game Object will have the
		/// name "Spot Light" and will have the Transform and Spot Light 
		/// components attached to it.
		/// </summary>
		/// <returns>
		/// The pointer to the Spot Light Object.
		/// </returns>
		std::unique_ptr<Honeycomb::Object::GameObject> newSpotLight();

		/// <summary>
		/// Builds a new Suzanne Game Object. The Game Object will have the 
		/// name "Suzanne" and will have the Transform and Mesh Renderer 
		/// components attached to it. The mesh and material data for the 
		/// Suzanne will come from the suzanne model file.
		/// </summary>
		/// <returns>
		/// The pointer to the Sphere Object.
		/// </returns>
		std::unique_ptr<Honeycomb::Object::GameObject> newSuzanne();
	private:
		/// <summary>
		/// Helper method for loading in default models. This creates an object
		/// clone from the specified model and then fetches the child of the
		/// specified name and deparents it from the RootNode. The independent
		/// child is then returned.
		/// </summary>
		/// <param name="model">
		/// The model from which the Game Object is to be cloned.
		/// </param>
		/// <param name="name">
		/// The name of the child of the RootNode.
		/// </param>
		/// <returns>
		/// The unique pointer to the imported Game Object clone.
		/// </returns>
		std::unique_ptr<GameObject> newDefaultImport(
				const Honeycomb::Geometry::Model &model,
				const std::string &name);
	};
} }

#endif
