#include <sstream>
#include <chrono>

#include "TestCase.h"

using std::cerr;
using std::stringstream;

//const char *copyMethodStrings[] = {"openCopy","fopenCopy","streamCopy"};

TestCase::TestCase(){

}

TestCase::~TestCase(){

}

TestCase::TestCase(FilePath& _origin, FilePath& _destination, FilePath& _dataset, string _copyMethod, string _strategy, int _numThreads, int _bufferSize){
    //Construct test case, set member variables
    this->origin = _origin;
    this->destination = _destination;
    this->dataset = _dataset;
    this->copyMethod = _copyMethod;
    this->strategy = _strategy;
    this->numThreads = _numThreads;
    this->bufferSize = _bufferSize;
    this->totalTime = -1;
}

bool TestCase::beginCopy(){
    //Facilitate the beginning of a copy for a specific test case
    //For example: copy this.dataset from this.origin to this.destination with this.copyMethod

    //Check to make sure object initialized properly
    if(this->origin.getPath() == "" || this->destination.getPath() == "" || this->dataset.getPath() == "" || this->copyMethod == ""){
        cerr << "TestCase object was initialized incorrectly" << endl;
    }

    //Set beginning time
    clock_t startTime = clock();

    //Choose the correct copy operation based on this.copyMethod
    if(this->copyMethod == "openCopy"){
        this->doOpenCopy();
    }
    else if(this->copyMethod == "fopenCopy")
    {
        this->doFopenCopy();
    }
    else if(this->copyMethod == "streamCopy")
    {
        this->doStreamCopy();
    }

    //Set ending time
    clock_t endTime = clock();
    //Get time dif
    this->totalTime = difftime(endTime,startTime)/CLOCKS_PER_SEC;

    //Now that the copy is done, clear the output directory
    this->clearDirectory(this->destination);

    //Send success return value
    return true;
}

void TestCase::doOpenCopy(){
    cout << "Simulating open() copy" <<endl;
}

void TestCase::doFopenCopy(){
    cout << "Simulating fopen() copy" <<endl;
}

void TestCase::doStreamCopy(){
    cout << "Simulating stream copy" <<endl;
}

void TestCase::clearDirectory(FilePath directoryToClear){
    cout << "Simulating clearing " << directoryToClear.getPath() << "directory" <<endl;
}

string TestCase::printReport(){
    stringstream ss;

    ss << "Dataset: " << this->dataset.getPath() << endl;
    ss << "Origin: " << this->origin.getPath() << endl;
    ss << "Destination: " << this->destination.getPath() << endl;
    ss << "Method: " << this->copyMethod << endl;
    ss << "Number of Threads: " << this->numThreads << endl;
    ss << "Buffer Size: " << this->bufferSize << endl;
    ss << "Time (Seconds): " << this->totalTime << endl;

    return ss.str();
}

//Test TestCase
//int TestCaseTest()
/*int main()
{
    //FilePath *testPath1 = new FilePath("E:/CAPSTONE_PROJECT/");
    //FilePath *testPath2 = new FilePath("D:/CAPSTONE_PROJECT/");
    //FilePath *testPath3 = new FilePath("C:/CAPSTONE_PROJECT/");
    FilePath testPath1;
    testPath1.setPath("E:/CAPSTONE_PROJECT/");
    FilePath testPath2;
    testPath2.setPath("D:/CAPSTONE_PROJECT/");
    FilePath testPath3;
    testPath3.setPath("C:/CAPSTONE_PROJECT/");
    string thisCopyMethod(copyMethodStrings[OPENCOPY]);
    //TestCase *fakeTest = new TestCase(testPath1,testPath2,testPath3, thisCopyMethod, 1, 1024);

    //Fake the copy
    if(fakeTest->beginCopy())
    {
        cout << fakeTest->printReport();
    }

    return 0;
}*/
