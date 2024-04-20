#include "hitbox.hpp"
#include "typedef.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

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
  if(shape == Shape::Rectangle) {
    return (x >= position.x && x <= position.x + size.x && y >= position.y && y <= position.y + size.y);
  }
  float dx = x - position.x;
  float dy = y - position.y;
  return dx * dx + dy * dy <= radius * radius;
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
  if(shape == Shape::Rectangle) {
    position.x = x - size.x / 2.0f;
    position.y = y - size.y / 2.0f;
  } else {
    position.x = x;
    position.y = y;
  }
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
  sf::RectangleShape shape;
  shape.setPosition(hitbox.getPosition().x, hitbox.getPosition().y);
  shape.setSize(sf::Vector2f(hitbox.getSize().x, hitbox.getSize().y));
  target->draw(shape, renderStates);
}

std::ostream& operator<<(std::ostream& os, const Hitbox& hitbox) {
  os << "Hitbox - Position: (" << hitbox.getPosition().x << ", " << hitbox.getPosition().y << "), ";
  if (hitbox.shape == Hitbox::Shape::Rectangle) {
    os << "Size: (" << hitbox.getSize().x << ", " << hitbox.getSize().y << ")";
  } else {
    os << "Radius: " << hitbox.getRadius();
  }
  return os;
}

