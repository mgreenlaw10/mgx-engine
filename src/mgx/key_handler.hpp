#pragma once

#include <unordered_map>
#include <functional>

#include <GLFW/glfw3.h>

namespace mgx
{
	
	class KeyHandler
	{
	private:
		struct KeyData
		{
			bool is_pressed;
			std::function<void()> while_pressed;
			std::function<void()> on_press;
			std::function<void()> on_release;

			KeyData()
			: is_pressed	(false),
			  while_pressed ([](){}),
			  on_press		([](){}),
			  on_release	([](){}) 
			  {}
		};
		std::unordered_map<int, KeyData> key_map;

	public:
		KeyHandler();
		void AddKey(int key);

		void UpdateKeyState(int key, int action, int mods);
		void ProcessKeyState();

		bool IsPressed(int key);

		void DefineWhilePressed	(int key, std::function<void()> func);
		void DefineOnPress		(int key, std::function<void()> func);
		void DefineOnRelease	(int key, std::function<void()> func);
	};
}