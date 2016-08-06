#include "stdafx.h"
#include "Utilities.h"

//Master game time
float		Utilities::m_gameTime = 0;
bool		Utilities::m_isGamePaused = false;

//This will be multiplied to calculate the passage of time
float		Utilities::m_currentSpeedFactor = 5;


unsigned int Utilities::fpsP1 = 0;
unsigned int Utilities::fpsP2 = 0;
unsigned int Utilities::fpsP3 = 0;
unsigned int Utilities::fpsP4 = 0;
unsigned int Utilities::fpsP5 = 0;
unsigned int Utilities::fpsAvg = 0;

float Utilities::FormatGameTime(float _time)
{
	if ((unsigned int)_time % 100 > 60)
	{
		//Increment to next hour
		_time += 100;

		//Set the timer back to 0 - CARRY OVER EXTRA TIME!
		_time -= 60;
	}

	if ((unsigned int)_time % 10000 > 2400)
	{
		//Increment to next day
		_time += 10000;

		//Set the hours back to 0 - CARRY OVER EXTRA TIME
		_time -= 2400;
	}

	//Add years? Who knows, who cares?
	return _time;
}

void Utilities::Update()
{
	//Don't calculate passage of time if game is paused ... maybe make it go real-time(?)
	if (!m_isGamePaused)
	{
		//Make change to game time
		m_gameTime += screensManager.m_timePerFrame * m_currentSpeedFactor;
		//Format the number
		FormatGameTime(m_gameTime);
	}
}

bool Utilities::isHourInRange(int lowerHourBound, int upperHourBound, int hour) {
	if (lowerHourBound <= upperHourBound) {
		return (hour >= lowerHourBound && hour <= upperHourBound);
	}
	return (hour >= lowerHourBound || hour <= upperHourBound);
}

float Utilities::getTimeSum(float _startTime, float _duration) {
	float finalTime = 0;

	//Handle minutes first
	finalTime += (unsigned int)_startTime % 100;
	finalTime += (unsigned int)_duration % 100;

	//Handle hours next
	finalTime += ((unsigned int)std::floor(_startTime / 100) % 10000) * 100;
	finalTime += ((unsigned int)std::floor(_duration / 100) % 10000) * 100;

	//Return as a formatted string
	return FormatGameTime(finalTime);
}

float Utilities::getTimeDifference(float _startTime, float _endTime)
{
	float finalTime = 0;
	bool newHour = false;

	//Handle minutes first
	finalTime += (unsigned int)_startTime % 100;
	finalTime -= (unsigned int)_endTime % 100;

	//If it cuts into a new hour, make note
	if (finalTime < 0)
	{
		newHour = true;
		finalTime += 60;
	}

	//Handle hours next
	finalTime += ((unsigned int)std::floor(_startTime / 100) % 10000) * 100;
	finalTime -= ((unsigned int)std::floor(_endTime / 100) % 10000) * 100;

	//If it cut into a new hour, subtract to account for that
	if (newHour)
		finalTime -= 100;

	//Make dev note if difference is negative - that probably shouldn't happen!
	if (finalTime < 0)
		debug.Log(2, "The difference between game time " + std::to_string(_startTime) + " and " + std::to_string(_endTime) + " is negative!");

	//Return as a formatted string
	return FormatGameTime(finalTime);
}

int Utilities::randInt(int lowerBound, int upperBound) {
	return 0;
}

int Utilities::getCurrentTime() {
	return 0;
}

int Utilities::getCurrentDay() {
	return getCurrentTime()/10000;
}

int Utilities::getCurrentHour() {
	return (getCurrentTime() % 10000)/100;
}

int Utilities::getCurrentMinute() {
	return getCurrentTime()%100;
}

int Utilities::getCurrentPhaseOfDay() {
	int phase = 0;

	if (getCurrentDay() % 7 >= 5) {
		phase += 3;
	}

	if (isHourInRange(EVENINGSTARTHOUR, EVENINGENDHOUR, getCurrentHour())) {
		phase += 1;
	}

	if (isHourInRange(NIGHTSTARTHOUR, NIGHTENDHOUR, getCurrentHour())) {
		phase += 2;
	}

	return phase;
}

int Utilities::getDay(int time) {
	return time / 10000;
}

int Utilities::getHour(int time) {
	return (time % 10000) / 100;
}

int Utilities::getMinute(int time) {
	return time % 100;
}

int Utilities::getPhaseOfDay(int time) {
	int phase = 0;

	if (getDay(time) % 7 > 4) {
		phase += 3;
	}

	if (isHourInRange(EVENINGSTARTHOUR, EVENINGENDHOUR, getHour(time))) {
		phase += 1;
	}

	if (isHourInRange(NIGHTSTARTHOUR, NIGHTENDHOUR, getHour(time))) {
		phase += 2;
	}

	return phase;
}

float Utilities::getFPS(const sf::Time & _time)
{
	fpsP5 = fpsP4;
	fpsP4 = fpsP3;
	fpsP3 = fpsP2;
	fpsP2 = fpsP1;
	fpsP1 = (unsigned int)(1000000.0f / _time.asMicroseconds());

	fpsAvg = fpsP1 + fpsP2 + fpsP3 + fpsP4 + fpsP5;
	fpsAvg /= 5;


	//This should probably be changed, but w.e
	return (float)fpsAvg;
}