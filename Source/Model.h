#ifndef MODEL_H_
#define MODEL_H_

#include <GL/glew.h>

class Model
{
public:
	Model();
	
	void draw();
	
	void bind();
	void unbind();
	
protected:
	GLuint m_vao;
	
};



#endif /* MODEL_H_ */
