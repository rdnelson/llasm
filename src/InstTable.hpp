/*-------------------------------------*\
|
|  File Name: InstTable.hpp
|
|  Creation Date: 31-10-2012
|
|  Last Modified:
|
|  Created By: Robert Nelson
|
\*-------------------------------------*/

#pragma once

#include <string>
#include <map>

class InstTable {

	public:
		static std::map<std::string, unsigned int> InstMap;
		static std::map<std::string, unsigned int> PrefixMap;

		static void InitializeTable();
};
