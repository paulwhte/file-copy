import CopyTestCase

class CopyUtility:
    def __init__(self):
        #This will hold all output data 
        self.testCaseList = []
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
        self.printOutAllTestCases()

    def printOutAllTestCases(self):
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
                if(not(thisMethod == 'non_threaded_copy')):
                    for numThreads in self.numThreadsList:
                        totalNumberCases += 1
                        print("%d. Source: %s, Dest: %s, Method: %s, Threads: %d" % (totalNumberCases, thisSource, thisDestination, thisMethod, numThreads))
                else:
                    totalNumberCases += 1
                    print("%d. Source: %s, Dest: %s, Method: %s, Threads: N/A" % (totalNumberCases, thisSource, thisDestination, thisMethod))
                        
        

    def outputAllDataOnceDone(self):
        #This is called at the very end of execution
        for testCase in self.testCaseList:
            #This assumes that the data is ordered as such:
            #   CopyTestCaseNum:int,Dataset:string,Origin:string,Destination:string,Time(seconds):datetime,IndividualTimes(microseconds):[(filename:string,time:datetime)...]
            #       No labels will be output (might output one file with labels)
            #       Semicolon will delimit individual test cases
            #       Comma will delimit different pieces of data in a test case
            print("butts")

if __name__ == '__main__':
    ass = CopyUtility()
