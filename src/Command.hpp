/*-------------------------------------*\
|
|  File Name: Command.hpp
|
|  Creation Date: 01-11-2012
|
|  Last Modified:
|
|  Created By: Robert Nelson
|
\*-------------------------------------*/

#pragma once

#include <string>
#include <vector>

enum eCmdOpType {
	Imm8,
	Imm16,
	Imm32,
	Reg8,
	Reg16,
	Rm8,
	Rm16,
	Op_Error
};

enum eCmdStat {
	Error,
	Label,
	Valid
};

struct CmdOperand {
	eCmdStat	valid;
	std::string	data;
	eCmdOpType	type;
	std::string	label;
};

class Command {
	public:
		static Command* MakeCommand(std::string inst, std::string prefix, std::vector<std::string> operands, std::string label);
		Command(const std::string & prefix, const unsigned int opcode) 
			: mPrefix(prefix), mMod('\0'), bModrm(false), mOpcode(opcode), mAddr(0) {}

		unsigned int GetLength() const { return mInst.size();}
		void SetAddr(unsigned int addr) { mAddr = addr; }
		unsigned int GetAddr() const { return mAddr; }
		std::string GetVirgoStr();
		std::string GetBinaryStr() {return "";}

		unsigned char GetOpcode() const;

		inline const std::string & getErrStr() const { return mErr; }
		inline const bool err() const { return mErr.size() != 0; }
		inline void SetErr(const std::string & str) { mErr.assign(str); }

		void AppendImm(const std::string & str);
		void AppendReg(const std::string & str);
		void AppendRm(const std::string & str);

		void AppendOperand(const CmdOperand & op);

		void SetLine(const std::string & str) { mLine.assign(str.substr(0, str.size()-1)); }

		//Operators for sorting
		inline bool operator <(const Command& cmd) const
			{ return GetLength() < cmd.GetLength(); }

		inline bool operator <=(const Command & cmd) const
			{ return !(*this > cmd); }

		inline bool operator >(const Command & cmd) const
			{ return (cmd < *this); }

		inline bool operator >=(const Command & cmd) const
			{ return !(*this < cmd); }

		inline bool operator ==(const Command & cmd) const
			{ return GetLength() == cmd.GetLength(); }

		inline bool operator !=(const Command & cmd) const
			{ return !(*this == cmd); }

		inline Command& operator=(const Command& cmd){
			mPrefix.assign(cmd.mPrefix);
			mInst.assign(cmd.mInst);
			mErr.assign(cmd.mErr);
			mMod = cmd.mMod;
			bModrm = cmd.bModrm;
			mImm.assign(cmd.mImm);
			mModTail.assign(cmd.mModTail);
			mOpcode = cmd.mOpcode;
			mAddr = cmd.mAddr;
			mLine.assign(cmd.mLine);
			return *this;
		}



	protected:
		Command();

	private:

		void UpdateInst();

		std::string mPrefix;
/*		static bool isHexStr(std::string);
		static bool isDecStr(std::string);
		static bool isRegStr(std::string);
		static bool isAddrStr(std::string);

		static std::string hexRep(std::string);
		static std::string decRep(std::string);
		static std::string regRep(std::string);
		static std::string modRep(std::string);

		static std::string instMapStr(unsigned int);
		static std::string bytecodeStr(std::string);*/

		std::string mInst;
		std::string mErr;

		unsigned char mMod;
		bool bModrm;
		std::string mImm;
		std::string mModTail;
		unsigned int mOpcode;
		unsigned int mAddr;
		std::string mLine;
};
