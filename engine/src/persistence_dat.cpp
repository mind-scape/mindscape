/**
 * @file persistence_dat.cpp
 *
 * @brief Purpose: Contains methods to save the game
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 *
 */
#include "persistence_dat.hpp"
#include "../engine/include/log.hpp"
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>

using namespace engine;

PersistenceDat *PersistenceDat::instance = 0;

/**
 * @brief Get Instance
 *
 * Method responsible for get instance
 *
 * @return void
 */
PersistenceDat *PersistenceDat::get_instance(){
	if (!instance) {
		instance = nullptr;
	}
	else {
		/*Do nothing*/
	}

	instance = new PersistenceDat();

	return instance;
}


/**
 * @brief Load Method
 *
 * Method responsible for load the saved game
 *
 * @param p_path path to saved game
 * @return game loaded
 */
PersistenceMap * PersistenceDat::load(std::string p_path){
	PersistenceMap *data = nullptr;
	data = new PersistenceMap();

	std::stack<std::string> paths;
	paths.push(p_path);
	std::string line = "";

	/* Reads the complete file */
	while(!paths.empty()){
		std::string path = paths.top();
		paths.pop();
		std::ifstream save_file;
		save_file.open(path, std::ifstream::in);

		/* Opens the file to be written */
		if (save_file.is_open()){

			/* Writes the opened file with game datas*/
			while (std::getline(save_file,line)){
				bool is_include = false;
				std::istringstream iss(line);
				std::string key = "";
				std::string value = "";
				std::unordered_map<std::string, std::string> object_data;

				/* If the line are empty or the line initialize with comment tag */
				if (line != "" && line[0] != '#'){
					while(iss >> key && iss >> value){

						/* Writes persistence values in opened file */
						if ((is_include = (key == "include"))) {
							paths.push(value);
						}
						else {
							/* Do nothing */
						}

						object_data[key] = value;
					}

					if (!is_include) {
						data->insert_object(object_data);
					}
					else {
				        /* Do nothing */
				    }
				}
				else {
		        	INFO("The file was opened incorrectly");
			    }
			}
		}
		else {
			INFO("Unable to open file");
			return NULL;
		}
	}

	return data;
}

/**
 * @brief Dump Method
 *
 * Method responsible for dump
 *
 * @param path path to save the open game in a file
 * @param data saved game
 * @return void
 */
bool PersistenceDat::dump(std::string path, PersistenceMap * data){
	std::ofstream save_file;
	save_file.open(path);

	/* Opens the file to be written */
	if (save_file.is_open()) {
		for (auto it = data->begin(); it < data->end(); it++) {
			
			/* Writes persistence datas in opened file */
			for (auto each_data : *it) {
				save_file << each_data.first << " " << each_data.second << " ";
			}

			save_file << std::endl;
		}
	}
	else {
		INFO("Unable to open file");

		return false;
	}

	save_file.close();

	return true;
}
