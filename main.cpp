#include <iostream>
#include <cstdlib>
#include <sys/stat.h>
#include <fstream>
#include <string>

using namespace std;

inline bool exists(const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

void toggleTmp(string s_tmpFile);
//string callPing(string s_pingTmpFile);
void findDirectories(char* c_tmpDir, string* s_tmpFile, string* s_pingTmpFile);
string callPing(string s_pingTmpFile, string address = "8.8.8.8", int wait = 4);

int main(int argc, char *argv[])
{
    bool toggleMode = false;
    char* c_tmpDir = {};
    string(s_tmpFile);
    string(s_pingTmpFile);

    //Find tmp directory
    findDirectories(c_tmpDir, &s_tmpFile, &s_pingTmpFile);

    //Check options
    if (argc > 1) {
        if (string(argv[1]) == "-t")
            toggleMode = true;
        if ((string(argv[1]) == "-h")) {
            cout << "Use with -t option to toggle on and off." << endl;
            cout << "Used without any option will return ping if on." << endl;
        }
    }

    if (toggleMode) {
        toggleTmp(s_tmpFile);
    } else {
        //Check if we should call ping
        if (exists(s_tmpFile))
            cout << callPing(s_pingTmpFile);
        else
            cout << "Off";
    }

    return 0;
}

void toggleTmp(string s_tmpFile) {
    //Check if tmp file exists
    if (exists(s_tmpFile)) {
        //Delete the tmp file
        remove(s_tmpFile.c_str());
    } else {
        //Create the tmp file
        ofstream o_tmp(s_tmpFile.c_str());
        o_tmp << '\0';
        o_tmp.close();
    }
}

string callPing(string s_pingTmpFile, string address, int wait) {
    //Call our ping command
    string s_pingCmd = "ping -c 1 -w " + std::to_string(wait) + " " + address + " | grep time= | sed 's/.*time=//' > " + s_pingTmpFile;
    string s_rmCmd = "rm " + s_pingTmpFile;
    system(s_pingCmd.c_str());

    //Get the results
    string line;
    ifstream results(s_pingTmpFile.c_str());
    if (results.is_open()) {
        getline(results,line);
        results.close();
        system(s_rmCmd.c_str());
    } else
        line = "Error";

    if (line.size() == 0)
        line = "Disconnected";

    return line;
}

void findDirectories(char* c_tmpDir, string* s_tmpFile, string* s_pingTmpFile) {
    //Determine tmp location
    char* c_username;
    char c_defaultTmpDir[] = {'/', 't', 'm', 'p', 0};
    c_tmpDir = getenv("TMPDIR");
    c_username = getenv("USER");
    *s_tmpFile = "net_check";
    *s_pingTmpFile = "net_check_ping";

    if (c_tmpDir == 0)
        c_tmpDir = c_defaultTmpDir;

    *s_tmpFile = string(c_tmpDir) + "/" + string(c_username) + *s_tmpFile;
    *s_pingTmpFile = string(c_tmpDir) + "/" + string(c_username) + *s_pingTmpFile;
}
