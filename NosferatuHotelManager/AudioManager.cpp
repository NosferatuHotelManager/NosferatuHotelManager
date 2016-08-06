#include "stdafx.h"
#include "AudioManager.h"

AudioManager::AudioManager()
{
	//Populate the sound instances list
	for (unsigned int cnt = 0; cnt < 100; cnt++)
	{
		soundInstancesList.push_back(SoundHolder());
	}
}

bool AudioManager::LoadSound(std::string _fileName)
{
	sf::SoundBuffer	buffer;
	std::string		message;
	std::string		fileLoc;

	//Check if sound file is already loaded before trying to load
	if (soundsMap.find(_fileName) == soundsMap.end())
	{
		//Set file location prefix
		fileLoc = "Resources/Sounds/";
		fileLoc += _fileName;

		//Try loading the file, return success/fail
		if (!buffer.loadFromFile(fileLoc))
		{
			message = "Couldn't load SOUND file '";
			message += _fileName;
			message += "'!";
			debug.Log(3, message);
			return false;
		}
		else
		{
			message = "Successfully loaded SOUND file '";
			message += _fileName;
			message += "'!";
			debug.Log(0, message);
		}

		//Save the loaded sound file if successful
		soundsMap.insert(std::pair<std::string, sf::SoundBuffer>(_fileName, buffer));
	}
	else
	{
		//Log double-loading of sound file - may or may not be intended
		message = "Attempted to reload SOUND file '";
		message += _fileName;
		message += "'!";
		debug.Log(0, message);
	}

	return true;
}
/*
bool AudioManager::LoadMusic(std::string _fileName)
{
	sf::Music		music;
	std::string		message;
	std::string		fileLoc;

	//Check if music file is already loaded before trying to load
	if (musicsMap.find(_fileName) == musicsMap.end())
	{
		fileLoc = "Resources/Music/";
		fileLoc += _fileName;

		if (!music.openFromFile(fileLoc))
		{
			message = "Couldn't load MUSIC file '";
			message += _fileName;
			message += "'!";
			debug.Log(3, message);
			return false;
		}
		else
		{
			message = "Successfully loaded MUSIC file '";
			message += _fileName;
			message += "'!";
			debug.Log(1, message);
		}

		musicsMap.insert(std::pair<std::string, sf::Music>(_fileName, music));
	}
	else
	{
		message = "Attempted to reload MUSIC file '";
		message += _fileName;
		message += "'!";
		debug.Log(1, message);
	}

	return true;
}
*/




/*
0	-	9	: GUI
10	-	14	: Player
15	-	49	: NPCs
50	-	69	: Tiles
69	-	99	: Spare/Other

Returns 500 if no spot was found
*/
unsigned int AudioManager::EnqueueSound(int _priority, sf::SoundBuffer& _buffer, Animation* _source)
{
	//Priority is used as a start point for the search
	for (unsigned int cnt = _priority; cnt < soundInstancesList.size(); cnt++)
	{
		//Find an empty/unused sf::Sound
		if (soundInstancesList[cnt].m_sound.getStatus() != sf::Sound::Playing)
		{
			soundInstancesList[cnt].m_sound.setBuffer(_buffer);
			soundInstancesList[cnt].m_sound.play();
			return cnt;
		}
	}

	//Error code
	return 500;
}

std::map<std::string, sf::SoundBuffer>& AudioManager::GetSoundsList()
{
	return soundsMap;
}

std::map<std::string, sf::Music>& AudioManager::GetMusicsList()
{
	return musicsMap;
}

std::vector<SoundHolder>& AudioManager::GetSoundInstancesList()
{
	return soundInstancesList;
}