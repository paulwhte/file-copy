#include <dirent.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

int main(void)
{
    //Get the relative path of the directory to check
    cout << "Enter the relative path of the directory: " << endl;
    string path;
    cin >> path;

    string relativePath = path;
    const char* c = relativePath.c_str();

    cout << "You have chosen to examine: " << c << endl;

    DIR           *d;
    struct dirent *dir;

    d = opendir(c);
    if (d)
    {
        //Write to file
        ofstream myfile;
        stringstream ss;
        ss << c << "_files.txt";
        string fileName = ss.str();
        myfile.open(fileName);
        std:: string filename = ss.str();

        while ((dir = readdir(d)) != NULL)
        {
            string curFile = dir->d_name;

            if(curFile != "." && curFile != "..")
            {
                printf("%s\n", dir->d_name);
                myfile << dir->d_name << "\n";
            }
        }
        closedir(d);
    }

    return(0);
}
