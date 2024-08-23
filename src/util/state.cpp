#include "state.hpp"

using namespace gs::util;

State::State() {
  this->currentState = 0;
  this->nextState = 0;
}

void State::changeState() {
  this->currentState = this->nextState;
  this->nextState = 0;
} 

void State::setState(int state) {
  this->currentState = state;
}

void State::setNextState(int state) {
  this->nextState = state;
}

int State::getState() const {
  return this->currentState;
}

int State::getNextState() const {
  return this->nextState;
}
