#include <iostream>
#include <list>
#include "tinythread.cpp"
//#include "fast_mutex.h"

using namespace std;
using namespace tthread;

//fast_mutex *numActiveThreads = new fast_mutex();
int numActiveThreads;
int MAX_THREADS;
int threadsLeft;

void testThread(void *aArg)
{
    int next,first,second = 0;

    for(int i = 0; i < 1000000; i++)
    {
        //Calc first 1000 fibonacci series
        if(i <= 1)
        {
            next = i;
        }
        else
        {
            next = first + second;
            first = second;
            second = next;
        }
    }

    //string *intPtr = static_cast<string*>(aArg);
    int *intPtr = static_cast<int*>(aArg);
    cout << "I am a thread, my name is " << *intPtr << endl;
    numActiveThreads--;
}

void threadTrackingThread(void *aArg)
{

}

void threadCreatorThread(void *aArg)
{
    bool running = true;

    while(running)
    {
        if(numActiveThreads < MAX_THREADS)
        {

        }
    }
}

int main()
{
    numActiveThreads = 0;
    MAX_THREADS = 5;
    threadsLeft = 100;

    list<thread *> threadList;

    /*string poo = "poo";
    void *voidStr = &poo;
    string doo = "doo";
    void *dooStr = &doo;
    thread t(testThread,voidStr);
    thread q(testThread,dooStr);

    t.detach();
    q.detach();
    */


    for(int i = 0; i < threadsLeft; i++)
    {
        //Check to see if number of threads is below max num of threads
        if(numActiveThreads < MAX_THREADS)
        {
            //Yes: Create thread, push_back onto threadList
            string poo = "poo";
            int j = i;
            void *voidInt = &j;
            void *voidStr = &poo;
            thread * t = new thread(testThread, voidInt);
            threadList.push_back(t);

            //Run through threads, join if done
            /*for(list<thread *>::iterator i = threadList.begin(); i != threadList.end(); ++ i)
            {
                thread * t = *i;
                t->join();
                delete t;
            }*/
        }
        else
        {
            //No: decrement i, wait a lil bit
            cout << "Too many threads" << endl;
            i--;
            Sleep(500);
        }
    }

    for(list<thread *>::iterator i = threadList.begin(); i != threadList.end(); ++ i)
    {
        thread * t = *i;
        if(t->joinable())
        {
            t->join();
            delete t;
        }
    }

    return 0;
}
