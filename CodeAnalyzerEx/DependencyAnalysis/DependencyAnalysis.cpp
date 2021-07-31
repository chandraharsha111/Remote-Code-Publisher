///////////////////////////////////////////////////////////////////
// DependencyAnalysis.cpp: creates an Dependendency table        //
// ver 1.0                                                       //
// Application: Type Based Dependency Analysis, Spring 2017      //
// Platform:    LenovoFlex4, Win 10, Visual Studio 2015          //
// Author:      Chandra Harsha Jupalli, OOD Project2             //
//              cjupalli@syr.edu                                 //
///////////////////////////////////////////////////////////////////


#include "DependencyAnalysis.h"
#include <algorithm>
#include <iomanip>
#include "../HelpSession/NoSqlDb/NoSqlDb.h"
#include "../HelpSession/DbToXml/persist.cpp"
std::unordered_map<std::string, std::vector<std::string>> DependencyAnalysis::DependencyAnalysistable(TypeTable& tt,std::string& s) {
	
	std::vector<std::string> temp;
	std::string fileSpec = s;
	std::ifstream in(fileSpec);
	if (!in.good()) {
		std::cout << "\n  can't open " << fileSpec << "\n\n";
	}

	Toker toker;
	toker.returnComments();
	toker.attach(&in);
	std::vector<std::pair<std::string, std::string>> tempo;
	do {
		std::string tok = toker.getTok();
		for (auto it = tt.getTypeTable().begin(); it != tt.getTypeTable().end(); ++it) {
			if (tok == it->first) {
				tempo = it->second;
				temp.push_back(tempo.begin()->second);
			}} 
	} while (in.good());

	//code to ensure that same file is printed only onces
	std::vector<std::string>::iterator temp2;
	temp2 = (std::unique(temp.begin(), temp.end()));
	temp.resize(distance(temp.begin(), temp2));

	depResult.insert(std::make_pair(fileSpec, temp));
	addElement.name = fileSpec;

	for (auto itr = temp.begin(); itr != temp.end(); ++itr) {
		addElement.children.getValue().push_back(*itr);
	}

	dbInst.save(addElement.name, addElement);
	/*for (auto iteration = depTable.begin(); iteration != depTable.end(); iteration++) {
		std::cout <<std::setw(60) <<iteration->first << std::left << "\t Depends on following file --->>"<<"\n";
		for (size_t ite = 0; ite < iteration->second.size(); ite++) {
			std::cout << std::setw(60)<<iteration->second[ite]<<"\t Base file  \n\n\n";
		}}*/
	return depResult;
}

//void displayXml(NoSqlDb<std::string> dbInst) {
//	std::string s = toXml(dbInst);
//	std::cout << s;
//}



#ifdef DEPENDENCY_ANALYSIS

void DependencyAnalysis::DependencyAnalysistable(TypeTable& tt, std::string& s) {
	using DependencyTable = std::unordered_map<std::string, std::vector<std::string>>;
	std::vector<std::string> temp;
	DependencyTable depTable;
	std::string fileSpec = s;
	std::ifstream in(fileSpec);
	if (!in.good()) {
		std::cout << "\n  can't open " << fileSpec << "\n\n";
	}

	Toker toker;
	toker.returnComments();
	toker.attach(&in);

	std::vector<std::pair<std::string, std::string>> tempo;
	do {
		std::string tok = toker.getTok();
		for (auto it = tt.getTypeTable().begin(); it != tt.getTypeTable().end(); ++it) {
			if (tok == it->first) {
				tempo = it->second;
				temp.push_back(tempo.begin()->second);
			}
		}
	} while (in.good());

	//code to ensure that same file is printed only onces
	std::vector<std::string>::iterator temp2;
	temp2 = (std::unique(temp.begin(), temp.end()));
	temp.resize(distance(temp.begin(), temp2));

	depTable.insert(std::make_pair(fileSpec, temp));
	addElement.name = fileSpec;
	while (!addElement.children.getValue().empty()) {
		addElement.children.getValue().pop_back();
	}

	for (auto itr = temp.begin(); itr != temp.end(); ++itr) {
		addElement.children.getValue().push_back(*itr);
	}

	dbInst.save(addElement.name, addElement);
	for (auto iteration = depTable.begin(); iteration != depTable.end(); iteration++) {
		std::cout << std::setw(60) << iteration->first << std::left << "\t Depends on --->>" << "\n";
		for (size_t ite = 0; ite < iteration->second.size(); ite++) {
			std::cout << std::setw(60) << iteration->second[ite] << "\t Base file upon which above files depend \n\n\n";
		}
	}
}

int main() {
	DependencyAnalysis da;
	da.DependencyAnalysisTable(TypeTable& tt, std::string& s);
}

#endif