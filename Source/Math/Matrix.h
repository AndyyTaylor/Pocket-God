#ifndef MATRIX_H_
#define MATRIX_H_

#include "../Glm_common.h"

struct Entity;

namespace Maths
{
glm::mat4 createViewMatrix();
glm::mat4 createModelMatrix(const Entity &entity);
glm::mat4 createProjMatrix();
}

#endif /* MATRIX_H_ */
