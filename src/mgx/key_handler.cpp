#include "key_handler.hpp"

#include <iostream>

namespace mgx
{
	KeyHandler::KeyHandler() {}

	void KeyHandler::AddKey(int key) {
		key_map[key] = KeyData();
	}

	void KeyHandler::UpdateKeyState(int key, int action, int mods) {
		if (key_map.find(key) == key_map.end())
			return;

		bool old_state = key_map[key].is_pressed;

		switch (action) {
			case GLFW_PRESS:
				key_map[key].is_pressed = true;
				break;
			case GLFW_RELEASE:
				key_map[key].is_pressed = false;
				break;
		}

		if (key_map[key].is_pressed && !old_state) {
			key_map[key].on_press();
		}
		else if (!key_map[key].is_pressed && old_state) {
			key_map[key].on_release();
		}
	}

	void KeyHandler::ProcessKeyState() {
		for (std::unordered_map<int, KeyData>::iterator it = key_map.begin(); it != key_map.end(); ++it)
    		if (it->second.is_pressed)
    			it->second.while_pressed();
	}

	void KeyHandler::DefineWhilePressed(int key, std::function<void()> func) {
		if (key_map.find(key) == key_map.end())
			AddKey(key);
		key_map[key].while_pressed = func;
	}

	void KeyHandler::DefineOnPress(int key, std::function<void()> func) {
		if (key_map.find(key) == key_map.end())
			AddKey(key);
		key_map[key].on_press = func;
	}

	void KeyHandler::DefineOnRelease(int key, std::function<void()> func) {
		if (key_map.find(key) == key_map.end())
			AddKey(key);
		key_map[key].on_release = func;
	}

	bool KeyHandler::IsPressed(int key) {
		if (key_map.find(key) != key_map.end())
			return key_map[key].is_pressed;
		return false;
	}
}