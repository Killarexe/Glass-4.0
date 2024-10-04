#include "text.hpp"
#include <SFML/Graphics.hpp>

namespace gs {
  #include "util/output.hpp"

  Text::Text() : shadow(false), shadowOffset(1.0f, 1.0f), shadowColor(0, 0, 0, 128) {
    locked = false;
  }

  Text::~Text() = default;

  void Text::update() {
    // No update logic needed for Text
  }

  void Text::render(sf::RenderTarget* target, sf::RenderStates renderStates) {
    if (shadow) {
      sf::Text shadowText = text;
      shadowText.setPosition(text.getPosition() + sf::Vector2f(shadowOffset.x, shadowOffset.y));
      shadowText.setFillColor(sf::Color(shadowColor.r, shadowColor.g, shadowColor.b, shadowColor.a));
      target->draw(shadowText, renderStates);
    }
    target->draw(text, renderStates);
  }

  void Text::setPosition(Vec2f position) {
    text.setPosition(sf::Vector2f(position.x, position.y));
    generateHitbox();
  }

  void Text::setPosition(float xpos, float ypos) {
    setPosition(Vec2f(xpos, ypos));
  }

  void Text::setCenter(Vec2f position) {
    sf::FloatRect bounds = text.getLocalBounds();
    setPosition(position.x - bounds.width / 2, position.y - bounds.height / 2);
  }

  void Text::setCenter(float xpos, float ypos) {
    setCenter(Vec2f(xpos, ypos));
  }

  void Text::move(Vec2f offset) {
    text.move(sf::Vector2f(offset.x, offset.y));
    generateHitbox();
  }

  void Text::move(float offsetx, float offsety) {
    move(Vec2f(offsetx, offsety));
  }

  void Text::applyStyle(const Style& style) {
    this->style = style;
    setFillColor(style.fillColor);
    setOutlineColor(style.outlineColor);
    setOutlineThickness(style.outlineThickness);
    // Apply other style properties as needed
  }

  void Text::lock() {
    locked = true;
  }

  void Text::unlock() {
    locked = false;
  }

  void Text::setScale(Vec2f scalar) {
    text.setScale(sf::Vector2f(scalar.x, scalar.y));
    generateHitbox();
  }

  void Text::setScale(float scalex, float scaley) {
    setScale(Vec2f(scalex, scaley));
  }

  void Text::setFont(const sf::Font& font) {
    text.setFont(font);
    generateHitbox();
  }

  void Text::setString(const std::string& string) {
    text.setString(string);
    generateHitbox();
  }

  void Text::setFillColor(Color color) {
    text.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
  }

  void Text::setOutlineThickness(float thickness) {
    text.setOutlineThickness(thickness);
    generateHitbox();
  }

  void Text::setOutlineColor(Color outlineColor) {
    text.setOutlineColor(sf::Color(outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a));
  }

  void Text::setShadow(bool hasShadow) {
    shadow = hasShadow;
  }

  void Text::setShadowOffset(Vec2f offset) {
    shadowOffset = offset;
  }

  void Text::setShadowOffset(float offsetx, float offsety) {
    setShadowOffset(Vec2f(offsetx, offsety));
  }

  void Text::setShadowColor(Color shadowColor) {
    this->shadowColor = shadowColor;
  }

  Vec2f Text::getPosition() const {
    sf::Vector2f pos = text.getPosition();
    return Vec2f(pos.x, pos.y);
  }

  Vec2f Text::getCenter() const {
    sf::FloatRect bounds = text.getLocalBounds();
    sf::Vector2f pos = text.getPosition();
    return Vec2f(pos.x + bounds.width / 2, pos.y + bounds.height / 2);
  }

  const Hitbox& Text::getHitbox() const {
    return hitbox;
  }

  const Style& Text::getStyle() {
    return style;
  }

  bool Text::isLocked() const {
    return locked;
  }

  Vec2f Text::getScale() const {
    sf::Vector2f scale = text.getScale();
    return Vec2f(scale.x, scale.y);
  }

  const sf::Font& Text::getFont() const {
    return *text.getFont();
  }

  const std::string& Text::getString() const {
    return text.getString();
  }

  Color Text::getFillColor() const {
    sf::Color color = text.getFillColor();
    return Color(color.r, color.g, color.b, color.a);
  }

  float Text::getOutlineThickness() const {
    return text.getOutlineThickness();
  }

  Color Text::getOutlineColor() const {
    sf::Color color = text.getOutlineColor();
    return Color(color.r, color.g, color.b, color.a);
  }

  bool Text::hasShadow() const {
    return shadow;
  }

  Vec2f Text::getShadowOffset() const {
    return shadowOffset;
  }

  Color Text::getShadowColor() const {
    return shadowColor;
  }

  sf::Text& Text::getText() {
    return text;
  }

  void Text::generateHitbox() {
    sf::FloatRect bounds = text.getLocalBounds();
    sf::Vector2f position = text.getPosition();
    Hitbox result = Hitbox(Hitbox::Shape::Rectangle);
    result.setPosition(position);
    result.setSize(bounds.getSize());
    hitbox = result;
  }

  void draw(sf::RenderTarget* target, Text& text, sf::RenderStates renderStates) {
    text.render(target, renderStates);
  }

  std::ostream& operator<<(std::ostream& os, const Text& text) {
    os << "Text: " << text.getString() << " at position " << text.getPosition();
    return os;
  }

} // namespace gs
