/*
  web_view_canvas.hpp

  Copyright (c) 2024 Leigh Johnston.  All Rights Reserved.

  This program is free software: you can redistribute it and / or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <neogfx/neogfx.hpp>

#include "web_view_canvas.hpp"

namespace neogfx
{
    web_view_canvas::web_view_canvas(i_widget& aParent, i_optional<i_string> const& aUrl) :
        base_type{ aParent }
    {
        init();
    }

    web_view_canvas::web_view_canvas(i_layout& aLayout, i_optional<i_string> const& aUrl) :
        base_type{ aLayout }
    {
        init();
    }

    void web_view_canvas::load_url(i_string const& aUrl)
    {
        iUrl = aUrl.to_std_string_view();
        update();
    }

    void web_view_canvas::init()
    {
        Painting([this](i_graphics_context& aGc)
        {
            auto const outlineStroke = 4.0_dip;
            if (!iUrl)
                aGc.draw_multiline_text(
                    point{ outlineStroke, outlineStroke }, 
                    u8"neogfx::web_view_canvas 🎊🎉😎\n\n"
                    "This web view canvas widget is\n"
                    "rendering from within the web view\n"
                    "plugin over a transparency background\n"
                    "rendered by the web view widget from\n"
                    "within the app.\n\n"
                    "Next up: integrate CEF to actually\n"
                    "render web pages."_t, 
                    font().with_size(32),
                    text_format{ color::White, text_effect{ text_effect_type::Outline, color::Black, outlineStroke } });
            else
                aGc.draw_multiline_text(
                    point{ outlineStroke, outlineStroke },
                    iUrl.value(),
                    font().with_size(32),
                    text_format{ color::White, text_effect{ text_effect_type::Outline, color::Black, outlineStroke } });
        });
    }
}
