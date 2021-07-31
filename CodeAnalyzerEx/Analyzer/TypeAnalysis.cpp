///////////////////////////////////////////////////////////////////
// TypeAnalysis.cpp:  It is used to create a type table            //
// ver 1.0                                                       //
// Application: Type Based Dependency Analysis, Spring 2017      //
// Platform:    LenovoFlex4, Win 10, Visual Studio 2015          //
// Author:      Chandra Harsha Jupalli, OOD Project2             //
//              cjupalli@syr.edu                                 //
///////////////////////////////////////////////////////////////////

#include "TypeAnalysis.h"
class TypeTable TT;

void TypeTable::showTypeTable() {
	for (auto iteration = TT.getTypeTable().begin(); iteration != TT.getTypeTable().end(); iteration++) {
		std::cout << iteration->first << "\t\t\t\t";
		std::vector<std::pair<std::string, std::string>> KeyPair = iteration->second;
		for (auto temp : KeyPair) {
			std::cout << temp.first << " \t\t\t\t" << temp.second << "\n";
		}
	}

}

#ifdef TYPE_Analysis

void TypeTable::showTypeTable() 
{
	for (auto iteration = TT.getTypeTable().begin(); iteration != TT.getTypeTable().end(); iteration++) {
		std::cout << iteration->first << "\t\t\t\t";
		std::vector<std::pair<std::string, std::string>> KeyPair = iteration->second;
		for (auto temp : KeyPair) {
			std::cout << temp.first << " \t\t\t\t" << temp.second << "\n";
		}
	}
}

int main() {
	TypeTable tt;
	tt.showTypeTable();
	tt.getTypeTable();
}

#endif
