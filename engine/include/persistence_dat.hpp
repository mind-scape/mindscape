/**
 * @file persistence_dat.hpp
 * @brief Purpose: Contains methods to save the game
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */
#ifndef PERSISTENCE_DAT_H
#define PERSISTENCE_DAT_H

#include "persistence.hpp"
#include "persistence_map.hpp"
#include "unordered_map"

namespace engine{
    /**
     * @brief A Persistence data class
     *
     * Class responsible for keep the persistence of game data.
     *
     */
    class PersistenceDat : public Persistence {
    private:
        PersistenceDat(){};
        static PersistenceDat *instance;

    public:
        static PersistenceDat *get_instance();
        ~PersistenceDat(){};

        void operator = (PersistenceDat const&) = delete;
        PersistenceMap * load (std::string);
        bool dump (std::string, PersistenceMap *);
    };
}
#endif
