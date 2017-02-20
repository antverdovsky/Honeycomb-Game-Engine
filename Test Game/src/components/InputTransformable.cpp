#include "..\..\include\components\InputTransformable.h"

#include "..\..\..\Honeycomb GE\include\base\GameTime.h"
#include "..\..\..\Honeycomb GE\include\base\GameInput.h"
#include "..\..\..\Honeycomb GE\include\math\Vector3f.h"

using Honeycomb::Base::GameInput;
using Honeycomb::Component::Physics::Transform;
using Honeycomb::Math::Vector3f;

using namespace Honeycomb::Base;

#include <iostream> //temp af

namespace HoneycombTest::Components {
	InputTransformable::InputTransformable() : InputTransformable(
		GameInput::KEY_CODE_W, GameInput::KEY_CODE_S, // Move forward & back
		GameInput::KEY_CODE_A, GameInput::KEY_CODE_D, // Move left & right
		GameInput::KEY_CODE_Q, GameInput::KEY_CODE_E, // Move up & down
		GameInput::KEY_CODE_Y, GameInput::KEY_CODE_U, // Pitch up & down
		GameInput::KEY_CODE_H, GameInput::KEY_CODE_J, // Roll left & right
		GameInput::KEY_CODE_N, GameInput::KEY_CODE_M, // Yaw left & right
		3.5F, 3.5F) {
		
	}

	InputTransformable::InputTransformable(
			int mF, int mB, int mL, int mR, int mU, int mD,
			int pU, int pD, int rL, int rR, int yL, int yR,
			float sM, float sR) : GameComponent("InputTransformable") {
		/// Keys for Movement
		this->movForward = mF;
		this->movBackward = mB;
		this->movLeft = mL;
		this->movRight = mR;
		this->movUp = mU;
		this->movDown = mD;

		/// Keys for Rotation
		this->pitchUp = pU;
		this->pitchDown = pD;
		this->rollLeft = rL;
		this->rollRight = rR;
		this->yawLeft = yL;
		this->yawRight = yR;

		/// Movement Speed Values (not adjusted for Frame Rate)
		this->speedM = sM;
		this->speedR = sR;
	}

	InputTransformable::~InputTransformable() {

	}

	InputTransformable* InputTransformable::clone() const {
		return new InputTransformable(*this);
	}

	void InputTransformable::input() {
		if (!this->isActive) return; // If not active, don't do anything!

		// Get the Transform which will be modified, and a pointer to the Input
		Transform *transform = 
			this->attached->getComponent<Transform>();
		GameInput *input = GameInput::getGameInput();

		// Adjust the speed values for the frame rate
		float adjSpeedM = 
			this->speedM * GameTime::getGameTime()->getDeltaTimeS();
		float adjSpeedR = 
			this->speedR * GameTime::getGameTime()->getDeltaTimeS();

		if (input->getKeyDown(this->movForward))
			transform->translate( transform->getLocalForward() * adjSpeedM);
		else if (input->getKeyDown(this->movBackward))
			transform->translate(-transform->getLocalForward() * adjSpeedM);
		if (input->getKeyDown(this->movLeft))
			transform->translate(-transform->getLocalRight() * adjSpeedM);
		else if (input->getKeyDown(this->movRight))
			transform->translate( transform->getLocalRight() * adjSpeedM);
		if (input->getKeyDown(this->movUp))
			transform->translate( transform->getLocalUp() * adjSpeedM);
		else if (input->getKeyDown(this->movDown))
			transform->translate(-transform->getLocalUp() * adjSpeedM);

		if (input->getKeyDown(this->pitchUp))
			transform->rotate( transform->getLocalRight(), adjSpeedR);
		else if (input->getKeyDown(this->pitchDown))
			transform->rotate(-transform->getLocalRight(), adjSpeedR);
		if (input->getKeyDown(this->rollLeft))
			transform->rotate(-transform->getLocalForward(), adjSpeedR);
		else if (input->getKeyDown(this->rollRight))
			transform->rotate( transform->getLocalForward(), adjSpeedR);
		if (input->getKeyDown(this->yawLeft))
			transform->rotate( transform->getLocalUp(), adjSpeedR);
		else if (input->getKeyDown(this->yawRight))
			transform->rotate(-transform->getLocalUp(), adjSpeedR);
	}
}