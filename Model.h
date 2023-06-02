#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include<json/json.h>
#include"Mesh.h"
#include"random"


using json = nlohmann::json;



class Model
{

private:
	// Variables for easy access
	const char* file;
	std::vector<unsigned char> data;
	json JSON;
	glm::vec3 _position;
	glm::vec3 _velocity;
	int             _id;


	// All the meshes and transformations
	std::vector<Mesh> meshes;
	std::vector<glm::vec3> translationsMeshes;
	std::vector<glm::quat> rotationsMeshes;
	std::vector<glm::vec3> scalesMeshes;
	std::vector<glm::mat4> matricesMeshes;

	// Prevents textures from being loaded twice
	std::vector<std::string> loadedTexName;
	std::vector<Texture> loadedTex;

	// Loads a single mesh by its index
	void loadMesh(unsigned int indMesh);

	// Traverses a node recursively, so it essentially traverses all connected nodes
	void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

	// Gets the binary data from a file
	std::vector<unsigned char> getData();
	// Interprets the binary data into floats, indices, and textures
	std::vector<float> getFloats(json accessor);
	std::vector<GLuint> getIndices(json accessor);
	std::vector<Texture> getTextures();

	// Assembles all the floats into vertices
	std::vector<Vertex> assembleVertices
	(
		std::vector<glm::vec3> positions,
		std::vector<glm::vec3> normals,
		std::vector<glm::vec2> texUVs
	);

	// Helps with the assembly from above by grouping floats
	std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
	std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
	std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);

public:


	// Loads in a model from a file and stores tha information in 'data', 'JSON', and 'file'
	Model(const char* file);

	void Draw(Shader& shader, Camera& camera, glm::vec3 translate, glm::vec3 scale);

	//  Methods
		//  Getters
	glm::vec3 get_position();
	glm::vec3 get_velocity();
	std::size_t      getID();

	//  Setters
	void set_position(glm::vec3 pos);
	void set_velocity(glm::vec3 vel);
	void set_ID(const int boidID);


	//  Update method
	void update_Boid_position(const float dTime);
	void separation(std::vector<Model>& models, const float protected_dist);
	void alignment(std::vector<Model>& models, const float protected_dist, const float modifier, const float max_speed);
	void cohesion(const std::vector<Model>& models, const float protected_dist, const float centering);


	//  Maths functions that depends on the boid class 
	static float euclidian_distance(const Model& m1, const Model& m2)
	{
		float distance = std::sqrt(std::pow(m1._position.x - m2._position.x, 2) +
			std::pow(m1._position.y - m2._position.y, 2) +
			std::pow(m1._position.z - m2._position.z, 2));
		return distance;
	}





};

#endif