#include<filesystem>
namespace fs = std::filesystem;

#include"Model.h"


const unsigned int width = 1920;
const unsigned int height = 1080;

float cubeSize = 20.0f;

float halfSize = cubeSize / 2.0f;

glm::vec3 minPosition(-halfSize, -halfSize, -halfSize);
glm::vec3 maxPosition(halfSize, halfSize, halfSize);

std::vector<Vertex> cubeVertices = {
	// Face avant
	{ { minPosition.x, minPosition.y, minPosition.z }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f } },
	{ { maxPosition.x, minPosition.y, minPosition.z }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f } },
	{ { maxPosition.x, maxPosition.y, minPosition.z }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f } },
	{ { minPosition.x, maxPosition.y, minPosition.z }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },
	// Face arrière
	{ { minPosition.x, minPosition.y, maxPosition.z }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f } },
	{ { maxPosition.x, minPosition.y, maxPosition.z }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f } },
	{ { maxPosition.x, maxPosition.y, maxPosition.z }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f } },
	{ { minPosition.x, maxPosition.y, maxPosition.z }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },
};



std::vector<GLuint> cubeIndices = {
	0, 1, 2, 2, 3, 0,   // Face avant
	1, 5, 6, 6, 2, 1,   // Face droite
	7, 6, 5, 5, 4, 7,   // Face arrière
	4, 0, 3, 3, 7, 4,   // Face gauche
	4, 5, 1, 1, 0, 4,   // Face inférieure
	3, 2, 6, 6, 7, 3    // Face supérieure
};

std::vector<Texture> cubeTex = {
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
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL App", NULL, NULL);
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
	glViewport(0, 0, width, height);




	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");
	Shader cubeShaderProgram("cube.vert", "cube.frag");

	// Take care of all the light related things
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	cubeShaderProgram.Activate();
	//	Culling
	glEnable(GL_CULL_FACE);

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// paths to the file
	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string modelPath = "/OpenGLTPS/models/bunny/scene.gltf";

	std::vector<Model> modelTab;
	for (int i = 0; i < 20; i++)
	{
		modelTab.push_back(Model((parentDir + modelPath).c_str()));
	}

	Mesh cubeMesh(cubeVertices, cubeIndices, cubeTex);

	
	//	Parameters relative to the behaviors of bunnies
	const float deltaTime = 0.1f;
	const float protectedDist = 0.3f;
	const float modifier = 0.1f;
	const float maxSpeed = 0.7f;
	const float centering = 0.2f;
	


	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.70f, 0.70f, 0.90f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);


		// Draw the cube
		cubeMesh.Draw(cubeShaderProgram, camera);



		// Draw a model
		for (int i = 0; i < modelTab.size(); i++)
		{

			modelTab[i].update_Boid_position(deltaTime);
			modelTab[i].separation(modelTab, protectedDist);
			modelTab[i].alignment(modelTab, protectedDist, modifier, maxSpeed);
			modelTab[i].cohesion(modelTab, protectedDist, centering);
			modelTab[i].Draw(shaderProgram, camera, modelTab[i].get_position(), glm::vec3(i));
			
		}


		// Switch back to the normal depth function
		glDepthFunc(GL_LESS);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	shaderProgram.Delete();
	cubeShaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}