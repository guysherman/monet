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
#include "../../include/ui/PlatformConfig.h"
#ifdef UI_PLATFORM_GTK

#include <GL/glew.h>

// C++ Standard Headers
#include <memory>
#include <iostream>

// C Standard Headers


// Boost Headers

// 3rd Party Headers


// GTK Headers
#include <gtkmm.h>

// Our Headers

#include "../../include/ui/gtk/MainWindow-gtk.h"
#include <renderer/Renderer.h>
#include <renderer/IRenderPass.h>
#include <renderer/SimpleRenderPass.h>


namespace monet
{
	namespace ui
	{
		MainWindowGtk::MainWindowGtk(const Glib::RefPtr<Gtk::Application>& app)
		: clientArea(Gtk::ORIENTATION_VERTICAL), 
			leftBox(nullptr), 
			mainBox(nullptr), 
			rightBox(nullptr)
		{

			set_title("Monet Photo");
			set_default_size(1280, 800);

			gtkBuilder = Gtk::Builder::create();

			add(clientArea);
			
			mainActionGroup = Gio::SimpleActionGroup::create();
			mainActionGroup->add_action("about", sigc::mem_fun(*this, &MainWindowGtk::showAbout));
			
			insert_action_group("app", mainActionGroup);

			try
			{
				gtkBuilder->add_from_file("assets/Menu.glade");
				gtkBuilder->add_from_file("assets/About.glade");
				gtkBuilder->add_from_file("assets/Layout.glade");
				//m_refBuilder->add_from_resource("./toolbar/toolbar.glade");
			}
			catch(const Glib::Error& ex)
			{
				std::cerr << "Building menus and toolbar failed: " <<  ex.what();
			}

			Gtk::MenuBar *menuBar = nullptr;
			gtkBuilder->get_widget("mainMenu", menuBar);
			if (!menuBar)
			{
				g_warning("menuBar not found");
			}
			else
			{
				clientArea.pack_start(*menuBar, Gtk::PACK_SHRINK);
			}

			Gtk::AboutDialog *about = nullptr;
			gtkBuilder->get_widget("aboutBox", about);
			if (!about)
			{
				g_warning("aboutBox not found");
			}
			else
			{
				aboutDialog = std::shared_ptr<Gtk::AboutDialog>(about);
			}

			Gtk::Paned *rootLayout = nullptr;
			gtkBuilder->get_widget("rootLayout", rootLayout);
			if (!rootLayout)
			{
				g_warning("rootLayout not found");
			}
			else
			{
				clientArea.pack_start(*rootLayout, Gtk::PACK_EXPAND_WIDGET);
				gtkBuilder->get_widget("leftBox", leftBox);
				gtkBuilder->get_widget("rightBox", rightBox);
				gtkBuilder->get_widget("mainBox", mainBox);
			}

			if (!mainBox)
			{
				g_warning("mainBox not found!");
			}
			else
			{
				glArea = Gtk::manage(new Gtk::GLArea());
				mainBox->pack_start(*glArea, Gtk::PACK_EXPAND_WIDGET);
				glArea->signal_render().connect(sigc::mem_fun(*this, &MainWindowGtk::onRender));
				glArea->signal_realize().connect(sigc::mem_fun(*this, &MainWindowGtk::onRealize));
				glArea->signal_resize().connect(sigc::mem_fun(*this, &MainWindowGtk::onResize));
			}

			show_all_children();
		}

		void MainWindowGtk::showAbout()
		{
			aboutDialog->show();
			aboutDialog->present();
		}

		bool MainWindowGtk::onRender(const Glib::RefPtr<Gdk::GLContext>& context)
		{
			renderer->Draw();
			// we completed our drawing; the draw commands will be
			// flushed at the end of the signal emission chain, and
			// the buffers will be drawn on the window
			return true;
		}

		void MainWindowGtk::onRealize() 
		{
			glArea->make_current();
			renderer = std::unique_ptr<monet::renderer::Renderer>(new monet::renderer::Renderer());
			auto pass = std::shared_ptr<monet::renderer::IRenderPass>(new monet::renderer::SimpleRenderPass());
			renderer->AddRenderPass(pass);
			
		}

		void MainWindowGtk::onResize(int width, int height)
		{
			renderer->ResizeView(width, height);
		}

		MainWindowGtk::~MainWindowGtk() {}

		
	}
}

#endif
