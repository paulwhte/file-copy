#import _thread
from threading import Thread
import time
import datetime
from multiprocessing import Process, Lock
import shutil
import os
import concurrent.futures

#Copy thread definition
def copy_file( filePath, dest, lock):
    try:
        shutil.copy(filePath, dest)
    except shutil.Error as e:
        print ("Error: %s, unable to copy file %s" % (e, filePath))
#end copy_file definition

#Clear directory definition
def clear_Dir( path ):
    try:
        shutil.rmtree( path )
        if not os.path.exists(path):
            os.makedirs(path)
    except shutil.Error as e:
        print("Error: %s, unable to delete files from directory %s" % (e, path))

#Non threaded file copy, need datasetBasePath, destPath, and file to open
def non_threaded_copy(datasetBasePath, destPath, filePathTextFile, lock):
    input("%s %s %s" %(datasetBasePath, destPath, filePathTextFile))
    #Get start time
    start = datetime.datetime.now()
    
    try:
        with open(filePathTextFile) as file:
            for line in file:
                fullFilePath = datasetBasePath + "/" + line
                fullFilePath = "\n".join(fullFilePath.split())
                copy_file(fullFilePath, destPath, lock)
        #Get end time
        end = datetime.datetime.now()
        #Return total time
        return end - start
    except:
        print("Some error occurred")
        exit()
#End non threaded copy

#Threaded file copy, need datasetBasePath, destPath, and file to open
def threaded_copy(datasetBasePath, destPath, filePathTextFile, lock):
    #Get start time
    start = datetime.datetime.now()

    try:
        #Open the file
        with open(filePathTextFile) as file:
            #Read line by line
            for line in file:
                #line is a string containing the filename
                fullFilePath = datasetBasePath + "/" + line
                fullFilePath = "\n".join(fullFilePath.split())
                #print("Starting copy on: %s" % (fullFilePath))
                #Fire off thread
                #thread_Array.append(_thread.start_new_thread(copy_file, (fullFilePath, destPath, lock)))
                thread = Thread(target=copy_file, args=(fullFilePath, destPath, lock))
                thread.start()
                thread_Array.append(thread)

        #Join all threads
        for thread in thread_Array:
            thread.join()

        #Get end time
        end = datetime.datetime.now()
        #Return total time
        return end - start
    except:
        print("Some error occurred")
        exit()
#End threaded copy

#Process copy, should use more than one core
def process_copy(datasetBasePath, destPath, filePathTextFile, lock):
    #Get start time
    start = datetime.datetime.now()

    try:
        #Open the file
        with open(filePathTextFile) as file:
            #Read line by line
            for line in file:
                #line is a string containing the filename
                fullFilePath = datasetBasePath + "/" + line
                fullFilePath = "\n".join(fullFilePath.split())
                #Fire off process
                thread = Process(target=copy_file, args=(fullFilePath, destPath, lock))
                thread.start()
                thread_Array.append(thread)

        #Join all threads
        for thread in thread_Array:
            thread.join()

        #Get end time
        end = datetime.datetime.now()
        #Return total time
        return end - start
    except:
        print("Some error occurred")
        exit()

#Pooled threads one core
def pooled_threaded_copy(datasetBasePath, destPath, filePathTextFile, lock):
    try:
        #Ask how many threads
        numThreads = int(input("How many threads? "))

        #Get start time
        start = datetime.datetime.now()

        filenameArray = []

        #Open the file, save filenames to array
        with open(filePathTextFile) as file:
            for line in file:
                fullFilePath = datasetBasePath + "/" + line
                fullFilePath = "\n".join(fullFilePath.split())
                filenameArray.append(fullFilePath)

        with concurrent.futures.ThreadPoolExecutor(max_workers=numThreads) as executor:
            for filePath in filenameArray:
                executor.submit(copy_file, (fullFilePath, destPath, lock))

    
        #Get end time
        end = datetime.datetime.now()
        #Return total time
        return end - start
    except:
        print("Some error occurred")
        exit()

#Pooled processes multiple cores
def pooled_process_copy(datasetBasePath, destPath, filePathTextFile, lock):
    try:
        #Ask how many threads
        numThreads = int(input("How many threads? "))

        #Get start time
        start = datetime.datetime.now()

        filenameArray = []

        #Open the file, save filenames to array
        with open(filePathTextFile) as file:
            for line in file:
                fullFilePath = datasetBasePath + "/" + line
                fullFilePath = "\n".join(fullFilePath.split())
                filenameArray.append(fullFilePath)

        with concurrent.futures.ProcessPoolExecutor(max_workers=numThreads) as executor:
            for filePath in filenameArray:
                executor.submit(copy_file, (fullFilePath, destPath, None))

    
        #Get end time
        end = datetime.datetime.now()
        #Return total time
        return end - start
    except:
        print("Some error occurred")
        exit()

#Buffered stream copy
def buffered_stream_copy(datasetBasePath, destPath, filePathTextFile, lock):
    try:
        #Ask how many threads
        numThreads = int(input("How many threads? "))

        #Get start time
        start = datetime.datetime.now()

        filenameArray = []

        #Open the file, save filenames to array
        with open(filePathTextFile) as file:
            for line in file:
                fullFilePath = datasetBasePath + "/" + line
                fullFilePath = "\n".join(fullFilePath.split())
                filenameArray.append(fullFilePath)

        for filePath in filenameArray:
            #Open the source file
            #sourceFileObj = open(filePath, 'r')
            #Open the destination file
            fileBasename = os.path.basename(filePath)
            destFilePath = destPath + "/" + fileBasename
            #print(destFilePath)
            #destFileObj = open(destFilePath, 'w+')
            #destFileObj.write(sourceFileObj)

            #Open the source file and read it into the destination file
            #with open(filePath, 'r') as sourceFileObj, open(destFilePath, 'w+') as destFileObj:
                #for line in sourceFileObj:
                    #destFileObj.write(line)
            
            #Close the destination file
            #destFileObj.close()
    
        #Get end time
        end = datetime.datetime.now()
        #Return total time
        return end - start
    except OSError as e:
        print("Some error occurred %s" % e)
        exit()


if __name__ == '__main__':

    #
    SOURCES = ['C:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F1',
               'C:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F2',
               'C:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F3',
               'D:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F1',
               'D:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F3',
               'D:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F2',
               'E:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F1',
               'E:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F2',
               'E:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F3']

    #
    DESTINATIONS = ['C:/CAPSTONE_PROJECT/output',
                    'D:/CAPSTONE_PROJECT/output',
                    'E:/CAPSTONE_PROJECT/output']

    #Tuples are SOURCES and DESTINATIONS indexes
    SOURCE_DEST_CASES = [(0,0),(1,0),(2,0),(3,0),(4,0),(5,0),(6,0),(7,0),(8,0),(9,0),
                         (0,1),(1,1),(2,1),(3,1),(4,1),(5,1),(6,1),(7,1),(8,1),(9,1),
                         (0,2),(1,2),(2,2),(3,2),(4,2),(5,2),(6,2),(7,2),(8,2),(9,2)]

    #This will only be used
    NUMTHREADS = [1,2,4,8,16,32]

    #Lock for if I need it
    lock = Lock()

    #Get the source that you want
    sourceNum = int(input("Choose source: \n 1. C: F1 \n 2. C: F2 \n 3. C: F3 \n 4. D: F1 \n 5. D: F2 \n 6. D: F3 \n 7. E: F1 \n 8. E: F2 \n 9. E: F3 \n"))
    if sourceNum > 9 or sourceNum < 1:
        print("Error")
        exit()
    else:
        print("Your selection: %d" % sourceNum)

    #Get the destination that you want
    destNum = int(input("Choose destination: \n 1. C: \n 2. D: \n 3. E: \n"))
    if destNum > 3 or destNum < 1:
        print("Error")
        exit()
    else:
        print("Your selection: %d" % destNum)

    #Decrement bc of array indexes
    sourceNum = sourceNum - 1
    destNum = destNum -1
    print("Will do copy from %s to %s" %(SOURCES[sourceNum],DESTINATIONS[destNum]))

    #Array to keep track of threads
    thread_Array = []

    #Now must read in the file at this filepath bc it has all the filenames
    datasetBasePath = SOURCES[sourceNum]
    filePathTextFile = datasetBasePath + "_files.txt"
    #Set destPath
    destPath = DESTINATIONS[destNum]

    #Ask what type of copy to do
    # 1. Not threaded
    # 2. Threaded
    # 3. Processes
    # 4. Pooled threads
    # 5. Pooled process
    # 6. Buffered stream (no threading, load whole files into buffer)
    copyType = int(input("What type of copy do you want to do? \n 1. Non-threaded \n 2. Threads \n 3. Processes (use multiple cores) \n 4. Pooled threads \n 5. Pooled processes \n 6. Buffered Stream (no thread, whole file) \n"))
    if copyType == 1:
        timeTaken = non_threaded_copy(datasetBasePath, destPath, filePathTextFile, lock)
        
    elif copyType == 2:
        timeTaken = threaded_copy(datasetBasePath, destPath, filePathTextFile, lock)
        
    elif copyType == 3:
        timeTaken = process_copy(datasetBasePath, destPath, filePathTextFile, lock)

    elif copyType == 4:
        timeTaken = pooled_threaded_copy(datasetBasePath, destPath, filePathTextFile, lock)

    elif copyType == 5:
        timeTaken = pooled_process_copy(datasetBasePath, destPath, filePathTextFile, lock)

    elif copyType == 6:
        timeTaken = buffered_stream_copy(datasetBasePath, destPath, filePathTextFile, lock)
        
    else:
        print("Error")
        exit()

    print("Done. Time %f microseconds" % (timeTaken.microseconds))

    print("Clearing files")
    clear_Dir(destPath)
    
    print("Number of threads: %d" % len(thread_Array))
            
