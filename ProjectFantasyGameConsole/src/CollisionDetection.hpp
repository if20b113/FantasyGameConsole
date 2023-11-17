#ifndef COLLISIONDETECTION_HPP
#define COLLISIONDETECTION_HPP

#include "glm/vec2.hpp"

namespace FantasyGameEngine { namespace collision {

bool aabb(
    const glm::vec2& pos_a, 
    const glm::vec2& size_a, 
    const glm::vec2& pos_b, 
    const glm::vec2& size_b)
{
    return !(
        pos_a.x + size_a.x < pos_b.x ||
        pos_a.x > pos_b.x + size_b.x ||
        pos_a.y + size_a.y < pos_b.y ||
        pos_a.y > pos_b.y + size_b.y );
}

} }

#endif