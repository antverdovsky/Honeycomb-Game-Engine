#include "..\..\include\components\InputTransformable.h"

#include "..\..\..\Honeycomb GE\include\base\GameInput.h"
#include "..\..\..\Honeycomb GE\include\math\Vector3f.h"

using Honeycomb::Base::GameInput;
using Honeycomb::Component::Physics::Transform;
using Honeycomb::Math::Vector3f;

namespace HoneycombTest::Components {
	InputTransformable::InputTransformable() : InputTransformable(
		GameInput::KEY_CODE_W, GameInput::KEY_CODE_S, // Move forward & back
		GameInput::KEY_CODE_A, GameInput::KEY_CODE_D, // Move left & right
		GameInput::KEY_CODE_Q, GameInput::KEY_CODE_E, // Move up & down
		GameInput::KEY_CODE_Y, GameInput::KEY_CODE_U, // Pitch up & down
		GameInput::KEY_CODE_H, GameInput::KEY_CODE_J, // Roll left & right
		GameInput::KEY_CODE_N, GameInput::KEY_CODE_M, // Yaw left & right
		0.05F, 0.05F) {
		
	}

	InputTransformable::InputTransformable(
			int mF, int mB, int mL, int mR, int mU, int mD,
			int pU, int pD, int rL, int rR, int yL, int yR,
			float sM, float sR) {
		this->movForward = mF;
		this->movBackward = mB;
		this->movLeft = mL;
		this->movRight = mR;
		this->movUp = mU;
		this->movDown = mD;

		this->pitchUp = pU;
		this->pitchDown = pD;
		this->rollLeft = rL;
		this->rollRight = rR;
		this->yawLeft = yL;
		this->yawRight = yR;

		this->speedM = sM;
		this->speedR = sR;
	}

	InputTransformable::~InputTransformable() {

	}

	void InputTransformable::input() {
		Transform *transform = 
			this->attached->getComponentOfType<Transform>("Transform");
		GameInput *input =
			GameInput::getGameInput();

		if (input->getKeyDown(this->movForward))
			transform->translate( transform->getLocalForward() * speedM);
		else if (input->getKeyDown(this->movBackward))
			transform->translate(-transform->getLocalForward() * speedM);
		if (input->getKeyDown(this->movLeft))
			transform->translate(-transform->getLocalRight() * speedM);
		else if (input->getKeyDown(this->movRight))
			transform->translate( transform->getLocalRight() * speedM);
		if (input->getKeyDown(this->movUp))
			transform->translate( transform->getLocalUp() * speedM);
		else if (input->getKeyDown(this->movDown))
			transform->translate(-transform->getLocalUp() * speedM);

		if (input->getKeyDown(this->pitchUp))
			transform->rotate( transform->getLocalRight(), speedR);
		else if (input->getKeyDown(this->pitchDown))
			transform->rotate(-transform->getLocalRight(), speedR);
		if (input->getKeyDown(this->rollLeft))
			transform->rotate(-transform->getLocalForward(), speedR);
		else if (input->getKeyDown(this->rollRight))
			transform->rotate( transform->getLocalForward(), speedR);
		if (input->getKeyDown(this->yawLeft))
			transform->rotate( transform->getLocalUp(), speedR);
		else if (input->getKeyDown(this->yawRight))
			transform->rotate(-transform->getLocalUp(), speedR);
	}
}