#pragma once
#ifndef INPUT_TRANSFORMABLE_H
#define INPUT_TRANSFORMABLE_H

#include "../../../Honeycomb GE/include/object/GameObject.h"
#include "../../../Honeycomb GE/include/component/GameComponent.h"
#include "../../../Honeycomb GE/include/component/physics/Transform.h"

namespace HoneycombTest { namespace Components {
	class InputTransformable : public Honeycomb::Component::GameComponent {
	public:
		/// Creates a new instance of the input transf. component. The W and S
		/// keys will be used to move forward and backward, A and D keys used 
		/// to move left and right, Q and E keys used to move up and down. The 
		/// Y and U keys will rotate the transform left and right on the 
		/// x-axis, H and J keys will rotate the transform left and right on 
		/// the y-axis, N and M keys will rotate the transform left and right 
		/// on the z-axis. No keys will be set for scaling the Transform. By 
		/// default, the transform will translate relative to its own local
		/// coordinate system.
		InputTransformable();

		/// Creates a new instance of the input transformable component. For 
		/// all keys, if the transform is to not be moved or rotated, a 
		/// negative integer can be provided instead of the key code.
		/// int mF : The key to move the transform forward.
		/// int mB : The key to move the transform backwards.
		/// int mL : The key to move the transform left.
		/// int mR : The key to move the transform right.
		/// int mU : The key to move the transform up.
		/// int mD : The key to move the transform down.
		/// int pU : The key to pitch the transform up.
		/// int pD : The key to pitch the transform down.
		/// int rL : The key to roll the transform left.
		/// int rR : The key to roll the transform right.
		/// int yL : The key to yaw the transform left on Z-axis.
		/// int yR : The key to yaw the transform right on Z-axis.
		/// int sUR : The key to scale up on the right axis.
		/// int sDR : The key to scale down on the right axis.
		/// int sUF : The key to scale up on the forward axis.
		/// int sDF : The key to scale down on the forward axis.
		/// int sUU : The key to scale up on the up axis.
		/// int sDU : The key to scale down on the up axis.
		/// float sM : The speed by which the transform is moved.
		/// float sR : The speed by which the transform is rotated.
		/// float sS : The speed by which the transform is scaled.
		/// Space space : The space (LOCAL or GLOBAL) relative to which the
		///				  Transform is to translate.
		InputTransformable(int mF, int mB, int mL, int mR, int mU, int mD,
			int pU, int pD, int rL, int rR, int yL, int yR,
			int sUR, int sDR, int sUF, int sDF, int sUU, int sDU, 
			float sM, float sR, float sS, Honeycomb::Component::Physics::Space 
			space);

		/// Default Destructor.
		~InputTransformable();

		/// Clones this Input Transformable into a new, dynamically allocated 
		/// Input Transformable. This function should be used instead of the 
		/// copy constructor to  prevent object slicing.
		/// return : The cloned Input Transformable.
		std::unique_ptr<InputTransformable> clone() const;

		/// <summary>
		/// Returns the Component ID integer representation of the Input
		/// Transformable.
		/// </summary>
		/// <returns>
		/// The Component ID of the Input Transformable Component.
		/// </returns>
		virtual Honeycomb::Component::GameComponentID 
				getGameComponentID() const noexcept override;

		/// Returns the space relative to which the translations occur.
		/// return : A reference to the space.
		Honeycomb::Component::Physics::Space& getSpace();

		/// Takes in the input and transforms the transform according to the
		/// input.
		void onInput() override;
	private:
		float speedM; // The speed with which the transform is moved
		float speedR; // The speed with which the transform is rotated
		float speedS; // The speed with which the transform is scaled

		/// Key Codes for moving the Transform
		int movForward = 0;
		int movBackward = 0;
		int movLeft = 0;
		int movRight = 0;
		int movUp = 0;
		int movDown = 0;
		
		/// Key Codes for rotating the Transform
		int pitchUp = 0;
		int pitchDown = 0;
		int rollLeft = 0;
		int rollRight = 0;
		int yawLeft = 0;
		int yawRight = 0;

		/// Key codes for scaling the Transform
		int scaleUpR = 0;
		int scaleUpU = 0;
		int scaleUpF = 0;
		int scaleDownR = 0;
		int scaleDownU = 0;
		int scaleDownF = 0;

		// The space relative to which the translation is to occur
		Honeycomb::Component::Physics::Space space;

		virtual InputTransformable* cloneInternal() const override;
	};
} }

#endif