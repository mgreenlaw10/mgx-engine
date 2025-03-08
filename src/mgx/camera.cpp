#include <mgx/camera.hpp>

#include <iostream>

namespace mgx {

	Camera3D::Camera3D(glm::vec3 _position, glm::vec3 _target) 
		: position    (_position),
		  front_normal( glm::normalize(_target - _position)),
		  right_normal( glm::normalize(glm::cross(front_normal, WORLD_UP))),
		  up_normal   (-glm::normalize(glm::cross(front_normal, right_normal)))
		  {}

	void Camera3D::Translate(const glm::vec3& translation) {
		position += translation;
	}

	// can be passed a negative number to move backwards
	void Camera3D::MoveForward(float distance) {
		position += distance * front_normal;
	}

	// can be passed a negative number to move left
	void Camera3D::Strafe(float distance) {
		position += distance * right_normal;
	}

	// can be passed a negative number to move down
	void Camera3D::MoveUp(float distance) {
		position += distance * WORLD_UP;
	}

	void Camera3D::SetPosition(const glm::vec3& _position) {
		position = _position;
	}

	void Camera3D::Rotate(float radians, const glm::vec3& axis) {
		glm::mat4 rotation_matrix(1.0f);
		rotation_matrix = glm::rotate(rotation_matrix, radians, axis);

		front_normal =  glm::normalize(glm::vec3(rotation_matrix * glm::vec4(front_normal, 1.0f)));
		right_normal =  glm::normalize(glm::cross(front_normal, WORLD_UP));
		up_normal    = -glm::normalize(glm::cross(front_normal, right_normal));
	}

	void Camera3D::Yaw(float radians) {
		Rotate(radians, up_normal);
	}

	void Camera3D::Pitch(float radians) {
		Rotate(radians, right_normal);
	}

	void Camera3D::SetDirection(const glm::vec3& direction) {
		front_normal = direction;
	}

}