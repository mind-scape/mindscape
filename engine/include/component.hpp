/** 
 * @file component.hpp
 * @brief Contains methods to component class' management. This methods can control the entire 
 * component object, naming the component, setting the priority, verifing activation and displacing. 
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <iostream>

namespace engine{

	/** 
     * @brief A Component class.
     * 
     * This class is a model that contains all the specification of components that can be added to game objects.
     * @warning Limitations: All components after being used needs to be free.
     */
	class Component{
	private:
		std::string name;
		std::pair<int, int> displacement;
		bool active;
		int priority;

	public:
		Component(){};
		Component(
				std::string p_name,
				std::pair<int, int> p_displacement,
				bool p_active,
				int p_priority)
				:name(p_name),
				 displacement(p_displacement),
				 active(p_active),
				 priority(p_priority){};

		~Component(){};

		virtual bool load(){};
		virtual void free(){};
		virtual void draw(int, int){};
		bool is_active();
		void activate();
		void deactivate();
		std::pair<int, int> get_displacement();
		void set_displacement(std::pair<int, int>);
		int get_priority();
		void set_priority(int);
		std::string get_name();
		void set_name(std::string);
	};
}

#endif
