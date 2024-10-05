#include "roundedRectangle.hpp"
#include "util/math.hpp"
#include <cmath>

namespace gs {

  #include "util/output.hpp"

  namespace priv {

    RoundedRectangleShape::RoundedRectangleShape(Vec2f size, float radius, unsigned int cornerPointCount)
        : rrSize(size), rrRadius(radius), cornerPointCount(cornerPointCount) {
        update();
    }

    void RoundedRectangleShape::setSize(Vec2f size) {
        rrSize = size;
        update();
    }

    void RoundedRectangleShape::setCornersRadius(float radius) {
        rrRadius = radius;
        update();
    }

    void RoundedRectangleShape::setCornerPointCount(unsigned int count) {
        cornerPointCount = count;
        update();
    }

    size_t RoundedRectangleShape::getPointCount() const {
        return cornerPointCount * 4;
    }

    sf::Vector2f RoundedRectangleShape::getPoint(size_t index) const {
        if (index >= getPointCount())
            return sf::Vector2f(0, 0);

        float deltaAngle = 90.0f / (cornerPointCount - 1);
        size_t centerIndex = index / cornerPointCount;
        sf::Vector2f center;
        float angle = 0;

        switch (centerIndex)
        {
            case 0: center = {rrRadius, rrRadius}; angle = 180.0f; break;
            case 1: center = {rrSize.x - rrRadius, rrRadius}; angle = 270.0f; break;
            case 2: center = {rrSize.x - rrRadius, rrSize.y - rrRadius}; angle = 0.0f; break;
            case 3: center = {rrRadius, rrSize.y - rrRadius}; angle = 90.0f; break;
        }

        return {
            center.x + std::cos(util::toRadians(angle + deltaAngle * (index % cornerPointCount))) * rrRadius,
            center.y + std::sin(util::toRadians(angle + deltaAngle * (index % cornerPointCount))) * rrRadius
        };
    }

    Vec2f RoundedRectangleShape::getSize() const {
        return rrSize;
    }

    float RoundedRectangleShape::getCornersRadius() const {
        return rrRadius;
    }

  } // namespace priv

  RoundedRectangle::RoundedRectangle() : Component() {}

  RoundedRectangle::~RoundedRectangle() = default;

  void RoundedRectangle::render(sf::RenderTarget* target, sf::RenderStates renderStates) {
      target->draw(internalShape, renderStates);
  }

  void RoundedRectangle::setPosition(Vec2f position) {
      internalShape.setPosition(position);
      generateHitbox();
  }

  void RoundedRectangle::setPosition(float xpos, float ypos) {
      setPosition(Vec2f(xpos, ypos));
  }

  void RoundedRectangle::setCenter(Vec2f position) {
      Vec2f size = internalShape.getSize();
      setPosition(position - size / 2.0f);
  }

  void RoundedRectangle::setCenter(float xpos, float ypos) {
      setCenter(Vec2f(xpos, ypos));
  }

  void RoundedRectangle::move(Vec2f offset) {
      internalShape.move(offset);
      generateHitbox();
  }

  void RoundedRectangle::move(float offsetx, float offsety) {
      move(Vec2f(offsetx, offsety));
  }

  void RoundedRectangle::applyStyle(const Style& style) {
    this->style = style;
  }

  void RoundedRectangle::lock() {
    locked = true;
  }

  void RoundedRectangle::unlock() {
    locked = false;
  }

  void RoundedRectangle::setSize(Vec2f size) {
      internalShape.setSize(size);
      generateHitbox();
  }

  void RoundedRectangle::setSize(float width, float height) {
      setSize(Vec2f(width, height));
  }

  void RoundedRectangle::setCornerRadius(float radius) {
      internalShape.setCornersRadius(radius);
      generateHitbox();
  }

  void RoundedRectangle::setCornerPointCount(unsigned int count) {
      internalShape.setCornerPointCount(count);
  }

  void RoundedRectangle::setFillColor(Color color) {
      internalShape.setFillColor(color);
  }

  void RoundedRectangle::setOutlineThickness(float thickness) {
      internalShape.setOutlineThickness(thickness);
      generateHitbox();
  }

  void RoundedRectangle::setOutlineColor(Color color) {
      internalShape.setOutlineColor(color);
  }

  Vec2f RoundedRectangle::getPosition() const {
      return internalShape.getPosition();
  }

  Vec2f RoundedRectangle::getCenter() const {
      return getPosition() + internalShape.getSize() / 2.0f;
  }

  const Hitbox& RoundedRectangle::getHitbox() const {
      return Component::getHitbox();
  }

  const Style& RoundedRectangle::getStyle() {
    return style;
  }

  bool RoundedRectangle::isLocked() const {
    return locked;
  }

  Vec2f RoundedRectangle::getSize() const {
      return internalShape.getSize();
  }

  float RoundedRectangle::getCornerRadius() const {
      return internalShape.getCornersRadius();
  }

  unsigned int RoundedRectangle::getCornerPointCount() const {
      return internalShape.getPointCount();
  }

  Color RoundedRectangle::getFillColor() const {
      return internalShape.getFillColor();
  }

  float RoundedRectangle::getOutlineThickness() const {
      return internalShape.getOutlineThickness();
  }

  Color RoundedRectangle::getOutlineColor() const {
      return internalShape.getOutlineColor();
  }

  priv::RoundedRectangleShape& RoundedRectangle::getInternalShape() {
      return internalShape;
  }

  void RoundedRectangle::generateHitbox() {
      Hitbox newHitbox;
      newHitbox.setSize(getSize());
      newHitbox.setPosition(getPosition());
      hitbox = newHitbox;
  }

  void draw(sf::RenderTarget* target, RoundedRectangle& rect, sf::RenderStates renderStates) {
      rect.render(target, renderStates);
  }

  std::ostream& operator<<(std::ostream& os, const RoundedRectangle& rect) {
      return os << "RoundedRectangle(pos: " << rect.getPosition()
                << ", size: " << rect.getSize()
                << ", radius: " << rect.getCornerRadius() << ")";
  }
}
