/*-------------------------------------*\
|
|  File Name: Variant.hpp
|
|  Creation Date: 01-11-2012
|
|  Last Modified:
|
|  Created By: Robert Nelson
|
\*-------------------------------------*/

#pragma once

#include <vector>
#include "Command.hpp"
#include "InstTable.hpp"

class Variant {

	public:
		Command* CreateCommand(const std::string& prefix, const std::vector<std::string> & operands);

		Variant(unsigned int opcode, unsigned int num) : mOpcode(opcode) {
			if(num > 4)
				mNum = 4;
			else
				mNum = num;
			mArgs.resize(mNum, InstTable::INVALID);
		}

		void AddArgument(unsigned int num, InstTable::eOperands op) { if(num < mNum) mArgs[num] = op; }


	private:

		static std::string getByte(const std::string&);
		static std::string getWord(const std::string&);
		static std::string getDword(const std::string&);
		static std::string getRm8(const std::string&, bool);
		static std::string getRm16(const std::string&, bool);
		static std::string _getRm(const std::string&);
		static std::string getReg8(const std::string&);
		static std::string getReg16(const std::string&);
		static std::string getSegReg(const std::string&);
		static std::string getLabel(const std::string&);
		static std::string getDirectAddr(const std::string&);

		unsigned int mOpcode;
		unsigned int mNum;
		std::vector<InstTable::eOperands> mArgs;

};
		
