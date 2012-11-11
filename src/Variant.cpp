/*-------------------------------------*\
|
|  File Name: Variant.cpp
|
|  Creation Date: 01-11-2012
|
|  Last Modified:
|
|  Created By: Robert Nelson
|
\*-------------------------------------*/

#include "Variant.hpp"
#include <algorithm>
#include <cmath>


Command* Variant::CreateCommand(const std::string & prefix, const std::vector<std::string> & operands) {

	Command* newCmd = new Command(prefix, mOpcode);

	if(operands.size() != mNum) {
		delete newCmd;
		return 0;
	}

	CmdOperand val;

	for(unsigned int i = 0; i < operands.size(); i++) {
		switch(mArgs[i]) {
			case InstTable::IMM8:
				val = getByte(operands[i]);
				if(val.valid == Error) {
					delete newCmd;
					return 0;
				}
				newCmd->AppendOperand(val);
				break;
			case InstTable::IMM16:
				val = getWord(operands[i]);
				if(val.valid == Error) {
					delete newCmd;
					return 0;
				}
				newCmd->AppendOperand(val);
				break;
			case InstTable::RM8:
				val = getRm8(operands[i], i == 0);
				if(val.valid == Error) {
					delete newCmd;
					return 0;
				}
				newCmd->AppendOperand(val);
				break;
			case InstTable::RM16:
				val = getRm16(operands[i], i == 0);
				if(val.valid == Error) {
					delete newCmd;
					return 0;
				}
				newCmd->AppendOperand(val);
				break;
			case InstTable::R8:
				val = getReg8(operands[i]);
				if(val.valid == Error) {
					delete newCmd;
					return 0;
				}
				newCmd->AppendOperand(val);
				break;
			case InstTable::R16:
				val = getReg16(operands[i]);
				if(val.valid == Error) {
					delete newCmd;
					return 0;
				}
				newCmd->AppendOperand(val);
				break;
			case InstTable::SREG:
				val = getSegReg(operands[i]);
				if(val.valid == Error) {
					delete newCmd;
					return 0;
				}
				newCmd->AppendOperand(val);
				break;
			//These ones are all hardcoded into the opcode
			case InstTable::AL:
				if(operands[i] != "AL") {
					delete newCmd;
					return 0;
				}
				break;
			case InstTable::AH:
				if(operands[i] != "AH") {
					delete newCmd;
					return 0;
				}
				break;
			case InstTable::BL:
				if(operands[i] != "BL") {
					delete newCmd;
					return 0;
				}
				break;
			case InstTable::BH:
				if(operands[i] != "BH") {
					delete newCmd;
					return 0;
				}
				break;
			case InstTable::DL:
				if(operands[i] != "DL") {
					delete newCmd;
					return 0;
				}
				break;
			case InstTable::DH:
				if(operands[i] != "DH") {
					delete newCmd;
					return 0;
				}
				break;
			case InstTable::CL:
				if(operands[i] != "CL") {
					delete newCmd;
					return 0;
				}
				break;
			case InstTable::CH:
				if(operands[i] != "CH") {
					delete newCmd;
					return 0;
				}
				break;
			case InstTable::AX:
				if(operands[i] != "AX") {
					delete newCmd;
					return 0;
				}
				break;
			case InstTable::BX:
				if(operands[i] != "BX") {
					delete newCmd;
					return 0;
				}
				break;
			case InstTable::CX:
				if(operands[i] != "CX") {
					delete newCmd;
					return 0;
				}
				break;
			case InstTable::DX:
				if(operands[i] != "DX") {
					delete newCmd;
					return 0;
				}
				break;
			case InstTable::SP:
				if(operands[i] != "SP") {
					delete newCmd;
					return 0;
				}
				break;
			case InstTable::BP:
				if(operands[i] != "BP") {
					delete newCmd;
					return 0;
				}
				break;
			case InstTable::SI:
				if(operands[i] != "SI") {
					delete newCmd;
					return 0;
				}
				break;
			case InstTable::DI:
				if(operands[i] != "DI") {
					delete newCmd;
					return 0;
				}
				break;

			//Not hardcoded anymore
			case InstTable::PTR16:
				val = getDword(operands[i]);
				if(val.valid == Error) {
					delete newCmd;
					return 0;
				}
				newCmd->AppendOperand(val);
				break;
			case InstTable::REL8:
				val = getByte(operands[i]);
				if(val.valid == Error) {
					delete newCmd;       
					return 0;
				}
				newCmd->AppendOperand(val);
				break;
			case InstTable::REL16:
				val = getWord(operands[i]);
				if(val.valid == Error) {
					delete newCmd;
					return 0;
				}
				newCmd->AppendOperand(val);
				break;
			case InstTable::FIXED1:
				if(operands[i] != "1") {
					delete newCmd;
					return 0;
				}
				break;
			case InstTable::FIXED3:
				if(operands[i] != "3") {
					delete newCmd;
					return 0;
				}
				break;
			case InstTable::DS:
				if(operands[i] != "DS") {
					delete newCmd;
					return 0;
				}
				break;
			case InstTable::ES:
				if(operands[i] != "ES") {
					delete newCmd;
					return 0;
				}
				break;
			case InstTable::SS:
				if(operands[i] != "SS") {
					delete newCmd;
					return 0;
				}
				break;
			case InstTable::CS:
				if(operands[i] != "CS") {
					delete newCmd;
					return 0;
				}
				break;
			case InstTable::MOFF8:
			case InstTable::MOFF16:
				val = getDirectAddr(operands[i]);
				if(val.valid == Error) {
					delete newCmd;
					return 0;
				}
				newCmd->AppendOperand(val);
				break;
			default:
				delete newCmd;
				return 0;
		}

	}


	return newCmd;
}

CmdOperand Variant::getByte(const std::string& str) {
	std::string t;

	CmdOperand retVal;
	retVal.type = Imm8;

	unsigned int start = 0;
	unsigned int end = 0;
	unsigned char val = 0;
	bool hex = false;

	if((str.find_first_of("1234567890") == 0) &&
			str.find_first_not_of("1234567890ABCDEF") == str.size() - 1 &&
			str.find("H") == str.size() - 1 &&
			str.size() >= 2 &&
			str.size() <= 3) {

		start = 0;
		end = str.size() - 1;
		hex = true;
	}

	//normal hex
	if(str.find("0X") == 0 &&
			str.find_first_not_of("1234567890ABCDEF", 2) == std::string::npos &&
			str.size() <= 4 &&
			str.size() >= 3) {
		start = 2;
		end = str.size();
		hex = true;
	}

	if(!hex && str.find_first_not_of("1234567890") != std::string::npos) {
		retVal.valid = Label;
		retVal.label = str;
		return retVal;
	} else if(!hex) { //decimal number

		for(unsigned int i = 0; i < str.size(); i++) {
			val += (int)pow(10, (str.size() - i - 1)) * (str[i] - '0');
			if(val > 0x100) {
				retVal.valid = Error;
				retVal.data = "Data exceeds size bounds";
			}
		}
		retVal.data.append(1, val);
		retVal.valid = Valid;
		return retVal;
	}


	if(start == 0 && end == 0) {
		retVal.data = "No immediate provided";
		retVal.valid = Error;
		return retVal;
	}

	for(unsigned int i = start; i < end; i++) {
		val <<= 4;
		if(str[i] >= '0' && str[i] <= '9') {
			val += str[i] - '0';
		} else if(str[2] >= 'A' && str[2] <= 'F') {
			val += str[i] - 'A' + 10;
		} else {
			retVal.data = "Invalid hex character: " + str[i];
			retVal.valid = Error;
			return retVal;
		}
	}
	retVal.data.append(1, val);
	retVal.valid = Valid;
	return retVal;
}

CmdOperand Variant::getWord(const std::string & str) {
	std::string t;
	CmdOperand retVal;
	retVal.type = Imm8;

	unsigned int start = 0;
	unsigned int end = 0;
	unsigned int val = 0;
	bool hex = false;

	if((str.find_first_of("1234567890") == 0) &&
			str.find_first_not_of("1234567890ABCDEF") == str.size() - 1 &&
			str.find("H") == str.size() - 1 &&
			str.size() >= 2 &&
			str.size() <= 3) {

		start = 0;
		end = str.size() - 1;
		hex = true;
	}

	//normal hex
	if(str.find("0X") == 0 &&
			str.find_first_not_of("1234567890ABCDEF", 2) == std::string::npos &&
			str.size() <= 4 &&
			str.size() >= 3) {
		start = 2;
		end = str.size();
		hex = true;
	}

	if(!hex && str.find_first_not_of("1234567890") != std::string::npos) {
		retVal.label = str;
		retVal.valid = Label;
		return retVal;
	} else if(!hex) { //decimal number

		for(unsigned int i = 0; i < str.size(); i++) {
			val += (int)pow(10, (str.size() - i - 1)) * (str[i] - '0');
			if(val > 0x10000) {
				retVal.data = "Data exceeds size bounds";
				retVal.valid = Error;
				return retVal;
			}
		}
		retVal.valid = Valid;
		retVal.data.append(1,(char)((val & 0xFF00) >> 8));
		retVal.data.append(1,(char)(val & 0xFF));
		return retVal;
	}


	if(end == 0 && start == 0) {
		retVal.valid = Error;
		retVal.data = "No operand provided";
		return retVal;
	}

	for(unsigned int i = start; i < end; i++) {
		val <<= 4;
		if(str[i] >= '0' && str[i] <= '9') {
			val += str[i] - '0';
		} else if(str[2] >= 'A' && str[2] <= 'F') {
			val += str[i] - 'A' + 10;
		} else {
			retVal.valid = Error;
			retVal.data = "Invalid hex character";
			return retVal;
		}
	}

	retVal.valid = Valid;
	retVal.data.append(1,(char)((val & 0xFF00) >> 8));
	retVal.data.append(1,(char)(val & 0xFF));
	return retVal;
}

CmdOperand Variant::getRm8(const std::string & str, bool isOp1) {

	std::string tmp = str;
	CmdOperand retVal;

	retVal.type = Rm8;

	if(tmp == "AL") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0xC0);
		return retVal;
	}
	if(tmp == "CL") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0xC1);
		return retVal;
	}
	if(tmp == "DL") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0xC2);
		return retVal;
	}
	if(tmp == "BL") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0xC3);
		return retVal;
	}
	if(tmp == "AH") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0xC4);
		return retVal;
	}
	if(tmp == "CH") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0xC5);
		return retVal;
	}
	if(tmp == "DH") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0xC6);
		return retVal;
	}
	if(tmp == "BH") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0xC7);
		return retVal;
	}

	if(str.find("WORD ") == 0) {
		retVal.valid = Error;
		retVal.data = "";
		return retVal;
	}

	if(str.find("BYTE ") == 0)
		tmp = str.substr(5);
	else {
		if(isOp1) {// size is mandatory for op1
			retVal.valid = Error;
			retVal.data = "Ambiguous destination size";
			return retVal;
		}
	}

	return _getRm(tmp, Rm8);
}

CmdOperand Variant::getRm16(const std::string & str, bool isOp1) {

	std::string tmp = str;
	CmdOperand retVal;
	retVal.type = Rm16;

	if(tmp == "AX") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0xC0);
		return retVal;
	}
	if(tmp == "CX") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0xC1);
		return retVal;
	}
	if(tmp == "DX") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0xC2);
		return retVal;
	}
	if(tmp == "BX") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0xC3);
		return retVal;
	}
	if(tmp == "SP") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0xC4);
		return retVal;
	}
	if(tmp == "BP") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0xC5);
		return retVal;
	}
	if(tmp == "SI") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0xC6);
		return retVal;
	}
	if(tmp == "DI") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0xC7);
		return retVal;
	}

	if(str.find("BYTE ") == 0) {
		retVal.valid = Error;
		return retVal;
	}

	if(str.find("WORD ") == 0)
		tmp = str.substr(5);
	else {
		if(isOp1) { // size is mandatory if it's the first operand
			retVal.valid = Error;
			retVal.data = "Ambiguous destination size";
			return retVal;
		}
	}
	return _getRm(tmp, Rm16);
}


CmdOperand Variant::_getRm(const std::string & str, eCmdOpType type) {

	std::string tmp;
	CmdOperand disp;
	CmdOperand retVal;
	retVal.type = type;
	retVal.valid = Error;

	unsigned int terms = 0;
	unsigned char modrm = 0;

	int start = 1;
	int end = str.find_first_of("+");
	if(end == std::string::npos) {
		end = str.size() - 1;
	}
	if(str[0] == '[' && str[str.size() - 1] == ']') {
		if((tmp = str.substr(start, end - start)) == "BX") {
			terms |= 0x80;
			terms++;
		} else if(tmp == "BP") {
			terms |= 0x40;
			terms++;
		} else if(tmp == "SI") {
			terms |= 0x20;
			terms++;
		} else if(tmp == "DI") {
			terms |= 0x10;
			terms++;
		} else if((disp = getWord(tmp)).data != "" && disp.valid == Valid) {
			terms++;
		} else if (disp.valid == Label) {
			retVal.valid = Label;
			retVal.label.assign(disp.label);
		} else { //label
			//check for starting letter, and valid characters
			if(tmp.find_first_not_of("QWERTYUIOPASDFGHJKLZXCVBNM1234567890_") == 
					std::string::npos &&
				tmp.find_first_of("QWERTYUIOPASDFGHJKLZXCVBNM") == 0 &&
				retVal.label.size() == 0) {

				retVal.label = tmp;
				retVal.valid = Label;
			} else {
				retVal.data = "Invalid symbol";
				return retVal;
			}
		}

		start = end + 1;
		end=str.find_first_of("+", start);
		if(end == std::string::npos)
			end = str.size() - 2;
	} else {
		retVal.data = "Invalid effective address";
		return retVal;
	}

	if(terms == 0x41) {//BP only exception
		disp.valid = Valid;
		disp.data.append(1, '\0');
	}

	if((disp.data.size() == 1 && disp.valid == Valid) || disp.valid == Label)
		modrm |= 0x40;
	
	if(terms & 0xF0) { //there are registers
		if(terms & 0x80) { //bx
			if(terms & 0x20) { //si
				modrm |= 0x00;
			} else if(terms & 0x10) { //di
				modrm |= 0x01;
			} else {
				modrm |= 0x07;
			}
		} else if(terms & 0x40) { //bp
			if(terms & 0x20) { //si
				modrm |= 2;
			} else if(terms & 0x10) { //di
				modrm |= 3;
			} else {
				modrm |= 6;
			}
		} else if(terms & 0x20) { //si
			modrm |= 4;
		} else if(terms & 0x10) { //di
			modrm |= 5;
		}
		if((disp.data.size() == 2 && disp.valid == Valid) || disp.valid == Label) {
			modrm |= 0x80;
		}
	} else { //disp only case
		if(disp.data.size() == 1 && disp.valid == Valid) {
			disp.data = '\0' + disp.data;
		}
		modrm = 0x06;
	}

	if(retVal.valid != Label)
		retVal.valid = Valid;

	retVal.data.append(1, modrm);
	if(disp.data.size() != 0 && disp.valid == Valid)
		retVal.data.append(disp.data);

	return retVal;
}

CmdOperand Variant::getReg8(const std::string& str) {
	std::string tmp;
	CmdOperand retVal;
	retVal.type = Reg8;
	retVal.valid = Error;

	if(str == "AL" ){
		retVal.valid = Valid;
		retVal.data.append(1, (char)0x00);
	}
	if(str == "AH") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0x10);
	}
	if(str == "BL") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0x18);
	}
	if(str == "BH") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0x38);
	}
	if(str == "CL") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0x08);
	}
	if(str == "CH") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0x28);
	}
	if(str == "DL") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0x10);
	}
	if(str == "DH") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0x30);
	}

	if(retVal.data.size() == 0) {
		retVal.data = "Invalid Register";
	}

	return retVal;
}

CmdOperand Variant::getReg16(const std::string& str) {
	std::string tmp;
	CmdOperand retVal;
	retVal.valid = Error;
	retVal.type = Reg16;

	if(str == "AX") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0x00);
	}
	if(str == "SP") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0x10);
	}
	if(str == "CX") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0x18);
	}
	if(str == "BP") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0x38);
	}
	if(str == "DX") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0x08);
	}
	if(str == "SI") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0x28);
	}
	if(str == "BX") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0x10);
	}
	if(str == "DI") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0x30);
	}

	if(retVal.data.size() == 0) {
		retVal.data = "Invalid register";
	}

	return retVal;
}

CmdOperand Variant::getSegReg(const std::string& str) {
	std::string tmp;
	CmdOperand retVal;
	retVal.type = Reg16;
	retVal.valid = Error;

	if (str == "CS") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0x08);
	}
	if(str == "DS") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0x18);
	}
	if(str == "ES") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0x00);
	}
	if(str == "SS") {
		retVal.valid = Valid;
		retVal.data.append(1, (char)0x10);
	}

	if(retVal.data.size() == 0) {
		retVal.data = "Invalid segment register";
	}

	return retVal;
}

CmdOperand Variant::getDword(const std::string& str) {
	unsigned int div;
	CmdOperand retVal;
	retVal.type = Imm32;
	retVal.valid = Error;

	if(str.find("WORD") != 0 || (div = str.find(":")) == std::string::npos) {
		retVal.data = "Invalid dword format 'WORD 0xXXXX:0xXXXX";
		return retVal;
	}

	std::string tmp;
	unsigned int beg = str.find(" ") + 1;
	CmdOperand c = getWord(str.substr(beg, div - beg));
	if(c.valid == Error) {
		c.type = Imm32;
		return c;
	}
	tmp.assign(c.data);
	unsigned int size = tmp.size();
	c = getWord(str.substr(div + 1));
	if(c.valid == Error) {
		c.type = Imm32;
		return c;
	}
	tmp.append(c.data);

	if(tmp.size() == size) {
		retVal.data = "Malformed operand";
		return retVal;
	}
	retVal.valid = Valid;
	retVal.data = tmp;

	return retVal;
}

CmdOperand Variant::getDirectAddr(const std::string& str) {
	CmdOperand retVal;
	retVal.type = Imm16;
	retVal.valid = Error;

	if(str[0] != '[' || str[str.size() - 1] != ']') {
		retVal.data = "Invalid address";
		return retVal;
	}
	return getWord(str);
}
/*
bool Variant::isByte(const std::string& str) {

	return str.find("BYTE") == 0;
}

bool Variant::isWord(const std::string& str) { 
	if(str.find("WORD") == 0)
		return true;

	if(str.find("0X") == 0)
		return (str.size() == 5 || str.size() == 6);

	else if(str.find("H") == str.size() - 1)
		return str.size() == 4 || str.size() == 5;

	return false;
}
		
bool Variant::isDword(const std::string& str) {
	if(str.find("WORD") != 0)
		return false;
	
	if(str.find(":") == std::string::npos)
		return false;

	return isWord(str.substr(0, str.find(":"))) && isWord(str.substr(str.find(":") + 1));
}

bool Variant::isRm(const std::string& str) {
	if(isReg8(str) == true)
		return true;

	if(str[0] != '[' || str[str.size() - 1] != ']')
		return false;

	std::string tmp = str;
	tmp.erase(std::remove(tmp.begin(), tmp.end(), ' '), tmp.end());
	tmp.erase(std::remove(tmp.begin(), tmp.end(), '\t'), tmp.end());

	return false;

}

bool Variant::isLabel(const std::string& str) {
	return (str.find_first_of("ZXCVBNMASDFGHJKLQWERTYUIOP") == 0 &&
		str.find_first_not_of("ZXCVBNMASDFGHJKLQWERTYUIOP1234567890") == std::string::npos);
}

bool Variant::isDirectAddr(const std::string& str) {
	if (str[0] != '[' || str[str.size() - 1] != ']')
		return false;

	std::string tmp = str.substr(1, str.size() - 2);
	tmp.erase(std::remove(tmp.begin(), tmp.end(), ' '), tmp.end());
	tmp.erase(std::remove(tmp.begin(), tmp.end(), '\t'), tmp.end());
	if(tmp.find("0X") == 0) {
		if(tmp.find_first_not_of("1234567890") != std::string::npos)
			return false;
		if(tmp.size() > 6)
			return false;
		return true;
	} else if(tmp.find("H") == tmp.size() - 1) {
		if(tmp.find_first_not_of("1234567890") != tmp.size() - 1)
			return false;
		if(tmp.size() > 5)
			return false;
		return true;
	}
	return false;
}
*/
