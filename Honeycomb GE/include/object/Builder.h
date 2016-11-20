#pragma once
#ifndef BUILDER_H
#define BUILDER_H

#include "GameObject.h"
#include "..\geometry\Model.h"

#include <map>

namespace Honeycomb::Object {
	class Builder {
	public:
		/// Destructs this Builder instance.
		~Builder();

		/// Gets the Builder Singleton instance.
		/// return : The Builder instance.
		static Builder* getBuilder();

		/// Builds a new Ambient Light GameObject. The game object will simply
		/// be the object named "Ambient Light", with a Transform and Ambient
		/// Light components attached to it. Both the Transform and Ambient
		/// Light components will be the default components.
		/// return : The new Ambient Light Object.
		GameObject* newAmbientLight();

		/// Builds a new Camera GameObject. The game object will simply be the
		/// object named "Camera", with a Transform and Camera Controller
		/// components attached to it. Both the Transform and Camera Controller
		/// components will be the default components.
		/// return : The new Camera object.
		GameObject* newCamera();

		/// Builds a new Directional Light GameObject. The game object will 
		/// simply be the object named "Directional Light", with a Transform 
		/// and Directional Light components attached to it. Both the Transform
		/// and Directional Light components will be the default components.
		/// return : The new Directional Light Object.
		GameObject* newDirectionalLight();

		/// Builds a new Cube GameObject. The game object will simply be the
		/// object named "Cube", with a MeshRenderer and Transform attached to
		/// it. The Mesh and Material data will come from the file from which 
		/// the Builder imports the cube.
		/// return : The new Cube Game Object.
		GameObject* newCube();

		/// Builds a new Plane GameObject. The game object will simply be the
		/// object named "Plane", with a MeshRenderer and Transform attached to
		/// it. The Mesh and Material data will come from the file from which 
		/// the Builder imports the plane.
		/// return : The new Plane Game Object.
		GameObject* newPlane();

		/// Builds a new Sphere GameObject. The game object will simply be the
		/// object named "Sphere", with a MeshRenderer and Transform attached 
		/// to it. The Mesh and Material data will come from the file from 
		/// which the Builder imports the sphere.
		/// return : The new Sphere Game Object.
		GameObject* newSphere();

		/// Imports a new model from the specified path and constructs a game
		/// object from it. The game object will be the the root node of the
		/// model, with all the individual objects parented to the root node.
		/// Each object in the hierarchy will receive the Transform component,
		/// and all meshes in the hierarchy will receive the Mesh Renderer
		/// component, initialized to the data extracted from the Model file.
		/// If the model has been previously imported, a copy of the game obj.
		/// from that model will be returned, rather than re-importing the 
		/// entire model again.
		/// return : The constructed Game Object.
		GameObject* newObjectWithPath(std::string path);
	private:
		static Builder *instance; // The Builder Singleton instance

		// Location of all of the Default Models
		const static std::string CUBE_LOCATION;
		const static std::string PLANE_LOCATION;
		const static std::string SPHERE_LOCATION;

		// Lists of the imported models and import objects. If a request is
		// received to build a model or object which has already been built, a
		// copy of it from one of these lists will be returned instead.
		std::vector<Honeycomb::Object::GameObject*> builtObjects;
		std::vector<Honeycomb::Geometry::Model*> importedModels;

		/// Constructs a new Builder instance.
		Builder();

		/// Finds the Model in the imported models list, if the model has been
		/// imported, with the matching path and returns it. If the model has 
		/// not yet been imported, a nullptr will be returned instead.
		/// return : The Model in the imported models list, or a nullptr if the
		///			 model has not yet been imported.
		Honeycomb::Geometry::Model* findModel(std::string path);

		/// Finds the Game Object in the build objects list, if the object has
		/// been built, with the matching name and returns it. If the object
		/// has not yet been built, a nullptr will be returned instead.
		Honeycomb::Object::GameObject* findObject(std::string name);

		/// Helper method for importing the default objects. The name refers to
		/// the name of the default object which is to be imported, and the
		/// path refers to where the object is to be imported from. If the
		/// object has already been built, a clone will be returned. Otherwise,
		/// the object will be imported and the clone of the import will be
		/// returned instead.
		/// string name : The name of the default object.
		Honeycomb::Object::GameObject* newImport(std::string name,
			std::string path);
	};
}

#endif