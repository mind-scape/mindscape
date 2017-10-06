/**
 * @file time.hpp
 * @brief Purpose: Contains methods to time class' management.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#ifndef TIME_H
#define TIME_H

#include <SDL2/SDL.h>

namespace engine {
	typedef enum {
		RUNNING, PAUSED
	} state;
	
	/**
 	 * @brief A Time class.
 	 *
 	 * A class responsible for making time management easier.
 	 */
	class Time {
	public:
		virtual ~Time() = default;
		static unsigned time_elapsed();
		static void pause_timer();
		static void resume_timer();
		static unsigned real_time_elapsed();
		static void update_time(unsigned now);
		static void init();
	
	protected:
		static unsigned last_time;
		static unsigned now;
		static unsigned m_time_elapsed;
		static unsigned m_last_update;
		static state m_current_state;
		
	};
}

#endif
