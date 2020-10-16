// text_field.cpp
/*
  neogfx C++ App/Game Engine
  Copyright (c) 2015, 2020 Leigh Johnston.  All Rights Reserved.
  
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
#include <neogfx/app/i_app.hpp>
#include <neogfx/gui/widget/text_field.hpp>

namespace neogfx
{
    text_field::input_box_container::input_box_container(i_layout& aParentLayout, frame_style aFrameStyle) :
        base_type{ aParentLayout, aFrameStyle }
    {
    }

    color text_field::input_box_container::frame_color() const
    {
        if (has_frame_color())
            return base_type::frame_color();
        else if (service<i_app>().current_style().palette().color(color_role::Theme).similar_intensity(background_color(), 0.03125))
            return base_type::frame_color();
        else
            return service<i_app>().current_style().palette().color(color_role::Theme).mid(background_color());
    }

    color text_field::input_box_container::palette_color(color_role aColorRole) const
    {
        if (has_palette_color(aColorRole))
            return base_type::palette_color(aColorRole);
        else if (aColorRole == color_role::Background)
            return palette_color(color_role::Base);
        else
            return base_type::palette_color(aColorRole);
    }

    text_field::text_field(const std::string& aLabel, const std::string& aHint, text_field_placement aPlacement, frame_style aFrameStyle) :
        widget{},
        iPlacement{ aPlacement },
        iLayout{ *this },
        iLabel{ iLayout, aLabel },
        iInputLayout{ iLayout },
        iInputBoxContainer{ iInputLayout, aFrameStyle },
        iInputBoxContainerLayout{ iInputBoxContainer },
        iInputBox{ iInputBoxContainerLayout, frame_style::NoFrame },
        iInputBoxLayout{ iInputBox },
        iHint{ iInputBoxLayout, aHint },
        iHelp{ iLayout }
    {
        init();
    }

    text_field::text_field(i_widget& aParent, const std::string& aLabel, const std::string& aHint, text_field_placement aPlacement, frame_style aFrameStyle) :
        widget{ aParent },
        iPlacement{ aPlacement },
        iLayout{ *this },
        iLabel{ iLayout, aLabel },
        iInputLayout{ iLayout },
        iInputBoxContainer{ iInputLayout, aFrameStyle },
        iInputBoxContainerLayout{ iInputBoxContainer },
        iInputBox{ iInputBoxContainerLayout, frame_style::NoFrame },
        iInputBoxLayout{ iInputBox },
        iHint{ iInputBoxLayout, aHint },
        iHelp{ iLayout }
    {
        init();
    }

    text_field::text_field(i_layout& aLayout, const std::string& aLabel, const std::string& aHint, text_field_placement aPlacement, frame_style aFrameStyle) :
        widget{ aLayout },
        iPlacement{ aPlacement },
        iLayout{ *this },
        iLabel{ iLayout, aLabel },
        iInputLayout{ iLayout },
        iInputBoxContainer{ iInputLayout, aFrameStyle },
        iInputBoxContainerLayout{ iInputBoxContainer },
        iInputBox{ iInputBoxContainerLayout, frame_style::NoFrame },
        iInputBoxLayout{ iInputBox },
        iHint{ iInputBoxLayout, aHint },
        iHelp{ iLayout }
    {
        init();
    }

    const std::string& text_field::text() const
    {
        return input_box().text();
    }

    void text_field::set_text(const std::string& aText)
    {
        input_box().set_text(aText);
    }

    const label& text_field::label() const
    {
        return iLabel;
    }

    label& text_field::label()
    {
        return iLabel;
    }

    const line_edit& text_field::input_box() const
    {
        return iInputBox;
    }

    line_edit& text_field::input_box()
    {
        return iInputBox;
    }

    const text_widget& text_field::hint() const
    {
        return iHint;
    }

    text_widget& text_field::hint()
    {
        return iHint;
    }

    text_field_placement text_field::placement() const
    {
        return iPlacement;
    }

    void text_field::set_placement(text_field_placement aPlacement)
    {
        if (iPlacement != aPlacement)
        {
            iPlacement = aPlacement;
            switch (iPlacement)
            {
            case text_field_placement::LabelLeft:
                iInputLayout.add_at(0, iLabel);
                break;
            case text_field_placement::LabelAbove:
                iLayout.add_at(0, iLabel);
                break;
            }
        }
    }

    const text_widget& text_field::help() const
    {
        return iHelp;
    }

    text_widget& text_field::help()
    {
        return iHelp;
    }

    neogfx::size_policy text_field::size_policy() const
    {
        if (widget::has_size_policy())
            return widget::size_policy();
        else if (has_fixed_size())
            return size_constraint::Fixed;
        else
            return neogfx::size_policy{ size_constraint::Expanding, size_constraint::Minimum };
    }

    size text_field::minimum_size(const optional_size& aAvailableSpace) const
    {
        return widget::minimum_size(aAvailableSpace);
    }

    size text_field::maximum_size(const optional_size& aAvailableSpace) const
    {
        return widget::maximum_size(aAvailableSpace);
    }

    void text_field::init()
    {
        if (iPlacement == text_field_placement::LabelLeft)
            iInputLayout.add_at(0, iLabel);

        set_padding(neogfx::padding{});
        iLayout.set_padding(neogfx::padding{});
        iInputLayout.set_padding(neogfx::padding{});
        iInputBoxContainer.set_padding(iInputBox.padding());
        iInputBoxContainerLayout.set_padding(neogfx::padding{});
        auto label_padding_updater = [this](const neogfx::optional_padding&)
        {
            if (iPlacement == text_field_placement::LabelAbove)
                iLabel.set_padding(neogfx::padding{ iInputBoxContainer.padding().left + iInputBoxContainer.effective_frame_width(), 0.0 });
            else
                iLabel.set_padding({});
        };
        iInputBoxContainer.Padding.Changed(label_padding_updater);
        label_padding_updater(iInputBoxContainer.Padding);
        iLabel.set_size_policy(neogfx::size_policy{ size_constraint::Minimum, size_constraint::Minimum });
        iInputBox.set_padding(neogfx::padding{});
        iInputBoxLayout.set_size_policy(neogfx::size_policy{ size_constraint::Expanding, size_constraint::Minimum });
        iInputBoxLayout.set_padding(neogfx::padding{});
        iHint.set_size_policy(neogfx::size_policy{ size_constraint::Expanding, size_constraint::Minimum });
        iHint.set_alignment(alignment::Left | alignment::VCenter);
        iHelp.set_padding(neogfx::padding{});
        iHelp.set_alignment(alignment::Left | alignment::VCenter);

        auto size_hint_updater = [this]()
        {
            input_box().set_size_hint(size_hint{ input_box().size_hint().primaryHint, hint().text() });
        };
        hint().TextChanged(size_hint_updater);
        size_hint_updater();

        auto hint_updater = [this]()
        { 
            hint().set_font(input_box().default_style().font());
            hint().set_text_color(input_box().default_text_color().with_alpha(0.5));
            hint().show(input_box().text().empty());
        };
        iSink += service<i_app>().current_style_changed([hint_updater](style_aspect)
        {
            hint_updater();
        });
        input_box().DefaultStyleChanged(hint_updater);
        input_box().TextChanged(hint_updater);
        hint_updater();
    }
}