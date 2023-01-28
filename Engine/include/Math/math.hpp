#ifndef MATH_HPP
#define MATH_HPP

#include <glm/glm.hpp>

namespace Y {
namespace math {

    bool Decompose(const glm::mat4& transform , glm::vec3& translate , glm::vec3& rotation , glm::vec3& scale);

}
}

#endif