#include "graph.hpp"
#include "hitbox.hpp"
#include <algorithm>
#include <cmath>

namespace gs {

  #include "util/output.hpp"

  namespace priv {
    void renderLine(sf::RenderTarget* target, Vec2f p1, Vec2f p2, Color color) {
      sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(p1.x, p1.y), color),
        sf::Vertex(sf::Vector2f(p2.x, p2.y), color)
      };
      target->draw(line, 2, sf::Lines);
    }
  }

  Graph::Graph()
    : Component(), numOfPoints(20), lowerBound(0.0f), upperBound(0.0f),
      autoAdjustLower(false), autoAdjustUpper(false),
      backGroundColor(Color::White), lineColor(Color::Black),
      outlineColor(Color::Black), pointColor(Color::Red),
      outlineThickness(1.0f), pointThickness(2.0f) {
    graphTexture.create(100, 100);
    graphSprite.setTexture(graphTexture.getTexture());
  }

  Graph::~Graph() = default;

  void Graph::update() {
    if (isLocked()) return;
    
    if (autoAdjustLower || autoAdjustUpper) {
      auto [min, max] = std::minmax_element(points.begin(), points.end());
      if (autoAdjustLower) lowerBound = *min;
      if (autoAdjustUpper) upperBound = *max;
    }
  }

  void Graph::render(sf::RenderTarget* target, sf::RenderStates renderStates) {
    graphTexture.clear(backGroundColor);

    if (!points.empty()) {
      float xStep = graphTexture.getSize().x / static_cast<float>(numOfPoints - 1);
      float yScale = graphTexture.getSize().y / (upperBound - lowerBound);

      for (size_t i = 1; i < points.size(); ++i) {
        float x1 = (i - 1) * xStep;
        float x2 = i * xStep;
        float y1 = graphTexture.getSize().y - (points[i - 1] - lowerBound) * yScale;
        float y2 = graphTexture.getSize().y - (points[i] - lowerBound) * yScale;

        priv::renderLine(&graphTexture, Vec2f(x1, y1), Vec2f(x2, y2), lineColor);

        if (pointThickness > 0) {
          sf::CircleShape point(pointThickness);
          point.setFillColor(pointColor);
          point.setPosition(x2 - pointThickness, y2 - pointThickness);
          graphTexture.draw(point);
        }
      }
    }

    graphTexture.display();
    graphSprite.setTexture(graphTexture.getTexture());
    graphSprite.render(target, renderStates);
  }

  void Graph::graph(float value) {
    points.push_back(value);
    if (points.size() > numOfPoints) {
      points.erase(points.begin());
    }
  }

  void Graph::clear() {
    points.clear();
  }

  void Graph::setPosition(Vec2f position) {
    graphSprite.setPosition(position);
    generateHitbox();
  }

  void Graph::setPosition(float xpos, float ypos) {
    setPosition(Vec2f(xpos, ypos));
  }

  void Graph::setCenter(Vec2f position) {
    Vec2f size = getSize();
    setPosition(position - size / 2.0f);
  }

  void Graph::setCenter(float xpos, float ypos) {
    setCenter(Vec2f(xpos, ypos));
  }

  void Graph::move(Vec2f offset) {
    graphSprite.move(offset);
    generateHitbox();
  }

  void Graph::move(float offsetx, float offsety) {
    move(Vec2f(offsetx, offsety));
  }

  void Graph::applyStyle(const Style& style) {
    Component::applyStyle(style);
    setFillColor(style.fillColor);
    setLineColor(style.lineColor);
    setOutlineColor(style.outlineColor);
    setOutlineThickness(style.outlineThickness);
  }

  void Graph::lock() {
    Component::lock();
  }

  void Graph::unlock() {
    Component::unlock();
  }

  void Graph::setSize(Vec2f size) {
    graphTexture.create(static_cast<unsigned int>(size.x), static_cast<unsigned int>(size.y));
    graphSprite.setTexture(graphTexture.getTexture(), true);
    generateHitbox();
  }

  void Graph::setSize(float width, float height) {
    setSize(Vec2f(width, height));
  }

  void Graph::setLowerBound(float height) {
    lowerBound = height;
  }

  void Graph::setUpperBound(float height) {
    upperBound = height;
  }

  void Graph::setLowerBoundAutoAdjust(bool enabled) {
    autoAdjustLower = enabled;
  }

  void Graph::setUpperBoundAutoAdjust(bool enabled) {
    autoAdjustUpper = enabled;
  }

  void Graph::setPointCount(size_t numOfPoints) {
    this->numOfPoints = numOfPoints;
    while (points.size() > numOfPoints) {
      points.erase(points.begin());
    }
  }

  void Graph::setFillColor(Color color) {
    backGroundColor = color;
  }

  void Graph::setLineColor(Color color) {
    lineColor = color;
  }

  void Graph::setOutlineThickness(float thickness) {
    outlineThickness = thickness;
    graphSprite.setOutlineThickness(thickness);
  }

  void Graph::setPointThickness(float thickness) {
    pointThickness = thickness;
  }

  void Graph::setOutlineColor(Color color) {
    outlineColor = color;
    graphSprite.setOutlineColor(color);
  }

  void Graph::setPointColor(Color color) {
    pointColor = color;
  }

  Vec2f Graph::getPosition() const {
    return graphSprite.getPosition();
  }

  Vec2f Graph::getCenter() const {
    return getPosition() + getSize() / 2.0f;
  }

  const Hitbox& Graph::getHitbox() const {
    return Component::getHitbox();
  }

  const Style& Graph::getStyle() {
    return Component::getStyle();
  }

  bool Graph::isLocked() const {
    return Component::isLocked();
  }

  Vec2f Graph::getSize() const {
    return Vec2f(graphTexture.getSize().x, graphTexture.getSize().y);
  }

  float Graph::getLowerBound() const {
    return lowerBound;
  }

  float Graph::getUpperBound() const {
    return upperBound;
  }

  bool Graph::getLowerBoundAutoAdjust() const {
    return autoAdjustLower;
  }

  bool Graph::getUpperBoundAutoAdjust() const {
    return autoAdjustUpper;
  }

  size_t Graph::getPointCount() const {
    return numOfPoints;
  }

  Color Graph::getFillColor() const {
    return backGroundColor;
  }

  Color Graph::getLineColor() const {
    return lineColor;
  }

  float Graph::getOutlineThickness() const {
    return outlineThickness;
  }

  float Graph::getPointThickness() const {
    return pointThickness;
  }

  Color Graph::getOutlineColor() const {
    return outlineColor;
  }

  Color Graph::getPointColor() const {
    return pointColor;
  }

  void Graph::generateHitbox() {
    Hitbox newHitbox(Hitbox::Shape::Rectangle);
    newHitbox.setPosition(getPosition());
    newHitbox.setSize(getSize());
    hitbox = newHitbox;
  }

  void draw(sf::RenderTarget* target, Graph& graph, sf::RenderStates renderStates) {
    graph.render(target, renderStates);
  }

  std::ostream& operator<<(std::ostream& os, const Graph& graph) {
    return os << "Graph(pos: " << graph.getPosition()
              << ", size: " << graph.getSize()
              << ", points: " << graph.getPointCount() << ")";
  }

}
