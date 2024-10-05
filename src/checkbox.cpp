#include "checkbox.hpp"

namespace gs {
  void Checkbox::update() {
    Button::update();
    prvsClick = click;
    //NOTE: Not sure of this line of code. Needs checking.
    click = isClickedOn && !prvsClick;
    on = isClickedOn;
  }
}
