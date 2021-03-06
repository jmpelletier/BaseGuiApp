
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once

#include "imgui.h"

namespace JMP
{
	class Application
	{
	protected:
		float clearColorRGBA[4];
		float clearColorRGBAPremultiplied[4];
		
		void drawGUI();

	public:
		Application();
		virtual ~Application();

		void renderGUI();

		inline void setClearColor(float r, float g, float b, float a)
		{
			clearColorRGBA[0] = r;
			clearColorRGBA[1] = g;
			clearColorRGBA[2] = b;
			clearColorRGBA[3] = a;

			clearColorRGBAPremultiplied[0] = r * a;
			clearColorRGBAPremultiplied[1] = g * a;
			clearColorRGBAPremultiplied[2] = b * a;
			clearColorRGBAPremultiplied[3] = a;
		}

		inline float const* const getClearColor() const
		{
			return clearColorRGBA;
		}

		inline float const* const getClearColorPremultiplied() const
		{
			return clearColorRGBAPremultiplied;
		}
	};
}