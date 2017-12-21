#ifndef SFGE_JSON_UTILIY_H
#define SFGE_JSON_UTILIY_H

//Externals includes
#include "json.hpp"
using json = nlohmann::json;

namespace sfge
{
	bool IsJsonValueNumeric(const json::value_type& jsonValue);
	bool CheckJsonExists(const json& jsonObject, std::string parameterName);
	bool CheckJsonParameter(const json& jsonObject, std::string parameterName, json::value_t expectedType);
	std::unique_ptr<json> LoadJson(std::string jsonPath);
}
#endif