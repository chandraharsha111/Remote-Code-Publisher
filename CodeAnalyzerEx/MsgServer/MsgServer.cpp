///////////////////////////////////////////////////////////////////////////
// MsgServer.cpp - Acts as a Remote Server demonstrating Two way HTTP    //
//                    Style Messaging and File Transfer                  //
// ChandraHarsha, CSE687 - Object Oriented Design, Spring 2017           //
// Application: Remote Code Publisher                                    //
// Platform:    LenovoFlex4, Win 10, Visual Studio 2015                  //
///////////////////////////////////////////////////////////////////////////


#include"MsgServer.h"
#include <string>
#include <iostream>
using namespace Logging;
using Show = StaticLogger<1>;
using namespace Utilities;
using namespace Async;

class ClientHandler
{
public:
  ClientHandler(BlockingQueue<HttpMessage>& msgQ) : msgQ_(msgQ) {}
  void operator()(Socket socket);
private:
  bool connectionClosed_;
  HttpMessage readMessage(Socket& socket);
  bool readFile(const std::string& filename, size_t fileSize, Socket& socket);
  BlockingQueue<HttpMessage>& msgQ_;
};
//----< this defines processing to frame messages >------------------

HttpMessage ClientHandler::readMessage(Socket& socket){
  connectionClosed_ = false;
  HttpMessage msg;
  while (true)  {
    std::string attribString = socket.recvString('\n');
    if (attribString.size() > 1){
      HttpMessage::Attribute attrib = HttpMessage::parseAttribute(attribString);
      msg.addAttribute(attrib);
    }
    else{break;}
  }
  if (msg.attributes().size() == 0){
    connectionClosed_ = true;
    return msg;
  }
  if (msg.attributes()[0].first == "POST"){
    std::string filename = msg.findValue("file");
    if (filename != ""){
      size_t contentSize;
      std::string sizeString = msg.findValue("content-length");
      if (sizeString != "")
        contentSize = Converter<size_t>::toValue(sizeString);
      else
        return msg;
      readFile(filename, contentSize, socket);
    }
    if (filename != ""){
      msg.removeAttribute("content-length");
      std::string bodyString = "<file>" + filename + "</file>";
      std::string sizeString = Converter<size_t>::toString(bodyString.size());
      msg.addAttribute(HttpMessage::Attribute("content-length", sizeString));
      msg.addBody(bodyString);
    }
    else{  // read message body
      size_t numBytes = 0;
      size_t pos = msg.findAttribute("content-length");
      if (pos < msg.attributes().size()){
        numBytes = Converter<size_t>::toValue(msg.attributes()[pos].second);
        Socket::byte* buffer = new Socket::byte[numBytes + 1];
        socket.recv(numBytes, buffer);
        buffer[numBytes] = '\0';
        std::string msgBody(buffer);
        msg.addBody(msgBody);
        delete[] buffer;}
    }
  }
  return msg;
}
//----< read a binary file from socket and save >--------------------
/*
 * This function expects the sender to have already send a file message, 
 * and when this function is running, continuosly send bytes until
 * fileSize bytes have been sent.
 */
bool ClientHandler::readFile(const std::string& filename, size_t fileSize, Socket& socket)
{
  std::string fqname = "../Repository/" + filename;
  FileSystem::File file(fqname);
  file.open(FileSystem::File::out, FileSystem::File::binary);
  if (!file.isGood()){
    Show::write("\n\n  can't open file " + fqname);
    return false;
  }

  const size_t BlockSize = 2048;
  Socket::byte buffer[BlockSize];

  size_t bytesToRead;
  while (true){
    if (fileSize > BlockSize)
      bytesToRead = BlockSize;
    else
      bytesToRead = fileSize;

    socket.recv(bytesToRead, buffer);

    FileSystem::Block blk;
    for (size_t i = 0; i < bytesToRead; ++i)
      blk.push_back(buffer[i]);

    file.putBlock(blk);
    if (fileSize < BlockSize)
      break;
    fileSize -= BlockSize;
  }
  file.close();
  return true;
}
//----< receiver functionality is defined by this function >---------

void ClientHandler::operator()(Socket socket){
  while (true)
  {
    HttpMessage msg = readMessage(socket);
    if (connectionClosed_ || msg.bodyString() == "quit")
    {
      Show::write("\n\n  clienthandler thread is terminating");
      break;
    }
    msgQ_.enQ(msg);
  }
}

//Method to help send files when client is listening
HttpMessage MsgClientFromServer::makeMessage(size_t n, const std::string& body, const EndPoint& ep)
{
	HttpMessage msg;
	HttpMessage::Attribute attrib;
	EndPoint myEndPoint = "localhost:8084";  // ToDo: make this a member of the sender
											 // given to its constructor.
	                                         //8084 client acting as server
	switch (n){
	case 1:
		msg.clear();
		msg.addAttribute(HttpMessage::attribute("POST", "Message"));
		msg.addAttribute(HttpMessage::Attribute("mode", "oneway"));
		msg.addAttribute(HttpMessage::parseAttribute("toAddr:" + ep));
		msg.addAttribute(HttpMessage::parseAttribute("fromAddr:" + myEndPoint));

		msg.addBody(body);
		if (body.size() > 0){
			attrib = HttpMessage::attribute("content-length", Converter<size_t>::toString(body.size()));
			msg.addAttribute(attrib);
		}
		break;
	default:
		msg.clear();
		msg.addAttribute(HttpMessage::attribute("Error", "unknown message type"));
	}
	return msg;
}

//Method to  send files when client is listening
bool MsgClientFromServer::sendFile(const std::string& filename, Socket& socket){
	std::string fqname = "../Repository/" + filename;
	FileSystem::FileInfo fi(fqname);
	size_t fileSize = fi.size();
	std::string sizeString = Converter<size_t>::toString(fileSize);
	FileSystem::File file(fqname);
	file.open(FileSystem::File::in, FileSystem::File::binary);
	if (!file.isGood())
		return false;

	HttpMessage msg = makeMessage(1, "", "localhost::8085"); //8085 acts as server from client side 
	msg.addAttribute(HttpMessage::Attribute("file", filename));
	msg.addAttribute(HttpMessage::Attribute("content-length", sizeString));
	sendMessage(msg, socket);
	const size_t BlockSize = 2048;
	Socket::byte buffer[BlockSize];
	while (true)
	{
		FileSystem::Block blk = file.getBlock(BlockSize);
		if (blk.size() == 0)
			break;
		for (size_t i = 0; i < blk.size(); ++i)
			buffer[i] = blk[i];
		socket.send(blk.size(), buffer);
		if (!file.isGood())
			break;
	}
	file.close();
	return true;
}
void MsgClientFromServer::sendMessage(HttpMessage& msg, Socket& socket)
{
	std::string msgString = msg.toString();
	socket.send(msgString.size(), (Socket::byte*)msgString.c_str());
}
////Method where execution of sending files when client is listening
void MsgClientFromServer::execute(const size_t TimeBetweenMessages, const size_t NumMessages){
	Show::attach(&std::cout);
	Show::start();
	Show::title(
		"Starting HttpMessage From Server to client on thread " + Utilities::Converter<std::thread::id>::toString(std::this_thread::get_id())
	);
	try{
		SocketSystem ss;
		SocketConnecter si;
		while (!si.connect("localhost", 8085)){
			Show::write("\n server waiting to connect to client to send files");
			::Sleep(100);
		}

		HttpMessage msg;
		for (int i = 0; i < 10000; i++) {
			for (int j = 0; j < 10000; j++) {
				for (int k = 0; k < 15; k++) {

				}
			}
		}
		std::vector<std::string> files = FileSystem::Directory::getFiles("../Repository/", "*.html");
		for (size_t i = 0; i < files.size(); ++i){
			Show::write("\n\n  sending file " + files[i]);
			sendFile(files[i], si);
		}
		msg = makeMessage(1, "quit", "toAddr:localhost:8084");
		sendMessage(msg, si);
		Show::write("\n\n  client sent\n" + msg.toIndentedString());
		Show::write("\n");
		Show::write("\n  All done ");
	}
	catch (std::exception& exc){
		Show::write("\n  Exeception caught: ");
		std::string exMsg = "\n  " + std::string(exc.what()) + "\n\n";
		Show::write(exMsg);
	}
}

//----< test stub >--------------------------------------------------

int main(){
  BlockingQueue<HttpMessage> msgQ;
  try{
    SocketSystem ss;
    SocketListener sl(8080, Socket::IP6);
    ClientHandler cp(msgQ);
    sl.start(cp);
	
	MsgClientFromServer c1;
	std::thread t1(
		[&]() { c1.execute(100, 20); } 
	);

	t1.join();
	
    while (true){
      HttpMessage msg = msgQ.deQ();
	  std::cout << "\n\n  server recvd message contents:\n" + msg.bodyString();
    }
  }
  catch (std::exception& exc){
    std::string exMsg = "\n  " + std::string(exc.what()) + "\n\n";
  }

}

//No Stub since it is an exe