#include "sprite.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace gs {

Sprite::Sprite() : outlineColor(Color::White), outlineThickness(0.0f) {}

Sprite::~Sprite() {}

void Sprite::update() {
    // This method is empty as mentioned in the header
}

void Sprite::render(sf::RenderTarget* target, sf::RenderStates renderStates) {
    if (outlineThickness > 0) {
        sf::Sprite outlineSprite = sprite;
        outlineSprite.setColor(outlineColor);
        outlineSprite.setScale(sprite.getScale().x + outlineThickness / sprite.getTextureRect().width,
                               sprite.getScale().y + outlineThickness / sprite.getTextureRect().height);
        target->draw(outlineSprite, renderStates);
    }
    target->draw(sprite, renderStates);
}

void Sprite::setPosition(Vec2f position) {
    Component::setPosition(position);
    sprite.setPosition(position);
}

void Sprite::setPosition(float xpos, float ypos) {
    Component::setPosition(xpos, ypos);
    sprite.setPosition(xpos, ypos);
}

void Sprite::setCenter(Vec2f position) {
    Component::setCenter(position);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(position);
}

void Sprite::setCenter(float xpos, float ypos) {
    setCenter(Vec2f(xpos, ypos));
}

void Sprite::move(Vec2f offset) {
    Component::move(offset);
    sprite.move(offset);
}

void Sprite::move(float offsetx, float offsety) {
    Component::move(offsetx, offsety);
    sprite.move(offsetx, offsety);
}

void Sprite::applyStyle(const Style& style) {
    Component::applyStyle(style);
    // Apply any relevant style properties to the sprite
}

void Sprite::lock() {
    Component::lock();
}

void Sprite::unlock() {
    Component::unlock();
}

void Sprite::setScale(Vec2f scalar) {
    sprite.setScale(scalar);
    generateHitbox();
}

void Sprite::setScale(float scalex, float scaley) {
    setScale(Vec2f(scalex, scaley));
}

void Sprite::setRotation(float angle) {
    sprite.setRotation(angle);
    generateHitbox();
}

void Sprite::rotate(float angle) {
    sprite.rotate(angle);
    generateHitbox();
}

void Sprite::setTexture(const sf::Texture& texture, bool resetRect) {
    sprite.setTexture(texture, resetRect);
    generateHitbox();
}

void Sprite::setTextureRect(const sf::IntRect& bounds) {
    sprite.setTextureRect(bounds);
    generateHitbox();
}

void Sprite::setColor(Color color) {
    sprite.setColor(color);
}

void Sprite::setOutlineThickness(float thickness) {
    outlineThickness = thickness;
}

void Sprite::setOutlineColor(Color color) {
    outlineColor = color;
}

Vec2f Sprite::getScale() const {
    return sprite.getScale();
}

float Sprite::getRotation() const {
    return sprite.getRotation();
}

const sf::Texture& Sprite::getTexture() const {
    return *sprite.getTexture();
}

sf::IntRect Sprite::getTextureRect() const {
    return sprite.getTextureRect();
}

Color Sprite::getColor() const {
    return sprite.getColor();
}

float Sprite::getOutlineThickness() const {
    return outlineThickness;
}

Color Sprite::getOutlineColor() const {
    return outlineColor;
}

sf::Sprite& Sprite::getSprite() {
    return sprite;
}

void Sprite::generateHitbox() {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    hitbox = Hitbox(Vec2f(bounds.left, bounds.top), Vec2f(bounds.width, bounds.height));
}

void mapSpriteToSize(Sprite& sprite, Vec2f size) {
    sf::FloatRect bounds = sprite.getSprite().getLocalBounds();
    sprite.setScale(size.x / bounds.width, size.y / bounds.height);
}

void mapSpriteToSize(sf::Sprite& sprite, Vec2f size) {
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setScale(size.x / bounds.width, size.y / bounds.height);
}

void draw(sf::RenderTarget* target, Sprite& sprite, sf::RenderStates renderStates) {
    sprite.render(target, renderStates);
}

std::ostream& operator<<(std::ostream& os, const Sprite& sprite) {
    os << "Sprite: Position(" << sprite.getPosition().x << ", " << sprite.getPosition().y << "), "
       << "Scale(" << sprite.getScale().x << ", " << sprite.getScale().y << "), "
       << "Rotation(" << sprite.getRotation() << ")";
    return os;
}

} // namespace gs
