#pragma once

///////////////////////////////////////////////////////////////////////////////
/// Glass 4.0 UI API - A multipurpose UI library created for and with SFML. 
/// Copyright (C) 2020 - 2022 by CodeNoodles. 
/// 
/// Permission is granted to anyone to use this software for any purpose,
/// including commercial applications, and to alter it and redistribute it freely,
/// subject to the following restrictions:
///
/// 1. The origin of this software must not be misrepresented;
///    you must not claim that you wrote the original software.
///    If you use this software in a product, an acknowledgment
///    in the product documentation would be appreciated but is not required.
///
/// 2. Altered source versions must be plainly marked as such,
///    and must not be misrepresented as being the original software.
///
/// 3. This notice may not be removed or altered from any source distribution.
/// 
/// To get started try the code below the header files. 
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////////////////////////

#include "macros.hpp"
#include "typedef.hpp"
#include "util/output.hpp"
#include "util/math.hpp"
#include "util/state.hpp"
#include "util/output.hpp"
#include "util/clock.hpp"
#include "input/mouse.hpp"
#include "input/key.hpp"
#include "hitbox.hpp"
#include "component.hpp"
#include "style.hpp"
#include "text.hpp"
#include "sprite.hpp"
#include "roundedRectangle.hpp"
#include "button.hpp"
#include "checkbox.hpp"
#include "textbox.hpp"
#include "slider.hpp"
#include "graph.hpp"
#include "menu.hpp"
#include "transition.hpp"

///////////////////////////////////////////////////////////////////////////////
/// #include <Glass/glass.hpp>
/// 
/// gs::Button button1;
/// gs::util::Clock clock1;
/// 
/// int main() {
/// 	sf::RenderWindow window(sf::VideoMode(720.0f, 480.0f), "Glass 4.0 Example");
/// 
/// 	gs::input::setWindow(&window);
/// 
/// 	button1.setSize(100.0f, 50.0f);
/// 	button1.setPosition(200.0f, 200.0f);
/// 
/// 	while (window.isOpen()) {
/// 		clock1.begin();
/// 
/// 		sf::Event action;
/// 
/// 		gs::input::updateInputs();
/// 
/// 		while (window.pollEvent(action)) {
/// 			gs::input::updateEvents(action);
/// 
/// 			switch (action.type) {
/// 			case sf::Event::Closed:
/// 				window.close();
/// 				break;
/// 			}
/// 		}
/// 
/// 		button1.update();
/// 
/// 		window.clear(gs::Color(0, 200, 255));
/// 
/// 		gs::draw(&window, button1);
/// 
/// 		window.display();
/// 
/// 		clock1.end();
/// 		clock1.wait(60);
/// 	}
/// 
/// 	return 0;
/// }
///////////////////////////////////////////////////////////////////////////////
