#pragma once
///////////////////////////////////////////////////////////////////////////////////
// Queries.h:  contains methods implementing queries supported by DataBase       //
// ver 1.0                                                                       //
// Application: Key Value DataBase, Spring 2017                                  //
// Platform:    LenovoFlex4, Win 10, Visual Studio 2015                          //
// Author:      Chandra Harsha Jupalli, OOD Project1                             //
//              cjupalli@syr.edu                                                 //
///////////////////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides the interface and implementation of various queries 
* supported by No SqlData Base.
*
* Required Files:
* ---------------
*   - NoSqlDb.h,NoSqlDb.cpp
*
*
* PublicInterface
* ----------------
* SpecifiedName(NoSqlDb<StrData> db,std::string s)                
* SpecifiedCategory(NoSqlDb<StrData> db,std::string s)             
* patternSimilarToKey(NoSqlDb<StrData> db,std::string s)          
* DataMakingSense(NoSqlDb<StrData> db, std::string s)
* KeysByEarlierQuery(NoSqlDb<StrData> db, Keys keys,std::string s)
* unionOfKeys(NoSqlDb<StrData> db, Keys keys,std::string s)
*
*
* Build Process:
* --------------
*   devenv CodeAnalyserEx.sln /debug rebuild
*
* Maintenance History:
* --------------------
* Ver 1.0 : 7 February 2017
* - first release
*
*/
#include  "../NoSqlDb/NoSqlDb.h"
using StrData = std::string;
using Key = NoSqlDb<StrData>::Key;
using Keys = NoSqlDb<StrData>::Keys;
using Data = std::string;
class Queries
{
public:
	Queries()  {}
//	Queries(NoSqlDb<StrData> db) : db_(db) {};
	void ValueOfKey(Key k,NoSqlDb<StrData> t);
	void ChildrenOfKey(Key k, NoSqlDb<StrData> t);
	std::vector<std::string>  SpecifiedName(NoSqlDb<Data> db,std::string s);
	std::vector<std::string> SpecifiedCategory(NoSqlDb<StrData> db,std::string s);
	std::vector<std::string> patternSimilarToKey(NoSqlDb<StrData> db, std::string s);
	std::vector<std::string> DataMakingSense(NoSqlDb<StrData> db, std::string s);
	std::vector<std::string> KeysByEarlierQuery(NoSqlDb<StrData> db, Keys keys,std::string s);
	std::vector<std::string> KeysByEarlierQuery2(NoSqlDb<StrData> db, Keys keys, std::string s);
	std::vector<std::string> unionOfKeys(NoSqlDb<StrData> db, Keys keys,std::string s);


	Keys MatchKeysWithInTimeInterval(NoSqlDb<StrData> db,Keys input, std::string time1, std::string time2);
	

private:
	NoSqlDb<StrData> db_;
};