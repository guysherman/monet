#ifndef _RENDERPASS_PARAMETER_H_
#define _RENDERPASS_PARAMETER_H_
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
#include <functional>
#include <string>

// C Standard Headers


// Boost Headers

// 3rd Party Headers


// GTK Headers


// Our Headers



namespace monet
{
	namespace renderer
	{
		class RenderPassParameter
		{
		public:
			RenderPassParameter(std::string name, std::function<void(void)> changedCallback) : parameterName(name), changedCallback(changedCallback) {}
			virtual ~RenderPassParameter() {}

		protected:
			std::string parameterName;
			std::function<void(void)> changedCallback;
			

		};

		template <class TValue>
		class TypedRenderPassParameter : public RenderPassParameter
		{
		public:
			TypedRenderPassParameter(std::string name, TValue value, std::function<void(void)> changedCallback) : RenderPassParameter(name, changedCallback), value(value)
			{

			}

			virtual ~TypedRenderPassParameter() {}

			TValue GetValue()
			{
				return value;
			}

			void SetValue(TValue value)
			{
				this->value = value;
				changedCallback();
			}

		protected:
			TValue value;
		};
	}
}

#endif // _RENDERPASS_PARAMETER_H_