///////////////////////////////////////////////////////////////////
// TypeAnalysis.h:  It is used to create a Type Table            //
// ver 1.0                                                       //
// Application: Type Based Dependency Analysis, Spring 2017      //
// Platform:    LenovoFlex4, Win 10, Visual Studio 2015          //
// Author:      Chandra Harsha Jupalli, OOD Project2             //
//              cjupalli@syr.edu                                 //
///////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* It creates a type table based on files given from command line arguments
* It creates a type table based on classes, functions, structs and interfaces
* It provides a base so that parser can help in genererating the type table based on it 
*
* Public Interface
* --------------------
* using TypeName = std::string;           //used to form a pair for value part of unorderedmap 
  using FileType = std::string;           //used to form a pair for value part of unorderedmap 
* using MapTypeAnalysis                   //unordered map of string as key and a pair of strings as value
* MapTypeAnalysis& getTypeTable()         //used to return the instance of unordered map
* void showTypeTable();                   //function to display values of type table
*
*
* Required Files:
* ---------------
*   - It Just uses Standard Libraries

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
#include <string>
#include <unordered_map>


class TypeTable {
public:
	TypeTable() {};
	using TypeName = std::string;
	using FileType = std::string;
	 
	using MapTypeAnalysis = std::unordered_map<std::string, std::vector<std::pair<TypeName, FileType>>>;
	void showTypeTable();
	~TypeTable() { maptypeanal; }
	MapTypeAnalysis& getTypeTable() {
		return maptypeanal;
	}

private:
	MapTypeAnalysis  maptypeanal;

};
