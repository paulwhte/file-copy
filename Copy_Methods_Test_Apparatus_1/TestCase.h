#include <string>
#include <time.h> //For: clock, clock_t, CLOCKS_PER_SEC

#include "FilePath.cpp"

enum CopyMethods {OPENCOPY = 0, FOPENCOPY, STREAMCOPY};

class TestCase {
    FilePath origin;
    FilePath destination;
    FilePath dataset;
    string copyMethod;
    string strategy;
    int numThreads;
    int bufferSize;
    double totalTime;

public:
    TestCase(FilePath& _origin, FilePath& _destination, FilePath& _dataset, string _copyMethod, string _strategy, int _numThreads, int _bufferSize);

    bool beginCopy(); // will return 1 if success, 0 if error

    void doOpenCopy();
    void doFopenCopy();
    void doStreamCopy();

    void clearDirectory(FilePath directoryToClear);

    string printReport(); //return a formatted string with results of this test case, as well as all input parameters
};
