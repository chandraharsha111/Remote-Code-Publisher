///////////////////////////////////////////////////////////////////
// MainWindow.xaml.cs:Seperate client with GUI in C#             //
// ver 1.0                                                       //
// Application: Remote Code Publisher, Spring 2017               //
// Platform:    LenovoFlex4, Win 10, Visual Studio 2015          //
// Author:      Chandra Harsha Jupalli, OOD Project3             //
//              cjupalli@syr.edu                                 //
///////////////////////////////////////////////////////////////////

/*
* Package Operations:
* -------------------
* This package acts as a seperate client and it provides GUI  
* User can select the directory from where files are needed to sent to client 
* It uses CLI shim package which would interact with managed code and pass the client request to mock channel 
* which inturn communicate to server
* 
* Public Interface
* --------------------
*  There is no public interface in this User interface as there are no C# classes 
*  
*
*
* Required Files:
* ---------------
* CLIShim.h,CLIShim.cpp  

* Build Process:
* --------------
*   devenv CodeAnalyzerEx.sln /debug rebuild
*
* Maintenance History:
* --------------------
* Ver 1.0 : 2 May 2017
* - first release
*
*/

using System;
using System.Windows;
using System.Windows.Controls;
using System.Threading;

using System.ComponentModel;
using System.Windows.Forms;
using System.ServiceModel;

namespace ClientGUI
{
    public partial class MainWindow : Window{
        Shim shim = new Shim();
        private readonly BackgroundWorker backWorker;
        private string DLLPath;
        public MainWindow(){
            InitializeComponent();
            backWorker = new BackgroundWorker();
            backWorker.DoWork += sendFiles;
        }

        private void sendFiles(object sender, DoWorkEventArgs e)
        {
           
        }

        private void UploadFilesToServer(object sender, RoutedEventArgs e)
        {
          
        }
       

        

        

        private void Server_Response(object sender, RoutedEventArgs e){

        }

        private void SelectDirectory(object sender, RoutedEventArgs e){
            FolderBrowserDialog dlg = new FolderBrowserDialog();
            DialogResult result = dlg.ShowDialog();
            if (result == System.Windows.Forms.DialogResult.OK){  
                string[] files = System.IO.Directory.GetFiles(dlg.SelectedPath);
                //String[] directories = System.IO.Directory.GetDirectories(dlg.SelectedPath);
                    foreach (String str in files){
                        ListBoxFiles.Items.Add(str);
                        shim.PostMessage(str);  
                    }
            }
            DLLPath = dlg.SelectedPath;
            Console.WriteLine(DLLPath);
        }

        private void Results(object sender, TextChangedEventArgs e){

        }

        private void sendFiles(object sender, RoutedEventArgs e){

        }
        

        private void DisplaySelectedFiles(object sender, TextChangedEventArgs e)
        {

        }
    }

    
}




