#ifndef _MAINWINDOWLINUX_H_
#define _MAINWINDOWLINUX_H_
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
#include <memory>

// C Standard Headers


// Boost Headers

// 3rd Party Headers


// GTK Headers
#include <gtkmm.h>

// Our Headers
#include "renderer/ForwardDeclarations.h"

namespace monet
{
	
	namespace ui
	{
		class MainWindowGtk : public Gtk::Window
		{
		public:
			MainWindowGtk(const Glib::RefPtr<Gtk::Application>& app, std::weak_ptr<monet::renderer::Renderer> renderer);
			virtual ~MainWindowGtk();

			
		
		protected:
			

		private:
			Glib::RefPtr<Gtk::Builder> gtkBuilder;
			Gtk::Box clientArea;

			std::shared_ptr<Gtk::AboutDialog> aboutDialog;
			Gtk::Box *leftBox;
			Gtk::Box *mainBox;
			Gtk::Box *rightBox;
			Glib::RefPtr<Gio::SimpleActionGroup> mainActionGroup;

			std::weak_ptr<monet::renderer::Renderer> renderer;

			void showAbout();

			bool onRender(const Glib::RefPtr<Gdk::GLContext>& context);
			void onRealize();
		};
	}
}

#endif // _MAINWINDOWLINUX_H_