//TODO Create enum to components types

#ifndef COMPONENT_H 
#define COMPONENT_H

#include <string>

namespace engine{

  class Component{
    public:
      Component(){};
      Component(std::string p_type):type(p_type){};
      ~Component(){};

      virtual bool load(){};
      virtual void free(){};

      std::string type;
  };

}

#endif
