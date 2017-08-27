#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <fstream>

class Config
{
public:

	static Config* C();
	~Config();

	bool LoadFromFile(std::string filename);
	bool SaveToFile(std::string filename);

	bool _MusicOn;
	bool _SFXOn;
	int _AILvl;

private:

	Config();
	static Config* _Instance;

};

#endif