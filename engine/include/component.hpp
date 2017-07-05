#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <iostream>

namespace engine{

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
