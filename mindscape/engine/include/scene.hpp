#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "game_object.hpp"

class Scene {
	public:
		std::string name;
		std::unordered_map<std::string, engine::GameObject*> objects;

		Scene();
		Scene(std::string nome, std::unordered_map<std::string, engine::GameObject*> components);
		~Scene();

		void add_object(std::string name, engine::GameObject* object);
		virtual void load();
		void render();
		void free();
};

#endif
