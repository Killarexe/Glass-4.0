#include "menu.hpp"
#include <algorithm>

namespace gs {
  namespace priv {
    bool defaultMenuEnabled = true;
  }

  Menu defaultMenu;

  Menu::Menu() {
    this->locked = false;
  }

  Menu::~Menu() = default;

  void Menu::update() {
    if (!locked) {
      for (auto& component : components) {
        component.ptr->update();
      }
    }
  }

  void Menu::render(sf::RenderTarget* target, sf::RenderStates renderStates) {
    for (auto& component : components) {
      component.ptr->render(target, renderStates);
    }
  }

  void Menu::add(Component* component, const std::string& name) {
    components.push_back({component, name});
    component->menuOffset = getPosition();
  }

  void Menu::add(Component* component) {
    add(component, "");
  }

  void Menu::remove(Component* component) {
    components.erase(
      std::remove_if(components.begin(), components.end(),
        [component](const ComponentContainer& container) {
          return container.ptr == component;
        }),
      components.end()
    );
  }

  void Menu::remove(const std::string& name) {
    components.erase(
      std::remove_if(components.begin(), components.end(),
        [&name](const ComponentContainer& container) {
          return container.name == name;
        }),
      components.end()
    );
  }

  void Menu::setPosition(Vec2f position) {
    hitbox.setPosition(position);
    updateInternalComponents();
  }

  void Menu::setPosition(float xpos, float ypos) {
    setPosition(Vec2f(xpos, ypos));
  }

  void Menu::setCenter(Vec2f position) {
    // Do nothing as specified in the header
  }

  void Menu::setCenter(float xpos, float ypos) {
    // Do nothing as specified in the header
  }

  void Menu::move(Vec2f offset) {
    hitbox.setPosition(hitbox.getPosition() + offset);
    updateInternalComponents();
  }

  void Menu::move(float offsetx, float offsety) {
    move(Vec2f(offsetx, offsety));
  }

  void Menu::applyStyle(const Style& style) {
    this->style = style;
    for (auto& component : components) {
      component.ptr->applyStyle(style);
    }
  }

  void Menu::lock() {
    locked = true;
  }

  void Menu::unlock() {
    locked = false;
  }

  Vec2f Menu::getPosition() const {
    return hitbox.getPosition();
  }

  Vec2f Menu::getCenter() const {
    return hitbox.getPosition(); // As specified, no center calculation
  }

  const Hitbox& Menu::getHitbox() const {
    return hitbox;
  }

  const Style& Menu::getStyle() {
    return style;
  }

  bool Menu::isLocked() const {
    return locked;
  }

  Component* Menu::operator[](size_t index) {
    if (index < components.size()) {
      return components[index].ptr;
    }
    return nullptr;
  }

  Component* Menu::operator[](const std::string& name) {
    auto it = std::find_if(components.begin(), components.end(),
      [&name](const ComponentContainer& container) {
        return container.name == name;
      });
    return (it != components.end()) ? it->ptr : nullptr;
  }

  void Menu::generateHitbox() {
    // Recalculate hitbox based on all components
    Vec2f min = getPosition(), max = getPosition();
    for (const auto& component : components) {
      const Hitbox& compHitbox = component.ptr->getHitbox();
      min.x = std::min(min.x, compHitbox.getPosition().x);
      min.y = std::min(min.y, compHitbox.getPosition().y);
      max.x = std::max(max.x, compHitbox.getPosition().x + compHitbox.getSize().x);
      max.y = std::max(max.y, compHitbox.getPosition().y + compHitbox.getSize().y);
    }
    hitbox.setPosition(min);
    hitbox.setSize(max - min);
  }

  void Menu::updateInternalComponents() {
    for (auto& component : components) {
      component.ptr->menuOffset = getPosition();
    }
  }

  void draw(sf::RenderTarget* target, Menu& menu, sf::RenderStates renderStates) {
    menu.render(target, renderStates);
  }

  std::ostream& operator<<(std::ostream& os, const Menu& menu) {
    os << "Menu with " << menu.components.size() << " components at position " << menu.getPosition();
    return os;
  }

  void enableDefaultMenu() {
    priv::defaultMenuEnabled = true;
  }

  void disableDefaultMenu() {
    priv::defaultMenuEnabled = false;
  }

  void updateDefaultMenu() {
    defaultMenu.update();
  }

  void drawDefaultMenu(sf::RenderTarget* target, sf::RenderStates renderStates) {
    defaultMenu.render(target, renderStates);
  }

} // namespace gs
