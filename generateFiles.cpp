// Generating 10,000 txt files for copying purposes
// Inspiration for random char* generator here: http://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
using namespace std;

int main () {

    //0-61
    char alpha[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for(int i = 0; i < 10000; i++)
    {
      ofstream myfile;
      stringstream ss;
      ss << "F1_new/" << i << ".txt";
      std:: string filename = ss.str();
      //cout << filename << endl;
      const char* thisFilename = filename.c_str();
      myfile.open(thisFilename);
      for(int i = 0; i < 1024; i++)
      {
        int index = rand() % 61;
        myfile << alpha[index];
        //myfile << rand() % 10;
      }
      //cout << getRandomString() << endl;
      myfile.close();
    }

    /*for(int i = 0; i < 10; i++)
    {
        ofstream myfile;
        stringstream ss;
        ss << "F4/" << i << ".txt";
        std:: string filename = ss.str();
        //cout << filename << endl;
        const char* thisFilename = filename.c_str();
        myfile.open(thisFilename);
        for(int i = 0; i < 1024000; i++)
        {
            int index = rand() % 61;
            myfile << alpha[index];
            //myfile << rand() % 61;
        }
        //cout << getRandomString() << endl;
        myfile.close();
    }*/


  return 0;
}
