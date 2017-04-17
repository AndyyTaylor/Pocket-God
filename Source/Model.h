#ifndef MODEL_H_
#define MODEL_H_

#include <GL/glew.h>
#include "Entity.h"
#include <vector>

class Model
{
public:
	Model();
	
	void draw();
	
	void bind();
	void unbind();
	
	void loadModel(const char* path);
	
	Entity entity; // temporary
	
protected:
	GLuint m_vao;
	
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	
};



#endif /* MODEL_H_ */
