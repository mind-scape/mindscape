#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <iostream>

namespace engine{

  class Component{
    private:
      std::string name;
      std::pair<int, int> coordinates;
      bool active;
      int priority;

    public:
      Component(){};
      Component(
        std::string p_name,
        std::pair<int, int> p_coordinates,
        bool isactive,
        int p_priority)
        :name(p_name),
        coordinates(p_coordinates),
        active(isactive),
        priority(p_priority){};

      ~Component(){};

      virtual bool load(){};
      virtual void free(){};
      virtual void draw(int, int){};
      bool is_active();
      void activate();
      void deactivate();
      std::pair<int, int> get_coordinates();
      void set_coordinates(std::pair<int, int>);
      int get_priority();
      void set_priority(int);
      std::string get_name();
      void set_name(std::string);

    };
}

#endif
