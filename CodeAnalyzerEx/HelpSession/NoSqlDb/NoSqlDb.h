#pragma once
////////////////////////////////////////////////////////////////////////////////
// NoSqlDb.h:   key/value pair in-memory database                             //
// Application: Key Value DataBase, Spring 2017                               //
// Platform:    LenovoFlex4, Win 10, Visual Studio 2015                       //
// Author:      Chandra Harsha Jupalli, CSE687 - OOD,Spring 2017              //
//              cjupalli@syr.edu                                              //
////////////////////////////////////////////////////////////////////////////////

/*
* Package Operations:
* -------------------
* This package provides template class called element containing data elements in NoSql DataBase
* It contains Interface and Implementation of Save,Delete,Updation,Display functionalities of DataBase
*
* PublicInterface
* ----------------
* std::string Element<Data>::show()                                            //Display elements in database
* bool NoSqlDb<Data>::Delete(Key key)
* bool NoSqlDb<Data>::save(Key key, Element<Data> elem)
* Element<Data> NoSqlDb<Data>::value(Key key)                                  //Display Value of given key
* size_t NoSqlDb<Data>::count()
*
*
*
* Required Files:
* ---------------
*   - CppProperties.h,CppProperties.cpp
*   - XmlDocument.h, XmlDocument.cpp, XmlElement.h, XmlElement.cpp

* Build Process:
* --------------
*   devenv XmlParser.sln /debug rebuild
*
* Maintenance History:
* --------------------
* Ver 1.0 : 7 February 2017
* - first release
*
*/

#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include "../CppProperties/CppProperties.h"
#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../Convert/Convert.h"
#include "../StrHelper.h"
#include "../XmlDocument/XmlElement/XmlElement.h"
#include <ctime>
#include <fstream>

/////////////////////////////////////////////////////////////////////
// Element class represents a data record in our NoSql database
// - in our NoSql database that is just the value in a key/value pair
template<typename Data>
class Element
{
public:
  using Name = std::string;
  using Category = std::string;
  using TimeDate = std::string;
  using ChildRelation = std::vector<std::string>;

  Property<Name> name;                // metadata
  Property<Category> category;        // metadata
  Property<TimeDate> timeDate;        // metadata
  Property<Data> data;                // data
  Property<ChildRelation> children;   //metadata
 
  std::string show();
};



	
//show function displays all the elements in the database
template<typename Data>
std::string Element<Data>::show()
{
  std::ostringstream out;
  out.setf(std::ios::adjustfield, std::ios::left);
  out << "\n    " << std::setw(8) << "name"     << " : " << name;
  out << "\n    " << std::setw(8) << "category" << " : " << category;
  out << "\n    " << std::setw(8) << "timeDate" << " : " << timeDate;
  out << "\n    " << std::setw(8) << "data"     << " : " << data;
  out << "\n    " << std::setw(8) << "children" << " : ";

  //children keys being displayed 
std::vector<std::string> temp = children;
  for (int i = 0; i < (int)temp.size(); i++) {
	  out << temp[i]<<" ";
  }
  return out.str();
}



/////////////////////////////////////////////////////////////////////
// NoSqlDb class is a key/value pair in-memory database
// - stores and retrieves elements
template<typename Data>
class NoSqlDb
{
public:
  using Key = std::string;
  using Keys = std::vector<Key>;

  Keys keys();
  bool save(Key key, Element<Data> elem);
  bool Delete(Key key);
  void Update(Key key, Element<Data> elem);
  Element<Data> value(Key key);
  size_t count();
  void ReadFromXml(std::string xml);
private:
  using Item = std::pair<Key, Element<Data>>;

  std::unordered_map<Key,Element<Data>> store; 
};

//keys of dataBase are stored in a collection 
template<typename Data>
typename NoSqlDb<Data>::Keys NoSqlDb<Data>::keys()
{
  Keys keys;
  for (Item item : store)
  {
    keys.push_back(item.first);
  }
  return keys;
}

//Elements are saved into DataBase using save function 
template<typename Data>
bool NoSqlDb<Data>::save(Key key, Element<Data> elem)
{

  if(store.find(key) != store.end())
    return false;
  store[key] = elem;
  return true;
}

//Elements metadata or data can be updated in to the database using update function
template<typename Data>
void NoSqlDb<Data>::Update(Key key, Element<Data> elem)
{
	    if(store.find(key)!=store.end())
		store[key] = elem;
		
}


//An element can be removed from database using Delete function
template<typename Data>
bool NoSqlDb<Data>::Delete(Key key)
{
	if (store.find(key) ==store.end()) {
		cout << "\n There is no element with entered key \n";
		return false;
	}
	else {
		store.erase(key);
		cout << "\n Element was deleted";
		return true;
	}
}

template<typename Data>
Element<Data> NoSqlDb<Data>::value(Key key)
{
  if (store.find(key) != store.end())
    return store[key];
  return Element<Data>();
}

//count function returns the number of elements in the database
template<typename Data>
size_t NoSqlDb<Data>::count()
{
  return store.size();
}

template<typename Data>
void NoSqlDb<Data>::ReadFromXml(std::string FileName)
{
	std::cout << "\n  Retrieving elements from XML File \n";
	std::string x;
	std::ifstream RawDbFile;
	std::string RawDbString = " ";
	// To read the data from the default database
	if (FileName == "Default")	{
		x = "../StringDB.xml";
	}
	else{
		x = FileName;
	}
	RawDbFile.open(x);
	if (RawDbFile.is_open()){
		std::string tp;
		while (std::getline(RawDbFile, tp)){
			RawDbString += tp;
			RawDbString += "\n";
		}
	}
	RawDbFile.close();
	XmlDocument doc(RawDbString, XmlDocument::str);
	// fetch the Node Tag from XML element
	std::vector<SPtr> desc = doc.descendents("Nodes").select();
	int i = 0;
	for (auto r : desc){
		Element<Data> NewElem;
		NewElem.name = trim(desc[i]->children()[0]->children()[0]->value());
		NewElem.category = trim(desc[i]->children()[1]->children()[0]->value());
		NewElem.timeDate = trim(desc[i]->children()[2]->children()[0]->value());
		NewElem.data = trim(desc[i]->children()[3]->children()[0]->value());
		std::stringstream a;
		std::string tChild = trim(desc[i]->children()[4]->children()[0]->value());
		a << tChild;
		tChild.clear();
		while (std::getline(a, tChild)) {
			tChild = trim(tChild);
			NewElem.children(tChild);
		}
		NewElem.data = trim(desc[i]->children()[5]->children()[0]->value());
		save(NewElem.name, NewElem);
		i++;
	}
	std::cout << "\n Data has been retreived to the Database successfully!\n";
}

















