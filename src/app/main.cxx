/*
	Monet is an open-source platform for building GPU-accelerated image
	processing applications.
	Copyright (C) 2017  Guy Sherman

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

	Contact the author via https://github.com/guysherman
*/


// C++ Standard Headers
#include <iostream>

// C Standard Headers


// Boost Headers

// 3rd Party Headers
#define GLM_PRECISION_MEDIUMP_INT
#define GLM_PRECISION_HIGHP_FLOAT
#include <glm/vec2.hpp>

// GTK Headers


// Our Headers
#include <ui/AppDelegate.h>
#include <ui/Window.h>

int main(int argc, char **argv) {
	monet::ui::AppDelegate::instance = new monet::ui::AppDelegate();
	auto window = std::shared_ptr<monet::ui::Window>( new monet::ui::Window("Monet Photo", glm::vec2(1280, 1024)) );
	monet::ui::AppDelegate::instance->Run(window);
}
