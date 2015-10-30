#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <fstream>
#include <vector>
#include <stdio.h>
#include<stdlib.h>
#include <dirent.h>
#include <iterator>
#include <sys/stat.h>
#include <fcntl.h>

//http://stackoverflow.com/questions/11007494/how-to-delete-all-files-in-a-folder-but-not-delete-the-folder-c-linux

using namespace std;

void wipeDirectory(string directory)
{
    time_t start = time(0);

    while(time(0) < start + 1)
    {

    }
    //Wipe all the files in outputLocation
    DIR *theFolder = opendir(directory.c_str());
    struct dirent *next_file;
    char filepath[256];

    while ( (next_file = readdir(theFolder)) != NULL )
    {
        // build the path for each file in the folder
        sprintf(filepath, "%s/%s", directory.c_str(), next_file->d_name);
        //cout << "Removing: " << filepath << endl;
        remove(filepath);
    }
}

string doCopy(int dataset, int destination)
{
    string inputFilename;
    string inputDirectory;
    string outputLocation;

    string inputFilenameArray[]
        {
            "C:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F1_files.txt",
            "C:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F2_files.txt",
            "C:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F3_files.txt",
            "D:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F1_files.txt",
            "D:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F2_files.txt",
            "D:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F3_files.txt",
            "E:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F1_files.txt",
            "E:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F2_files.txt",
            "E:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F3_files.txt"
        };

    string inputDirectoryArray[]
        {
            "C:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F1",
            "C:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F2",
            "C:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F3",
            "D:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F1",
            "D:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F2",
            "D:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F3",
            "E:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F1",
            "E:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F2",
            "E:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F3"
        };

    string outputLocationArray[]
        {
            "C:/CAPSTONE_PROJECT/output",
            "D:/CAPSTONE_PROJECT/output",
            "E:/CAPSTONE_PROJECT/output"
        };

    cout << "You have chosen: " << inputFilenameArray[dataset-1] << endl;
    inputFilename = inputFilenameArray[dataset-1];
    inputDirectory = inputDirectoryArray[dataset-1];

    cout << "You have chosen: " << outputLocationArray[destination-1] << endl;
    outputLocation = outputLocationArray[destination-1];

    cout << "Choose buffer size: " << endl
         << "- 8192 bytes (default)" << endl
         << "- 4096 bytes" << endl
         << "- 1024 bytes" << endl
         << "- 16384 bytes" << endl;
    int bufferSize;
    cin >> bufferSize;

    //Begin timer
    time_t startTime = time(0);

    //Copy all the files in order they are in the txt file
    cout << endl << "Copying..." << endl << endl;
    string line;
    std:ifstream infile(inputFilename);
    while(std::getline(infile, line))
    {
        //cout << "Copying: " << line << endl;
        //line will be something like "file.txt"
        //inputFilename will not be used again
        //inputDirectory will be something like "C:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F1"
        //Take inputDirectory and concat line to get full filepath, then open it
        string thisFilePath = inputDirectory + "/" + line;
        string destFilePath = outputLocation + "/" + line;

        int input, output, oflags;
        oflags = O_CREAT | O_WRONLY | O_TRUNC;


        char buf[bufferSize];
        //size_t size;
        ssize_t size;
        mode_t fp;

        input = open(thisFilePath.c_str(), O_RDONLY);

        if(input == -1)
        {
            cout << "value was -1" << endl;
        }

        output = open(destFilePath.c_str(), oflags);

        while((size = read(input, buf, bufferSize)) > 0)
        {
            if(write(output, buf, size) != size)
            {
                cout <<"Buffer error";
            }
        }

        if(size == -1)
        {
            cout <<"Read error";
        }

        if(close(input) != 0)
        {
            cout <<"Input file close error";
        }
        if(close(output) != 0)
        {
            cout <<"Output file close error";
        }
    }

    cout << endl;
    //End the timer, record any data necessary
    time_t endTime = time(0);

    //cout << "Copy done, total time: " << endTime - startTime << " seconds" << endl << endl;

    string c;
    cout << "Wiping all files at " << outputLocation << endl;
    wipeDirectory(outputLocation);

    stringstream ss;

    ss << "\n" << dataset << "-" << destination << " completed\n";
    ss << "File source: " << inputDirectory << ", File destination: " << outputLocation << "\n";
    ss << "Total time: " << endTime - startTime << " seconds \n\n";
    //cout << "Copy done, total time: " << endTime - startTime << " seconds" << endl << endl;
    return ss.str();
}

void runManualMode()
{
    int outputFileNum;
    int inputFileNum;

    //Ask for what files will be copied
    cout<< "Choose the input files:" << endl
        << "1. F1 (many small) C: SSD" << endl
        << "2. F2 (few large) C: SSD" << endl
        << "3. F3 (mixed) C: SSD" << endl
        << "4. F1 (many small) D: Old disk 1TB" << endl
        << "5. F2 (few large) D: Old disk 1TB" << endl
        << "6. F3 (mixed) D: Old disk 1TB" << endl
        << "7. F1 (many small) E: New disk 1TB" << endl
        << "8. F2 (few large) E: New disk 1TB" << endl
        << "9. F3 (mixed) E: New disk 1TB" << endl;

    cout << "Make your selection: ";

    //Catch when it's not an int
    try
    {
        cin >> inputFileNum;
    }
    catch (...)
    {
        cout << "An exception has occurred (Probably didn't enter a number). Terminating..." << endl;
        //return 0;
    }
    //Catch out of bounds
    if(inputFileNum < 1 || inputFileNum > 9)
    {
        cout << "Input out of bounds" << endl;
        //return 0;
    }

    //cout << "You have chosen: " << inputFilenameArray[inputFileNum-1] << endl;
    //inputFilename = inputFilenameArray[inputFileNum-1];
    //inputDirectory = inputDirectoryArray[inputFileNum-1];

    //Ask for what the destination should be
    cout<< "Choose the output destination: " << endl
        << "1. C: SSD" << endl
        << "2. D: Old disk" << endl
        << "3. E: New disk" << endl
        << "Make your selection: ";

    //Catch when it's not an int
    try
    {
        cin >> outputFileNum;
    }
    catch (...)
    {
        cout << "An exception has occurred (Probably didn't enter a number). Terminating..." << endl;
        //return 0;
    }
    //Catch out of bounds
    if(outputFileNum < 1 || outputFileNum > 3)
    {
        cout << "Input out of bounds" << endl;
        //return 0;
    }

    //cout << "You have chosen: " << outputLocationArray[outputFileNum-1] << endl;
    //outputLocation = outputLocationArray[outputFileNum-1];

    string output = doCopy(inputFileNum, outputFileNum);

    cout << output;
} //End runManualMode

void runAutoMode()
{
    std::ifstream infile("../testCases.txt");

    int a,b;
    string copyResult;
    vector<string> copyResultsArray;
    while(infile >> a >> b)
    {
        for(int i = 0; i < 3; i++)
        {
            //Do the copy and get the output string
            copyResult = doCopy(a,b);
            //Push it into the output vector
            copyResultsArray.push_back(copyResult);
        }
    }

    //Output all the data
    std::ofstream output_file("openCopyResults.txt");
    std::ostream_iterator<std::string> output_iterator(output_file, "\n");
    std::copy(copyResultsArray.begin(), copyResultsArray.end(), output_iterator);

} //End runAutoMode

int main ()
{
    //CIN exception stuff
    std::cin.exceptions(std::istream::failbit);

    //Timing stuff
    //time_t startTime = time(0);
    //time_t endTime = time(0);

    int opMode;
    //Ask if manual or automatic copy
    cout<< "Choose operation mode:" << endl
        << "1. Run all test cases." << endl
        << "2. Manual operation" << endl
        << "Enter choice: ";

    try
    {
        cin >> opMode;
    }
    catch (...)
    {
        cout << "An exception has occurred (Probably didn't enter a number). Terminating..." << endl;
        return 0;
    }

    if(opMode == 1)
    {
        runAutoMode();
    }
    else if(opMode == 2)
    {
        runManualMode();
    }

    cout<<"End of program, terminating...";
    return 0;
}




