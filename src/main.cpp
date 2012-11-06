/*-------------------------------------*\
|
|  File Name: main.cpp
|
|  Creation Date: 31-10-2012
|
|  Last Modified:
|
|  Created By: Robert Nelson
|
\*-------------------------------------*/

#include "InstTable.hpp"
#include "Parser.hpp"

#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {

	InstTable::InitializeTable();

	std::ifstream fin(argv[1]);
	char line[1024];
	Parser p;
	std::string s;
	bool err = false;
	int i = 0;
	while(fin) {
		i++;
		fin.getline(line, 1024);
		s = p.parseLine(line);
		if(s != "") {
			std::cout << "Error (Line " << i << "): " << s << std::endl;
			err = true;
		}
	}

	if(err) {
		return 1;
	}

	std::string op(argv[1]);
	op.append(".obj");

	std::ofstream fout(op.c_str());

	//TODO Instruction always starts at 0
	fout << "3 " << p.getCommands().size() << " 0 " << p.GetSize() << std::endl;

	for(unsigned int i = 0; i < p.getCommands().size(); i++) {
		fout << p.getCommands()[i]->GetVirgoStr();
		if(i != p.getCommands().size() - 1)
			fout << std::endl;
	}

	fout.close();


	return 0;
}
