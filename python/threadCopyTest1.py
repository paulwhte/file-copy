import _thread
import time
import shutil

#Copy thread definition
def copy_file( filePath, dest, lock):
    try:
        shutil.copy(filePath, dest)
    except shutil.Error as e:
        print ("Error: %s, unable to copy file %s" % (e, filePath))
#end copy_file definition

if __name__ == '__main__':

    #Ask what the source will be
    SOURCES = ['C:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F1',
               'C:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F2',
               'C:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F3',
               'D:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F1',
               'D:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F3',
               'D:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F2',
               'E:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F1',
               'E:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F2',
               'E:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F3']

    DESTINATIONS = ['C:/CAPSTONE_PROJECT/output',
                    'D:/CAPSTONE_PROJECT/output',
                    'E:/CAPSTONE_PROJECT/output']

    SOURCE_DEST_CASES = [(0,0),(1,0),(2,0),(3,0),(4,0),(5,0),(6,0),(7,0),(8,0),(9,0),
                         (0,1),(1,1),(2,1),(3,1),(4,1),(5,1),(6,1),(7,1),(8,1),(9,1),
                         (0,2),(1,2),(2,2),(3,2),(4,2),(5,2),(6,2),(7,2),(8,2),(9,2)]

    sourceNum = int(input("Choose source: \n 1. C: F1 \n 2. C: F2 \n 3. C: F3 \n 4. D: F1 \n 5. D: F2 \n 6. D: F3 \n 7. E: F1 \n 8. E: F2 \n 9. E: F3 \n"))
    if sourceNum > 9 or sourceNum < 0:
        print("Error")
        exit()
    else:
        print("Your selection: %d" % sourceNum)
