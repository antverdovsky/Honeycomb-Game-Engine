#pragma once
#ifndef INPUT_TRANSFORMABLE_H
#define INPUT_TRANSFORMABLE_H

#include "..\..\..\Honeycomb GE\include\object\GameObject.h"
#include "..\..\..\Honeycomb GE\include\component\GameComponent.h"
#include "..\..\..\Honeycomb GE\include\component\physics\Transform.h"

namespace HoneycombTest::Components {
	class InputTransformable : public Honeycomb::Component::GameComponent {
	public:
		/// Creates a new instance of the input movable component. The W and S
		/// keys will be used to move forward and backward, A and D keys used 
		/// to move left and right, Q and E keys used to move up and down. The 
		/// Y and U keys will rotate the transform left and right on the 
		/// x-axis, H and J keys will rotate the transform left and right on 
		/// the y-axis, N and M keys will rotate the transform left and right 
		/// on the z-axis.
		InputTransformable();

		/// Creates a new instance of the input movable component. For all 
		/// keys, if the transform is to not be moved or rotated, a negative
		/// integer can be provided instead of the key code.
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
		/// float sM : The speed by which the transform is moved.
		/// float sR : The speed by which the transform is rotated.
		InputTransformable(int mF, int mB, int mL, int mR, int mU, int mD,
			int pU, int pD, int rL, int rR, int yL, int yR,
			float sM, float sR);

		/// Default Destructor.
		~InputTransformable();

		/// Clones this Input Transformable into a new, dynamically allocated 
		/// Input Transformable. This function should be used instead of the 
		/// copy constructor to  prevent object slicing.
		/// return : The cloned Input Transformable.
		InputTransformable* clone();

		/// Takes in the input and transforms the transform according to the
		/// input.
		void input();
	private:
		float speedM; // The speed with which the transform is moved
		float speedR; // The speed with which the transform is rotated

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
	};
}

#endif