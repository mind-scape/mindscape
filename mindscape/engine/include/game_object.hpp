#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

namespace engine {

  class GameObject{
    public:
      GameObject(){};
      ~GameObject(){};

      virtual bool load();
      virtual void free();
      bool add_component(Component & component);

      std::name; 
      std::unordered_map<std::string ,std::vector<Components * > > components;

  };

}

#endif
