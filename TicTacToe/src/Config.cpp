#include "Config.h"

Config* Config::_Instance = 0;

Config* Config::C()
{
	if (_Instance == 0)
		_Instance = new Config();
	return _Instance;
};

Config::Config()
{
	_MusicOn = true;
	_SFXOn = true;
	_AILvl = 0;

	if (!LoadFromFile("Config.txt"))
		SaveToFile("Config.txt");
};
Config::~Config()
{
	SaveToFile("Config.txt");
};

bool Config::LoadFromFile(std::string filename)
{
	std::fstream file(filename, std::ios::in);
	std::string line;

	if (!file.is_open())
		return false;

	//	Music On/Off
	std::getline(file, line);
	_MusicOn = (line == "Music: On");
	//	SFX On/Off
	std::getline(file, line);
	_SFXOn = (line == "SFX: On");
	//	AI Level
	std::getline(file, line);
	if (line == "AI: Easy") _AILvl = 0;
	else if (line == "AI: Medium") _AILvl = 1;
	else _AILvl = 2;

	file.close();

	return true;
};

bool Config::SaveToFile(std::string filename)
{
	std::fstream file(filename, std::ios::out | std::ios::trunc);
	
	if (_MusicOn)
		file << "Music: On" << std::endl;
	else
		file << "Music: Off" << std::endl;

	if (_SFXOn)
		file << "SFX: On" << std::endl;
	else
		file << "SFX: Off" << std::endl;

	if (_AILvl == 0)
		file << "AI: Easy" << std::endl;
	else if (_AILvl == 1)
		file << "AI: Medium" << std::endl;
	else
		file << "AI: Hard" << std::endl;

	file.close();

	return true;
}