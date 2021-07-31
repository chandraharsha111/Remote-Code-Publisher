///////////////////////////////////////////////////////////////////////////
// MsgServer.h- Acts as a Remote Server demonstrating Two way HTTP   //
//                    Style Messaging and File Transfer                  //
// ChandraHarsha, CSE687 - Object Oriented Design, Spring 2017           //
// Application: Remote Code Publisher                                    //
// Platform:    LenovoFlex4, Win 10, Visual Studio 2015                  //
///////////////////////////////////////////////////////////////////////////

/*
* Package Operations:
* -------------------
* This package implements a Remote Server that sends HTTP style messages and
* files to a Client listening on port 8084
*
* It also Listens on port 8080 and acts as a server and it receives files send from clients
* publishes the html files based on dependencies using HTTP Style messages and files
*
*
* Public Interface
* --------------------
*  using EndPoint = std::string;                                               //variable to act as end pont
*  void execute(const size_t TimeBetweenMessages, const size_t NumMessages);   //function used to send required files to destination
*
*
*
* Required Files:
* ---------------
*   -MsgClient.cpp, MsgServer.cpp
*   HttpMessage.h, HttpMessage.cpp
*   Cpp11-BlockingQueue.h
*   Sockets.h, Sockets.cpp
*   FileSystem.h, FileSystem.cpp
*   Logger.h, Logger.cpp
*   Utilities.h, Utilities.cpp

* Build Process:
* --------------
*   devenv CodeAnalyzerEx.sln /debug rebuild
*
* Maintenance History:
* --------------------
* Ver 1.0 : 2nd May 2017
* - first release
*
*/


#include "../HttpMessage/HttpMessage.h"
#include "../Sockets/Sockets.h"
#include "../FileSystem/FileSystem.h"
#include "../Logger/Cpp11-BlockingQueue.h"
#include "../Logger/Logger.h"
#include "../Utilities/Utilities.h"


class MsgClientFromServer {
public:
	using EndPoint = std::string;
	void execute(const size_t TimeBetweenMessages, const size_t NumMessages);
private:
	HttpMessage makeMessage(size_t n, const std::string& msgBody, const EndPoint& ep);
	void sendMessage(HttpMessage& msg, Socket& socket);
	bool sendFile(const std::string& fqname, Socket& socket);
};