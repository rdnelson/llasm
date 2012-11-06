/*-------------------------------------*\
|
|  File Name: Parser.hpp
|
|  Creation Date: 31-10-2012
|
|  Last Modified:
|
|  Created By: Robert Nelson
|
\*-------------------------------------*/

#pragma once

#include "Command.hpp"

#include <string>
#include <vector>

class Parser {
	public:
		Parser();
		std::string parseLine(std::string line);
		unsigned int GetSize() const { return mSize; }

		const std::vector<Command*> & getCommands() const { return mLines; }

	private:
		unsigned int NumTokens(std::string line);
		std::string GetToken(std::string line, unsigned int num);
		std::string GetSummary(std::string tok);
		std::string GetRegisterSummary(std::string tok);

		void AddLabel(std::string name) {}
		void Trim(std::string& str);

		std::vector<Command*> mLines;
		unsigned int mAddr;
		unsigned int mSize;

};

