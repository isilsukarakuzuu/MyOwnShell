#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <fstream>


using namespace std;

int main()
{

    //getting current user's name to show in our cell
    string userName = getlogin();
    
    string line;
    vector<string> commandHistory;

    while(true){
        //printing the shell's starting line
        cout << userName << " " << ">>> ";

        //take input from terminal, create a vector to split the words between spaces
        getline(cin, line);
        vector<string> wordsInEachLine = {""};
        for(auto i:line){
            if (i == ' '){
                wordsInEachLine.push_back("");
            }else{
                wordsInEachLine.back().push_back(i);
            }
        }

        //we will only going to hold last 15 commands entered
        if (commandHistory.size() == 15){
            commandHistory.erase(commandHistory.begin());
        }

        //we are going to add "" to the commands because of the dididothat parameter
        commandHistory.push_back('"' + line + '"');


        //list of commands which will be given

        //prints the current list of files and directories
        if (wordsInEachLine[0] == "listdir"){
            system("ls");
        }

        //prints the hostname
        if (wordsInEachLine[0] == "mycomputername"){
            system("hostname");
        }

        //prints the ip
        if (wordsInEachLine[0] == "whatsmyip"){
            system("curl ifconfig.me");
            cout << endl;
        }

        //it includes 2 different usages depending on parameter style
        if (wordsInEachLine[0] == "printfile"){
            string fileName = wordsInEachLine[1];

            //first usage of printfile: copy file to another file
            if (wordsInEachLine.size() == 4){
                string newFileName = wordsInEachLine[3];
                string copyToANewFile = "cp " + fileName + " " + newFileName;
                system(copyToANewFile.c_str());
            }
            //write file context to the terminal
            else{
                ifstream fileReader(fileName);
                string readingLine;
                while (getline (fileReader, readingLine)) {
                    cout << readingLine;
                    cin.ignore();
                }
            }
        }

        //check whether you did the parameter command
        if (wordsInEachLine[0] == "dididothat"){

            //getting the command part excluding dididothat command
            string checkedCommandName;
            for (auto i:wordsInEachLine){
                if (i != "dididothat"){
                    checkedCommandName += i;
                    checkedCommandName += " ";
                }
            }  

            //deleting the last space
            checkedCommandName.pop_back();

            //checking the command
            if (count(commandHistory.begin(), commandHistory.end(), checkedCommandName)){
                cout << "Yes" << endl;
            }else{
                cout << "No" << endl;
            }
        }

        //open gedit
        if (wordsInEachLine[0] == "hellotext"){
            system("gedit");
        }

        //exits the terminal
        if (wordsInEachLine[0] == "exit"){
            return 0;
        }

    }
    
    return 0;
}