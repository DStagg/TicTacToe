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

	file.close();

	return true;
}