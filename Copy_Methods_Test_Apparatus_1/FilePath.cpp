#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

class FilePath {
    string path;

public:
    FilePath();
    ~FilePath();
    FilePath(string pathString);
    void setPath(string pathString);
    string getPath();
    string getFileName();
};

FilePath::FilePath(){

}

FilePath::~FilePath(){

}

FilePath::FilePath(string pathString){

    this->path = pathString;
}

 void FilePath::setPath(string pathString){
    this->path = pathString;
}

string FilePath::getPath(){
    return this->path;
}

string FilePath::getFileName(){
    return "Not implemented";
}


//Use to test FilePath class
/*int main(){

    FilePath *testPath = new FilePath("E:/CAPSTONE_PROJECT/file-copy");

    cout << "File path: " << testPath->getPath() << endl;
    cout << "File name: " << testPath->getFileName() << endl;

    return 0;
}*/
