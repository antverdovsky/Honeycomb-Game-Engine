#pragma once
#ifndef BUILDER_H
#define BUILDER_H

#include "GameObject.h"
#include "..\geometry\Model.h"

namespace Honeycomb::Object {
	class Builder {
	public:
		/// Destructs this Builder instance.
		~Builder();

		/// Gets the Builder Singleton instance.
		/// return : The Builder instance.
		static Builder* getBuilder();

		/// Builds a new Ambient Light GameObject. The game object will simply
		/// be the object named "Ambient Light", with Transform and Ambient
		/// Light components attached to it. Both components will use their
		/// default initializations.
		/// return : The new Ambient Light Object.
		GameObject* newAmbientLight();

		/// Builds a new Camera GameObject. The game object will simply be the
		/// object named "Camera", with Transform and Camera Controller
		/// components attached to it. Both components will use their
		/// default initializations.
		/// return : The new Camera object.
		GameObject* newCamera();

		/// Builds a new Directional Light GameObject. The game object will
		/// be the object named "Directional Light", with Transform and 
		/// Directional Light components attached to it. Both components will 
		/// use their default initializations.
		/// return : The new Directional Light Object.
		GameObject* newDirectionalLight();

		/// Builds a new Cube GameObject. The game object will simply be the
		/// object named "Cube", with MeshRenderer and Transform attached to
		/// it. The Mesh and Material data will come from the file from which 
		/// the Builder imports the cube.
		/// return : The new Cube Game Object.
		GameObject* newCube();

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

		/// Builds a new Plane GameObject. The game object will simply be the
		/// object named "Plane", with a MeshRenderer and Transform attached to
		/// it. The Mesh and Material data will come from the file from which 
		/// the Builder imports the plane
		/// return : The new Plane Game Object.
		GameObject* newPlane();

		/// Builds a new Point Light GameObject. The game object will be the
		/// object named "Point Light", with the PointLight and Transform 
		/// components attached to it. The PointLight and Transform will be the
		/// default instances of their respective components.
		/// return : The new Point Light Game Object.
		GameObject* newPointLight();

		/// Builds a new Sphere GameObject. The game object will simply be the
		/// object named "Sphere", with a MeshRenderer and Transform attached 
		/// to it. The Mesh and Material data will come from the file from 
		/// which the Builder imports the sphere.
		/// return : The new Sphere Game Object.
		GameObject* newSphere();

		/// Builds a new Spot Light GameObject. The game object will be the
		/// object named "Spot Light", with the SpotLight and Transform 
		/// components attached to it. The SpotLight and Transform will be the
		/// default instances of their respective components.
		/// return : The new Spot Light Game Object.
		GameObject* newSpotLight();

		/// Builds a new Suzanne (Blender Monkey) Game Object. The game object
		/// will simply be the object named "Suzanne", with a MeshRenderer and
		/// Transform attached to it.  The Mesh and Material data will come 
		/// from the file from which the Builder imports the sphere.
		/// return : The new Suzanne Game Object. 
		GameObject* newSuzanne();
	private:
		static Builder *instance; // The Builder Singleton instance

		// File Location of all of the Default Models
		const static std::string CUBE_LOCATION;
		const static std::string PLANE_LOCATION;
		const static std::string SPHERE_LOCATION;
		const static std::string SUZANNE_LOCATION;

		/// Helper method for loading in the default models (cube, plane, etc).
		/// A new object will be instantiated from the model imported from the
		/// path specified, and then a new object composed of the child of the
		/// imported object with the specified name will be returned.
		/// const std::string &name : The name of the child of the game object
		///							  returned by the Model. This should match
		///							  the name of the geometry shape being
		///							  imported.
		/// const std::string &path : The path to the file from which the
		///							  geometry is being imported.
		/// return : The child object, with the specified name, of the model
		///			 with the specified path.
		GameObject* newDefaultImport(const std::string &name, 
				const std::string &path);

		/// Constructs a new Builder instance.
		Builder();
	};
}

#endif