#include "key.hpp"
#include <SFML/Graphics.hpp>

namespace gs {
  namespace input {
    // Initialize external variables from mouse.hpp
    Vec2f mousePosition;
    Vec2f mouseChange;
    bool activeMouseClickL = false;
    bool activeMouseClickM = false;
    bool activeMouseClickR = false;
    bool mouseClickL = false;
    bool mouseClickM = false;
    bool mouseClickR = false;

    namespace priv {
      // Initialize private variables from mouse.hpp
      Vec2f prvsMousePosition;

      // Initialize private variables from key.hpp
      sf::RenderWindow* internalWindow = nullptr;
      Vec2f defaultWindowSize;
      int ticks = 0;
      bool space = false;
      bool backSpace = false;
      bool enter = false;
    }

    // Initialize external variables from key.hpp
    unsigned int textUnicode = 0;

    void setWindow(sf::RenderWindow* window) {
      priv::internalWindow = window;
      if (window) {
        sf::Vector2u size = window->getSize();
        priv::defaultWindowSize = Vec2f(static_cast<float>(size.x), static_cast<float>(size.y));
      }
    }

    void updateInputs() {
      if (!priv::internalWindow) {
        return;
      }

      priv::ticks++;

      // Update mouse position and change
      sf::Vector2i mousePos = sf::Mouse::getPosition(*priv::internalWindow);
      mousePosition = Vec2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
      mouseChange = mousePosition - priv::prvsMousePosition;
      priv::prvsMousePosition = mousePosition;

      // Update mouse clicks
      activeMouseClickL = sf::Mouse::isButtonPressed(sf::Mouse::Left);
      activeMouseClickM = sf::Mouse::isButtonPressed(sf::Mouse::Middle);
      activeMouseClickR = sf::Mouse::isButtonPressed(sf::Mouse::Right);

      // Update keyboard input
      priv::space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
      priv::backSpace = sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace);
      priv::enter = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);

      // Reset single-frame inputs
      mouseClickL = false;
      mouseClickM = false;
      mouseClickR = false;
      textUnicode = 0;
    }

    void updateEvents(sf::Event& event) {
      switch (event.type) {
        case sf::Event::MouseButtonPressed:
          if (event.mouseButton.button == sf::Mouse::Left) mouseClickL = true;
          if (event.mouseButton.button == sf::Mouse::Middle) mouseClickM = true;
          if (event.mouseButton.button == sf::Mouse::Right) mouseClickR = true;
          break;

        case sf::Event::TextEntered:
          textUnicode = event.text.unicode;
          break;

        default:
          break;
      }
    }

  } // namespace input
} // namespace gs
