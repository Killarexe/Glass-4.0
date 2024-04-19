#include "Glass/hitbox.hpp"

using namespace gs;

Hitbox::Hitbox(Shape shape) {
  this->shape = shape;
  this->position = Vec2f(0.0f, 0.0f);
  this->size = Vec2f(0.0f, 0.0f);
  this->radius = 0.0f;
  this->intersectFlag = false;
}

void Hitbox::draw(sf::RenderTarget* target, const Hitbox& hitbox, sf::RenderStates renderStates) {
}
