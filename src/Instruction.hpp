/*-------------------------------------*\
|
|  File Name: Instruction.hpp
|
|  Creation Date: 01-11-2012
|
|  Last Modified:
|
|  Created By: Robert Nelson
|
\*-------------------------------------*/

#pragma once

#include "Variant.hpp"
#include "Command.hpp"

class Instruction {

	public:
		Instruction(const std::string& str) : mName(str) {}
		Command* CreateCommand(const std::string & prefix, const std::vector<std::string> & operands);

		inline void AddVariant(Variant* var) { if(var) mVariants.push_back(var); }

	private:
		std::vector<Variant*> mVariants;
		std::string mName;

};
