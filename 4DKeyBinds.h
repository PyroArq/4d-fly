#pragma once

#include <glfw.h>
#include <string>
#include <type_traits>
#include <windows.h>
#include <4dm.h>
#include "4Dconsole.h"
#include <iostream>  // for debugging
using fdm::base;

namespace glfw {

enum Keys {
	Unknown = -1,
	Space = 32, Apostrophe = 39, Comma = 44, Minus = 45, Period = 46, Slash = 47,
	Alpha0 = 48, Alpha1 = 49, Alpha2 = 50, Alpha3 = 51, Alpha4 = 52,
	Alpha5 = 53, Alpha6 = 54, Alpha7 = 55, Alpha8 = 56, Alpha9 = 57,
	SemiColon = 59, Equal = 61,
	A = 65, B = 66, C = 67, D = 68, E = 69, F = 70, G = 71, H = 72, I = 73, J = 74, K = 75, L = 76, M = 77,
	N = 78, O = 79, P = 80, Q = 81, R = 82, S = 83, T = 84, U = 85, V = 86, W = 87, X = 88, Y = 89, Z = 90,
	LeftBracket = 91, Backslash = 92, RightBracket = 93,
	Escape = 256, Enter = 257, Tab = 258, Backspace = 259, Insert = 260, Delete = 261,
	Right = 262, Left = 263, Down = 264, Up = 265, PageUp = 266, PageDown = 267, Home = 268, End = 269,
	CapsLock = 280, ScrollLock = 281, NumLock = 282, PrintScreen = 283, Pause = 284,
	F1  = 290, F2  = 291, F3  = 292, F4  = 293, F5  = 294, F6  = 295, F7  = 296, F8  = 297,
	F9  = 298, F10 = 299, F11 = 300, F12 = 301, F13 = 302, F14 = 303, F15 = 304, F16 = 305,
	F17 = 306, F18 = 307, F19 = 308, F20 = 309, F21 = 310, F22 = 311, F23 = 312, F24 = 313,
	Numpad0 = 320, Numpad1 = 321, Numpad2 = 322, Numpad3 = 323, Numpad4 = 324,
	Numpad5 = 325, Numpad6 = 326, Numpad7 = 327, Numpad8 = 328, Numpad9 = 329,
	NumpadDecimal = 330, NumpadDivide = 331, NumpadMultiply = 332, NumpadSubtract = 333,
	NumpadAdd = 334, NumpadEnter = 335, NumpadEqual = 336,
	LeftShift = 340, LeftControl = 341, LeftAlt = 342, LeftSuper = 343,
	RightShift = 344, RightControl = 345, RightAlt = 346, RightSuper = 347,
	Menu = 348
};

std::unordered_map<glfw::Keys,const char*> keynames = {
	{ Keys::Unknown, "¿" },
	{ Keys::Space, "Space" }, { Keys::Apostrophe, "\'" }, { Keys::Comma, "," },
	{ Keys::Minus, "-" }, { Keys::Period, "." }, { Keys::Slash, "/" },
	{ Keys::Alpha0, "0" }, { Keys::Alpha1, "1" }, { Keys::Alpha2, "2" }, { Keys::Alpha3, "3" },
	{ Keys::Alpha4, "4" }, { Keys::Alpha5, "5" }, { Keys::Alpha6, "6" }, { Keys::Alpha7, "7" },
	{ Keys::Alpha8, "8" }, { Keys::Alpha9, "9" },
	{ Keys::SemiColon, ";" }, { Keys::Equal, "=" },
	{ Keys::A, "A" }, { Keys::B, "B" }, { Keys::C, "C" }, { Keys::D, "D" }, { Keys::E, "E" },
	{ Keys::F, "F" }, { Keys::G, "G" }, { Keys::H, "H" }, { Keys::I, "I" }, { Keys::J, "J" },
	{ Keys::K, "K" }, { Keys::L, "L" }, { Keys::M, "M" }, { Keys::N, "N" }, { Keys::O, "O" },
	{ Keys::P, "P" }, { Keys::Q, "Q" }, { Keys::R, "R" }, { Keys::S, "S" }, { Keys::T, "T" },
	{ Keys::U, "U" }, { Keys::V, "V" }, { Keys::W, "W" }, { Keys::X, "X" }, { Keys::Y, "Y" },
	{ Keys::Z, "Z" },
	{ Keys::LeftBracket, "[" }, { Keys::Backslash, "\\" }, { Keys::RightBracket, "]" },
	{ Keys::Escape, "Escape" }, { Keys::Enter, "Enter" }, { Keys::Tab, "Tab" },
	{ Keys::Backspace, "Backspace" }, { Keys::Insert, "Insert" }, { Keys::Delete, "Delete" },
	{ Keys::Right, "Right" }, { Keys::Left, "Left" }, { Keys::Down, "Down" }, { Keys::Up, "Up" },
	{ Keys::PageUp, "PageUp" }, { Keys::PageDown, "PageDown" }, { Keys::Home, "Home" },
	{ Keys::End, "End" }, { Keys::CapsLock, "CapsLock" }, { Keys::ScrollLock, "ScrollLock" },
	{ Keys::NumLock, "NumLock" }, { Keys::PrintScreen, "PrntScr" }, { Keys::Pause, "Pause" },
	{ Keys::F1,  "F1"  }, { Keys::F2,  "F2"  }, { Keys::F3,  "F3"  }, { Keys::F4,  "F4"  },
	{ Keys::F5,  "F5"  }, { Keys::F6,  "F6"  }, { Keys::F7,  "F7"  }, { Keys::F8,  "F8"  },
	{ Keys::F9,  "F9"  }, { Keys::F10, "F10" }, { Keys::F11, "F11" }, { Keys::F12, "F12" },
	{ Keys::F13, "F13" }, { Keys::F14, "F14" }, { Keys::F15, "F15" }, { Keys::F16, "F16" },
	{ Keys::F17, "F17" }, { Keys::F18, "F18" }, { Keys::F19, "F19" }, { Keys::F20, "F20" },
	{ Keys::F21, "F21" }, { Keys::F22, "F22" }, { Keys::F23, "F23" }, { Keys::F24, "F24" },
	{ Keys::Numpad0, "N0" }, { Keys::Numpad1, "N1" }, { Keys::Numpad2, "N2" },
	{ Keys::Numpad3, "N3" }, { Keys::Numpad4, "N4" }, { Keys::Numpad5, "N5" },
	{ Keys::Numpad6, "N6" }, { Keys::Numpad7, "N7" }, { Keys::Numpad8, "N8" },
	{ Keys::Numpad9, "N9" },
	{ Keys::NumpadDecimal, "N." }, { Keys::NumpadDivide, "N/" }, { Keys::NumpadMultiply, "N*" },
	{ Keys::NumpadSubtract, "N-" }, { Keys::NumpadAdd, "N+" }, { Keys::NumpadEnter, "NEnter" },
	{ Keys::NumpadEqual, "N=" },
	{ Keys::LeftShift, "LShift" }, { Keys::LeftControl, "LCtrl" },
	{ Keys::LeftAlt, "LAlt" }, { Keys::LeftSuper, "LWin" },
	{ Keys::RightShift, "RShift" }, { Keys::RightControl, "RCtrl" },
	{ Keys::RightAlt, "RAlt" }, { Keys::RightSuper, "RWin" },
	{ Keys::Menu, "Menu" },
};

}


namespace KeyBinds {

enum KeyBindsScope
{
	GLOBAL,
	PLAYER,
	STATEGAME,
	STATETITLESCREEN,
	TEXTINPUT,
	
	STATECREDITS,
	STATECREATEWORLD,  // everything is createnewworld
	STATEMULTIPLAYER,
	STATEDEATHSCREEN,
	STATETUTORIAL,
	STATESKINCHOOSER,
	STATESETTINGS,
	
	__LAST
};

std::unordered_map<KeyBindsScope,uintptr_t> KeyBindsScopeAddrs = {
	{ GLOBAL, base + idaOffsetFix(0x9E490) },
	
	{ STATEGAME, fdm::getFuncAddr((int)fdm::Func::StateGame::keyInput) },
	{ STATETITLESCREEN, fdm::getFuncAddr((int)fdm::Func::StateTitleScreen::keyInput) },
	{ STATECREDITS, fdm::getFuncAddr((int)fdm::Func::StateCredits::keyInput) },
	{ STATECREATEWORLD, fdm::getFuncAddr((int)fdm::Func::StateCreateWorld::keyInput) },
	{ STATEMULTIPLAYER, fdm::getFuncAddr((int)fdm::Func::StateMultiplayer::keyInput) },
	{ STATEDEATHSCREEN, fdm::getFuncAddr((int)fdm::Func::StateDeathScreen::keyInput) },
	{ STATETUTORIAL, fdm::getFuncAddr((int)fdm::Func::StateTutorial::keyInput) },
	{ STATESKINCHOOSER, fdm::getFuncAddr((int)fdm::Func::StateSkinChooser::keyInput) },
	{ STATESETTINGS, fdm::getFuncAddr((int)fdm::Func::StateSettings::keyInput) },
	
	{ PLAYER, fdm::getFuncAddr((int)fdm::Func::Player::keyInput) },
	
	{ TEXTINPUT, fdm::getFuncAddr((int)fdm::Func::gui_Nested::TextInput::keyInput) },
};

inline std::string KeyToString(glfw::Keys key) {
	if (auto keyname = glfw::keynames.find(key); keyname != glfw::keynames.end())
        return keyname->second;
    else  // no name set
		return "kc"+std::to_string(key);
}

using BindCallback = std::add_pointer<void(GLFWwindow* window, int action, int mods)>::type;


std::unordered_map<KeyBindsScope, std::unordered_map<glfw::Keys, std::vector<BindCallback>>> bindCallbacks;
void callCallbacks2(GLFWwindow* window, glfw::Keys key, int action, int mods, KeyBindsScope scope) {
	for (const auto& callback : bindCallbacks[scope][key])
		callback(window, action, mods);
}
typedef bool(__thiscall* KeyInputFunct)(void* self, fdm::StateManager& s, glfw::Keys key, int scancode, int action, int mods);
bool isInTextInput = false;

// Global (any keyinput)
void(__thiscall* global_keyInput)(GLFWwindow* window, glfw::Keys key, int scancode, int action, int mods);
void global_keyInput_H(GLFWwindow* window, glfw::Keys key, int scancode, int action, int mods ) {
	
	isInTextInput = false;
	
	// this will call gui_textinput_keyInput_H() if a TextInput is focused
	global_keyInput(window,key,scancode,action,mods);
	
	// if gui_textinput_keyInput_H() was called, we don't do shortcuts
	if (!isInTextInput)
		callCallbacks2(window,key,action,mods,GLOBAL);
}
// Player (in game and no other panel open)
bool(__thiscall* player_keyInput)(void* self, GLFWwindow* window, void* world, glfw::Keys key, int scancode, int action, int mods);
bool player_keyInput_H(void* self, GLFWwindow* window, void* world, glfw::Keys key, int scancode, int action, int mods) {
	callCallbacks2(window,key,action,mods,PLAYER);
	return player_keyInput(self,window,world,key,scancode,action,mods);
}
// any Textinput
void(__thiscall* gui_textinput_keyinput)(void* self, fdm::gui::Window* w, glfw::Keys key, int scancode, int action, int mods);
void __fastcall gui_textinput_keyinput_H(void* self, fdm::gui::Window* w, glfw::Keys key, int scancode, int action, int mods) {
	isInTextInput = true;
	callCallbacks2(w->getGLFWwindow(),key,action,mods,KeyBindsScope::TEXTINPUT);
	gui_textinput_keyinput(self, w, key, scancode, action, mods);
}
std::unordered_map<KeyBindsScope,KeyInputFunct> originals;
template<auto scope> bool generic_keyinput(void* self, fdm::StateManager& s, glfw::Keys key, int scancode, int action, int mods ) {
	
	auto result = originals[scope](self,s,key,scancode,action,mods);
	
	// if gui_textinput_keyInput_H() was called, we don't do shortcuts
	if (isInTextInput)
		return result;
	
	callCallbacks2(s.window,key,action,mods,scope);
	
	return result;
}

template<auto scope> constexpr void instantiate(){
	if (scope == GLOBAL)
		return Hook( KeyBindsScopeAddrs[GLOBAL], global_keyInput_H, &global_keyInput );
	if (scope == PLAYER)
		return Hook( KeyBindsScopeAddrs[PLAYER], player_keyInput_H, &player_keyInput );
	if (scope == TEXTINPUT)
		return Hook( KeyBindsScopeAddrs[TEXTINPUT], gui_textinput_keyinput_H, &gui_textinput_keyinput );
	
	Hook( KeyBindsScopeAddrs[scope], generic_keyinput<scope>, &originals[scope] );
}
void fallbackInfo(){
	printf("%s: 4DKeyBinds.dll not found, running in fallback mode on default keys!\n",fdm::getModName(fdm::modID).c_str());
}

inline void fallbackBind(const std::string& bindName, glfw::Keys defaultKey, KeyBindsScope scope, BindCallback callback) {
	
	static bool initialized = false;
	if (!initialized) {
		registerConsoleCallback(fallbackInfo,ConsoleEvent::info);
		// don't even try touching this, this hooks all addresses in KeyBindsScopeAddrs[] with generic_keyinput() or a custom function shape
		([]<auto... i>(std::index_sequence<i...>){(instantiate<KeyBindsScope(i)>(),...);})(std::make_index_sequence<__LAST>());
		
		initialized = true;
	}
	
	registerConsoleKeyinfo({{KeyToString(defaultKey),bindName+" ("+fdm::getModName(fdm::modID)+")"}});
	bindCallbacks[scope][defaultKey].push_back(callback);
}


// old function no longer needed with new 4dm modloader which has dll load order
/*
inline bool IsLoaded() {
	
	static int result = -1;
	if (result >= 0)
		return result;
	
	// why do I have to do this Tr1Ngle?? Why?????
	int i = 0;
	while (!GetModuleHandleA("4DKeyBinds.dll")) {  // wait for module to load or 2s
		if (i++>200)
			return result = false;
		Sleep(10);
	}
	
	// sleep some more to make sure keybyinds.json is loaded, so our default keys aren't ignored
	Sleep(200);
	
	return result = true;
}
// */
inline bool IsLoaded() {
	return fdm::isModLoaded("tr1ngledev.4dkeybinds");
}

// creates a bind with name "MOD_NAME:bindName"
inline void addBind(const std::string& bindName, glfw::Keys defaultKey, KeyBindsScope scope, BindCallback callback) {
	
	if (!IsLoaded())
		return fallbackBind(bindName,defaultKey,scope,callback);
	
    reinterpret_cast<void(__stdcall*)(const msvc_string&, int, int, BindCallback)>(GetProcAddress(fdm::getModHandle("tr1ngledev.4dkeybinds"), "addBind"))
		( fdm::modID+":"+bindName, (int)defaultKey, (int)scope, callback);
}

inline void hookBind(const std::string& bindName, KeyBindsScope scope, BindCallback callback)
{
	if (!IsLoaded())
		return;
	reinterpret_cast<void(__stdcall*)(const msvc_string&, KeyBindsScope, BindCallback)>(GetProcAddress(fdm::getModHandle("tr1ngledev.4dkeybinds"), "hookBind"))
		( fdm::modID+":"+bindName, scope, callback);
}

inline void triggerBind(const std::string& bindName, KeyBindsScope scope, int action, int mods)
{
	if (!IsLoaded())
		return;
	reinterpret_cast<void(__stdcall*)(const msvc_string&, KeyBindsScope, int, int)>(GetProcAddress(fdm::getModHandle("tr1ngledev.4dkeybinds"), "triggerBind"))
		( fdm::modID+":"+bindName, scope, action, mods);
}

}  // namespace KeyBinds
using KeyBinds::KeyBindsScope;