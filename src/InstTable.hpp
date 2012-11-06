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
#include <set>

class Instruction;

class InstTable {

	public:
		static std::map<std::string, Instruction*> InstMap;
		static std::map<std::string, unsigned int> PrefixMap;
		static std::set<unsigned char> VirgoBlacklist;

		static void InitializeTable();

	enum eOperands {
 		IMM8,
 		IMM16,
		RM8,
		RM16,
		R8,
		R16,
		SREG,
		AL,
		AH,
		BL,
		BH,
		CL,
		CH,
		DL,
		DH,
		AX,
		BX,
		CX,
		DX,
		SP,
		BP,
		SI,
		DI,
		PTR16,
		REL8,
		REL16,
		FIXED1,
		FIXED3,
		DS,
		ES,
		SS,
		CS,
		MOFF8,
		MOFF16,
		NEAR,
		FAR,
		INVALID
	};	
};
