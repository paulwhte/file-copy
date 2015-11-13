#include <sstream>
#include <chrono>

#include "tinythread.h"

#include "TestCase.h"

using std::cerr;
using std::stringstream;
using std::string;
using namespace tthread;

//const char *copyMethodStrings[] = {"openCopy","fopenCopy","streamCopy"};

TestCase::TestCase(){

}

TestCase::~TestCase(){

}

TestCase::TestCase(FilePath& _origin, FilePath& _destination, FilePath& _dataset, string _copyMethod, string _strategy, int _Max_Threads, int _bufferSize){
    //Construct test case, set member variables
    //_origin and _destination will come in as C,D, or E
    //Append :/CAPSTONE_PROJECT/CAPSTONE_DATASETS/ + _dataset to origin
    string originBase = _origin.getPath();
    string originFull = originBase + ":/CAPSTONE_PROJECT/CAPSTONE_DATASETS/" + _dataset.getPath();
    FilePath fullOriginPath;
    fullOriginPath.setPath(originFull);
    this->origin = fullOriginPath;
    //Append :/CAPSTONE_PROJECT/output to destination
    string destinationBase = _destination.getPath();
    string destinationFull = destinationBase + ":/CAPSTONE_PROJECT/output";
    FilePath fullDestinationPath;
    fullDestinationPath.setPath(destinationFull);
    this->destination = fullDestinationPath;
    //Dataset will come in as F1, F2, or F3
    this->dataset = _dataset;
    this->copyMethod = _copyMethod;
    this->strategy = _strategy;
    this->Max_Threads = _Max_Threads;
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
    else {
        cout << "Begin copy: " << this->origin.getPath() << " to " << this->destination.getPath() << ", Dataset: " << this->dataset.getPath() << endl;
    }

    //Set beginning time
    clock_t startTime = clock();

    //Choose the correct copy operation based on this.copyMethod and this.strategy
    if(this->strategy == "native")
    {
        if(this->copyMethod == "open"){
            this->doOpenCopy();
        }
        else if(this->copyMethod == "fopen"){
            this->doFopenCopy();
        }
        else if(this->copyMethod == "stream"){
            this->doStreamCopy();
        }
    }
    else if(this->strategy == "threaded")
    {
        if(this->copyMethod == "open"){
            this->doThreadedOpenCopy();
        }
        else if(this->copyMethod == "fopen"){
            this->doThreadedFopenCopy();
        }
        else if(this->copyMethod == "stream"){
            this->doThreadedStreamCopy();
        }
    }
    //Catch any unimplemented copy methods
    else{
        //Return false to indicate error
        return false;
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

void TestCase::doThreadedOpenCopy(){
    cout << "Simulating threaded open copy" << endl;
}

void TestCase::doThreadedFopenCopy(){
    cout << "Simulating threaded fopen copy" << endl;
}

void TestCase::doThreadedStreamCopy(){
    cout << "Simulating threaded stream copy" << endl;
}

void TestCase::clearDirectory(FilePath directoryToClear){
    cout << "Simulating clearing " << directoryToClear.getPath() << " directory" <<endl;
}

string TestCase::printReport(){
    stringstream ss;

    ss << "Dataset:" << this->dataset.getPath() << ",";
    ss << "Origin:" << this->origin.getPath() << ",";
    ss << "Destination:" << this->destination.getPath() << ",";
    ss << "Method:" << this->copyMethod << ",";
    ss << "Number of Threads:" << this->Max_Threads << ",";
    ss << "Buffer Size:" << this->bufferSize << ",";
    ss << "Time (Seconds):" << this->totalTime << ";";

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
