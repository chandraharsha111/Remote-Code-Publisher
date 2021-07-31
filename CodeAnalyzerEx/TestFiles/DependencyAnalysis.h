/////////////////////////////////////////////////////////////////////////////////////////
// DependencyAnalysis.h:  Provides necessary declarations to create a dependency table //
// ver 1.0                                                                             //
// Application: Type Based Dependency Analysis, Spring 2017                            //
// Platform:    LenovoFlex4, Win 10, Visual Studio 2015                                //
// Author:      Chandra Harsha Jupalli, OOD Project2                                   //
//              cjupalli@syr.edu                                                       //
/////////////////////////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package use a tokenizer and scan's through all the files from path specified in command line arguments
* Finds if there is any dependency by running type table on files from path
* Creates a Dependency table which could be save to database and stored in an Xml File
*
*
* Public Interface
* --------------------
*  void DependencyAnalysistable(TypeTable& tt,std::string& s);                      //Function  to create Dependency Table
*  NoSqlDb<std::string>& getDataBase()                                              //Function to return a database instance
*  NoSqlDb<std::string> dbInst;                                                     //Using a DataBase Instance  in NoSqlDB
*  Element<std::string> addElement;                                                 //Using an Element Class Instance in NoSqlDb
*
*
* Required Files:
* ---------------
*   -Utilities.h, Tokenizer.h, NoSqlDb.h,TypeAnalysis.h

* Build Process:
* --------------
*   devenv CodeAnalyzerEx.sln /debug rebuild
*
* Maintenance History:
* --------------------
* Ver 1.0 : 11 March 2017
* - first release
*
*/



#pragma once
#include <iostream>
#include<unordered_map>
#include <string>
#include <fstream>
#include <vector>
#include "DependencyAnalysis.h"
#include "..\Utilities\Utilities.h"
#include "..\Tokenizer\Tokenizer.h"
#include "..\Analyzer\TypeAnalysis.h"
#include "../HelpSession/NoSqlDb/NoSqlDb.h"

using namespace Scanner;
class DependencyAnalysis{
public:
	DependencyAnalysis() {
	}
	void DependencyAnalysistable(TypeTable& tt,std::string& s);
	NoSqlDb<std::string> dbInst;
	Element<std::string> addElement;
	//void displayXml(NoSqlDb<std::string> db);
	NoSqlDb<std::string>& getDataBase() {
		return dbInst;
	};
	
	~DependencyAnalysis(){}

};
