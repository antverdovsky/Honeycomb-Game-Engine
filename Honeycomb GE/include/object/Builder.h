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
		GameObject* newModel(std::string path);
	private:
		static Builder *instance; // The Builder Singleton instance

		// Location of all of the Default Models
		const static std::string CUBE_LOCATION;
		const static std::string PLANE_LOCATION;
		const static std::string SPHERE_LOCATION;

		/// Helper method for loading in the default models (cube, plane, etc).
		/// A new object will be instantiated from the model imported from the
		/// path specified, and then a new object composed of the child of the
		/// imported object with the specified name will be returned. The model
		/// object will be destroyed.
		/// return : The child object, with the specified name, of the model
		///			 with the specified path.
		GameObject* newDefaultImport(std::string name, std::string path);

		/// Constructs a new Builder instance.
		Builder();
	};
}

#endif