#pragma once
#ifndef GAME_H
#define GAME_H

namespace Honeycomb::Object { class Transform; }
namespace Honeycomb::Mesh { class Mesh; }
namespace Honeycomb::Render { class Camera; }
namespace Honeycomb::Shader { class ShaderProgram; }

namespace Honeycomb::Base {
	class Game {
	public:
		Game();
		
		~Game();

		void input();

		void render();

		void update();

	private:
		Honeycomb::Render::Camera* testCamera;
		Honeycomb::Object::Transform* testTransform;
		Honeycomb::Mesh::Mesh* testMesh;
		Honeycomb::Shader::ShaderProgram* testShader;
	};
}

#endif