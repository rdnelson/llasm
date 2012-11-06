/*-------------------------------------*\
|
|  File Name: Instruction.cpp
|
|  Creation Date: 01-11-2012
|
|  Last Modified:
|
|  Created By: Robert Nelson
|
\*-------------------------------------*/

#include "Instruction.hpp"
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

bool cmpCmd(const Command* cmd1, const Command* cmd2) {
	return *cmd1 < *cmd2;
}

Command* Instruction::CreateCommand(const std::string & prefix, const std::vector<std::string> & operands) {

	std::vector<Command*> newCmds;
	Command* tmp;

	std::ofstream fout;
	fout.open("allvalid.log", std::fstream::app);
	fout << mName << std::endl;
	for(unsigned int i = 0; i < mVariants.size(); i++) {
		if((tmp = mVariants[i]->CreateCommand(prefix, operands))) {
			fout << tmp->GetVirgoStr() << std::endl;
			newCmds.push_back(tmp);
		}
	}

	if(newCmds.size() > 1) {
		std::sort(newCmds.begin(), newCmds.end(), cmpCmd);
		for(unsigned int i = 1; i < newCmds.size(); i++) {
			delete newCmds[i];
		}
	}

	fout.close();

	if(newCmds.size() == 0)
		return 0;

	return newCmds[0];
}
