import CopyTestCase

class CopyUtility:
    def __init__(self):
        #This will hold all output data 
        self.testCaseList = []

    def outputAllDataOnceDone(self):
        #This is called at the very end of execution
        for testCase in self.testCaseList:
            #This assumes that the data is ordered as such:
            #   CopyTestCaseNum:int,Dataset:string,Origin:string,Destination:string,Time(seconds):datetime,IndividualTimes(microseconds):[(filename:string,time:datetime)...]
            #       No labels will be output (might output one file with labels)
            #       Semicolon will delimit individual test cases
            #       Comma will delimit different pieces of data in a test case
            print("butts")
