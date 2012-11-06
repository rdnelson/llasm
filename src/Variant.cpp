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

	std::string val;

	for(unsigned int i = 0; i < operands.size(); i++) {
		switch(mArgs[i]) {
			case InstTable::IMM8:
				if((val = getByte(operands[i])) == "") {
					delete newCmd;
					return 0;
				}
				newCmd->AppendImm(val);
				break;
			case InstTable::IMM16:
				if((val = getWord(operands[i])) == "") {
					delete newCmd;
					return 0;
				}
				newCmd->AppendImm(val);
				break;
			case InstTable::RM8:
				if((val = getRm8(operands[i], i == 0)) == "") {
					delete newCmd;
					return 0;
				}
				newCmd->AppendRm(val);
				break;
			case InstTable::RM16:
				if((val = getRm16(operands[i], i == 0)) == "") {
					delete newCmd;
					return 0;
				}
				newCmd->AppendRm(val);
				break;
			case InstTable::R8:
				if((val = getReg8(operands[i])) == "") {
					delete newCmd;
					return 0;
				}
				newCmd->AppendReg(val);
				break;
			case InstTable::R16:
				if((val = getReg16(operands[i])) == "") {
					delete newCmd;
					return 0;
				}
				newCmd->AppendReg(val);
				break;
			case InstTable::SREG:
				if((val = getSegReg(operands[i])) == "") {
					delete newCmd;
					return 0;
				}
				newCmd->AppendReg(val);
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
				if((val = getDword(operands[i])) == "") {
					delete newCmd;
					return 0;
				}
				newCmd->AppendImm(val);
				break;
			case InstTable::REL8:
				if((val = getByte(operands[i])) == "") {
					delete newCmd;       
					return 0;
				}
				newCmd->AppendImm(val);
				break;
			case InstTable::REL16:
				if((val = getWord(operands[i])) == "") {
					delete newCmd;
					return 0;
				}
				newCmd->AppendImm(val);
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
				if((val = getDirectAddr(operands[i])) == "") {
					delete newCmd;
					return 0;
				}
				newCmd->AppendImm(val);
				break;
			default:
				delete newCmd;
				return 0;
		}

	}


	return newCmd;
}

std::string Variant::getByte(const std::string& str) {
	std::string t;

	unsigned int start = 0;
	unsigned int end = 0;
	unsigned char val = 0;
	bool hex = false;

	if(str.find("H") == str.size() - 1 && str.size() >= 2 && str.size() <= 3) {
		start = 0;
		end = str.size() - 1;
		hex = true;
	}

	//normal hex
	if(str.find("0X") == 0 && str.size() <= 4 && str.size() >= 3) {
		start = 2;
		end = str.size();
		hex = true;
	}

	if(!hex && str.find_first_not_of("1234567890") != std::string::npos) {
		return "";
	} else if(!hex) { //decimal number

		for(unsigned int i = 0; i < str.size(); i++) {
			val += (int)pow(10, (str.size() - i - 1)) * (str[i] - '0');
			if(val > 0x100)
				return "";
		}
		t.append(1,val);
		return t;
	}


	if(start == 0 && end == 0) {
		return "";
	}

	for(unsigned int i = start; i < end; i++) {
		val <<= 4;
		if(str[i] >= '0' && str[i] <= '9') {
			val += str[i] - '0';
		} else if(str[2] >= 'A' && str[2] <= 'F') {
			val += str[i] - 'A' + 10;
		} else {
			return "";
		}
	}
	t.append(1,val);
	return t;
}

std::string Variant::getWord(const std::string & str) {
	std::string t;

	unsigned int start = 0;
	unsigned int end = 0;
	unsigned int val = 0;
	bool hex = false;

	if(str.find("H") == str.size() - 1 && str.size() >= 2 && str.size() <= 3) {
		start = 0;
		end = str.size() - 1;
		hex = true;
	} else if(str.find("0X") == 0 && str.size() <= 4 && str.size() >= 3) {
		start = 2;
		end = str.size();
		hex = true;
	} 

	if(!hex && str.find_first_not_of("1234567890") != std::string::npos) {
		return "";
	} else if(!hex) { //decimal number

		for(unsigned int i = 0; i < str.size(); i++) {
			val += (int)pow(10, (str.size() - i - 1)) * (str[i] - '0');
			if(val > 0x10000)
				return "";
		}
		t.append(1,(char)((val & 0xFF00) >> 8));
		t.append(1,(char)(val & 0xFF));
		return t;
	}


	if(end == 0 && start == 0)
		return "";

	for(unsigned int i = start; i < end; i++) {
		val <<= 4;
		if(str[i] >= '0' && str[i] <= '9') {
			val += str[i] - '0';
		} else if(str[2] >= 'A' && str[2] <= 'F') {
			val += str[i] - 'A' + 10;
		} else {
			return "";
		}
	}

	t.append(1,(char)((val & 0xFF00) >> 8));
	t.append(1,(char)(val & 0xFF));
	return t;
}

std::string Variant::getRm8(const std::string & str, bool isOp1) {

	std::string tmp = str;

	if(tmp == "AL") {
		tmp.clear();
		tmp.append(1, (char)0xC0);
		return tmp;
	}
	if(tmp == "CL") {
		tmp.clear();
		tmp.append(1, (char)0xC1);
		return tmp;
	}
	if(tmp == "DL") {
		tmp.clear();
		tmp.append(1, (char)0xC2);
		return tmp;
	}
	if(tmp == "BL") {
		tmp.clear();
		tmp.append(1, (char)0xC3);
		return tmp;
	}
	if(tmp == "AH") {
		tmp.clear();
		tmp.append(1, (char)0xC4);
		return tmp;
	}
	if(tmp == "CH") {
		tmp.clear();
		tmp.append(1, (char)0xC5);
		return tmp;
	}
	if(tmp == "DH") {
		tmp.clear();
		tmp.append(1, (char)0xC6);
		return tmp;
	}
	if(tmp == "BH") {
		tmp.clear();
		tmp.append(1, (char)0xC7);
		return tmp;
	}

	if(str.find("WORD ") == 0)
		return "";

	if(str.find("BYTE ") == 0)
		tmp = str.substr(5);
	else
		if(isOp1) // size is mandatory for op1
			return "";

	return _getRm(tmp);
}

std::string Variant::getRm16(const std::string & str, bool isOp1) {

	std::string tmp = str;

	if(tmp == "AX") {
		tmp.clear();
		tmp.append(1, (char)0xC0);
		return tmp;
	}
	if(tmp == "CX") {
		tmp.clear();
		tmp.append(1, (char)0xC1);
		return tmp;
	}
	if(tmp == "DX") {
		tmp.clear();
		tmp.append(1, (char)0xC2);
		return tmp;
	}
	if(tmp == "BX") {
		tmp.clear();
		tmp.append(1, (char)0xC3);
		return tmp;
	}
	if(tmp == "SP") {
		tmp.clear();
		tmp.append(1, (char)0xC4);
		return tmp;
	}
	if(tmp == "BP") {
		tmp.clear();
		tmp.append(1, (char)0xC5);
		return tmp;
	}
	if(tmp == "SI") {
		tmp.clear();
		tmp.append(1, (char)0xC6);
		return tmp;
	}
	if(tmp == "DI") {
		tmp.clear();
		tmp.append(1, (char)0xC7);
		return tmp;
	}

	if(str.find("BYTE ") == 0)
		return "";

	if(str.find("WORD ") == 0)
		tmp = str.substr(5);
	else
		if(isOp1) // size is mandatory if it's the first operand
			return "";

	return _getRm(tmp);
}


std::string Variant::_getRm(const std::string & str) {

	std::string tmp;
	std::string disp;
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
		} else if((disp = getWord(tmp)) != "") {
			terms++;
		} else {
			return "";
		}

		start = end + 1;
		end=str.find_first_of("+", start);
		if(end == std::string::npos)
			end = str.size() - 2;
	} else {
		return "";
	}

	if(terms == 0x41) {//BP only exception
		disp.append(1, '\0');
	}

	if(disp.size() == 1)
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
		if(disp.size() == 2) {
			modrm |= 0x80;
		}
	} else { //disp only case
		if(disp.size() == 1) {
			disp = '\0' + disp;
		}
		modrm = 0x06;
	}

	tmp.clear();
	tmp.append(1, modrm);
	if(disp.size() != 0)
		tmp.append(disp);

	return tmp;
}

std::string Variant::getReg8(const std::string& str) {
	std::string tmp;
	if(str == "AL" ){
		tmp.append(1, (char)0x00);
	}
	if(str == "AH") {
		tmp.append(1, (char)0x10);
	}
	if(str == "BL") {
		tmp.append(1, (char)0x18);
	}
	if(str == "BH") {
		tmp.append(1, (char)0x38);
	}
	if(str == "CL") {
		tmp.append(1, (char)0x08);
	}
	if(str == "CH") {
		tmp.append(1, (char)0x28);
	}
	if(str == "DL") {
		tmp.append(1, (char)0x10);
	}
	if(str == "DH") {
		tmp.append(1, (char)0x30);
	}
	return tmp;
}

std::string Variant::getReg16(const std::string& str) {
	std::string tmp;
	if(str == "AX") {
		tmp.append(1, (char)0x00);
	}
	if(str == "SP") {
		tmp.append(1, (char)0x10);
	}
	if(str == "CX") {
		tmp.append(1, (char)0x18);
	}
	if(str == "BP") {
		tmp.append(1, (char)0x38);
	}
	if(str == "DX") {
		tmp.append(1, (char)0x08);
	}
	if(str == "SI") {
		tmp.append(1, (char)0x28);
	}
	if(str == "BX") {
		tmp.append(1, (char)0x10);
	}
	if(str == "DI") {
		tmp.append(1, (char)0x30);
	}
	return tmp;
}

std::string Variant::getSegReg(const std::string& str) {
	std::string tmp;
	if (str == "CS") {
		tmp.append(1, (char)0x08);
	}
	if(str == "DS") {
		tmp.append(1, (char)0x18);
	}
	if(str == "ES") {
		tmp.append(1, (char)0x00);
	}
	if(str == "SS") {
		tmp.append(1, (char)0x10);
	}
	return tmp;
}

std::string Variant::getDword(const std::string& str) {
	unsigned int div;
	if(str.find("WORD") != 0 || (div = str.find(":")) == std::string::npos)
		return "";

	std::string tmp;
	unsigned int beg = str.find(" ") + 1;
	tmp.append(getWord(str.substr(beg, div - beg)));
	if(tmp == "")
		return tmp;
	unsigned int size = tmp.size();
	tmp.append(getWord(str.substr(div + 1)));
	if(tmp.size() == size)
		return "";
	return tmp;
}

std::string Variant::getDirectAddr(const std::string& str) {
	if(str[0] != '[' || str[str.size() - 1] != ']') {
		return "";
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
