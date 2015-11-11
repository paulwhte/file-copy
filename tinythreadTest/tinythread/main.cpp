#include <iostream>
#include "tinythread.cpp"

using namespace std;
using namespace tthread;

void testThread(void *aArg)
{
    string *intPtr = static_cast<string*>(aArg);
    cout << "I am a thread, my name is " << *intPtr << endl;
}

int main()
{
    string poo = "poo";
    void *voidStr = &poo;
    string doo = "doo";
    void *dooStr = &doo;
    thread t(testThread,voidStr);
    thread q(testThread,dooStr);

    t.join();
    q.join();

    return 0;
}
