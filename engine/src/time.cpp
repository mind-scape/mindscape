/**
 * @file time.cpp
 * @brief Purpose: Contains methods to time class' management.
 *
 * MIT License
 * Copyright (c) 2017 MindScape
 *
 * https://github.com/TecProg2017-2/mindscape/blob/master/LICENSE.md
 */

#include "time.hpp"

using namespace engine;

unsigned Time::now;
unsigned Time::last_time;
unsigned Time::m_time_elapsed;
unsigned Time::m_last_update;
state Time::m_current_state;

/**
 * @brief Initialize variables
 *
 * @return void
 */
void Time::init() {
	now = SDL_GetTicks();
	last_time = SDL_GetTicks();
}

/**
 * @brief Counts the time elapsed
 *
 * @return unsigned with the time elapsed
 */
unsigned Time::time_elapsed() {
	if (Time::m_current_state == RUNNING) {
		unsigned now = real_time_elapsed();
		update_time(now);
	}
	else {
		/* Do nothing */
	}
	
	return m_time_elapsed;
}

/**
 * @brief Return elapsed time since game opening
 *
 * @return return the milliseconds since the game started
 */
unsigned Time::real_time_elapsed() {
	return SDL_GetTicks();
}

/**
 * @brief Pauses the timer
 *
 * @return void
 */
void Time::pause_timer() {
	if (Time::m_current_state == RUNNING) {
		unsigned now = real_time_elapsed();
		update_time(now);
		Time::m_current_state = PAUSED;
	}
	else {
		/* Do nothing */
	}
}

/**
 * @brief Resumes the timer
 *
 * @return void
 */
void Time::resume_timer() {
	if (Time::m_current_state == PAUSED) {
		unsigned now = real_time_elapsed();
		m_last_update = now;
		Time::m_current_state = RUNNING;
	}
	else {
		/* Do nothing */
	}
}

/**
 * @brief Updates the timer
 *
 * @param now Time on the given moment
 *
 * @return void
 */
void Time::update_time(unsigned now) {
	m_time_elapsed += now - m_last_update;
	m_last_update = now;
}
