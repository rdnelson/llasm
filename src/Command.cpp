/*-------------------------------------*\
|
|  File Name: Command.cpp
|
|  Creation Date: 01-11-2012
|
|  Last Modified:
|
|  Created By: Robert Nelson
|
\*-------------------------------------*/

#include "Command.hpp"
#include "InstTable.hpp"
#include "Instruction.hpp"
#include <sstream>
#include <iomanip>

Command* Command::MakeCommand(
		std::string inst, std::string prefix, std::vector<std::string>operands, std::string label) {
	if(InstTable::InstMap.count(inst)) {
		return InstTable::InstMap[inst]->CreateCommand(prefix, operands);
	}
	return 0;
}

void Command::AppendImm(const std::string & str) {
	mImm = str;

	UpdateInst();
}

unsigned char Command::GetOpcode() const {
	if((mOpcode & 0xFF00) == 0x0F)
		return 0x0F;
	else
		return mOpcode & 0xFF;
}

void Command::UpdateInst() {
	mInst = "";
	if((mOpcode & 0xFF00) == 0x0F)
		mInst.append(1, 0x0F);
	mInst.append(1, (char)mOpcode & 0xFF);

	//insert subcode
	if((mOpcode & 0xFF000000) < 0x07000000) {
		bModrm = true;
		mMod = (mMod & 0xC7) | ((mOpcode & 0x07000000) >> 21);
	}

	if(bModrm) {
		mInst.append(1, mMod);
		mInst.append(mModTail);
	}
	for(unsigned int i = 0; i < mImm.size(); i++)
		mInst.append(1, mImm[mImm.size() - i - 1]);
}

void Command::AppendRm(const std::string & str) {
	bModrm = true;
	mMod = (mMod & 0x38) | (str[0] & 0xC7);
	mModTail = str.substr(1);
	UpdateInst();
}

void Command::AppendReg(const std::string & str) {
	mMod = (mMod & 0xC7) | (str[0] & 0x38);
	bModrm = true;
	UpdateInst();
}

std::string Command::GetVirgoStr() {

	UpdateInst();
	std::stringstream ss;

	ss << std::uppercase;

	//address
	ss << (char)31;
	ss << std::hex << std::setfill('0') << std::setw(4);
	ss << mAddr;
	ss << std::setw(1);
	ss << (char)31;

	//size
	ss << (char)31;
	ss << std::dec << std::setfill('0') << std::setw(1);
	ss << mInst.size();
	ss << std::setw(1) << std::hex;
	ss << (char)31;

	//instruction
	ss << (char)31;
	for(unsigned int i = 0; i < mInst.size(); i++) {
		ss << std::hex << std::setfill('0') << std::setw(2);
		ss << ((unsigned int)mInst[i] & 0xFF);
	}
	ss << std::setw(1);
	ss << (char)31;

	//label
	ss << (char)31;
	ss << (char)31;

	ss << std::nouppercase;

	//source code
	ss << (char)31;
	ss << mLine;
	ss << (char)31;

	ss << (char)31;
	ss << "20";
	ss << (char)31;

	return ss.str();
}
