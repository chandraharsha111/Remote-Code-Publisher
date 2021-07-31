///////////////////////////////////////////////////////////////////
// Persist.cpp:  stores elements in database to XML file         //
// ver 1.0                                                       //
// Application: Key Value DataBase, Spring 2017                  //
// Platform:    LenovoFlex4, Win 10, Visual Studio 2015          //
// Author:      Chandra Harsha Jupalli, OOD Project1             //
//              cjupalli@syr.edu                                 //
///////////////////////////////////////////////////////////////////


#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../XmlDocument/XmlElement/XmlElement.h"
#if 0
#include "../CppProperties/CppProperties.h"
#endif
#include "../Convert/Convert.h"
#include "../StrHelper.h"
#include  "../NoSqlDb/NoSqlDb.h"
#include <iostream>
#include <fstream>

using namespace XmlProcessing;
using SPtr = std::shared_ptr<AbstractXmlElement>;
using StrData = std::string;
using intData = int;
using Key = NoSqlDb<StrData>::Key;
using Keys = NoSqlDb<StrData>::Keys;


template<typename Data>
std::string toXml(NoSqlDb<Data>& db)
{
	title("Creating XmlDocument and storing it in Project folder");
	SPtr pRoot = makeTaggedElement("DataBase");
	XmlDocument doc(XmlProcessing::makeDocElement(pRoot));
    Keys ikeys2 = db.keys();
  for (Key key1 : ikeys2)
  {
	  //std::cout << "\n" << key1 << ":";// << db.value(key1).show();

		  SPtr child1 = makeTaggedElement(db.value(key1).name);
		  SPtr TagName = makeTaggedElement("Name");
		  TagName->addChild(makeTextElement(db.value(key1).name));
		  child1->addChild(TagName);
		  

		  SPtr TagCategory = makeTaggedElement("Category");
		  TagCategory->addChild(makeTextElement(db.value(key1).category));
		  child1->addChild(TagCategory);

		  SPtr TagDateAdded = makeTaggedElement("DateAdded");
		  TagDateAdded->addChild(makeTextElement(db.value(key1).timeDate));
		  child1->addChild(TagDateAdded);

		  SPtr TagData = makeTaggedElement("Data");
		  TagData->addChild(makeTextElement(db.value(key1).data));
		  child1->addChild(TagData);

		  SPtr ChildrenToElement = makeTaggedElement("Children");
		  std::vector<std::string> te = db.value(key1).children;
		  for (int i = 0; i < (int)te.size(); i++) {
			  ChildrenToElement->addChild(makeTextElement(te[i]));
		  }
		  child1->addChild(ChildrenToElement);
		  pRoot->addChild(child1);
  }
  
	std::string xml = doc.toString();  
	//std::ofstream myXmlFile;//create file
	//myXmlFile.open("XmlPersist.xml");
	//myXmlFile << xml;
	//myXmlFile.close();
   return xml;
}


#ifdef Persist

/////////////////////////////////////////////////////////////////////////////
//----< creating an XML file and retrieving data from DataBase >------------

template<typename Data>
std::string toXmldemo(NoSqlDb<Data>& db)
{
	title("Creating XmlDocument and storing it in xml.txt file");
	SPtr pRoot = makeTaggedElement("DataBase");
	XmlDocument doc(XmlProcessing::makeDocElement(pRoot));
	Keys ikeys2 = db.keys();
	for (Key key1 : ikeys2){
		SPtr child1 = makeTaggedElement("Element Key");
		child1->addChild(makeTextElement(db.value(key1).name));
		pRoot->addChild(child1);

		SPtr grandChild11 = makeTaggedElement("Category");
		grandChild11->addChild(makeTextElement(db.value(key1).category));
		child1->addChild(grandChild11);
		pRoot->addChild(child1);

		SPtr grandChild12 = makeTaggedElement("Date Time");
		grandChild12->addChild(makeTextElement(db.value(key1).timeDate));
		child1->addChild(grandChild12);
		pRoot->addChild(child1);
	}
	xml = doc.toString();
	std::ofstream myXmlFile;//create file
	myXmlFile.open("../xml.txt");
	myXmlFile << xml;
	myXmlFile.close();
	return xml;
}

int main()
{
	NoSqlDb<StrData> db;
	Element<StrData> elem1;
	elem1.name = "elem1";
	elem1.category = "test";
	elem1.data = "elem1's StrData";
	elem1.timeDate = __TIMESTAMP__;

	db.save(elem1.name, elem1);
	string xml = toXml(db);
	std::cout << xml;
}

#endif