#include "transition.hpp"

namespace gs {
  Transition::Transition() : 
    percentage(0),
    min(0),
    max(255),
    inc(5),
    state(0),
    switchedState(false),
    color(Color::Black),
    position(0, 0) {
  }

  Transition::~Transition() {}

  void Transition::update() {
    if (state != 0) {
      percentage += inc * state;
      
      if (percentage >= max) {
        percentage = max;
        state = -1;
        switchedState = true;
      } else if (percentage <= min) {
        percentage = min;
        state = 0;
        switchedState = false;
      }
    }
  }

  void Transition::start() {
    if (state == 0) {
      state = 1;
      switchedState = false;
    }
  }

  void Transition::setType(Type newType) {
    type = newType;
    
    switch (type) {
      case Type::Fade:
        min = 0;
        max = 255;
        inc = 5;
        break;
      case Type::Scope:
        min = 0;
        max = 100;
        inc = 2;
        break;
    }
    
    percentage = min;
    state = 0;
    switchedState = false;
  }

  void Transition::apply(sf::RenderTarget& target) {
    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f(target.getSize()));
    
    switch (type) {
      case Type::Fade:
        color.a = static_cast<sf::Uint8>(percentage);
        overlay.setFillColor(color);
        target.draw(overlay);
        break;
      case Type::Scope:
        float radius = (percentage / 100.0f) * 
          std::max(target.getSize().x, target.getSize().y);
        sf::CircleShape circle(radius);
        circle.setFillColor(color);
        circle.setPosition(position - sf::Vector2f(radius, radius));
        target.draw(circle);
        break;
    }
  }

  void Transition::setPosition(Vec2f newPosition) {
    position = newPosition;
  }

  void Transition::setPosition(float xpos, float ypos) {
    position.x = xpos;
    position.y = ypos;
  }

  Vec2f Transition::getPosition() const {
    return position;
  }
}
