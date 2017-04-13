#include "Model.h"

#include <GL/glew.h>
#include <vector>

namespace
{
std::vector<GLfloat> points = {
	-0.5, 0.5, 0.0,
	0.5, -0.5, 0.0,
	0.5, 0.5, 0.0,
	-0.5, 0.5, 0.0,
	0.5, -0.5, 0.0,
	-0.5, -0.5, 0.0
};

std::vector<GLfloat> colors = {
	1.0, 0.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	1.0, 0.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 0.0, 1.0, 1.0
};
}

Model::Model()
{
	GLuint pos_vbo;
	glGenBuffers(1, &pos_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, pos_vbo);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(GLfloat), points.data(), GL_STATIC_DRAW);
	
	GLuint col_vbo;
	glGenBuffers(1, &col_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, col_vbo);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), colors.data(), GL_STATIC_DRAW);
	
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, pos_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, col_vbo);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Model::draw()
{
	bind();
	
	glDrawArrays(GL_TRIANGLES, 0, points.size()/3);
	
	unbind();
}

void Model::bind()
{
	glBindVertexArray(m_vao);
}

void Model::unbind()
{
	glBindVertexArray(0);
}
