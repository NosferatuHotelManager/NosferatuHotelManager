#pragma once
#include "AnimationFrame.h"

//This class will represent a single drawn entity - ie. a single character
//It will contain all animations for that character
class Animation
{
	sf::Sprite												m_sprite;
	sf::Sound												m_sound;
	std::map <std::string, std::vector<AnimationFrame>>		m_animations;
	std::map<std::string, sf::SoundBuffer>					m_soundEffects;
	sf::Time												m_timeSinceLastUpdate;
	std::string												m_CurrentAnim;
	unsigned int											m_currentAnimFrame;
	ScreensManager::ScreenTag								m_screenTag;

public:
	Animation();
	Animation(const Animation &_obj);
	~Animation();

	bool													LoadAnimation(std::string _fileName);
	bool													BeginAnimation(std::string _animationName);
	std::string&											GetCurrentAnim();
	sf::Sprite&												GetSprite();
	std::string&											GetSoundEffect();
	sf::Sound&												GetSound();

	//Update may not need to be virtual ...
	virtual void											Update(sf::Time& _deltaTime);
	virtual void											ChangeScreenTag(ScreensManager::ScreenTag _newTag);
	ScreensManager::ScreenTag								GetScreenTag();

	void													AssignAnimation(std::string& _anim, Animation &_ref);
};