#include "textbox.hpp"
#include "input/key.hpp"
#include <SFML/Window/Keyboard.hpp>

namespace gs {
  Textbox::Textbox() : Button() {
    // Initialize Textbox-specific members
  }

  Textbox::~Textbox() {
    // Destructor
  }

  void Textbox::update() {
    Button::update(); // Call parent class update

    if (isActive && inputMethod == InputMethod::Keyboard) {
      sf::String textString(input::textUnicode);
      std::string input = textString.toAnsiString();
      if (!input.empty() && storedString.length() < maxLength) {
        if (validInputs == ValidInputs::Alpha && std::isalpha(input[0])) {
          storedString += input;
        } else if (validInputs == ValidInputs::Numeric && std::isdigit(input[0])) {
          storedString += input;
        } else if (validInputs == ValidInputs::AlphaNumeric && std::isalnum(input[0])) {
          storedString += input;
        }
      }

      // Handle backspace
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && !storedString.empty()) {
        storedString.pop_back();
      }

      // Update text display
      updateTextDisplay();
    }

    // Handle cursor blinking
    static int tickCount = 0;
    if (++tickCount >= cursorTickSpeed) {
      tickCount = 0;
      // Toggle cursor visibility
    }
  }

  void Textbox::setStoredString(const std::string& string) {
    storedString = string;
    updateTextDisplay();
  }

  void Textbox::setMessageString(const std::string& string) {
    defaultMessage = string;
    updateTextDisplay();
  }

  void Textbox::setMaxInputLength(size_t length) {
    maxLength = length;
  }

  void Textbox::setCursorTickSpeed(int speed) {
    cursorTickSpeed = speed;
  }

  void Textbox::setActive(bool active) {
    isActive = active;
  }

  const std::string& Textbox::getStoredString() const {
    return storedString;
  }

  const std::string& Textbox::getMessageString() const {
    return defaultMessage;
  }

  size_t Textbox::getMaxInputLength() const {
    return maxLength;
  }

  int Textbox::getCursorTickSpeed() const {
    return cursorTickSpeed;
  }

  bool Textbox::getActive() const {
    return isActive;
  }

  // Protected helper method
  void Textbox::updateTextDisplay() {
    std::string displayText;
    switch (textRenderMethod) {
      case TextRenderMethod::None:
        displayText = "";
        break;
      case TextRenderMethod::Message:
        displayText = defaultMessage;
        break;
      case TextRenderMethod::StoredValue:
        displayText = storedString;
        break;
      case TextRenderMethod::MessageAndStoredValue:
        displayText = storedString.empty() ? defaultMessage : storedString;
        break;
    }
    
    Button::setString(displayText); // Assuming Button has a setString method
  }
}
