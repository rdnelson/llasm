/*-------------------------------------*\
|
|  File Name: Parser.cpp
|
|  Creation Date: 31-10-2012
|
|  Last Modified:
|
|  Created By: Robert Nelson
|
\*-------------------------------------*/

#include "Parser.hpp"
#include "InstTable.hpp"

#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <cctype>

Parser::Parser() : mAddr(0), mSize(0) {}

std::string Parser::parseLine(std::string line) {
	
	Command* newCmd = 0;
	std::string tline(line);
	Trim(tline);

	//uppercase the string
	std::transform(tline.begin(), tline.end(), tline.begin(), ::toupper);
	std::string tmpLine(tline);

	if(tmpLine[0] == ';')
		return "";

	bool comma = false;
	unsigned int index = 0;
	std::string label;
	std::string token; //current token
	std::string prefix; //4 is the max number of prefixes
	std::vector<std::string> operands; //4 is also the max number of operands
	std::string inst; //Lookup string for map

	//find a label
	if((index = tmpLine.find(':')) != std::string::npos) {
		label = tmpLine.substr(0, index);
		tmpLine = tmpLine.substr(index + 1);
		Trim(tmpLine);
		AddLabel(label);
	}

#ifdef DEBUG
	std::cout << "Label: " << label << std::endl;
#endif

	//if there isn't any code, then we're done.
	if(tmpLine == "")
		return "";

	
	while(true) {
		if(tmpLine[0] == ';')
			break;
		index = tmpLine.find(comma ? ',' : ' ');
		if(index == std::string::npos) {
			if(inst == "") {
				inst.assign(tmpLine);
				break;
			} else {
				if(operands.size() >= 4)
					return "Number of operands exceeds maximum amount (4)";
				unsigned int pos = 0;
				if(tmpLine[0] == '[')
					pos = tmpLine.find(']');

				if(pos == std::string::npos)
					return "No closing ']' found";				

				if(tmpLine.find(' ', pos) == std::string::npos)
					operands.push_back(tmpLine);
				else
					//check for size overrides
					if(tmpLine.find("BYTE") == 0 ||
						tmpLine.find("WORD") == 0 ||
						tmpLine.find("FAR") == 0 ||
						tmpLine.find("NEAR") == 0) {
						operands.push_back(tmpLine);
					} else {
						return "Invalid operand: `" + tmpLine + "'";
					}
				break;
			}
		} else {
			token = tmpLine.substr(0, index);
			if(inst == "") {
				if(InstTable::PrefixMap.count(token)) {
					if(prefix.size() >= 4)
						return "Number of prefix keywords exceeds maximum amount (4)";
					prefix.append(1, (char)InstTable::PrefixMap[token]);
				} else {
					inst.assign(token);
					comma = true;
				}
			} else {
				operands.push_back(token);
			}
		}
		tmpLine = tmpLine.substr(index + 1);
		Trim(tmpLine);
	}

#ifdef DEBUG
	std::cout << "Prefix count: " << prefix.size() << std::endl;
	std::cout << "Command: " << inst << std::endl;
	std::cout << "Operands:" << std::endl;
	for(unsigned int i = 0; i < operands.size(); i++) {
		std::cout << operands[i] << std::endl;
	}
#endif

	newCmd = Command::MakeCommand(inst, prefix, operands, label);
	if(!newCmd) {
		return "Error creating command";
	} else if(newCmd->err()) {
		return newCmd->getErrStr();
	}
	if(InstTable::VirgoBlacklist.count(newCmd->GetOpcode()))
		return "Valid syntax, but unsupported by virgo.";

	newCmd->SetLine(line);
	newCmd->SetAddr(mAddr);
	mAddr += newCmd->GetLength();
	mSize += newCmd->GetLength();
	mLines.push_back(newCmd);
	return "";
}

void Parser::Trim(std::string& str) {

	str.erase(str.find_last_not_of(" \f\n\r\t\v") + 1);
	str.erase(0, str.find_first_not_of(" \f\n\r\t\v"));
}

