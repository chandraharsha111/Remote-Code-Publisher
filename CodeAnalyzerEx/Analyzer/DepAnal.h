#pragma once
///////////////////////////////////////////////////////////////////
// DepenAnal.h: Creates Dependency Information by Scanning AST   //
// ver 1.0                                                       //
// Application: Type Based Dependency Analysis, Spring 2017      //
// Platform:    LenovoFlex4, Win 10, Visual Studio 2015          //
// Author:      Chandra Harsha Jupalli, OOD Project2             //
//              cjupalli@syr.edu                                 //
//Reference:    Dr.Fawcett, Syracuse University                  //
///////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* Uses Abstract Syntax Tree to scan dependency information
* It helps executive with accessing medium level details of creating a Dependency Table and TypeTable
* It helps executive access strong Components information
*
* Required Files:
* ---------------
*   - Action and Rules.h,TypeAnalysis.h,DependencyAnalysis.h,FileSystem.h
*
*
* Public Interface
* --------------------
*  using CodeAnalysis                     //Namespace used to check coding standards of the project
*  doTypeAnal()                           //Implements type analysis by scanning the AST 
*  DependencyTable()                      //Traveres Directories in current path specified and invokes dependency table 
*  DFS()                                  //scans Abstract Syntax tree 
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

#include "../Parser/ActionsAndRules.h"
#include "TypeAnalysis.h"
#include <iostream>
#include "../DependencyAnalysis/DependencyAnalysis.h"
#include "../FileSystem/FileSystem.h"
#include "../CodePublisher/publisher.h"
#include <set>


using Keys = std::vector<std::string>;


#pragma warning (disable : 4101)  // disable warning re unused variable x, below

namespace CodeAnalysis
{
	class TypeAnal
	{
	public:
		using SPtr = std::shared_ptr<ASTNode*>;

		TypeAnal();
		void doTypeAnal();
		std::unordered_map<std::string, std::vector<std::string>> dependencyTable(int argc, char* argv[]);
		void callingPublisher();
	private:
		void DFS(ASTNode* pNode);
		AbstrSynTree& ASTref_;
		ScopeStack<ASTNode*> scopeStack_;
		Scanner::Toker& toker_;
		TypeTable TT;
		NoSqlDb <std::string> DBnew;
		std::set<std::string> myvector;
		DependencyAnalysis  dep;
		FileSystem::Directory directory;
		FileSystem::Path  path;

		Publisher p;

	};

	inline TypeAnal::TypeAnal() :
		ASTref_(Repository::getInstance()->AST()),
		scopeStack_(Repository::getInstance()->scopeStack()),
		toker_(*(Repository::getInstance()->Toker()))
	{
		//directory()
		std::function<void()> test = [] { int x; };  // This is here to test detection of lambdas.
	}                                              // It doesn't do anything useful for dep anal.

	inline bool doDisplay(ASTNode* pNode)
	{
		static std::string toDisplay[] = {
		  "function", "lambda", "class", "struct", "enum", "alias", "typedef"
		};
		for (std::string type : toDisplay)
		{
			if (pNode->type_ == type)
				return true;
		}
		return false;
	}
	inline void TypeAnal::DFS(ASTNode* pNode)
	{
		static std::string path = "";
		if (pNode->path_ != path){
			std::cout << "\n    -- " << pNode->path_ << "\\" << pNode->package_;
			path = pNode->path_;
		}
		if (doDisplay(pNode)) {
			std::cout << "\n  " << pNode->name_;
			std::cout << ", " << pNode->type_;
			//std::cout << " ," << pNode->parentType_;
		}

		if ((pNode->type_ == "struct") || (pNode->type_ == "class") || (pNode->type_ == "interface")) {
			std::vector<std::pair<std::string, std::string>> KeyPair;
			KeyPair.push_back(std::make_pair(pNode->type_, pNode->package_));
			TT.getTypeTable().insert(std::make_pair(pNode->name_, KeyPair));
		}

		for (auto pChild : pNode->children_)
			DFS(pChild);
	}

	inline void TypeAnal::doTypeAnal()
	{
		ASTNode* pRoot = ASTref_.root();
		DFS(pRoot);
	}

	//function to iterate through all files in repository by accepting command line arguments
	inline std::unordered_map<std::string, std::vector<std::string>> TypeAnal::dependencyTable(int argc, char* argv[]) {
		std::vector<std::string> filecontainer;
		std::vector<std::string> currentFiles;
		std::string dirpath_ = argv[1];
		std::string openInBrowser = argv[4];
		std::vector<std::string> currentDirectories = directory.getDirectories(dirpath_);
		for (size_t i = 0; i < currentDirectories.size(); i++) {
			std::cout << currentDirectories[i]<<"\n";
		}
		for (size_t i = 0; i < currentDirectories.size(); i++) {
			std::string appendpath = dirpath_ + "/" + currentDirectories[i];
			std::string temp = dirpath_ + "/" + currentDirectories[i] + "/";
			p.StylingPublisherCSS(temp);
			p.StylingPublisherJS(temp);
			std::vector<std::string> temporaryFiles = directory.getFiles(appendpath);
			for (size_t k = 0; k < temporaryFiles.size(); k++) {
				currentFiles.push_back(dirpath_ + "/" + currentDirectories[i] + "/" + temporaryFiles[k]);
			}
		}
		for (size_t temp = 0; temp < currentFiles.size(); temp++) {
			if ((path.getExt(currentFiles[temp]) == "h") || (path.getExt(currentFiles[temp]) == "cpp"))
				filecontainer.push_back(currentFiles[temp]);
		}
		//print the result 
		std::cout << "\n\n  List of files checked into Repository check\n\n";
		for (size_t t = 0; t < filecontainer.size(); t++) {
			std::cout << filecontainer[t] << "\n";
			std::string path = filecontainer[t];
			p.publishCode(path);
		}
		for (auto t : filecontainer) {
			std::string refTTString = t;
			dep.depResult = dep.DependencyAnalysistable(TT, refTTString);
		}
		std::string temp1 =  openInBrowser;
		std::cout <<"\n\n -------------------File to be opened in browser path -->"<< temp1 << std::endl<<"\n\n\n\n";
		std::wstring temp2= std::wstring(temp1.begin(), temp1.end());
		LPCWSTR helpfile = (LPCWSTR)temp2.c_str();
		ShellExecute(NULL, L"open", helpfile, NULL, NULL, SW_SHOWNORMAL);
		return dep.depResult;
	}

	//calls the fileIteration package in Publisher package
	inline void TypeAnal::callingPublisher() {
		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < 100; j++) {

			}
		}
		p.FileIteration();
	}
}