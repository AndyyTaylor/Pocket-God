#include "Matrix.h"

#include "../Glm_common.h"
#include "../Entity.h"
#include "../Display.h"
#include "../Camera.h"

namespace Maths
{
glm::mat4 createViewMatrix(const Camera& camera)
{
	glm::mat4 matrix;
    // glm::rotate is actually kinda confusing
    matrix = glm::rotate(matrix, glm::radians(camera.rotation.x), {1, 0, 0});
    matrix = glm::rotate(matrix, glm::radians(camera.rotation.y), {0, 1, 0});
    matrix = glm::rotate(matrix, glm::radians(camera.rotation.z), {0, 0, 1});
    
    matrix = glm::translate(matrix, -camera.position);
    return matrix;
}

glm::mat4 createModelMatrix(const Entity& entity)
{
	glm::mat4 matrix;

	matrix = glm::translate(matrix, entity.position);

	matrix = glm::rotate(matrix, glm::radians(entity.rotation.x), {1, 0, 0});
	matrix = glm::rotate(matrix, glm::radians(entity.rotation.y), {0, 1, 0});
	matrix = glm::rotate(matrix, glm::radians(entity.rotation.z), {0, 0, 1});

	matrix = glm::scale(matrix, glm::vec3(entity.scale.x, entity.scale.y, entity.scale.z)); // I think scale is meant to be last as matrix operation order is reversed?

	return matrix;
}

glm::mat4 createProjMatrix()
{
	return glm::perspective(glm::radians(120.0f), (float) 1280 / (float) 720, 0.1f, 10000.0f);
}
}
