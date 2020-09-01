// library.cpp
/*
neoGFX Resource Compiler
Copyright(C) 2019 Leigh Johnston

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
#include <boost/range/iterator_range.hpp>
#include <neolib/core/string_ci.hpp>
#include <neogfx/app/app.hpp>
#include <neogfx/app/action.hpp>
#include <neogfx/gui/window/window.hpp>
#include <neogfx/gui/widget/widget.hpp>
#include <neogfx/gui/widget/text_widget.hpp>
#include <neogfx/gui/widget/image_widget.hpp>
#include <neogfx/gui/widget/menu_bar.hpp>
#include <neogfx/gui/widget/toolbar.hpp>
#include <neogfx/gui/widget/status_bar.hpp>
#include <neogfx/gui/widget/tab_page_container.hpp>
#include <neogfx/gui/widget/tab_page.hpp>
#include <neogfx/game/canvas.hpp>
#include <neogfx/gui/widget/push_button.hpp>
#include <neogfx/gui/widget/check_box.hpp>
#include <neogfx/gui/widget/radio_button.hpp>
#include <neogfx/gui/widget/label.hpp>
#include <neogfx/gui/widget/text_edit.hpp>
#include <neogfx/gui/widget/line_edit.hpp>
#include <neogfx/gui/widget/text_field.hpp>
#include <neogfx/gui/widget/drop_list.hpp>
#include <neogfx/gui/widget/table_view.hpp>
#include <neogfx/gui/widget/tree_view.hpp>
#include <neogfx/gui/widget/group_box.hpp>
#include <neogfx/gui/widget/slider.hpp>
#include <neogfx/gui/widget/spin_box.hpp>
#include <neogfx/gui/widget/gradient_widget.hpp>
#include <neogfx/gui/layout/vertical_layout.hpp>
#include <neogfx/gui/layout/horizontal_layout.hpp>
#include <neogfx/gui/layout/grid_layout.hpp>
#include <neogfx/gui/layout/flow_layout.hpp>
#include <neogfx/gui/layout/stack_layout.hpp>
#include <neogfx/gui/layout/border_layout.hpp>
#include <neogfx/gui/layout/spacer.hpp>
#include <neogfx/tools/DesignStudio/element.hpp>
#include "library.hpp"

namespace neogfx::DesignStudio
{
    default_element_library::default_element_library(neolib::i_application& aApplication, const std::string& aPluginPath) :
        iApplication{ aApplication },
        iPluginPath{ aPluginPath },
        iElements
        {
            { "app" },
            { "action" },
            { "menu" },
            { "window" },
            { "widget" },
            { "text_widget" },
            { "image_widget" },
            { "menu_bar" },
            { "toolbar" },
            { "status_bar" },
            { "tab_page_container" },
            { "tab_page" },
            { "canvas" },
            { "push_button" },
            { "check_box" },
            { "radio_button" },
            { "label" },
            { "text_edit" },
            { "line_edit" },
            { "text_field" },
            { "drop_list" },
            { "table_view" },
            { "tree_view" },
            { "group_box" },
            { "slider" },
            { "double_slider" },
            { "spin_box" },
            { "double_spin_box" },
            { "gradient_widget" },
            { "vertical_layout" },
            { "horizontal_layout" },
            { "grid_layout" },
            { "flow_layout" },
            { "stack_layout" },
            { "border_layout" },
            { "spacer" },
            { "vertical_spacer" },
            { "horizontal_spacer" }
        }
    {
    }

    const default_element_library::elements_t& default_element_library::elements() const
    {
        return iElements;
    }

    void default_element_library::create_element(i_element& aParent, const neolib::i_string& aElementType, const neolib::i_string& aElementId, neolib::i_ref_ptr<i_element>& aResult)
    {
        static const std::map<std::string, std::function<i_element*(i_element&, const neolib::i_string&)>> sFactoryMethods =
        {
            #define MAKE_ELEMENT_FACTORY_FUNCTION(Type) { #Type, [](i_element& aParent, const neolib::i_string& aElementId) -> i_element* { return new element<Type>{ aParent, #Type, aElementId }; } },
            MAKE_ELEMENT_FACTORY_FUNCTION(app)
            MAKE_ELEMENT_FACTORY_FUNCTION(action)
            MAKE_ELEMENT_FACTORY_FUNCTION(window)
            MAKE_ELEMENT_FACTORY_FUNCTION(widget)
            MAKE_ELEMENT_FACTORY_FUNCTION(text_widget)
            MAKE_ELEMENT_FACTORY_FUNCTION(image_widget)
            MAKE_ELEMENT_FACTORY_FUNCTION(status_bar)
            MAKE_ELEMENT_FACTORY_FUNCTION(menu_bar)
            MAKE_ELEMENT_FACTORY_FUNCTION(menu)
            MAKE_ELEMENT_FACTORY_FUNCTION(toolbar)
            MAKE_ELEMENT_FACTORY_FUNCTION(tab_page_container)
            MAKE_ELEMENT_FACTORY_FUNCTION(tab_page)
            MAKE_ELEMENT_FACTORY_FUNCTION(canvas)
            MAKE_ELEMENT_FACTORY_FUNCTION(push_button)
            MAKE_ELEMENT_FACTORY_FUNCTION(check_box)
            MAKE_ELEMENT_FACTORY_FUNCTION(radio_button)
            MAKE_ELEMENT_FACTORY_FUNCTION(label)
            MAKE_ELEMENT_FACTORY_FUNCTION(text_edit)
            MAKE_ELEMENT_FACTORY_FUNCTION(line_edit)
            MAKE_ELEMENT_FACTORY_FUNCTION(text_field)
            MAKE_ELEMENT_FACTORY_FUNCTION(drop_list)
            MAKE_ELEMENT_FACTORY_FUNCTION(table_view)
            MAKE_ELEMENT_FACTORY_FUNCTION(tree_view)
            MAKE_ELEMENT_FACTORY_FUNCTION(group_box)
            MAKE_ELEMENT_FACTORY_FUNCTION(slider)
            MAKE_ELEMENT_FACTORY_FUNCTION(double_slider)
            MAKE_ELEMENT_FACTORY_FUNCTION(spin_box)
            MAKE_ELEMENT_FACTORY_FUNCTION(double_spin_box)
            MAKE_ELEMENT_FACTORY_FUNCTION(gradient_widget)
            MAKE_ELEMENT_FACTORY_FUNCTION(vertical_layout)
            MAKE_ELEMENT_FACTORY_FUNCTION(horizontal_layout)
            MAKE_ELEMENT_FACTORY_FUNCTION(grid_layout)
            MAKE_ELEMENT_FACTORY_FUNCTION(flow_layout)
            MAKE_ELEMENT_FACTORY_FUNCTION(stack_layout)
            MAKE_ELEMENT_FACTORY_FUNCTION(border_layout)
            MAKE_ELEMENT_FACTORY_FUNCTION(spacer)
            MAKE_ELEMENT_FACTORY_FUNCTION(vertical_spacer)
            MAKE_ELEMENT_FACTORY_FUNCTION(horizontal_spacer)
        };
        auto method = sFactoryMethods.find(aElementType);
        if (method != sFactoryMethods.end())
        {
            aResult.reset((method->second)(aParent, aElementId));
            return;
        }
        throw unknown_element_type();
    }
}
