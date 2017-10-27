// sdl_keyboard.cpp
/*
  neogfx C++ GUI Library
  Copyright(C) 2016 Leigh Johnston
  
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

#pragma once

#include <neogfx/neogfx.hpp>
#include <unordered_map>
#include "sdl_keyboard.hpp"

namespace neogfx
{
	bool sdl_keyboard::is_key_pressed(scan_code_e aScanCode) const
	{
		const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
		return keyboardState[to_sdl_scan_code(aScanCode)] == 1;
	}

	scan_code_e sdl_keyboard::from_sdl_scan_code(SDL_Scancode aScanCode)
	{
		static const std::unordered_map<SDL_Scancode, scan_code_e> sTable
		{
			{ SDL_SCANCODE_UNKNOWN	,	ScanCode_UNKNOWN },
			{ SDL_SCANCODE_A	,	ScanCode_A },
			{ SDL_SCANCODE_B	,	ScanCode_B },
			{ SDL_SCANCODE_C	,	ScanCode_C },
			{ SDL_SCANCODE_D	,	ScanCode_D },
			{ SDL_SCANCODE_E	,	ScanCode_E },
			{ SDL_SCANCODE_F	,	ScanCode_F },
			{ SDL_SCANCODE_G	,	ScanCode_G },
			{ SDL_SCANCODE_H	,	ScanCode_H },
			{ SDL_SCANCODE_I	,	ScanCode_I },
			{ SDL_SCANCODE_J	,	ScanCode_J },
			{ SDL_SCANCODE_K	,	ScanCode_K },
			{ SDL_SCANCODE_L	,	ScanCode_L },
			{ SDL_SCANCODE_M	,	ScanCode_M },
			{ SDL_SCANCODE_N	,	ScanCode_N },
			{ SDL_SCANCODE_O	,	ScanCode_O },
			{ SDL_SCANCODE_P	,	ScanCode_P },
			{ SDL_SCANCODE_Q	,	ScanCode_Q },
			{ SDL_SCANCODE_R	,	ScanCode_R },
			{ SDL_SCANCODE_S	,	ScanCode_S },
			{ SDL_SCANCODE_T	,	ScanCode_T },
			{ SDL_SCANCODE_U	,	ScanCode_U },
			{ SDL_SCANCODE_V	,	ScanCode_V },
			{ SDL_SCANCODE_W	,	ScanCode_W },
			{ SDL_SCANCODE_X	,	ScanCode_X },
			{ SDL_SCANCODE_Y	,	ScanCode_Y },
			{ SDL_SCANCODE_Z	,	ScanCode_Z },
			{ SDL_SCANCODE_1	,	ScanCode_1 },
			{ SDL_SCANCODE_2	,	ScanCode_2 },
			{ SDL_SCANCODE_3	,	ScanCode_3 },
			{ SDL_SCANCODE_4	,	ScanCode_4 },
			{ SDL_SCANCODE_5	,	ScanCode_5 },
			{ SDL_SCANCODE_6	,	ScanCode_6 },
			{ SDL_SCANCODE_7	,	ScanCode_7 },
			{ SDL_SCANCODE_8	,	ScanCode_8 },
			{ SDL_SCANCODE_9	,	ScanCode_9 },
			{ SDL_SCANCODE_0	,	ScanCode_0 },
			{ SDL_SCANCODE_RETURN	,	ScanCode_RETURN },
			{ SDL_SCANCODE_ESCAPE	,	ScanCode_ESCAPE },
			{ SDL_SCANCODE_BACKSPACE	,	ScanCode_BACKSPACE },
			{ SDL_SCANCODE_TAB	,	ScanCode_TAB },
			{ SDL_SCANCODE_SPACE	,	ScanCode_SPACE },
			{ SDL_SCANCODE_MINUS	,	ScanCode_MINUS },
			{ SDL_SCANCODE_EQUALS	,	ScanCode_EQUALS },
			{ SDL_SCANCODE_LEFTBRACKET	,	ScanCode_LEFTBRACKET },
			{ SDL_SCANCODE_RIGHTBRACKET	,	ScanCode_RIGHTBRACKET },
			{ SDL_SCANCODE_BACKSLASH	,	ScanCode_BACKSLASH },
			{ SDL_SCANCODE_NONUSHASH	,	ScanCode_NONUSHASH },
			{ SDL_SCANCODE_SEMICOLON	,	ScanCode_SEMICOLON },
			{ SDL_SCANCODE_APOSTROPHE	,	ScanCode_APOSTROPHE },
			{ SDL_SCANCODE_GRAVE	,	ScanCode_GRAVE },
			{ SDL_SCANCODE_COMMA	,	ScanCode_COMMA },
			{ SDL_SCANCODE_PERIOD	,	ScanCode_PERIOD },
			{ SDL_SCANCODE_SLASH	,	ScanCode_SLASH },
			{ SDL_SCANCODE_CAPSLOCK	,	ScanCode_CAPSLOCK },
			{ SDL_SCANCODE_F1	,	ScanCode_F1 },
			{ SDL_SCANCODE_F2	,	ScanCode_F2 },
			{ SDL_SCANCODE_F3	,	ScanCode_F3 },
			{ SDL_SCANCODE_F4	,	ScanCode_F4 },
			{ SDL_SCANCODE_F5	,	ScanCode_F5 },
			{ SDL_SCANCODE_F6	,	ScanCode_F6 },
			{ SDL_SCANCODE_F7	,	ScanCode_F7 },
			{ SDL_SCANCODE_F8	,	ScanCode_F8 },
			{ SDL_SCANCODE_F9	,	ScanCode_F9 },
			{ SDL_SCANCODE_F10	,	ScanCode_F10 },
			{ SDL_SCANCODE_F11	,	ScanCode_F11 },
			{ SDL_SCANCODE_F12	,	ScanCode_F12 },
			{ SDL_SCANCODE_PRINTSCREEN	,	ScanCode_PRINTSCREEN },
			{ SDL_SCANCODE_SCROLLLOCK	,	ScanCode_SCROLLLOCK },
			{ SDL_SCANCODE_PAUSE	,	ScanCode_PAUSE },
			{ SDL_SCANCODE_INSERT	,	ScanCode_INSERT },
			{ SDL_SCANCODE_HOME	,	ScanCode_HOME },
			{ SDL_SCANCODE_PAGEUP	,	ScanCode_PAGEUP },
			{ SDL_SCANCODE_DELETE	,	ScanCode_DELETE },
			{ SDL_SCANCODE_END	,	ScanCode_END },
			{ SDL_SCANCODE_PAGEDOWN	,	ScanCode_PAGEDOWN },
			{ SDL_SCANCODE_RIGHT	,	ScanCode_RIGHT },
			{ SDL_SCANCODE_LEFT	,	ScanCode_LEFT },
			{ SDL_SCANCODE_DOWN	,	ScanCode_DOWN },
			{ SDL_SCANCODE_UP	,	ScanCode_UP },
			{ SDL_SCANCODE_NUMLOCKCLEAR	,	ScanCode_NUMLOCKCLEAR },
			{ SDL_SCANCODE_KP_DIVIDE	,	ScanCode_KP_DIVIDE },
			{ SDL_SCANCODE_KP_MULTIPLY	,	ScanCode_KP_MULTIPLY },
			{ SDL_SCANCODE_KP_MINUS	,	ScanCode_KP_MINUS },
			{ SDL_SCANCODE_KP_PLUS	,	ScanCode_KP_PLUS },
			{ SDL_SCANCODE_KP_ENTER	,	ScanCode_KP_ENTER },
			{ SDL_SCANCODE_KP_1	,	ScanCode_KP_1 },
			{ SDL_SCANCODE_KP_2	,	ScanCode_KP_2 },
			{ SDL_SCANCODE_KP_3	,	ScanCode_KP_3 },
			{ SDL_SCANCODE_KP_4	,	ScanCode_KP_4 },
			{ SDL_SCANCODE_KP_5	,	ScanCode_KP_5 },
			{ SDL_SCANCODE_KP_6	,	ScanCode_KP_6 },
			{ SDL_SCANCODE_KP_7	,	ScanCode_KP_7 },
			{ SDL_SCANCODE_KP_8	,	ScanCode_KP_8 },
			{ SDL_SCANCODE_KP_9	,	ScanCode_KP_9 },
			{ SDL_SCANCODE_KP_0	,	ScanCode_KP_0 },
			{ SDL_SCANCODE_KP_PERIOD	,	ScanCode_KP_PERIOD },
			{ SDL_SCANCODE_NONUSBACKSLASH	,	ScanCode_NONUSBACKSLASH },
			{ SDL_SCANCODE_APPLICATION	,	ScanCode_APPLICATION },
			{ SDL_SCANCODE_POWER	,	ScanCode_POWER },
			{ SDL_SCANCODE_KP_EQUALS	,	ScanCode_KP_EQUALS },
			{ SDL_SCANCODE_F13	,	ScanCode_F13 },
			{ SDL_SCANCODE_F14	,	ScanCode_F14 },
			{ SDL_SCANCODE_F15	,	ScanCode_F15 },
			{ SDL_SCANCODE_F16	,	ScanCode_F16 },
			{ SDL_SCANCODE_F17	,	ScanCode_F17 },
			{ SDL_SCANCODE_F18	,	ScanCode_F18 },
			{ SDL_SCANCODE_F19	,	ScanCode_F19 },
			{ SDL_SCANCODE_F20	,	ScanCode_F20 },
			{ SDL_SCANCODE_F21	,	ScanCode_F21 },
			{ SDL_SCANCODE_F22	,	ScanCode_F22 },
			{ SDL_SCANCODE_F23	,	ScanCode_F23 },
			{ SDL_SCANCODE_F24	,	ScanCode_F24 },
			{ SDL_SCANCODE_EXECUTE	,	ScanCode_EXECUTE },
			{ SDL_SCANCODE_HELP	,	ScanCode_HELP },
			{ SDL_SCANCODE_MENU	,	ScanCode_MENU },
			{ SDL_SCANCODE_SELECT	,	ScanCode_SELECT },
			{ SDL_SCANCODE_STOP	,	ScanCode_STOP },
			{ SDL_SCANCODE_AGAIN	,	ScanCode_AGAIN },
			{ SDL_SCANCODE_UNDO	,	ScanCode_UNDO },
			{ SDL_SCANCODE_CUT	,	ScanCode_CUT },
			{ SDL_SCANCODE_COPY	,	ScanCode_COPY },
			{ SDL_SCANCODE_PASTE	,	ScanCode_PASTE },
			{ SDL_SCANCODE_FIND	,	ScanCode_FIND },
			{ SDL_SCANCODE_MUTE	,	ScanCode_MUTE },
			{ SDL_SCANCODE_VOLUMEUP	,	ScanCode_VOLUMEUP },
			{ SDL_SCANCODE_VOLUMEDOWN	,	ScanCode_VOLUMEDOWN },
			{ SDL_SCANCODE_KP_COMMA	,	ScanCode_KP_COMMA },
			{ SDL_SCANCODE_KP_EQUALSAS400	,	ScanCode_KP_EQUALSAS400 },
			{ SDL_SCANCODE_INTERNATIONAL1	,	ScanCode_INTERNATIONAL1 },
			{ SDL_SCANCODE_INTERNATIONAL2	,	ScanCode_INTERNATIONAL2 },
			{ SDL_SCANCODE_INTERNATIONAL3	,	ScanCode_INTERNATIONAL3 },
			{ SDL_SCANCODE_INTERNATIONAL4	,	ScanCode_INTERNATIONAL4 },
			{ SDL_SCANCODE_INTERNATIONAL5	,	ScanCode_INTERNATIONAL5 },
			{ SDL_SCANCODE_INTERNATIONAL6	,	ScanCode_INTERNATIONAL6 },
			{ SDL_SCANCODE_INTERNATIONAL7	,	ScanCode_INTERNATIONAL7 },
			{ SDL_SCANCODE_INTERNATIONAL8	,	ScanCode_INTERNATIONAL8 },
			{ SDL_SCANCODE_INTERNATIONAL9	,	ScanCode_INTERNATIONAL9 },
			{ SDL_SCANCODE_LANG1	,	ScanCode_LANG1 },
			{ SDL_SCANCODE_LANG2	,	ScanCode_LANG2 },
			{ SDL_SCANCODE_LANG3	,	ScanCode_LANG3 },
			{ SDL_SCANCODE_LANG4	,	ScanCode_LANG4 },
			{ SDL_SCANCODE_LANG5	,	ScanCode_LANG5 },
			{ SDL_SCANCODE_LANG6	,	ScanCode_LANG6 },
			{ SDL_SCANCODE_LANG7	,	ScanCode_LANG7 },
			{ SDL_SCANCODE_LANG8	,	ScanCode_LANG8 },
			{ SDL_SCANCODE_LANG9	,	ScanCode_LANG9 },
			{ SDL_SCANCODE_ALTERASE	,	ScanCode_ALTERASE },
			{ SDL_SCANCODE_SYSREQ	,	ScanCode_SYSREQ },
			{ SDL_SCANCODE_CANCEL	,	ScanCode_CANCEL },
			{ SDL_SCANCODE_CLEAR	,	ScanCode_CLEAR },
			{ SDL_SCANCODE_PRIOR	,	ScanCode_PRIOR },
			{ SDL_SCANCODE_RETURN2	,	ScanCode_RETURN2 },
			{ SDL_SCANCODE_SEPARATOR	,	ScanCode_SEPARATOR },
			{ SDL_SCANCODE_OUT	,	ScanCode_OUT },
			{ SDL_SCANCODE_OPER	,	ScanCode_OPER },
			{ SDL_SCANCODE_CLEARAGAIN	,	ScanCode_CLEARAGAIN },
			{ SDL_SCANCODE_CRSEL	,	ScanCode_CRSEL },
			{ SDL_SCANCODE_EXSEL	,	ScanCode_EXSEL },
			{ SDL_SCANCODE_KP_00	,	ScanCode_KP_00 },
			{ SDL_SCANCODE_KP_000	,	ScanCode_KP_000 },
			{ SDL_SCANCODE_THOUSANDSSEPARATOR	,	ScanCode_THOUSANDSSEPARATOR },
			{ SDL_SCANCODE_DECIMALSEPARATOR	,	ScanCode_DECIMALSEPARATOR },
			{ SDL_SCANCODE_CURRENCYUNIT	,	ScanCode_CURRENCYUNIT },
			{ SDL_SCANCODE_CURRENCYSUBUNIT	,	ScanCode_CURRENCYSUBUNIT },
			{ SDL_SCANCODE_KP_LEFTPAREN	,	ScanCode_KP_LEFTPAREN },
			{ SDL_SCANCODE_KP_RIGHTPAREN	,	ScanCode_KP_RIGHTPAREN },
			{ SDL_SCANCODE_KP_LEFTBRACE	,	ScanCode_KP_LEFTBRACE },
			{ SDL_SCANCODE_KP_RIGHTBRACE	,	ScanCode_KP_RIGHTBRACE },
			{ SDL_SCANCODE_KP_TAB	,	ScanCode_KP_TAB },
			{ SDL_SCANCODE_KP_BACKSPACE	,	ScanCode_KP_BACKSPACE },
			{ SDL_SCANCODE_KP_A	,	ScanCode_KP_A },
			{ SDL_SCANCODE_KP_B	,	ScanCode_KP_B },
			{ SDL_SCANCODE_KP_C	,	ScanCode_KP_C },
			{ SDL_SCANCODE_KP_D	,	ScanCode_KP_D },
			{ SDL_SCANCODE_KP_E	,	ScanCode_KP_E },
			{ SDL_SCANCODE_KP_F	,	ScanCode_KP_F },
			{ SDL_SCANCODE_KP_XOR	,	ScanCode_KP_XOR },
			{ SDL_SCANCODE_KP_POWER	,	ScanCode_KP_POWER },
			{ SDL_SCANCODE_KP_PERCENT	,	ScanCode_KP_PERCENT },
			{ SDL_SCANCODE_KP_LESS	,	ScanCode_KP_LESS },
			{ SDL_SCANCODE_KP_GREATER	,	ScanCode_KP_GREATER },
			{ SDL_SCANCODE_KP_AMPERSAND	,	ScanCode_KP_AMPERSAND },
			{ SDL_SCANCODE_KP_DBLAMPERSAND	,	ScanCode_KP_DBLAMPERSAND },
			{ SDL_SCANCODE_KP_VERTICALBAR	,	ScanCode_KP_VERTICALBAR },
			{ SDL_SCANCODE_KP_DBLVERTICALBAR	,	ScanCode_KP_DBLVERTICALBAR },
			{ SDL_SCANCODE_KP_COLON	,	ScanCode_KP_COLON },
			{ SDL_SCANCODE_KP_HASH	,	ScanCode_KP_HASH },
			{ SDL_SCANCODE_KP_SPACE	,	ScanCode_KP_SPACE },
			{ SDL_SCANCODE_KP_AT	,	ScanCode_KP_AT },
			{ SDL_SCANCODE_KP_EXCLAM	,	ScanCode_KP_EXCLAM },
			{ SDL_SCANCODE_KP_MEMSTORE	,	ScanCode_KP_MEMSTORE },
			{ SDL_SCANCODE_KP_MEMRECALL	,	ScanCode_KP_MEMRECALL },
			{ SDL_SCANCODE_KP_MEMCLEAR	,	ScanCode_KP_MEMCLEAR },
			{ SDL_SCANCODE_KP_MEMADD	,	ScanCode_KP_MEMADD },
			{ SDL_SCANCODE_KP_MEMSUBTRACT	,	ScanCode_KP_MEMSUBTRACT },
			{ SDL_SCANCODE_KP_MEMMULTIPLY	,	ScanCode_KP_MEMMULTIPLY },
			{ SDL_SCANCODE_KP_MEMDIVIDE	,	ScanCode_KP_MEMDIVIDE },
			{ SDL_SCANCODE_KP_PLUSMINUS	,	ScanCode_KP_PLUSMINUS },
			{ SDL_SCANCODE_KP_CLEAR	,	ScanCode_KP_CLEAR },
			{ SDL_SCANCODE_KP_CLEARENTRY	,	ScanCode_KP_CLEARENTRY },
			{ SDL_SCANCODE_KP_BINARY	,	ScanCode_KP_BINARY },
			{ SDL_SCANCODE_KP_OCTAL	,	ScanCode_KP_OCTAL },
			{ SDL_SCANCODE_KP_DECIMAL	,	ScanCode_KP_DECIMAL },
			{ SDL_SCANCODE_KP_HEXADECIMAL	,	ScanCode_KP_HEXADECIMAL },
			{ SDL_SCANCODE_LCTRL	,	ScanCode_LCTRL },
			{ SDL_SCANCODE_LSHIFT	,	ScanCode_LSHIFT },
			{ SDL_SCANCODE_LALT	,	ScanCode_LALT },
			{ SDL_SCANCODE_LGUI	,	ScanCode_LGUI },
			{ SDL_SCANCODE_RCTRL	,	ScanCode_RCTRL },
			{ SDL_SCANCODE_RSHIFT	,	ScanCode_RSHIFT },
			{ SDL_SCANCODE_RALT	,	ScanCode_RALT },
			{ SDL_SCANCODE_RGUI	,	ScanCode_RGUI },
			{ SDL_SCANCODE_MODE	,	ScanCode_MODE },
			{ SDL_SCANCODE_AUDIONEXT	,	ScanCode_AUDIONEXT },
			{ SDL_SCANCODE_AUDIOPREV	,	ScanCode_AUDIOPREV },
			{ SDL_SCANCODE_AUDIOSTOP	,	ScanCode_AUDIOSTOP },
			{ SDL_SCANCODE_AUDIOPLAY	,	ScanCode_AUDIOPLAY },
			{ SDL_SCANCODE_AUDIOMUTE	,	ScanCode_AUDIOMUTE },
			{ SDL_SCANCODE_MEDIASELECT	,	ScanCode_MEDIASELECT },
			{ SDL_SCANCODE_WWW	,	ScanCode_WWW },
			{ SDL_SCANCODE_MAIL	,	ScanCode_MAIL },
			{ SDL_SCANCODE_CALCULATOR	,	ScanCode_CALCULATOR },
			{ SDL_SCANCODE_COMPUTER	,	ScanCode_COMPUTER },
			{ SDL_SCANCODE_AC_SEARCH	,	ScanCode_AC_SEARCH },
			{ SDL_SCANCODE_AC_HOME	,	ScanCode_AC_HOME },
			{ SDL_SCANCODE_AC_BACK	,	ScanCode_AC_BACK },
			{ SDL_SCANCODE_AC_FORWARD	,	ScanCode_AC_FORWARD },
			{ SDL_SCANCODE_AC_STOP	,	ScanCode_AC_STOP },
			{ SDL_SCANCODE_AC_REFRESH	,	ScanCode_AC_REFRESH },
			{ SDL_SCANCODE_AC_BOOKMARKS	,	ScanCode_AC_BOOKMARKS },
			{ SDL_SCANCODE_BRIGHTNESSDOWN	,	ScanCode_BRIGHTNESSDOWN },
			{ SDL_SCANCODE_BRIGHTNESSUP	,	ScanCode_BRIGHTNESSUP },
			{ SDL_SCANCODE_DISPLAYSWITCH	,	ScanCode_DISPLAYSWITCH },
			{ SDL_SCANCODE_KBDILLUMTOGGLE	,	ScanCode_KBDILLUMTOGGLE },
			{ SDL_SCANCODE_KBDILLUMDOWN	,	ScanCode_KBDILLUMDOWN },
			{ SDL_SCANCODE_KBDILLUMUP	,	ScanCode_KBDILLUMUP },
			{ SDL_SCANCODE_EJECT	,	ScanCode_EJECT },
			{ SDL_SCANCODE_SLEEP	,	ScanCode_SLEEP },
			{ SDL_SCANCODE_APP1	,	ScanCode_APP1 },
			{ SDL_SCANCODE_APP2	,	ScanCode_APP2 }
		};
		auto result = sTable.find(aScanCode);
		if (result != sTable.end())
			return result->second;
		return ScanCode_UNKNOWN;
	}

	SDL_Scancode sdl_keyboard::to_sdl_scan_code(scan_code_e aScanCode)
	{
		static const std::unordered_map<scan_code_e, SDL_Scancode> sTable
		{
			{ ScanCode_UNKNOWN	,	SDL_SCANCODE_UNKNOWN },
			{ ScanCode_A	,	SDL_SCANCODE_A },
			{ ScanCode_B	,	SDL_SCANCODE_B },
			{ ScanCode_C	,	SDL_SCANCODE_C },
			{ ScanCode_D	,	SDL_SCANCODE_D },
			{ ScanCode_E	,	SDL_SCANCODE_E },
			{ ScanCode_F	,	SDL_SCANCODE_F },
			{ ScanCode_G	,	SDL_SCANCODE_G },
			{ ScanCode_H	,	SDL_SCANCODE_H },
			{ ScanCode_I	,	SDL_SCANCODE_I },
			{ ScanCode_J	,	SDL_SCANCODE_J },
			{ ScanCode_K	,	SDL_SCANCODE_K },
			{ ScanCode_L	,	SDL_SCANCODE_L },
			{ ScanCode_M	,	SDL_SCANCODE_M },
			{ ScanCode_N	,	SDL_SCANCODE_N },
			{ ScanCode_O	,	SDL_SCANCODE_O },
			{ ScanCode_P	,	SDL_SCANCODE_P },
			{ ScanCode_Q	,	SDL_SCANCODE_Q },
			{ ScanCode_R	,	SDL_SCANCODE_R },
			{ ScanCode_S	,	SDL_SCANCODE_S },
			{ ScanCode_T	,	SDL_SCANCODE_T },
			{ ScanCode_U	,	SDL_SCANCODE_U },
			{ ScanCode_V	,	SDL_SCANCODE_V },
			{ ScanCode_W	,	SDL_SCANCODE_W },
			{ ScanCode_X	,	SDL_SCANCODE_X },
			{ ScanCode_Y	,	SDL_SCANCODE_Y },
			{ ScanCode_Z	,	SDL_SCANCODE_Z },
			{ ScanCode_1	,	SDL_SCANCODE_1 },
			{ ScanCode_2	,	SDL_SCANCODE_2 },
			{ ScanCode_3	,	SDL_SCANCODE_3 },
			{ ScanCode_4	,	SDL_SCANCODE_4 },
			{ ScanCode_5	,	SDL_SCANCODE_5 },
			{ ScanCode_6	,	SDL_SCANCODE_6 },
			{ ScanCode_7	,	SDL_SCANCODE_7 },
			{ ScanCode_8	,	SDL_SCANCODE_8 },
			{ ScanCode_9	,	SDL_SCANCODE_9 },
			{ ScanCode_0	,	SDL_SCANCODE_0 },
			{ ScanCode_RETURN	,	SDL_SCANCODE_RETURN },
			{ ScanCode_ESCAPE	,	SDL_SCANCODE_ESCAPE },
			{ ScanCode_BACKSPACE	,	SDL_SCANCODE_BACKSPACE },
			{ ScanCode_TAB	,	SDL_SCANCODE_TAB },
			{ ScanCode_SPACE	,	SDL_SCANCODE_SPACE },
			{ ScanCode_MINUS	,	SDL_SCANCODE_MINUS },
			{ ScanCode_EQUALS	,	SDL_SCANCODE_EQUALS },
			{ ScanCode_LEFTBRACKET	,	SDL_SCANCODE_LEFTBRACKET },
			{ ScanCode_RIGHTBRACKET	,	SDL_SCANCODE_RIGHTBRACKET },
			{ ScanCode_BACKSLASH	,	SDL_SCANCODE_BACKSLASH },
			{ ScanCode_NONUSHASH	,	SDL_SCANCODE_NONUSHASH },
			{ ScanCode_SEMICOLON	,	SDL_SCANCODE_SEMICOLON },
			{ ScanCode_APOSTROPHE	,	SDL_SCANCODE_APOSTROPHE },
			{ ScanCode_GRAVE	,	SDL_SCANCODE_GRAVE },
			{ ScanCode_COMMA	,	SDL_SCANCODE_COMMA },
			{ ScanCode_PERIOD	,	SDL_SCANCODE_PERIOD },
			{ ScanCode_SLASH	,	SDL_SCANCODE_SLASH },
			{ ScanCode_CAPSLOCK	,	SDL_SCANCODE_CAPSLOCK },
			{ ScanCode_F1	,	SDL_SCANCODE_F1 },
			{ ScanCode_F2	,	SDL_SCANCODE_F2 },
			{ ScanCode_F3	,	SDL_SCANCODE_F3 },
			{ ScanCode_F4	,	SDL_SCANCODE_F4 },
			{ ScanCode_F5	,	SDL_SCANCODE_F5 },
			{ ScanCode_F6	,	SDL_SCANCODE_F6 },
			{ ScanCode_F7	,	SDL_SCANCODE_F7 },
			{ ScanCode_F8	,	SDL_SCANCODE_F8 },
			{ ScanCode_F9	,	SDL_SCANCODE_F9 },
			{ ScanCode_F10	,	SDL_SCANCODE_F10 },
			{ ScanCode_F11	,	SDL_SCANCODE_F11 },
			{ ScanCode_F12	,	SDL_SCANCODE_F12 },
			{ ScanCode_PRINTSCREEN	,	SDL_SCANCODE_PRINTSCREEN },
			{ ScanCode_SCROLLLOCK	,	SDL_SCANCODE_SCROLLLOCK },
			{ ScanCode_PAUSE	,	SDL_SCANCODE_PAUSE },
			{ ScanCode_INSERT	,	SDL_SCANCODE_INSERT },
			{ ScanCode_HOME	,	SDL_SCANCODE_HOME },
			{ ScanCode_PAGEUP	,	SDL_SCANCODE_PAGEUP },
			{ ScanCode_DELETE	,	SDL_SCANCODE_DELETE },
			{ ScanCode_END	,	SDL_SCANCODE_END },
			{ ScanCode_PAGEDOWN	,	SDL_SCANCODE_PAGEDOWN },
			{ ScanCode_RIGHT	,	SDL_SCANCODE_RIGHT },
			{ ScanCode_LEFT	,	SDL_SCANCODE_LEFT },
			{ ScanCode_DOWN	,	SDL_SCANCODE_DOWN },
			{ ScanCode_UP	,	SDL_SCANCODE_UP },
			{ ScanCode_NUMLOCKCLEAR	,	SDL_SCANCODE_NUMLOCKCLEAR },
			{ ScanCode_KP_DIVIDE	,	SDL_SCANCODE_KP_DIVIDE },
			{ ScanCode_KP_MULTIPLY	,	SDL_SCANCODE_KP_MULTIPLY },
			{ ScanCode_KP_MINUS	,	SDL_SCANCODE_KP_MINUS },
			{ ScanCode_KP_PLUS	,	SDL_SCANCODE_KP_PLUS },
			{ ScanCode_KP_ENTER	,	SDL_SCANCODE_KP_ENTER },
			{ ScanCode_KP_1	,	SDL_SCANCODE_KP_1 },
			{ ScanCode_KP_2	,	SDL_SCANCODE_KP_2 },
			{ ScanCode_KP_3	,	SDL_SCANCODE_KP_3 },
			{ ScanCode_KP_4	,	SDL_SCANCODE_KP_4 },
			{ ScanCode_KP_5	,	SDL_SCANCODE_KP_5 },
			{ ScanCode_KP_6	,	SDL_SCANCODE_KP_6 },
			{ ScanCode_KP_7	,	SDL_SCANCODE_KP_7 },
			{ ScanCode_KP_8	,	SDL_SCANCODE_KP_8 },
			{ ScanCode_KP_9	,	SDL_SCANCODE_KP_9 },
			{ ScanCode_KP_0	,	SDL_SCANCODE_KP_0 },
			{ ScanCode_KP_PERIOD	,	SDL_SCANCODE_KP_PERIOD },
			{ ScanCode_NONUSBACKSLASH	,	SDL_SCANCODE_NONUSBACKSLASH },
			{ ScanCode_APPLICATION	,	SDL_SCANCODE_APPLICATION },
			{ ScanCode_POWER	,	SDL_SCANCODE_POWER },
			{ ScanCode_KP_EQUALS	,	SDL_SCANCODE_KP_EQUALS },
			{ ScanCode_F13	,	SDL_SCANCODE_F13 },
			{ ScanCode_F14	,	SDL_SCANCODE_F14 },
			{ ScanCode_F15	,	SDL_SCANCODE_F15 },
			{ ScanCode_F16	,	SDL_SCANCODE_F16 },
			{ ScanCode_F17	,	SDL_SCANCODE_F17 },
			{ ScanCode_F18	,	SDL_SCANCODE_F18 },
			{ ScanCode_F19	,	SDL_SCANCODE_F19 },
			{ ScanCode_F20	,	SDL_SCANCODE_F20 },
			{ ScanCode_F21	,	SDL_SCANCODE_F21 },
			{ ScanCode_F22	,	SDL_SCANCODE_F22 },
			{ ScanCode_F23	,	SDL_SCANCODE_F23 },
			{ ScanCode_F24	,	SDL_SCANCODE_F24 },
			{ ScanCode_EXECUTE	,	SDL_SCANCODE_EXECUTE },
			{ ScanCode_HELP	,	SDL_SCANCODE_HELP },
			{ ScanCode_MENU	,	SDL_SCANCODE_MENU },
			{ ScanCode_SELECT	,	SDL_SCANCODE_SELECT },
			{ ScanCode_STOP	,	SDL_SCANCODE_STOP },
			{ ScanCode_AGAIN	,	SDL_SCANCODE_AGAIN },
			{ ScanCode_UNDO	,	SDL_SCANCODE_UNDO },
			{ ScanCode_CUT	,	SDL_SCANCODE_CUT },
			{ ScanCode_COPY	,	SDL_SCANCODE_COPY },
			{ ScanCode_PASTE	,	SDL_SCANCODE_PASTE },
			{ ScanCode_FIND	,	SDL_SCANCODE_FIND },
			{ ScanCode_MUTE	,	SDL_SCANCODE_MUTE },
			{ ScanCode_VOLUMEUP	,	SDL_SCANCODE_VOLUMEUP },
			{ ScanCode_VOLUMEDOWN	,	SDL_SCANCODE_VOLUMEDOWN },
			{ ScanCode_KP_COMMA	,	SDL_SCANCODE_KP_COMMA },
			{ ScanCode_KP_EQUALSAS400	,	SDL_SCANCODE_KP_EQUALSAS400 },
			{ ScanCode_INTERNATIONAL1	,	SDL_SCANCODE_INTERNATIONAL1 },
			{ ScanCode_INTERNATIONAL2	,	SDL_SCANCODE_INTERNATIONAL2 },
			{ ScanCode_INTERNATIONAL3	,	SDL_SCANCODE_INTERNATIONAL3 },
			{ ScanCode_INTERNATIONAL4	,	SDL_SCANCODE_INTERNATIONAL4 },
			{ ScanCode_INTERNATIONAL5	,	SDL_SCANCODE_INTERNATIONAL5 },
			{ ScanCode_INTERNATIONAL6	,	SDL_SCANCODE_INTERNATIONAL6 },
			{ ScanCode_INTERNATIONAL7	,	SDL_SCANCODE_INTERNATIONAL7 },
			{ ScanCode_INTERNATIONAL8	,	SDL_SCANCODE_INTERNATIONAL8 },
			{ ScanCode_INTERNATIONAL9	,	SDL_SCANCODE_INTERNATIONAL9 },
			{ ScanCode_LANG1	,	SDL_SCANCODE_LANG1 },
			{ ScanCode_LANG2	,	SDL_SCANCODE_LANG2 },
			{ ScanCode_LANG3	,	SDL_SCANCODE_LANG3 },
			{ ScanCode_LANG4	,	SDL_SCANCODE_LANG4 },
			{ ScanCode_LANG5	,	SDL_SCANCODE_LANG5 },
			{ ScanCode_LANG6	,	SDL_SCANCODE_LANG6 },
			{ ScanCode_LANG7	,	SDL_SCANCODE_LANG7 },
			{ ScanCode_LANG8	,	SDL_SCANCODE_LANG8 },
			{ ScanCode_LANG9	,	SDL_SCANCODE_LANG9 },
			{ ScanCode_ALTERASE	,	SDL_SCANCODE_ALTERASE },
			{ ScanCode_SYSREQ	,	SDL_SCANCODE_SYSREQ },
			{ ScanCode_CANCEL	,	SDL_SCANCODE_CANCEL },
			{ ScanCode_CLEAR	,	SDL_SCANCODE_CLEAR },
			{ ScanCode_PRIOR	,	SDL_SCANCODE_PRIOR },
			{ ScanCode_RETURN2	,	SDL_SCANCODE_RETURN2 },
			{ ScanCode_SEPARATOR	,	SDL_SCANCODE_SEPARATOR },
			{ ScanCode_OUT	,	SDL_SCANCODE_OUT },
			{ ScanCode_OPER	,	SDL_SCANCODE_OPER },
			{ ScanCode_CLEARAGAIN	,	SDL_SCANCODE_CLEARAGAIN },
			{ ScanCode_CRSEL	,	SDL_SCANCODE_CRSEL },
			{ ScanCode_EXSEL	,	SDL_SCANCODE_EXSEL },
			{ ScanCode_KP_00	,	SDL_SCANCODE_KP_00 },
			{ ScanCode_KP_000	,	SDL_SCANCODE_KP_000 },
			{ ScanCode_THOUSANDSSEPARATOR	,	SDL_SCANCODE_THOUSANDSSEPARATOR },
			{ ScanCode_DECIMALSEPARATOR	,	SDL_SCANCODE_DECIMALSEPARATOR },
			{ ScanCode_CURRENCYUNIT	,	SDL_SCANCODE_CURRENCYUNIT },
			{ ScanCode_CURRENCYSUBUNIT	,	SDL_SCANCODE_CURRENCYSUBUNIT },
			{ ScanCode_KP_LEFTPAREN	,	SDL_SCANCODE_KP_LEFTPAREN },
			{ ScanCode_KP_RIGHTPAREN	,	SDL_SCANCODE_KP_RIGHTPAREN },
			{ ScanCode_KP_LEFTBRACE	,	SDL_SCANCODE_KP_LEFTBRACE },
			{ ScanCode_KP_RIGHTBRACE	,	SDL_SCANCODE_KP_RIGHTBRACE },
			{ ScanCode_KP_TAB	,	SDL_SCANCODE_KP_TAB },
			{ ScanCode_KP_BACKSPACE	,	SDL_SCANCODE_KP_BACKSPACE },
			{ ScanCode_KP_A	,	SDL_SCANCODE_KP_A },
			{ ScanCode_KP_B	,	SDL_SCANCODE_KP_B },
			{ ScanCode_KP_C	,	SDL_SCANCODE_KP_C },
			{ ScanCode_KP_D	,	SDL_SCANCODE_KP_D },
			{ ScanCode_KP_E	,	SDL_SCANCODE_KP_E },
			{ ScanCode_KP_F	,	SDL_SCANCODE_KP_F },
			{ ScanCode_KP_XOR	,	SDL_SCANCODE_KP_XOR },
			{ ScanCode_KP_POWER	,	SDL_SCANCODE_KP_POWER },
			{ ScanCode_KP_PERCENT	,	SDL_SCANCODE_KP_PERCENT },
			{ ScanCode_KP_LESS	,	SDL_SCANCODE_KP_LESS },
			{ ScanCode_KP_GREATER	,	SDL_SCANCODE_KP_GREATER },
			{ ScanCode_KP_AMPERSAND	,	SDL_SCANCODE_KP_AMPERSAND },
			{ ScanCode_KP_DBLAMPERSAND	,	SDL_SCANCODE_KP_DBLAMPERSAND },
			{ ScanCode_KP_VERTICALBAR	,	SDL_SCANCODE_KP_VERTICALBAR },
			{ ScanCode_KP_DBLVERTICALBAR	,	SDL_SCANCODE_KP_DBLVERTICALBAR },
			{ ScanCode_KP_COLON	,	SDL_SCANCODE_KP_COLON },
			{ ScanCode_KP_HASH	,	SDL_SCANCODE_KP_HASH },
			{ ScanCode_KP_SPACE	,	SDL_SCANCODE_KP_SPACE },
			{ ScanCode_KP_AT	,	SDL_SCANCODE_KP_AT },
			{ ScanCode_KP_EXCLAM	,	SDL_SCANCODE_KP_EXCLAM },
			{ ScanCode_KP_MEMSTORE	,	SDL_SCANCODE_KP_MEMSTORE },
			{ ScanCode_KP_MEMRECALL	,	SDL_SCANCODE_KP_MEMRECALL },
			{ ScanCode_KP_MEMCLEAR	,	SDL_SCANCODE_KP_MEMCLEAR },
			{ ScanCode_KP_MEMADD	,	SDL_SCANCODE_KP_MEMADD },
			{ ScanCode_KP_MEMSUBTRACT	,	SDL_SCANCODE_KP_MEMSUBTRACT },
			{ ScanCode_KP_MEMMULTIPLY	,	SDL_SCANCODE_KP_MEMMULTIPLY },
			{ ScanCode_KP_MEMDIVIDE	,	SDL_SCANCODE_KP_MEMDIVIDE },
			{ ScanCode_KP_PLUSMINUS	,	SDL_SCANCODE_KP_PLUSMINUS },
			{ ScanCode_KP_CLEAR	,	SDL_SCANCODE_KP_CLEAR },
			{ ScanCode_KP_CLEARENTRY	,	SDL_SCANCODE_KP_CLEARENTRY },
			{ ScanCode_KP_BINARY	,	SDL_SCANCODE_KP_BINARY },
			{ ScanCode_KP_OCTAL	,	SDL_SCANCODE_KP_OCTAL },
			{ ScanCode_KP_DECIMAL	,	SDL_SCANCODE_KP_DECIMAL },
			{ ScanCode_KP_HEXADECIMAL	,	SDL_SCANCODE_KP_HEXADECIMAL },
			{ ScanCode_LCTRL	,	SDL_SCANCODE_LCTRL },
			{ ScanCode_LSHIFT	,	SDL_SCANCODE_LSHIFT },
			{ ScanCode_LALT	,	SDL_SCANCODE_LALT },
			{ ScanCode_LGUI	,	SDL_SCANCODE_LGUI },
			{ ScanCode_RCTRL	,	SDL_SCANCODE_RCTRL },
			{ ScanCode_RSHIFT	,	SDL_SCANCODE_RSHIFT },
			{ ScanCode_RALT	,	SDL_SCANCODE_RALT },
			{ ScanCode_RGUI	,	SDL_SCANCODE_RGUI },
			{ ScanCode_MODE	,	SDL_SCANCODE_MODE },
			{ ScanCode_AUDIONEXT	,	SDL_SCANCODE_AUDIONEXT },
			{ ScanCode_AUDIOPREV	,	SDL_SCANCODE_AUDIOPREV },
			{ ScanCode_AUDIOSTOP	,	SDL_SCANCODE_AUDIOSTOP },
			{ ScanCode_AUDIOPLAY	,	SDL_SCANCODE_AUDIOPLAY },
			{ ScanCode_AUDIOMUTE	,	SDL_SCANCODE_AUDIOMUTE },
			{ ScanCode_MEDIASELECT	,	SDL_SCANCODE_MEDIASELECT },
			{ ScanCode_WWW	,	SDL_SCANCODE_WWW },
			{ ScanCode_MAIL	,	SDL_SCANCODE_MAIL },
			{ ScanCode_CALCULATOR	,	SDL_SCANCODE_CALCULATOR },
			{ ScanCode_COMPUTER	,	SDL_SCANCODE_COMPUTER },
			{ ScanCode_AC_SEARCH	,	SDL_SCANCODE_AC_SEARCH },
			{ ScanCode_AC_HOME	,	SDL_SCANCODE_AC_HOME },
			{ ScanCode_AC_BACK	,	SDL_SCANCODE_AC_BACK },
			{ ScanCode_AC_FORWARD	,	SDL_SCANCODE_AC_FORWARD },
			{ ScanCode_AC_STOP	,	SDL_SCANCODE_AC_STOP },
			{ ScanCode_AC_REFRESH	,	SDL_SCANCODE_AC_REFRESH },
			{ ScanCode_AC_BOOKMARKS	,	SDL_SCANCODE_AC_BOOKMARKS },
			{ ScanCode_BRIGHTNESSDOWN	,	SDL_SCANCODE_BRIGHTNESSDOWN },
			{ ScanCode_BRIGHTNESSUP	,	SDL_SCANCODE_BRIGHTNESSUP },
			{ ScanCode_DISPLAYSWITCH	,	SDL_SCANCODE_DISPLAYSWITCH },
			{ ScanCode_KBDILLUMTOGGLE	,	SDL_SCANCODE_KBDILLUMTOGGLE },
			{ ScanCode_KBDILLUMDOWN	,	SDL_SCANCODE_KBDILLUMDOWN },
			{ ScanCode_KBDILLUMUP	,	SDL_SCANCODE_KBDILLUMUP },
			{ ScanCode_EJECT	,	SDL_SCANCODE_EJECT },
			{ ScanCode_SLEEP	,	SDL_SCANCODE_SLEEP },
			{ ScanCode_APP1	,	SDL_SCANCODE_APP1 },
			{ ScanCode_APP2	,	SDL_SCANCODE_APP2 }
		};
		auto result = sTable.find(aScanCode);
		if (result != sTable.end())
			return result->second;
		return SDL_SCANCODE_UNKNOWN;
	}
}