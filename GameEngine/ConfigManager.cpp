#include "ConfigManager.h"
#include "json.h"
#include <fstream>
#include <iostream>

const std::string CONFIG_KEY = "config";
const std::string SECTION_KEY = "section";
const std::string ENTRIES_KEY = "entries";
const std::string KEY_KEY = "key";
const std::string VALUE_KEY = "value";

std::map<std::string, std::map<std::string, std::string>> ConfigManager::loadConfig()
{
	std::map<std::string, std::map<std::string, std::string>> config;

	std::ifstream file{ CONFIG_FILE_PATH };
	if (file.is_open())
	{
		nlohmann::json data;
		file >> data;

		for (auto section : data[CONFIG_KEY])
		{
			std::map<std::string, std::string> sectionData;
			for (auto entry : section[ENTRIES_KEY])
			{
				sectionData.emplace(entry[KEY_KEY], entry[VALUE_KEY]);
			}

			std::cout << "Read section of length: " << sectionData.size() << std::endl;

			config.emplace(section[SECTION_KEY], sectionData);
		}

		std::cout << "Read config of section count: " << config.size() << std::endl;
	}

	return config;
}

std::string ConfigManager::getString(std::string section, std::string key)
{
	try
	{
		return m_config.at(section).at(key);
	}
	catch (std::out_of_range e) 
	{
		std::cerr << "Unable to find key in section " << section << " with key " << key << std::endl;
		return "";
	}
}
