Note:  TestFiles folder act as consle client's acting location
====== Repository folder act as Remote Server's acting location 

* Test Files folder in the project contains all the files that the console client sends to server (Demonstrates one way communication,Server acting as listener)
* After files are sent to Repository folder code publisher runs on server and generates the .html files with dependencies in Repository
* Later only .html files in Repository are sent to Test folder (Client acting as Listener demonstrating 2 way HTTP communication) 
* C# GUI acts as other client which could upload files to Mock Channel(i.e Mock channel is dequeing files sent by GUI) 
* I was not able to handle servers response to client in GUI.
* Console client-server 2 way communication is working fine   


client Acting as server in Console Application Indicating that client is listening