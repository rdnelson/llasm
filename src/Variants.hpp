/*-------------------------------------*\
|
|  File Name: Variants.hpp
|
|  Creation Date: 01-11-2012
|
|  Last Modified:
|
|  Created By: Robert Nelson
|
\*-------------------------------------*/

#pragma once

#include "IVariant.hpp"

class Variant0 {
	public:
		Command* CreateCommand(const std::string & prefix, const std::vector<std::string> & operands);
		Variant0(unsigned int opcode) : Variant(opcode) {}

};

class Variant1 {
	public:
		Command* CreateCommand(const std::string & prefix, const std::vector<std::string> & operands);
		Variant1(unsigned int opcode, eOperands op1) : Variant(opcode), mOp(op1) {}

	private:
		eOperands mOp;
};

class Variant2 {
	public:
		Command* CreateCommand(const std::string & prefix, const std::vector<std::string> & operands);
		Variant2(unsigned int opcode, eOperands op1, eOperands op2) 
			: Variant(opcode) {
			mOp[0] = op1;
			mOp[1] = op2;
		}

		eOperands mOp[2];
}

class Variant3 {
	public:
		Command* CreateCommand(const std::string & prefix, const std::vector<std::string> & operands);
		Variant3(unsigned int opcode, eOperands op1, eOperands op2, eOperands op3) 
			: Variant(opcode) {
			mOp[0] = op1;
			mOp[1] = op2;
			mOp[2] = op3;
		}

		eOperands mOp[3];
}

class Variant4 {
	public:
		Command* CreateCommand(const std::string & prefix, const std::vector<std::string> & operands);
		Variant4(unsigned int opcode, eOperands op1, eOperands op2, eOperands op3, eOperands op4) 
			: Variant(opcode) {
			mOp[0] = op1;
			mOp[1] = op2;
			mOp[2] = op3;
			mOp[3] = op4;
		}

		eOperands mOp[4];
}
