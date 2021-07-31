///////////////////////////////////////////////////////////////////
// publisher.cpp: Publishes HTML files for given Repository files//
// ver 1.0                                                       //
// Application: Dependency Based Code Publisher, Spring 2017     //
// Platform:    LenovoFlex4, Win 10, Visual Studio 2015          //
// Author:      Chandra Harsha Jupalli, OOD Project3             //
//              cjupalli@syr.edu                                 //
///////////////////////////////////////////////////////////////////

#include "publisher.h"
#include <fstream>
using namespace std;

void Publisher::publishCode(string path) {
	std::string loc="../";
	ifstream myReadFile; ofstream myWriteFile; //string TargetPath = "Target";
	int count=0; char output = NULL;
	myReadFile.open(path);
	myWriteFile.open(path+".html");

	if (myReadFile.is_open()) {
		myWriteFile << "<html>\n";
		myWriteFile << "<head>\n";
		myWriteFile << "<link rel=\"stylesheet\" href=\"cssStyleFile.css\">\n";
		myWriteFile << "<script src=\"ScopeHandler.js\"></script>\n";
		myWriteFile << "</head>\n";
		myWriteFile << "<body>";
		myWriteFile << "<pre>";

		while ((!myReadFile.eof()) && (myReadFile.get(output))) {
			switch (output){
			case '<':
				myWriteFile << "&lt;"; break;
			case '>':
				myWriteFile << "&gt;"; break;
			case '{':
				count++;
				myWriteFile << "<input type='button' value='-' id='bt" << count << "' onclick='scopeHandle(this);'//>{<div id='dbt" << count << "'>";break;
			case '}':
				myWriteFile << output; break;
			default:
				myWriteFile << output;
				break;
			}
		}
		myWriteFile << "</pre>";
		myWriteFile << "</body>\n";
		myWriteFile << "</html>\n";
	}
	myReadFile.close();
	myWriteFile.close();
}

void Publisher::StylingPublisherCSS(string temp) {
	ofstream cssStyling;
	string pat = temp + "cssStyleFile.css";
	cssStyling.open(pat);
	if (cssStyling.is_open())
	{
		cssStyling << "body {\n margin:20px; \n color:black; \n background-color:#eee; \n font-family:Consolas; \n";
		cssStyling << "font-weight: 600; \n font-size: 110%;\n ";
		cssStyling << "}";

		cssStyling << ".indent {\n margin-left:20px; \n margin-right:20px; \n }";
		cssStyling << "h4 { \n margin-bottom:3px; \n margin-top:3px; \n}";
		cssStyling << "div { display: inline}";
		cssStyling.close();
	}
	else cout << "Issue openeing the file";
}

void Publisher::StylingPublisherJS(string temp) {
	ofstream ScopeHandling;
	string pat = temp + "ScopeHandler.Js";
	ScopeHandling.open(pat);
	if (ScopeHandling.is_open())
	{
		ScopeHandling << "function scopeHandle(object)\n{\n";
		ScopeHandling << "var temp=\"d\"+object.id;\n";
		ScopeHandling << "var div = document.getElementById(temp);\n";
		ScopeHandling << "var button = document.getElementById(object.id);\n";
		ScopeHandling << "if(div.style.display != 'none'){\n";
		ScopeHandling << "\t div.style.display = 'none';\n";
		ScopeHandling << "button.value = '+';\n";
		ScopeHandling << "}\n else {\n";
		ScopeHandling << "div.style.display = 'inline';\n";
		ScopeHandling << "button.value = '-';\n";
		ScopeHandling << "}";
		ScopeHandling << "};";
	}

	ScopeHandling.close();

}

void Publisher::FileIteration() {
	cout << "\nRequirement 1 and 2 can be verifired from the code \n\n";
	cout << "\n\nPublisher Package publishes HTML files in the same location i.e where the files are present in repository folder respectively\n\n";
	cout << "\n\n\n Requirement 5 of Styling HTML Files using CSS file and Using JavaScipt to Handle Mouse Clicks are created once in every directory specified inside command line argument i.e Repository folder\n\n";
	std::string dirpath_ = "../Repository";
    currentDirectories = directory.getDirectories(dirpath_);
	cout << "\n\n Displaying directories in given path\n";
	for (size_t i = 0; i < currentDirectories.size(); i++) {
		//std::cout << currentDirectories[i] << "\n";	
	}
	cout << "\n\nReuirement 6 of providing links in Head Section is implemented in publishCode function of Publisher package\n\n";

	for (size_t i = 0; i < currentDirectories.size(); i++) {
		std::string appendpath = dirpath_ + "/" + currentDirectories[i];
		string temp = dirpath_ + "/" + currentDirectories[i] + "/";
		StylingPublisherCSS(temp);
		StylingPublisherJS(temp);
		std::vector<std::string> temporaryFiles = directory.getFiles(appendpath);
		for (size_t k = 0; k < temporaryFiles.size(); k++) {
			currentFiles.push_back(dirpath_ + "/" + currentDirectories[i] + "/" + temporaryFiles[k]);
			fileCollection.push_back(temporaryFiles[k]);
		}
	}
	for (size_t k = 0; k < currentFiles.size(); k++) {
		if ((path.getExt(currentFiles[k]) == "h") || (path.getExt(currentFiles[k]) == "cpp")) {
			fileCollection.push_back(currentFiles[k]);
		}
	}
	
	for (size_t t = 0; t < fileCollection.size(); t++) {
		string path = fileCollection[t]; 
		publishCode(path);
	}
}

#ifdef PUBLISHER

void Publisher::publishCode(string path) {
	std::string loc = "../";
	ifstream myReadFile; ofstream myWriteFile; //string TargetPath = "Target";
	int count = 0; char output = NULL;
	myReadFile.open(path);
	myWriteFile.open(path + ".html");

	if (myReadFile.is_open()) {
		myWriteFile << "<html>\n";
		myWriteFile << "<head>\n";
		myWriteFile << "<link rel=\"stylesheet\" href=\"cssStyleFile.css\">\n";
		myWriteFile << "<script src=\"ScopeHandler.js\"></script>\n";
		myWriteFile << "</head>\n";
		myWriteFile << "<body>";
		myWriteFile << "<pre>";

		while ((!myReadFile.eof()) && (myReadFile.get(output))) {
			switch (output) {
			case '<':
				myWriteFile << "&lt;"; break;
			case '>':
				myWriteFile << "&gt;"; break;
			case '{':
				count++;
				myWriteFile << "<input type='button' value='-' id='bt" << count << "' onclick='scopeHandle(this);'//>{<div id='dbt" << count << "'>"; break;
			case '}':
				myWriteFile << output; break;
			default:
				myWriteFile << output;
				break;
			}
		}
		myWriteFile << "</pre>";
		myWriteFile << "</body>\n";
		myWriteFile << "</html>\n";
	}
	myReadFile.close();
	myWriteFile.close();
}

void Publisher::StylingPublisherCSS(string temp) {
	ofstream cssStyling;
	string pat = temp + "cssStyleFile.css";
	cssStyling.open(pat);
	if (cssStyling.is_open())
	{
		cssStyling << "body {\n margin:20px; \n color:black; \n background-color:#eee; \n font-family:Consolas; \n";
		cssStyling << "font-weight: 600; \n font-size: 110%;\n ";
		cssStyling << "}";

		cssStyling << ".indent {\n margin-left:20px; \n margin-right:20px; \n }";
		cssStyling << "h4 { \n margin-bottom:3px; \n margin-top:3px; \n}";
		cssStyling << "div { display: inline}";
		cssStyling.close();
	}
	else cout << "Issue openeing the file";
}
 
int main(){
publisher p;
p.publishCode();
p.StylingPublisherCSS();
}
#endif


