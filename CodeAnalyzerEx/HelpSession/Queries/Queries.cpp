///////////////////////////////////////////////////////////////////
// Queries.cpp:  Implemts various methods supporting Db Queries  //
// ver 1.0                                                       //
// Application: Key Value DataBase, Spring 2017                  //
// Platform:    LenovoFlex4, Win 10, Visual Studio 2015          //
// Author:      Chandra Harsha Jupalli, OOD Project1             //
//              cjupalli@syr.edu                                 //
///////////////////////////////////////////////////////////////////



#include "../StrHelper.h"
#include <iostream>
#include "Queries.h"
#include <ostream>
#include <regex>
#include "../NoSqlDb/NoSqlDb.h"
#include <set>
using namespace std;
using StrData = std::string;
using intData = int;
using Data = std::string;

//Query to implement requirement 7a of finding value of given key
void Queries::ValueOfKey(Key k, NoSqlDb<StrData> db) {
	std::cout << "\n---- Value of Specified Key Element1's name elem1-------\n";
		std::string temp = db.value(k).name;
		if ((temp != "\0"))
			std::cout << " Key's value is--> " << temp<<"\n";
		if (temp == "\0")
			std::cout << "No Value for given key";
}

//Query to implement requirement 7b of finding children of given key
void Queries::ChildrenOfKey(Key k, NoSqlDb<StrData> db)
{
	std::cout << "\n---- Children of Specified Key Element2's elem2 name-------\n";
	std::vector<std::string> temp = db.value(k).children;
	for (int i = 0; i < (int)temp.size(); i++) {
		std::cout <<"Children of key "<<k<<"is "<< temp[i] << " ";
		cout << "\n";
	}
	if (temp.size()== 0)
		cout << "No children present";
}

//Query to implement requirement 7c of finding all keys with specific pattern in name
vector<std::string> Queries::SpecifiedName(NoSqlDb<StrData> db,std::string s) {
	std::vector<std::string> result;
	Keys k2 = db.keys();
	std::regex r("[a-z1-9]*(" + s + ")[a-z1-9]*");
	for (Key k : k2) {
		Element<Data> res = db.value(k);
		std::string name = res.name;
		if (regex_match(name, r)) {
			result.push_back(res.name);
		}
	}
	if (result.size() == 0)
		cout << "No element with specified name";
	return result;
}

//Query to implement requirement 7d of finding all keys with specific pattern in category
vector<std::string> Queries::SpecifiedCategory(NoSqlDb<StrData> db, std::string s) {
	std::vector<std::string> result;
	Keys k2 = db.keys();
	std::regex r("[a-z1-9]*(" + s + ")[a-z1-9]*");
	for (Key k : k2) {
		Element<Data> res = db.value(k);
		std::string name = res.category;
		if (regex_match(name, r)) {
			result.push_back(res.name);
		}
	}
	if (result.size() == 0)
		cout << "No element with similar category patern";

	return result;
}

//Query to implement requirement 7e of finding all keys with specific pattern in key
vector<std::string> Queries::patternSimilarToKey(NoSqlDb<StrData> db, std::string s) {
	std::vector<std::string> result;
	Keys k2 = db.keys();
	std::regex r("[a-z1-9]*(" + s + ")[a-z1-9]*");
	for (Key k : k2) {
		Element<Data> res = db.value(k);
		std::string name = res.name;
		if (regex_match(name, r)) {
			result.push_back(res.name);
		}
	}
	if (result.size() == 0)
		cout << "No element with similar pattern";
	return result;
}

//Query to implement requirement 7f of finding all keys with specific data present in value of key as queried
vector<std::string> Queries::DataMakingSense(NoSqlDb<StrData> db, std::string s) {
	std::vector<std::string> result;
	Keys k2 = db.keys();
	std::regex r("[a-z1-9]*(" + s + ")[a-z1-9]*");
	for (Key k : k2) {
		Element<Data> res = db.value(k);
		std::string name = res.name;
		if (regex_match(name, r)) {
			result.push_back(res.name);
		}
	}
	if (result.size() == 0)
		cout << "No element with similar pattern";
	return result;
}

//Query to implement requirement 8 of taking input from previous queries
vector<std::string> Queries::KeysByEarlierQuery(NoSqlDb<StrData> db, Keys keys,std::string s) {
	std::vector<std::string> result;
	
	std::regex r("[a-z1-9]*(" + s + ")[a-z1-9]*");
	for (Key k : keys) {
		Element<Data> res = db.value(k);
		std::string name = res.name;
		if (regex_match(name, r)) {
			result.push_back(res.name);
		}
	}
	if (result.size() == 0)
		cout << "No element with similar pattern";
	return result;
}
//Query to implement requirement 8 of taking input from previous queries
vector<std::string> Queries::KeysByEarlierQuery2(NoSqlDb<StrData> db, Keys keys, std::string s) {
	std::vector<std::string> result;

	std::regex r("[a-z1-9]*(" + s + ")[a-z1-9]*");
	for (Key k : keys) {
		Element<Data> res = db.value(k);
		std::string name = res.name;
		if (regex_match(name, r)) {
			result.push_back(res.name);
		}
	}
	if (result.size() == 0)
		cout << "No element with similar pattern";
	return result;
}

//Query to implement requirement 9 of taking input as union of keys from previous queries
vector<std::string> Queries::unionOfKeys(NoSqlDb<StrData> db, Keys keys, std::string s) {
	std::vector<std::string> result;

	std::regex r("[a-z1-9]*(" + s + ")[a-z1-9]*");
	for (Key k : keys) {
		Element<Data> res = db.value(k);
		std::string name = res.name;
		if (regex_match(name, r)) {
			result.push_back(res.name);
		}
	}
	if (result.size() == 0)
		cout << "No element with similar pattern";
	return result;
}

#ifdef Queries
vector<std::string> Queries::unionOfKeys(NoSqlDb<StrData> db, Keys keys, std::string s) {
	std::vector<std::string> result;

	std::regex r("[a-z1-9]*(" + s + ")[a-z1-9]*");
	for (Key k : keys) {
		Element<Data> res = db.value(k);
		std::string name = res.name;
		if (regex_match(name, r)) {
			result.push_back(res.name);
		}
	}
	if (result.size() == 0)
		cout << "No element with similar pattern";
	return result;
}


int main() {
	try {
		std::vector<std::string> addKeysresult = q.unionOfKeys(db, AddKeys, "lem");
		cout << "\n--Requirement 9 of union of keys,adding 2keys resulting from requiremnt 8 demonstration---\n";
		for (int i = 0; i < (int)addKeysresult.size(); i++) {
			std::cout << addKeysresult[i] << "\n";
		}
	}
	catch (...) {
		cout << "An Exception has occured";
	}
}

#endif

