#include <vector>
#include <tuple>
#include <iostream>

#include "TestCase.h"

using std::vector;
using std::tuple;
using std::cout;

class MainCopyTest {
public:
    vector <FilePath> datasets;
    vector <tuple<string,string>> sourceDests;
    vector <string> copyMethodList;
    vector <string> strategyList;
    vector <int> threadNum;
    vector <int> bufferSize;

    MainCopyTest();
    ~MainCopyTest();
    void beginTest();
};

MainCopyTest::MainCopyTest(){

}

MainCopyTest::~MainCopyTest(){

}

void MainCopyTest::beginTest(){
    //Cartesian product this extra efficiently
    int testCount = 1;

    for(std::vector<FilePath>::size_type i1 = 0; i1 != this->datasets.size(); i1++) {
        for(std::vector<tuple<string,string>>::size_type i2 = 0; i2 != this->sourceDests.size(); i2++) {
            for(std::vector<string>::size_type i3 = 0; i3 != this->copyMethodList.size(); i3++) {
                for(std::vector<string>::size_type i4 = 0; i4 != this->strategyList.size(); i4++) {
                    for(std::vector<int>::size_type i5 = 0; i5 != this->threadNum.size(); i5++) {
                        for(std::vector<int>::size_type i6 = 0; i6 != this->bufferSize.size(); i6++) {
                            //Set necessary variables
                            FilePath dataset = this->datasets[i1];
                            FilePath origin, destination;
                            origin.setPath(std::get<0>(this->sourceDests[i2]));
                            destination.setPath(std::get<1>(this->sourceDests[i2]));
                            string method = this->copyMethodList[i3];
                            string strategy = this->strategyList[i4];
                            //if strategy is native, no threading
                            int numThreads;
                            if(strategy != "native")
                            {
                                numThreads = this->threadNum[i5];
                            } else { numThreads = 0; }
                            //all copying will be buffered
                            int bufSize = this->bufferSize[i6];

                            //Create instance of TestCase
                            //TestCase *newTestCase = new TestCase(origin, destination, dataset, method, strategy, numThreads, bufSize);

                            cout << "Test " << testCount << endl;
                            cout << "    Dataset: " << this->datasets[i1].getPath() << endl;
                            cout << "    Source: " << std::get<0>(this->sourceDests[i2]) << ", Destination: " << std::get<1>(this->sourceDests[i2]) << endl;
                            cout << "    Method: " << this->copyMethodList[i3] << endl;
                            cout << "    Strategy: " << this->strategyList[i4] << endl;
                            cout << "    Number of threads: " << this->threadNum[i5] << endl;
                            cout << "    Buffer size: " << this->bufferSize[i6] << endl;
                            cout << endl;
                            testCount++;

                        }
                    }
                }
            }
        }

        //
    }
}

int main(){
    //Create mainCopyTest objects
    MainCopyTest *mainCopyTest = new MainCopyTest();

    //Populate datasets vector
    FilePath dataset1; // = new FilePath("F1");
    dataset1.setPath("F1");
    FilePath dataset2; // = new FilePath("F2");
    dataset2.setPath("F2");
    FilePath dataset3; // = new FilePath("F3");
    dataset3.setPath("F3");
    mainCopyTest->datasets.push_back(dataset1);
    mainCopyTest->datasets.push_back(dataset2);
    mainCopyTest->datasets.push_back(dataset3);

    //Populate source/destinations vector
    mainCopyTest->sourceDests.push_back(std::make_tuple("C","C"));
    mainCopyTest->sourceDests.push_back(std::make_tuple("D","D"));
    mainCopyTest->sourceDests.push_back(std::make_tuple("E","E"));
    mainCopyTest->sourceDests.push_back(std::make_tuple("C","D"));
    mainCopyTest->sourceDests.push_back(std::make_tuple("C","E"));
    mainCopyTest->sourceDests.push_back(std::make_tuple("D","C"));
    mainCopyTest->sourceDests.push_back(std::make_tuple("D","E"));
    mainCopyTest->sourceDests.push_back(std::make_tuple("E","C"));
    mainCopyTest->sourceDests.push_back(std::make_tuple("E","D"));

    //Populate copyMethodList
    mainCopyTest->copyMethodList.push_back("open");
    mainCopyTest->copyMethodList.push_back("fopen");
    mainCopyTest->copyMethodList.push_back("stream");

    //Populate strategyList
    mainCopyTest->strategyList.push_back("native");
    //mainCopyTest->strategy.push_back("threaded");
    //mainCopyTest->strategy.push_back("calcThreaded");
    //mainCopyTest->strategy.push_back("orderFiles");

    //Populate threadNum
    mainCopyTest->threadNum.push_back(5);
    mainCopyTest->threadNum.push_back(10);
    mainCopyTest->threadNum.push_back(20);
    mainCopyTest->threadNum.push_back(50);
    mainCopyTest->threadNum.push_back(100);

    //Populate bufferSize
    mainCopyTest->bufferSize.push_back(8192);
    mainCopyTest->bufferSize.push_back(2048);
    mainCopyTest->bufferSize.push_back(512);
    mainCopyTest->bufferSize.push_back(128);
    mainCopyTest->bufferSize.push_back(32);
    mainCopyTest->bufferSize.push_back(8);

    //Begin test
    mainCopyTest->beginTest();

    return 0;
}
