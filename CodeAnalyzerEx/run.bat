cd "Debug"
start MsgServer.exe

start MsgClient.exe

start CodeAnalyzer.exe  ..\Repository *.h *.cpp ..\\Repository\\index.html  /f /r 
 
cd..

cd ClientGUI\bin\x86\Debug
start ClientGUI.exe
