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

//Function to publish HTML files 
void Publisher::publishCode(string path) {
	std::string loc = "../"; string link, name; size_t t = string::npos;
	ifstream myReadFile; ofstream myWriteFile; string getLine;//string TargetPath = "Target";
	int count = 0; char output = NULL; int begin, end;
	myReadFile.open(path);
	myWriteFile.open(path+".html");
	std::ifstream input(path);
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
				myWriteFile <<"}</div>"; break;
			default:
				myWriteFile << output;
				break;
			}
			while (getline(input, getLine)) {
				if ((getLine.find("if") != t)) {
				}
				else if (getLine.find("#include") != t && (getLine.find("\"") != t)) {
					begin = getLine.find('"');
					end = getLine.find_last_of('"');
					link = getLine.substr(begin + 1, end - begin - 1);
					name = getLine.substr(begin + 1, end - begin - 1);
					myWriteFile << "<a href = \"" << link << ".html\">" << name << "</a>\n";
				}}
		}
		myWriteFile << "</pre>";
		myWriteFile << "</body>\n";
		myWriteFile << "</html>\n";
	}
	myReadFile.close();
	myWriteFile.close();
}

//Function to Style HTML files generated
void Publisher::StylingPublisherCSS(string temp) {
	ofstream cssStyling;
	cssStyling.open(temp + "cssStyleFile.css");
	if (cssStyling.is_open()){
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

//Function to provide scope handling on mouse clicks
void Publisher::StylingPublisherJS(string temp) {
	ofstream ScopeHandling;
	ScopeHandling.open(temp + "ScopeHandler.Js");
	if (ScopeHandling.is_open()){
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

//Function to Iterate through all files in repository and to invoke publishing HTML Files and display Executive information on console
void Publisher::FileIteration() {
	cout << "\n\n---------Requirement 1 and 2 can be verifired from the code----------------------------------- \n\n";
	cout << "\n\n---------Requirement 3 can be demonstrated by Publisher Package which publishes HTML files in the same location(specified by command line) where the .h and .cpp files are present----------------------\n\n";
	cout << "\n\n---------Requirement 5 of Styling HTML Files using CSS file named (cssStylefile.css) and Using JavaScipt file named (ScopeHandler.Js) to Handle Mouse clicks can be demonstrated by clicking .h and .cpp files which are displayed using index.html file upon executing run.bat--------------\n\n";
	std::string dirpath_ = "../Repository";
    currentDirectories = directory.getDirectories(dirpath_);
	cout << "\n\n---------Requirement 6 of providing links in Head Section to (cssStylefile.css) file and to JavaScript file (ScopeHandler.Js) is implemented in publishCode function of Publisher.cpp file of publisher package--------------\n\n";
	for (size_t i = 0; i < currentDirectories.size(); i++) {
		std::string appendpath = dirpath_ + "/" + currentDirectories[i];
		string temp = dirpath_ + "/" + currentDirectories[i] + "/";
		StylingPublisherCSS(temp);
		StylingPublisherJS(temp);
		std::vector<std::string> temporaryFiles = directory.getFiles(appendpath);
		for (size_t k = 0; k < temporaryFiles.size(); k++) {
			currentFiles.push_back(dirpath_ + "/" + currentDirectories[i] + "/" + temporaryFiles[k]);
			fileCollection.push_back(temporaryFiles[k]);
		}}
	
	cout << "\n\n ---------Requirement 7 of displaying dependency information in published files can be verified upon opening the published files in the browser----------\n\n";
	cout << "\n\n ---------Requirement 8 of developing command line processing can be verified by checking the run.bat file, main function in Executive.cpp file and dependencyTable function in DepAnal.h  and upon execution----------\n\n\n";
	cout << "\n\n ---------Requirement 9 All important packages of Project3 are present in Repository folder of the application -------\n\n";
	cout << "\n\n--------- Requirement 4 of hiding and unhiding code upon different scopes in published files can be verified using + and - BUTTON in published files--------\n\n\n";
	cout << "\n\n ---------Requirement 10 of Automated Test Suite is completed for project3 ----------------\n\n\n";
	cout << "\n\n ---------File to open in browser upon execution can be specified as the 4th argument in run.bat or could be changed by replacing ..\\Repository\\index.html argument in run.bat file ---\n\n"; 
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


