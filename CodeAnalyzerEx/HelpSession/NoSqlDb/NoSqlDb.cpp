////////////////////////////////////////////////////////////////////////////////
// NoSqlDb.cpp: key/value pair in-memory database                             //
// Application: Key Value DataBase, Spring 2017                               //
// Platform:    LenovoFlex4, Win 10, Visual Studio 2015                       //
// Author:      Chandra Harsha Jupalli, CSE687 - OOD,Spring 2017              //
//              cjupalli@syr.edu                                              //
////////////////////////////////////////////////////////////////////////////////


#include "NoSqlDb.h"
#include <iostream>
#include "../DbToXml/persist.cpp"
#include "../Queries/Queries.h"     
#include <fstream>
#include <algorithm>

using StrData = std::string;
using intData = int;
using Key = NoSqlDb<StrData>::Key;
using Keys = NoSqlDb<StrData>::Keys;
using namespace std;


//cpp operator overloaded function to solve function being declared twice
std::ostream& operator<<(std::ostream& out, Property<std::string>& p)
{
	std::string temp = p;
	try {
		out << (temp).c_str();
	}
	catch (std::exception& ex)
	{
		std::cout << "\n  exception:\n  " << ex.what() << "\n";
	}
	return out;
}

//cpp operator overloaded function to solve function being declared twice
std::ostream& operator<<(std::ostream& out, Property<const std::string>& p)
{
	std::string temp = p;
	try {
		out << (temp).c_str();
	}
	catch (std::exception& ex)
	{
		std::cout << "\n  exception:\n  " << ex.what() << "\n";
	}
	return out;
}

//Function performing Insertion operation into the string dataBase
void NoSqlStringDbInsert(NoSqlDb<StrData>& db,Element<StrData>& elem1, Element<StrData>& elem2, Element<StrData>& elem3, Element<StrData>& child2,int& count){
	std::cout << "\nDemonstrating Requirement 2 of providing a template class with Meta Data and Value in Template class of String DB\n";
	std::cout << "\n =================================\n";
	std::cout << "\n  Creating and saving NoSqlDb elements with string data";
	cout << "\n---Inserting element1 with key elem1-----\n";
	elem1.name = "elem1";
	elem1.category = "test";
	elem1.data = "elem1's StrData";
	elem1.timeDate = __TIMESTAMP__;
	db.save(elem1.name, elem1);
	count++;
	cout << "\n---Inserting element2 with key elem2-----\n";
	elem2.name = "elem2";
	elem2.category = "test";
	elem2.data = "elem2's StrData";
	elem2.timeDate = __TIMESTAMP__;
	elem2.children = { "child2" };
	db.save(elem2.name, elem2);
	count++;
	std::cout << "\n  Retrieving elements from NoSqlDb<string> DataBase ";
	std::cout << "\n ------------------------------------------\n";
	std::cout << "\n  size of db = " << db.count() << "\n";
	Keys keys = db.keys();
	for (Key key : keys) {
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();}
	cout << "\n Demomstrating Requirement3 of adding element3 and child2 (child of element2 to show adding child relationship) to StringDataBase\n";
	elem3.name = "elem3";
	elem3.category = "test";
	elem3.data = "elem3's StrData";
	elem3.timeDate = __TIMESTAMP__;
	elem3.children = { "child31","child32" };
	child2.name = "child2";
	child2.timeDate = __TIMESTAMP__;
	db.save(child2.name, child2);
	db.save(elem3.name, elem3);
	count++;
	cout << "\n\nDataBase elements after adding the new element element3 and child2 as a key \n";
	Keys ke = db.keys();
	for (Key key : ke) {
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();}
	if (count % 4 == 0) {
		cout << "\nDemonstrating requirement of persisting database after 5 db access instances\n";
		cout << "\nxml file is stored in ../debug as PersistXml and xml is being displayed\n";
		string s = toXml(db);
		cout << "\n\n" << s << "\n\n";}
}

//Function performing Insertion operation into the Int dataBase
void InsertIntoIntDb()
{
  std::cout << "\n  Demonstrating Requirement 2 of providing a template class with Meta Data and Value in Template class of Int DB";
  std::cout << "\n =================================\n";
  std::cout << "\n  Creating and saving NoSqlDb elements with Integer data";
  std::cout << "\n -------------------------------------------------------\n";
  NoSqlDb<intData> idb;
  Element<intData> ielem1;
  cout << "\n---Inserting element with key E1-----\n";
  ielem1.name = "E1";
  ielem1.category = "test";
  ielem1.data = 1;
  ielem1.timeDate = __TIMESTAMP__;
  idb.save(ielem1.name, ielem1);
  cout << "\n---Inserting element with key E2-----\n";
  Element<intData> ielem2;
  ielem2.name = "E2";
  ielem2.category = "test";
  ielem2.data = 2;
  ielem2.timeDate = __TIMESTAMP__;
  idb.save(ielem2.name, ielem2);
  cout << "\n---Inserting element with key E3-----\n";
  Element<intData> ielem3;
  ielem3.name = "E3";
  ielem3.category = "test";
  ielem3.data = 3;
  ielem3.timeDate = __TIMESTAMP__;
  idb.save(ielem3.name, ielem3);
  cout << "\n---Inserting element with key E4-----\n";
  Element<intData> ielem4;
  ielem4.name = "E4";
  ielem4.category = "test";
  ielem4.data = 4;
  ielem4.timeDate = __TIMESTAMP__;
  idb.save(ielem4.name, ielem4);

  std::cout << "\n  Retrieving elements from NoSqlDb<int> DataBase";
  std::cout << "\n ---------------------------------------\n";
  std::cout << "\n  size of idb = " << idb.count() << "\n";
  Keys ikeys = idb.keys();
  for (Key key : ikeys)
  {
    std::cout << "\n  " << key << ":";
    std::cout << idb.value(key).show();
  }
  std::cout << "\n\n";
}

//Function to convert db elements to Xml and vice versa
void XmlToAndFro(NoSqlDb<StrData>& db)
{
	cout << "\n\n--- Creating an Xml named PersistXml.xml in location ../debug with DB elements and Displaying Xml String-----\n\n";
	string xml = toXml(db);
	std::cout << xml;
}

//Function to demonstrate queries being implemented 
void queriesDemonstration(NoSqlDb<StrData>& db,Element<StrData>& elem1,Element<StrData>& elem2) {
	Queries q;
	cout << "\n\n\n******************** requirement7 Queries************************";
	q.ValueOfKey(elem1.name, db);
	q.ChildrenOfKey(elem2.name, db);
	std::vector<std::string> temp = q.SpecifiedName(db, "ele");
	cout << "\nElements with string ele in Elements name  are\n";
	for (int i = 0; i < (int)temp.size(); i++) {
		std::cout << temp[i] << "\n";}

	std::vector<std::string> tem = q.SpecifiedCategory(db, "test");
	cout << "\nElements with category test are\n";
	for (int i = 0; i < (int)tem.size(); i++) {
		std::cout << tem[i] << "\n";}

	std::vector<std::string> te = q.patternSimilarToKey(db, "le");
	cout << "\nElements with patterm are le in key are \n";
	for (int i = 0; i < (int)te.size(); i++) {
		std::cout << te[i] << "\n";}

	std::vector<std::string> t = q.patternSimilarToKey(db, "m3");
	cout << "\nElements with keys with m3 are are\n";
	for (int i = 0; i < (int)t.size(); i++) {
		std::cout << t[i] << "\n";}

	std::vector<std::string> AddKeys;
	std::vector<std::string> re = q.KeysByEarlierQuery(db, te, "elem1");
	cout << "\n--Requirement 8 of getting all keys matching (elem1) pattern given on keys returned by PatternSimailarToKey when its pattern is (le)  query---\n";
	for (int i = 0; i < (int)re.size(); i++) {
		std::cout << re[i] << "\n";
		AddKeys.push_back(re[i]);}

	std::vector<std::string> r = q.KeysByEarlierQuery2(db, t, "el");
	cout << "\n--Requirement 8 of getting all keys matching (el) pattern given on keys returned by PatternSimailarToKey query when its pattern is (m3)---\n";
	for (int i = 0; i < (int)r.size(); i++) {
		std::cout << r[i] << "\n";
		AddKeys.push_back(r[i]);
	}

	std::vector<std::string> addKeysresult = q.unionOfKeys(db, AddKeys, "lem");
	cout << "\n--Requirement 9 of union of keys,adding 2keys resulting from requiremnt 8 demonstration---\n";
	for (int i = 0; i < (int)addKeysresult.size(); i++) {
		std::cout << addKeysresult[i] << "\n";
	}
	cout << "----\nResult of Requirement9 will be combination of Requirement 8 demonstration's quieries--\n";
}

//Function to demonstrate update and delete operations to DataBase
void UpdateAndDelete(NoSqlDb<StrData>& db,Element<StrData> elem2,int& count,Element<StrData> child2) {
	cout << "\n\n----Demonstrating requirements of adding,deleting,updating metadata of Db Elements-----------\n";
	cout << "\n\n------------Elements in db before update------------\n\n";
	Keys bukeys = db.keys();
	for (Key key : bukeys) {
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}
	cout << "\n\n---------Elements in db after updating element 2's text to Updated String Text and Updated Test-----\n\n";
	elem2.category = "Updated Test";
	elem2.data = "Updated String Text";
	db.Update(elem2.name,elem2);
	count++;
	
	Keys ukeys = db.keys();
	for (Key key : ukeys){
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}

	cout << "\n\n-----------Deleting element Element2 ---------\n\n";
	db.Delete(elem2.name);
	db.Delete(child2.name);
	cout << "\n------DataBase elements after Deleting element2--------\n";
	Keys dkeys = db.keys();
	for (Key key : dkeys) {
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}
	cout << "\n\n---- Elements in database after adding element2 to DB----\n\n";
	db.save(elem2.name, elem2);
	count++;
	Keys akeys = db.keys();
	for (Key key : akeys) {
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}
}


int main(){        
	try {
		int count = 1;
		NoSqlDb<StrData> db;
		Element<StrData> elem1;
		Element<StrData> elem2;
		Element<StrData> elem3;
		Element<StrData> child;
		InsertIntoIntDb();
		NoSqlStringDbInsert(db, elem1, elem2, elem3, child, count);
		UpdateAndDelete(db, elem2, count, child);
		XmlToAndFro(db);
		queriesDemonstration(db, elem1, elem2);
		cout << "\n DataBase Structure Xml file is stored in location ../debug as DataBaseStructure.xml\n";
	}
	catch (...) {
		cout << "An exception has occured";
	}

	
	    
}

	


