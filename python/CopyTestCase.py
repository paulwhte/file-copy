import datetime
import shutil
import os.path

class CopyTestCase:
    def __init__(self, _source, _destination, _dataset, _method, _numThreads, _bufferSize):
        self.source = _source
        self.destination = _destination
        self.dataset = _dataset
        self.method = _method
        self.totalCopyTime = 0
        self.indivFileCopyTimes = []

    #Run self.method, which will be non_threaded_copy, threaded_copy, process_copy,
    #    pooled_thread_copy, pooled_process_copy, or buffered_stream_copy
    def beginCopy(self):
        print("Begin copy")
        #Get the text file for the names of all the files in the dataset
        

        #return datetime.datetime.now()
        
    #End begin copy

    #This should return all the relevant data about this object once it's done with the copy
    def reportData(self):
        dataPacket = []
        return dataPacket
    #End reportData

    #Clear the directory after the copy is done
    def clearDirectory(self, path):
        try:
            shutil.rmtree( path )
            if not os.path.exists(path):
                os.makedirs(path)
        except shutil.Error as e:
            print("Error: %s, unable to delete files from directory %s" % (e, path))
    #End clearDirectory

    #Non threaded file copy, need datasetBasePath, destPath, and file to open
    def non_threaded_copy(self, datasetBasePath, destPath, filePathTextFile, lock):
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
    def threaded_copy(self, datasetBasePath, destPath, filePathTextFile, lock):
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
    def process_copy(self, datasetBasePath, destPath, filePathTextFile, lock):
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
    def pooled_threaded_copy(self, datasetBasePath, destPath, filePathTextFile, lock):
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
    def pooled_process_copy(self, datasetBasePath, destPath, filePathTextFile, lock):
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
    def buffered_stream_copy(self, datasetBasePath, destPath, filePathTextFile, lock):
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

        
            #Get end time
            end = datetime.datetime.now()
            #Return total time
            return end - start
        except:
            print("Some error occurred")
            exit()
