#include "component.hpp"
#include "hitbox.hpp"
#include "typedef.hpp"
#include <SFML/Graphics/RenderStates.hpp>

using namespace gs;

void Component::setPosition(Vec2f position) {
  hitbox.setPosition(position);
}

void Component::setPosition(float x, float y) {
  hitbox.setPosition(x, y);
}

void Component::setCenter(Vec2f center) {
  hitbox.setCenter(center);
}

void Component::setCenter(float x, float y) {
  hitbox.setCenter(x, y);
}

void Component::move(Vec2f offset) {
  menuOffset += offset;
}

void Component::move(float x, float y) {
  menuOffset.x += x;
  menuOffset.y += y;
}

void Component::applyStyle(const Style& style) {
  this->style = style;
}

void Component::lock() {
  locked = true;
}

void Component::unlock() {
  locked = false;
}

Vec2f Component::getPosition() const {
  return hitbox.getPosition();
}

Vec2f Component::getCenter() const {
  return hitbox.getCenter();
}

const Hitbox& Component::getHitbox() const {
  return hitbox;
}

const Style& Component::getStyle() {
  return style;
}

bool Component::isLocked() const {
  return locked;
}
