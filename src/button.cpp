#include "button.hpp"

namespace gs {

  #include "util/output.hpp"

  Button::Button() : isSelected(false), isClickedOn(false) {}

  Button::~Button() {}

  void Button::update() {
    if (!isLocked()) {
      updateColorAndScale();
    }
  }

  void Button::render(sf::RenderTarget* target, sf::RenderStates renderStates) {
    if (renderMethod == RenderMethod::Basic) {
      if (shape == Shape::Rectangle) {
        sf::RectangleShape rect(getSize());
        rect.setPosition(getPosition());
        rect.setFillColor(currentColor);
        rect.setOutlineThickness(outlineThickness);
        rect.setOutlineColor(outlineColor);
        target->draw(rect, renderStates);
      } else if (shape == Shape::Circle) {
        sf::CircleShape circle(getRadius());
        circle.setPosition(getPosition());
        circle.setFillColor(currentColor);
        circle.setOutlineThickness(outlineThickness);
        circle.setOutlineColor(outlineColor);
        target->draw(circle, renderStates);
      }
    } else if (renderMethod == RenderMethod::Textured) {
      sprite.render(target, renderStates);
    }
    text.render(target, renderStates);
  }

  void Button::clearShapeColors() {
    inActiveFillColor = sf::Color::White;
    selectedFillColor = sf::Color::White;
    clickedFillColor = sf::Color::White;
  }

  void Button::clearShapeScaleModifiers() {
    selectedScaleModifier = 1.0f;
    clickedScaleModifier = 1.0f;
  }

  void Button::clearTextColors() {
    inActiveTextFillColor = sf::Color::White;
    selectedTextFillColor = sf::Color::White;
    clickedTextFillColor = sf::Color::White;
  }

  void Button::clearTextScaleModifiers() {
    selectedTextScaleModifier = 1.0f;
    clickedTextScaleModifier = 1.0f;
  }

  void Button::clearColors() {
    clearShapeColors();
    clearTextColors();
  }

  void Button::clearScaleModifiers() {
    clearShapeScaleModifiers();
    clearTextScaleModifiers();
  }

  void Button::clear() {
    clearColors();
    clearScaleModifiers();
  }

  void Button::setPosition(Vec2f position) {
    Component::setPosition(position);
    text.setPosition(position + textOffset);
    sprite.setPosition(position);
    generateHitbox();
  }

  void Button::setPosition(float xpos, float ypos) {
    setPosition(Vec2f(xpos, ypos));
  }

  void Button::setCenter(Vec2f position) {
    Vec2f size = getSize();
    setPosition(position - size / 2.0f);
  }

  void Button::setCenter(float xpos, float ypos) {
    setCenter(Vec2f(xpos, ypos));
  }

  void Button::move(Vec2f offset) {
    setPosition(getPosition() + offset);
  }

  void Button::move(float offsetx, float offsety) {
    move(Vec2f(offsetx, offsety));
  }

  void Button::applyStyle(const Style& style) {
    this->style = style;
  }

  void Button::lock() {
    Component::lock();
  }

  void Button::unlock() {
    Component::unlock();
  }

  void Button::setSize(Vec2f size) {
    if (shape == Shape::Rectangle) {
      virtualHitbox.setSize(size);
      sprite.setScale(size.x / sprite.getTexture().getSize().x, 
                      size.y / sprite.getTexture().getSize().y);
    }
    generateHitbox();
  }

  void Button::setSize(float sizex, float sizey) {
    setSize(Vec2f(sizex, sizey));
  }

  void Button::setRadius(float radius) {
    if (shape == Shape::Circle) {
      virtualHitbox.setRadius(radius);
      sprite.setScale(radius * 2 / sprite.getTexture().getSize().x, 
                      radius * 2 / sprite.getTexture().getSize().y);
    }
    generateHitbox();
  }

  Vec2f Button::getPosition() const {
    return Component::getPosition();
  }

  Vec2f Button::getCenter() const {
    return getPosition() + getSize() / 2.0f;
  }

  const Hitbox& Button::getHitbox() const {
    return Component::getHitbox();
  }

  const Style& Button::getStyle() {
    return style;
  }

  bool Button::isLocked() const {
    return Component::isLocked();
  }

  Vec2f Button::getSize() const {
    return virtualHitbox.getSize();
  }

  float Button::getRadius() const {
    return virtualHitbox.getRadius();
  }

  void Button::generateHitbox() {
    if (shape == Shape::Rectangle) {
      hitbox.setSize(virtualHitbox.getSize() * currentScaleModifier);
    } else if (shape == Shape::Circle) {
      hitbox.setRadius(virtualHitbox.getRadius() * currentScaleModifier);
    }
    hitbox.setPosition(getPosition());
  }

  void Button::updateColorAndScale(bool _customButton) {
    // Update color and scale based on button state
    if (isSelected && !isClickedOn) {
      currentColor = selectedFillColor;
      currentTextColor = selectedTextFillColor;
      currentScaleModifier = selectedScaleModifier;
      currentTextScaleModifier = selectedTextScaleModifier;
    } else if (isClickedOn) {
      currentColor = clickedFillColor;
      currentTextColor = clickedTextFillColor;
      currentScaleModifier = clickedScaleModifier;
      currentTextScaleModifier = clickedTextScaleModifier;
    } else {
      currentColor = inActiveFillColor;
      currentTextColor = inActiveTextFillColor;
      currentScaleModifier = 1.0f;
      currentTextScaleModifier = 1.0f;
    }

    text.setFillColor(currentTextColor);
    text.setScale(textScale.x * currentTextScaleModifier, textScale.y * currentTextScaleModifier);

    generateHitbox();
  }

  void draw(sf::RenderTarget* target, Button& button, sf::RenderStates renderStates) {
    button.render(target, renderStates);
  }

  std::ostream& operator<<(std::ostream& os, const Button& button) {
    os << "Button: " << button.getPosition() << " " << button.getSize();
    return os;
  }
}
