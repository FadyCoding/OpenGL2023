#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

class Camera {

	public:	
		//	Camera's parameters
		glm::vec3 _position; 
		glm::vec3 _orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 _up_direction = glm::vec3(0.0f, 1.0f, 0.0f);

		int width;
		int height;

		float _speed;
		const float sensivity = 100.0f;

		//	Constructor
		Camera(const int width, const int height, glm::vec3 _position);

		//	Destructor 
		~Camera() {};

		//	Methods
		void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
		void Inputs(GLFWwindow* window);


};

#endif
