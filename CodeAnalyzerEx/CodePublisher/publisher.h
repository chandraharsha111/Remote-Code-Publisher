/////////////////////////////////////////////////////////////////////////////////////////
// Publisher.h: Publishes HTML files for given Repository files                        //
// ver 1.0                                                                             //
// Application: Dependency Based Code Publisher, Spring 2017 , Spring 2017             //
// Platform:    LenovoFlex4, Win 10, Visual Studio 2015                                //
// Author:      Chandra Harsha Jupalli, OOD Project3                                   //
//              cjupalli@syr.edu                                                       //
/////////////////////////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package uses a file System that iterates through all the files from path specified in command line arguments
* Publishes the HTML files present in the directory 
* It contains function StylingPublisherCSS  which would apply styles on published files 
* It contains function StylingPublisherJS which would handle scope functionality
*
*
* Public Interface
* --------------------
*  void publishCode(std::string path);                //Function  to create HTML File
*  void StylingPublisherCSS(std::string pat);         //Function  to apply styling on published files
*  void StylingPublisherJS(std::string t);            //Function  to handle scope handling functionality 
*  void FileIteration();                              //Function to iterate through files 
*  std::vector<std::string> currentDirectories,       //variables to access repository
*  std::vector<std::string> currentFiles;             //variables to access repository
*  std::vector<std::string> currentFiles;             //variables to access repository
*  std::vector<std::string> fileCollection;           //variables to access repository
*  std::vector<std::string> filecontainer;            //variables to access repository
*  
*
*
* Required Files:
* ---------------
*   -FileSystem.h,DependencyAnalysis.h

* Build Process:
* --------------
*   devenv CodeAnalyzerEx.sln /debug rebuild
*
* Maintenance History:
* --------------------
* Ver 1.0 : 4 April 2017
* - first release
*
*/


#pragma once
#include <iostream>
#include <vector>
#include "../FileSystem/FileSystem.h"
#include "../DependencyAnalysis/DependencyAnalysis.h"
#include "../Analyzer/TypeAnalysis.h"
class Publisher {
public:
	void publisher() {};
	void publishCode(std::string path);
	void StylingPublisherCSS(std::string pat);
	void StylingPublisherJS(std::string t);
	FileSystem::Directory directory;
	FileSystem::Path  path ;
	void FileIteration();
	std::vector<std::string> currentDirectories;
	std::vector<std::string> currentFiles;
	std::vector<std::string> fileCollection;
	std::vector<std::string> filecontainer;
	DependencyAnalysis  dep;
	TypeTable TT;
};
