#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<filesystem>
namespace fs = std::filesystem;

#include<glm/glm.hpp>						  
#include<glm/gtc/matrix_transform.hpp>		 
#include<glm/gtc/type_ptr.hpp>
#include<stb/stb_image.h>


#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"IBO.h"
#include"Camera.h"


 
/*
 GLfloat vertices[] =
{// Coordinates								//Colors
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.0f, 0.0f, 1.0f, // Lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 1.0f, 0.0f, 0.0f, // Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, 0.0f, 1.0f, 0.0f, // Upper corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, 1.0f, 0.0f, 1.0f, // Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, 1.0f, 0.0f, 1.0f, // Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f, 1.0f, 0.0f, 1.0f // Inner down
};

GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};
*/

const unsigned int width = 800;
const unsigned int height = 800;

//Sphere
//Sphere Sphere1(1.0f, 1, 1);
//glimac::Sphere s1(1.0f, 1, 1);





//Pyramid
// Vertices coordinates
GLfloat vertices[] =
{// Coordinates			 //Colors					//Texture Coordinates
	-0.5f, 0.0f, 0.5f,  0.83f, 0.70f, 0.44f,		0.0f, 0.0f,			
	-0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f,		5.0f, 0.0f,
	0.5f, 0.0f, -0.5f,  0.83f, 0.70f, 0.44f,		1.0f, 1.0f,
	0.5f, 0.0f, 0.5f,   0.83f, 0.70f, 0.44f,		5.0f, 0.0f,
	0.0f, 0.8f, 0.0f,   0.92f, 0.86f, 0.76f,		2.5f, 5.0f
};


// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};





int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "TPs", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);



	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");



	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();


	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	
	// Generates Element Buffer Object and links it to indices
	IBO IBO1(indices, sizeof(indices));


	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	IBO1.Unbind();

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


	// Original code from the tutorial
	Texture triforce("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	triforce.texUnit(shaderProgram, "tex0", 0);

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	//	Create a camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "uCam");

		double currentTime = glfwGetTime();
		if (currentTime - prevTime >= 1 / 60)
		{
			rotation += 0.5f;
			prevTime = currentTime;
		}

		//matrix initialization
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		//rotate matrix applied to the model (i.e object)
		model = glm::translate(model, glm::vec3(0, 0, 0));
		model = glm::rotate(model, glm::radians(rotation/4.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(0, 0, 0));
		model = glm::scale(model, glm::vec3(1.2, 1.2, 1.2));
		//we move the "world" coordinates
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
		//we can see object far from 0.1f to 100.0f to us
		proj = glm::perspective(glm::radians(60.0f), (float)(800 / 800), 0.1f, 100.0f);

		//import uniform variable from frag shader
		int modelloc = glGetUniformLocation(shaderProgram.ID, "uModel");
		glUniformMatrix4fv(modelloc, 1, GL_FALSE, glm::value_ptr(model));
		int viewloc = glGetUniformLocation(shaderProgram.ID, "uView");
		glUniformMatrix4fv(viewloc, 1, GL_FALSE, glm::value_ptr(view));
		int projloc = glGetUniformLocation(shaderProgram.ID, "uProj");
		glUniformMatrix4fv(projloc, 1, GL_FALSE, glm::value_ptr(proj));



		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		glUniform1f(uniID, 0.5f);
		// Binds texture so that is appears in rendering
		triforce.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//Call of the second object
		model = glm::translate(model, glm::vec3(0, 0, 0));
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(1, 0, 0));
		model = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));
		glUniformMatrix4fv(modelloc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	IBO1.Delete();
	triforce.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}


////rotate matrix function
//glm::mat3 rotate(float a_radians)
//{
//	float c = cos(a_radians);
//	float s = sin(a_radians);
//
//	glm::vec3 row1(c, s, 0.0f);
//	glm::vec3 row2(-s, c, 0.0f);
//	glm::vec3 row3(0.0f, 0.0f, 1.0f);
//
//	return glm::mat3(row1, row2, row3);
//}
//
////translate matrix function
//glm::mat3 translation(float tx, float ty)
//{
//	glm::vec3 row1(1, 0, tx);
//	glm::vec3 row2(0, 1, ty);
//	glm::vec3 row3(0, 0, 1);
//
//	return glm::mat3(row1, row2, row3);
//}
//
////scale matrix function
//glm::mat3 scale(float sx, float sy)
//{
//	glm::vec3 row1(sx, 0, 0);
//	glm::vec3 row2(0, sy, 0);
//	glm::vec3 row3(0, 0, 1);
//
//	return glm::mat3(row1, row2, row3);
//}