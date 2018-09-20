#pragma once

#include <string>
#include <map>

class ConfigManager {

	const std::string CONFIG_FILE_PATH = "../resources/configs/config.json";

	const std::map<std::string, std::map<std::string, std::string>> m_config = loadConfig();

private:
	ConfigManager() {};
	std::map<std::string, std::map<std::string, std::string>> loadConfig();

public:
	#pragma region Singleton
	static ConfigManager & getInstance() {
		static ConfigManager instance;
		return instance;
	}
	#pragma endregion

	std::string getString(std::string section, std::string key);
};

