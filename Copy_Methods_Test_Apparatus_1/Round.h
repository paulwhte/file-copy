#include "TestCase.h"
#include <vector>

using std::vector;

class Round {

    vector<TestCase> testCaseObjects;
    vector<FilePath> datasets;
    vector<string> testCaseStrings;

public:
    Round();
    ~Round();
    void beginRound();
};
