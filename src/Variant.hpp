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

		static CmdOperand getByte(const std::string&);
		static CmdOperand getWord(const std::string&);
		static CmdOperand getDword(const std::string&);
		static CmdOperand getRm8(const std::string&, bool);
		static CmdOperand getRm16(const std::string&, bool);
		static CmdOperand _getRm(const std::string&, eCmdOpType);
		static CmdOperand getReg8(const std::string&);
		static CmdOperand getReg16(const std::string&);
		static CmdOperand getSegReg(const std::string&);
		static CmdOperand getLabel(const std::string&);
		static CmdOperand getDirectAddr(const std::string&);

		unsigned int mOpcode;
		unsigned int mNum;
		std::vector<InstTable::eOperands> mArgs;

};
		
