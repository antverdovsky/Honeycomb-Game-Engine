#include "../../include/components/InputTransformable.h"

#include "../../../Honeycomb GE/include/base/GameTime.h"
#include "../../../Honeycomb GE/include/base/GameInput.h"
#include "../../../Honeycomb GE/include/math/Vector3f.h"

using Honeycomb::Base::GameInput;
using Honeycomb::Component::GameComponentID;
using Honeycomb::Component::Physics::Space;
using Honeycomb::Component::Physics::Transform;
using Honeycomb::Math::Vector3f;

using namespace Honeycomb::Base;

namespace HoneycombTest { namespace Components {
	InputTransformable::InputTransformable() : InputTransformable(
		GameInput::KEY_CODE_W, GameInput::KEY_CODE_S, // Move forward & back
		GameInput::KEY_CODE_A, GameInput::KEY_CODE_D, // Move left & raight
		GameInput::KEY_CODE_Q, GameInput::KEY_CODE_E, // Move up & down
		GameInput::KEY_CODE_T, GameInput::KEY_CODE_G, // Pitch up & down
		GameInput::KEY_CODE_F, GameInput::KEY_CODE_H, // Roll left & right
		GameInput::KEY_CODE_R, GameInput::KEY_CODE_Y, // Yaw left & right
		-1, -1, -1, -1, -1, -1, 3.5F, 3.5F, 3.5F, Space::LOCAL) {
		
	}

	InputTransformable::InputTransformable(
			int mF, int mB, int mL, int mR, int mU, int mD,
			int pU, int pD, int rL, int rR, int yL, int yR,
			int sUR, int sDR, int sUF, int sDF, int sUU, int sDU,
			float sM, float sR, float sS, Space space) {
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

		/// Keys for Scaling
		this->scaleUpR = sUR;
		this->scaleUpU = sUU;
		this->scaleUpF = sUF;
		this->scaleDownR = sDR;
		this->scaleDownU = sDU;
		this->scaleDownF = sDF;

		/// Movement Speed Values (not adjusted for Frame Rate)
		this->speedM = sM;
		this->speedR = sR;
		this->speedS = sS;

		this->space = space;
	}

	InputTransformable::~InputTransformable() {

	}

	std::unique_ptr<InputTransformable> InputTransformable::clone() const {
		return std::unique_ptr<InputTransformable>(this->cloneInternal());
	}

	GameComponentID InputTransformable::getGameComponentID() const noexcept {
		return GameComponent::getGameComponentTypeID<InputTransformable>();
	}

	Space& InputTransformable::getSpace() {
		return this->space;
	}

	void InputTransformable::onInput() {
		// Get the Transform which will be modified, and a pointer to the Input
		Transform &transform = this->attached->getComponent<Transform>();
		GameInput *input = GameInput::getGameInput();

		// Get the forward, up and right vectors
		Vector3f forward = Vector3f::getGlobalForward();
		Vector3f right = Vector3f::getGlobalRight();
		Vector3f up = Vector3f::getGlobalUp();

		// Adjust the speed values for the frame rate
		float sM = this->speedM * GameTime::getGameTime()->getDeltaTimeS();
		float sR = this->speedR * GameTime::getGameTime()->getDeltaTimeS();
		float sS = this->speedS * GameTime::getGameTime()->getDeltaTimeS();

		if (input->getKeyDown(this->movForward))
			transform.translate( forward * sM, this->space);
		else if (input->getKeyDown(this->movBackward))
			transform.translate(-forward * sM, this->space);
		if (input->getKeyDown(this->movRight))
			transform.translate( right * sM, this->space);
		else if (input->getKeyDown(this->movLeft))
			transform.translate(-right * sM, this->space);
		if (input->getKeyDown(this->movUp))
			transform.translate( up * sM, this->space);
		else if (input->getKeyDown(this->movDown))
			transform.translate(-up * sM, this->space);

		if (input->getKeyDown(this->pitchUp))
			transform.rotate( right, sR, this->space);
		else if (input->getKeyDown(this->pitchDown))
			transform.rotate(-right, sR, this->space);
		if (input->getKeyDown(this->rollLeft))
			transform.rotate(-forward, sR, this->space);
		else if (input->getKeyDown(this->rollRight))
			transform.rotate( forward, sR, this->space);
		if (input->getKeyDown(this->yawLeft))
			transform.rotate( up, sR, this->space);
		else if (input->getKeyDown(this->yawRight))
			transform.rotate(-up, sR, this->space);

		Vector3f scale = this->space == Space::GLOBAL ?
			transform.getGlobalScale() : transform.getLocalScale();

		if (input->getKeyDown(this->scaleUpR))
			transform.setScale(scale + (right * sS), this->space);
		else if (input->getKeyDown(this->scaleDownR))
			transform.setScale(scale - (right * sS), this->space);
		if (input->getKeyDown(this->scaleUpU))
			transform.setScale(scale + (up * sS), this->space);
		else if (input->getKeyDown(this->scaleDownU))
			transform.setScale(scale - (up * sS), this->space);
		if (input->getKeyDown(this->scaleUpF))
			transform.setScale(scale + (forward * sS), this->space);
		else if (input->getKeyDown(this->scaleDownF))
			transform.setScale(scale - (forward * sS), this->space);
	}

	InputTransformable* InputTransformable::cloneInternal() const {
		return new InputTransformable(
			this->movForward, this->movBackward, this->movLeft,
			this->movRight, this->movUp, this->movDown,
			this->pitchUp, this->pitchDown, this->rollLeft, 
			this->rollRight, this->yawLeft, this->yawRight,
			this->scaleUpR, this->scaleDownR, this->scaleUpF,
			this->scaleDownF, this->scaleUpU, this->scaleDownU,
			this->speedM, this->speedR, this->speedS,
			this->space);
	}
} }