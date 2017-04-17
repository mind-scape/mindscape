#ifndef COMPONENT_H 
#define COMPONENT_H

namespace engine{

  class Component{
    public:
      Component(){};
      ~Component(){};

      virtual bool load(){};
      virtual void free(){};
  };

}

#endif
