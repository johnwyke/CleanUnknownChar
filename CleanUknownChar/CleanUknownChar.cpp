// CleanUknownChar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std; 
namespace fs = std::filesystem;

bool deleteChar(string path);
string prompt();
string getFileName(const string& s);
string getPath(const string& s , string file);
string getFileExt(const string& s);
void recursiveDir(const string& path);
list<string> getDirectories(const string& path);


int main()
{
    string path;
    path = prompt();
    // User wants to exit program
    if (path == "q")
        system("pause");

    fs::directory_entry dir(path);
    if (dir.is_directory()) {
        // Check to see if other directories 
        // if no other directories at base began reading file.
        // else dive deeper with recursive method
        recursiveDir(path);
    }
    else {
        // it is a single file
        deleteChar(path);
    }
    
    
     
    // else get folder stucture 
        // This needs to be a tree. 
    // 
    //myfile.open(path);
}

void recursiveDir(const string& path) {
    string newPath = "";

    // Create List of Dirs 
    fs::directory_entry dir(path);
    

    // Create List of Files 

    if (dir.is_directory()) {
        // Check to see if other directories 
        // if no other directories at base began reading file.
        // else dive deeper with recursive method
        for (auto& p : fs::directory_iterator(path)) {
            cout << "Editing Current Path: " + path + "\n";
            newPath = p.path().string();
            recursiveDir(newPath);
        }
       
    }
    if(dir.is_regular_file()) {
        // it is a single file
        deleteChar(path);
    }
    // If any Dirs 
    
        // For Loop Cycle Through Dirs
            // Add Dir name to File Path Call function again. 

    // if Any Files 
        // For Loop Cycle through files 
            // Call Delete CharFunction with File name



}



/// <summary>
/// Promp the User for the File or Path
/// </summary>
/// <returns></returns>
string prompt() {
    string path;
    bool check = true;
    // Prompt User to Enter Path
    while (check){
        cout << "Enter in the Path you want changed press (q) to exit: ";
        cin >> path;
        fs::directory_entry dir(path);
        // Check is path is a File or a folder 
        if (dir.is_directory() || fs::exists(path) || path =="q") {
            check = false;
        }
    }
    return path;
}

/// <summary>
/// Delete Chars in the path. 
/// </summary>
/// <param name="path"></param>
/// <returns></returns>
bool deleteChar(string filePath) {
    string fileName = "";
    string path = "";
    string ext = "";
    int result = 0;
    ifstream myFile;
    fileName = getFileName(filePath);
    ext = getFileExt(filePath);
    path = getPath(filePath, fileName + ext);
    
    ofstream fileout(path + fileName+"_new" + ext);
    string line = "";
    
    
    myFile.open(path + fileName + ext);
    bool check = false;
    // open file
  
    // call function to read file 
    while (getline(myFile,line)) {
        cout << line <<"\n";
        for(int i = 0; i < line.length(); i++){
            if (int(line[i]) < 128 && int(line[i]) > -1)
                continue; 
            else
                line[i] = ' '; 
            //fileout.put(line[i]);
        }

        fileout << line +"\n";
    
        // Begin to cycle through and compare against ASCII Values to see if
    }
    myFile.close();

    result = rename((path + fileName + ext).c_str(), (path + fileName + "_old" + ext).c_str());
    if (result !=0) {
        cout << " Error Renaming File: " + path + fileName + ext + " to Old.";
        
    }
    
    fileout.close();
    result = rename((path + fileName + "_new" + ext).c_str(), (path + fileName + ext).c_str());
    if (result !=0) {
        cout << " Error Renaming File: " + path + fileName + ext + " to New.";
        
    }
    result = remove((path + fileName + "_old" + ext).c_str());
    if (result != 0) {
        cout << "Error Removing File: " + path + fileName + "_old" + ext;
    }
    return check;
}

/// <summary>
/// Get the file name and extension
/// </summary>
/// <param name="s"></param>
/// <returns></returns>
string getFileName(const string& s) {

    char sep = '\\';
    string temp = "";
    size_t i = s.rfind(sep, s.length());
    temp = s.substr(i + 1, s.length());
    if (i != string::npos) {
        cout << "Getting " + temp;
        return(temp.substr(0, temp.length() - getFileExt(temp).length()));
    }

    return("");
}

/// <summary>
/// Return File Path.
/// </summary>
/// <param name="s"></param>
/// <param name="file"></param>
/// <returns></returns>
string getPath(const string& s, string file) {
    char sep = '\\';
    string temp = "";
    size_t i = s.rfind(sep, s.length());
    temp = s.substr(i + 1, s.length());
    if (i != string::npos) {
        cout << "Getting  Path " + temp;
        return(s.substr(0, s.length() - temp.length()));
    }
    //return(s.substr(0, file.length()));
    return("");

}

string getFileExt(const string& s) {

    size_t i = s.rfind('.', s.length());
    if (i != string::npos) {
        return(s.substr(i, s.length() - i));
    }

    return("");
}


