#pragma once

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

namespace mgx
{
	constexpr glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);

	class Camera3D {
	private:
		glm::vec3 position;
		glm::vec3 front_normal; // the direction that the camera is facing
		glm::vec3 right_normal; // the "right" axis in relation to the camera's direction
		glm::vec3 up_normal;	// the "up" axis in relation to the camera's direction

	public:
		Camera3D(glm::vec3 position = {0.0f, 0.0f, 3.0f}, 
				 glm::vec3 target   = {0.0f, 0.0f, 0.0f});

		// change position

		void Translate(const glm::vec3& translation);
		void MoveForward(float distance);
		void Strafe(float distance);
		void MoveUp(float distance);

		void SetPosition(const glm::vec3& _position);

		// change rotation

		void Rotate(float radians, const glm::vec3& axis);
		void Yaw(float radians);
		void Pitch(float radians);
		void Roll(float radians) = delete; // doesn't work yet

		void SetDirection(const glm::vec3& direction);

		glm::mat4 GetViewMatrix();

		inline glm::vec3& GetPosition() 	{ return position; }
		inline glm::vec3& GetDirection() 	{ return front_normal; }
		inline glm::vec3& GetRight() 		{ return right_normal; }
		inline glm::vec3& GetUp() 			{ return up_normal; }
	};
}