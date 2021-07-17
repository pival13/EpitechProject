/*
** By Kevin Pruvost, June 2020
** File description:
** Mutex class.
*/

#pragma once

// C++ includes
#include <mutex>
#include <condition_variable>

#define LINE() std::string(__FILE__) + ": line " + \
std::to_string(__LINE__)

/**
 * @brief Just for testing if mutex is responsible for some freezes.
 */
class Mutex : public std::mutex
{
public:
	Mutex();
	~Mutex();

	/**
	 * @brief Modified version of std::mutex::lock().
	 */
	void lock(const std::string & str = "");
	/**
	 * @brief Modified version of std::mutex::unlock().
	 */
	void unlock();

public:
	bool locked = false;
};