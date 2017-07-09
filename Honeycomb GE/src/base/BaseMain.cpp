#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../include/base/BaseGame.h"
#include "../../include/base/BaseMain.h"
#include "../../include/base/GameInput.h"
#include "../../include/base/GameTime.h"
#include "../../include/base/GameWindow.h"
#include "../../include/debug/Logger.h"
#include "../../include/scene/GameScene.h"
#include "../../include/render/RenderingEngine.h"

using Honeycomb::Debug::Logger;
using Honeycomb::Render::RenderingEngine;
using Honeycomb::Render::RenderingType;
using Honeycomb::Scene::GameScene;

namespace Honeycomb { namespace Base {
	BaseMain& BaseMain::getBaseMain() {
		static BaseMain *baseMain = new BaseMain();
		return *baseMain;
	}

	void BaseMain::runGame(BaseGame &game) {
		this->game = &game;

		this->start();
		this->run();
		this->stop();
	}

	void BaseMain::render() {
		this->game->render();
		if (GameScene::getActiveScene() != nullptr)
			this->renderingEngine->render(*GameScene::getActiveScene());
		
		GameWindow::getGameWindow()->refresh();
	}

	void BaseMain::run() {
		// The expected time that we should spend rendering each frame in order
		// to hit the desired FPS count.
		const float msPerFrame = (FRAME_RATE_CAP > 0) ?
			1.0F / FRAME_RATE_CAP * GameTime::SECOND :
			0.00000000001F;

		// Last time a frame was renderered and the time between frame renders,
		// both are in milliseconds.
		float lastTime = GameTime::getGameTime()->getElapsedTimeMS();
		float deltaTime = 0;

		// The number of frames rendered in some amount of time that we spent
		// rendering them (used to calculate the FPS).
		int framesRendered = 0;
		float timeSpentRenderingFrames = 0;

		do {
			// Get the game time at the start of the loop and calculate the 
			// delta time between the last loop iteration and the current. 
			// Reset the last render time to the current loop start time.
			float currentTime = GameTime::getGameTime()->getElapsedTimeMS();
			deltaTime += currentTime - lastTime;
			lastTime = currentTime;

			// If the time between this iteration and last iteration exceeds
			// the minimum amount of time between frames -> Render & update.
			if (deltaTime >= msPerFrame) {
				update(); // Update the game
				render(); // Render the game & the game window.

				// Time spent rendering frames is to increase by how long it 
				// took to render this frame.
				timeSpentRenderingFrames += deltaTime;
				framesRendered++;

				// Record the time between frames in the Time namespace and
				// reset the delta time for future iterations of the loop.
				GameTime::getGameTime()->setDeltaTimeMS(deltaTime);
				deltaTime = 0;

				// If we have spent at least one second rendering the frames,
				// we have the current number of frames for the last second.
				// Reset the variables so the FPS can be calculated next frame.
				if (timeSpentRenderingFrames >= GameTime::SECOND) {
					Logger::getLogger().logEntry(__FUNCTION__, __LINE__,
						"FPS: " + std::to_string(framesRendered));

					timeSpentRenderingFrames = 0;
					framesRendered = 0;
				}
			}

			// "Is game running" is based on the window close requested event
			isGameRunning = !GameWindow::getGameWindow()->isCloseRequested();
		} while (isGameRunning);
	}

	void BaseMain::start() {
		if (isGameRunning) return; // If already running -> No need to start!

		// Initialize the GLFW, and the components which rely on GLFW (Window
		// & Input).
		glfwInit();
		GameWindow::getGameWindow(); // Initialize the Game Window (first time)
		GameInput::getGameInput(); // Initialize the Game Input (first time)

		// Initialize GLEW and OpenGL.
		glewExperimental = true;
		glewInit();
		this->renderingEngine = RenderingEngine::getRenderingEngine();
		this->renderingEngine->setRenderingType(
			RenderingType::TYPE_DEFERRED_RENDERER);

		Logger::getLogger().logEntry(__FUNCTION__, __LINE__,
			"All GLEW and GLFW initializations complete!");

		// Initialize the Game & Start!
		this->game->start();
	}

	void BaseMain::stop() {
		if (!isGameRunning) return; // If already stopped -> No need to stop!

		this->game->stop();
		if (GameScene::getActiveScene()) GameScene::getActiveScene()->onStop();
		
		glfwTerminate(); // Terminate GLFW
	}

	void BaseMain::update() {
		this->game->input();
		if (GameScene::getActiveScene()) GameScene::getActiveScene()->onInput();

		this->game->update();
		if (GameScene::getActiveScene()) GameScene::getActiveScene()->onUpdate();

		GameInput::getGameInput()->clear(); // Clear input in between frames
	}
} }
