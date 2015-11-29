import CopyTestCase

class CopyUtility:
    def __init__(self):
        #This will hold all output data 
        self.testCaseObjects = []
        self.sourceList = ['C:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F1',
                           'C:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F2',
                           'C:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F3',
                           'D:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F1',
                           'D:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F3',
                           'D:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F2',
                           'E:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F1',
                           'E:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F2',
                           'E:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F3']

        self.destinationList = ['C:/CAPSTONE_PROJECT/output',
                                'D:/CAPSTONE_PROJECT/output',
                                'E:/CAPSTONE_PROJECT/output']

        self.caseList = [(0,0),(1,0),(2,0),(3,0),(4,0),(5,0),(6,0),(7,0),(8,0),
                         (0,1),(1,1),(2,1),(3,1),(4,1),(5,1),(6,1),(7,1),(8,1),
                         (0,2),(1,2),(2,2),(3,2),(4,2),(5,2),(6,2),(7,2),(8,2),]

        self.numThreadsList = [1,2,4,8,16,32]

        #Change these from strings to methods l8r
        self.methodList = ['non_threaded_copy', 'threaded_copy', 'process_copy', 'pooled_threaded_copy', 'pooled_process_copy']

        self.beginAllTests()

    def beginAllTests(self):
        
        self.runAllTestCases()

    def runAllTestCases(self):
        totalNumberCases = 0
        
        for case in self.caseList:
            #Gather the source and destination for this bunch of test cases
            #sourceIndex = case[0]
            #destinationIndex = case[1]
            thisSource = self.sourceList[case[0]]
            thisDestination = self.destinationList[case[1]]
            #print("Source(%d): %s, Destination(%d): %s" % (sourceIndex, thisSource, destinationIndex, thisDestination))
            for method in self.methodList:
                thisMethod = method
                #Skip if the method is non_threaded_copy
                if(not(thisMethod == 'non_threaded_copy') and not (thisMethod == 'threaded_copy') and not (thisMethod == 'process_copy')):
                    for numThreads in self.numThreadsList:
                        totalNumberCases += 1
                        print("%d. Source: %s, Dest: %s, Method: %s, Threads: %d" % (totalNumberCases, thisSource, thisDestination, thisMethod, numThreads))
                        #Create test case
                        newCase = CopyTestCase.CopyTestCase(thisSource, thisDestination, "ass", thisMethod, numThreads, 0)
                        #Begin copy, it will return the total time
                        thisTime = newCase.beginCopy()
                        self.testCaseObjects.append(newCase)
                else:
                    totalNumberCases += 1
                    print("%d. Source: %s, Dest: %s, Method: %s, Threads: N/A" % (totalNumberCases, thisSource, thisDestination, thisMethod))
                    #Create test case
                    newCase = CopyTestCase.CopyTestCase(thisSource, thisDestination, "ass", thisMethod, 0, 0)
                    #Begin copy, it will return the total time
                    thisTime = newCase.beginCopy()
                    self.testCaseObjects.append(newCase)

        self.outputAllDataOnceDone()
    #End print out all test cases

    def outputAllDataOnceDone(self):
        #This is called at the very end of execution
        caseNum = 1
            #This assumes that the data is ordered as such:
            #   CopyTestCaseNum:int,Dataset:string,Method:string,Origin:string,Destination:string,NumThreads:int,Time(seconds):datetime,     IndividualTimes(microseconds):[(filename:string,time:datetime)...]
            #       No labels will be output (might output one file with labels)
            #       Semicolon will delimit individual test cases
            #       Comma will delimit different pieces of data in a test case
        with open("E:/CAPSTONE_PROJECT/output/No_Label_Output_File_%s.txt" % datetime.datetime.now().strftime("%m-%d-%y-%H-%M-%f"), "w") as noLabelOutputFile:
            with open("E:/CAPSTONE_PROJECT/output/Label_Output_File_%s.txt" % datetime.datetime.now().strftime("%m-%d-%y-%H-%M-%f"), "w") as labelOutputFile:
                for testCase in self.testCaseList:
                    exceptionString = ""
                    for ex in testCase.exceptionsRaised:
                        exceptionString += ex + "-"
                    #Output to both files
                    labeledLineString = "CopyTestCaseNum:%d,Dataset:%s,Method:%s,Origin:%s,Destination:%s,NumThreads:%d,Time(seconds):%s,Exceptions:%s \n" % (caseNum, testCase.dataset,testCase.Method,testCase.origin,testCase.destination,testCase.numThreads,testCase.totalCopyTime,exceptionString)
                    unlabeledLineString = "%d,%s,%s,%s,%s,%d,%s,%s \n" % (caseNum, testCase.dataset,testCase.Method,testCase.origin,testCase.destination,testCase.numThreads,testCase.totalCopyTime,exceptionString)
                    noLabelOutputFile.write(unlabeledLineString)
                    labelOutputFile.write(labeledLineString)
                    
                    caseNum += 1

        noLabelOutputFile.close()
        labelOutputFile.close()
        print("Output is written in E:/CAPSTONE_PROJECT/output")
        print("Done...")

if __name__ == '__main__':
    ass = CopyUtility()
