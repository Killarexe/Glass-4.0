#include "slider.hpp"
#include "hitbox.hpp"
#include "input/mouse.hpp"

namespace gs {

  #include "util/output.hpp"

  Slider::Slider() : isSelected(false), isClickedOn(false), percentage(0.0f), renderPercentage(0.0f), clampToEdge(true), disableMovement(false) {
    direction = Direction::Horizontal;
    onColor = sf::Color::White;
    offColor = sf::Color::Black;
    onOutlineColor = sf::Color::Black;
    offOutlineColor = sf::Color::Black;
    onOutlineThickness = 1.0f;
    offOutlineThickness = 1.0f;
  }

  Slider::~Slider() {}

  void Slider::update() {
    if (!isLocked()) {
      button.update();
      
      if (button.isSelected) {
        isSelected = true;
      } else {
        isSelected = false;
      }

      if (button.isClickedOn) {
        isClickedOn = true;
        if (!disableMovement) {
          Vec2f mousePos = input::mousePosition;
          Vec2f sliderPos = getPosition();
          Vec2f sliderSize = getSize();

          if (direction == Direction::Horizontal) {
            float newX = std::max(sliderPos.x, std::min(mousePos.x, sliderPos.x + sliderSize.x));
            percentage = (newX - sliderPos.x) / sliderSize.x * 100.0f;
          } else {
            float newY = std::max(sliderPos.y, std::min(mousePos.y, sliderPos.y + sliderSize.y));
            percentage = (newY - sliderPos.y) / sliderSize.y * 100.0f;
          }

          setButtonPosition(calculateButtonPosition());
        }
      } else {
        isClickedOn = false;
      }

      // Smooth transition for renderPercentage
      renderPercentage += (percentage - renderPercentage) * 0.1f;
    }
  }

  void Slider::render(sf::RenderTarget* target, sf::RenderStates renderStates) {
    // Render the slider bar
    sf::RectangleShape bar(getSize());
    bar.setPosition(getPosition());
    bar.setFillColor(offColor);
    bar.setOutlineColor(offOutlineColor);
    bar.setOutlineThickness(offOutlineThickness);
    target->draw(bar, renderStates);

    // Render the filled portion of the bar
    sf::RectangleShape filledBar;
    if (direction == Direction::Horizontal) {
      filledBar.setSize(Vec2f(getSize().x * renderPercentage / 100.0f, getSize().y));
    } else {
      filledBar.setSize(Vec2f(getSize().x, getSize().y * renderPercentage / 100.0f));
    }
    filledBar.setPosition(getPosition());
    filledBar.setFillColor(onColor);
    filledBar.setOutlineColor(onOutlineColor);
    filledBar.setOutlineThickness(onOutlineThickness);
    target->draw(filledBar, renderStates);

    // Render the button
    button.render(target, renderStates);
  }

  void Slider::setPosition(Vec2f position) {
    Component::setPosition(position);
    setButtonPosition(calculateButtonPosition());
    generateHitbox();
  }

  void Slider::setPosition(float xpos, float ypos) {
    setPosition(Vec2f(xpos, ypos));
  }

  void Slider::setCenter(Vec2f position) {
    setPosition(position - getSize() / 2.0f);
  }

  void Slider::setCenter(float xpos, float ypos) {
    setCenter(Vec2f(xpos, ypos));
  }

  void Slider::move(Vec2f offset) {
    setPosition(getPosition() + offset);
  }

  void Slider::move(float offsetx, float offsety) {
    move(Vec2f(offsetx, offsety));
  }

  void Slider::applyStyle(const Style& style) {
    button.applyStyle(style);
    this->style = style;
  }

  void Slider::lock() {
    Component::lock();
    button.lock();
  }

  void Slider::unlock() {
    Component::unlock();
    button.unlock();
  }

  void Slider::setSize(Vec2f size) {
    button.setSize(size);
    generateHitbox();
    setButtonPosition(calculateButtonPosition());
  }

  void Slider::setSize(float width, float height) {
    setSize(Vec2f(width, height));
  }

  void Slider::setOnColor(Color color) {
    onColor = color;
  }

  void Slider::setOffColor(Color color) {
    offColor = color;
  }

  void Slider::setOnOutlineColor(Color color) {
    onOutlineColor = color;
  }

  void Slider::setOffOutlineColor(Color color) {
    offOutlineColor = color;
  }

  void Slider::setOnOutlineThickness(float thickness) {
    onOutlineThickness = thickness;
  }

  void Slider::setOffOutlineThickness(float thickness) {
    offOutlineThickness = thickness;
  }

  void Slider::setClampedToEdge(bool clamped) {
    clampToEdge = clamped;
    setButtonPosition(calculateButtonPosition());
  }

  void Slider::setPercentage(float newPercentage) {
    percentage = std::max(0.0f, std::min(newPercentage, 100.0f));
    setButtonPosition(calculateButtonPosition());
  }

  void Slider::setPercentage(float newPercentage, float max) {
    setPercentage(newPercentage / max * 100.0f);
  }

  Vec2f Slider::getPosition() const {
    return Component::getPosition();
  }

  Vec2f Slider::getCenter() const {
    return getPosition() + getSize() / 2.0f;
  }

  const Hitbox& Slider::getHitbox() const {
    return Component::getHitbox();
  }

  const Style& Slider::getStyle() {
    return style;
  }

  bool Slider::isLocked() const {
    return Component::isLocked();
  }

  Vec2f Slider::getSize() const {
    return button.getSize();
  }

  Color Slider::getOnColor() const {
    return onColor;
  }

  Color Slider::getOffColor() const {
    return offColor;
  }

  Color Slider::getOnOutlineColor() const {
    return onOutlineColor;
  }

  Color Slider::getOffOutlineColor() const {
    return offOutlineColor;
  }

  float Slider::getOnOutlineThickness() const {
    return onOutlineThickness;
  }

  float Slider::getOffOutlineThickness() const {
    return offOutlineThickness;
  }

  bool Slider::getClampedToEdge() const {
    return clampToEdge;
  }

  float Slider::getPercentage() const {
    return percentage;
  }

  float Slider::getPercentage(float max) const {
    return percentage / 100.0f * max;
  }

  void Slider::generateHitbox() {
    Hitbox newHitbox(Hitbox::Shape::Rectangle);
    newHitbox.setPosition(getPosition());
    newHitbox.setSize(getSize());
    hitbox = newHitbox;
  }

  void Slider::setButtonPosition(Vec2f position) {
    button.setPosition(position);
  }

  void Slider::setButtonPosition(float xpos, float ypos) {
    setButtonPosition(Vec2f(xpos, ypos));
  }

  Vec2f Slider::getButtonPosition() {
    return button.getPosition();
  }

  Vec2f Slider::getButtonSize() {
    return button.getSize();
  }

  Vec2f Slider::calculateButtonPosition() {
    Vec2f sliderPos = getPosition();
    Vec2f sliderSize = getSize();
    Vec2f buttonSize = getButtonSize();

    if (direction == Direction::Horizontal) {
      float x = sliderPos.x + (sliderSize.x - buttonSize.x) * percentage / 100.0f;
      float y = sliderPos.y + (sliderSize.y - buttonSize.y) / 2.0f;
      return Vec2f(x, y);
    } else {
      float x = sliderPos.x + (sliderSize.x - buttonSize.x) / 2.0f;
      float y = sliderPos.y + (sliderSize.y - buttonSize.y) * percentage / 100.0f;
      return Vec2f(x, y);
    }
  }

  void draw(sf::RenderTarget* target, Slider& slider, sf::RenderStates renderStates) {
    slider.render(target, renderStates);
  }

  std::ostream& operator<<(std::ostream& os, const Slider& slider) {
    os << "Slider: " << slider.getPosition() << " " << slider.getSize() << " " << slider.getPercentage() << "%";
    return os;
  }

}
