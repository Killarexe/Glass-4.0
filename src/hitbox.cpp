#include "hitbox.hpp"
#include "typedef.hpp"

using namespace gs;

Hitbox::Hitbox(Shape shape) {
  this->shape = shape;
  this->position = Vec2f(0.0f, 0.0f);
  this->size = Vec2f(0.0f, 0.0f);
  this->radius = 0.0f;
  this->intersectFlag = false;
}

bool Hitbox::intersects(Vec2f point) const {
  return intersects(point.x, point.y);
}

bool Hitbox::intersects(float x, float y) const {
  return false;
}

void Hitbox::setPosition(Vec2f position) {
  setPosition(position.x, position.y);
}

void Hitbox::setPosition(float x, float y) {
  this->position.x = x;
  this->position.y = y;
}

void Hitbox::setSize(Vec2f size) {
  setSize(position.x, position.y);
}

void Hitbox::setSize(float x, float y) {
  this->position.x = x;
  this->position.y = y;
}

void Hitbox::setRadius(float radius) {
  this->radius = radius;
}

void Hitbox::setCenter(Vec2f position) {
  setCenter(position.x, position.y);
}

void Hitbox::setCenter(float x, float y) {
  
}

void Hitbox::move(Vec2f offset) {
  move(offset.x, offset.y);
}

void Hitbox::move(float x, float y) {
  this->position.x += x;
  this->position.y += y;
}

Vec2f Hitbox::getPosition() const {
  return position;
}


Vec2f Hitbox::getSize() const {
  return size;
}

float Hitbox::getRadius() const {
  return radius;
}

Vec2f Hitbox::getCenter() const {
  return position;
}

void draw(sf::RenderTarget* target, const Hitbox& hitbox, sf::RenderStates renderStates) {

}
