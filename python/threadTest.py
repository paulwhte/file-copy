#!/usr/bin/python

import _thread
import time
from multiprocessing import Process, Lock
import shutil

#Call it directly or use it to start a thread
def copy_file( filePath , destinationPath, l):
   l.acquire()
   print("Thread begun")
   l.release()
   try:
      shutil.copy(filePath, destinationPath)
      l.acquire()
      print("Copy finised: %s to %s" % (filePath, destinationPath))
      l.release()
   except shutil.Error as e:
      l.acquire()
      print ("Error: %s" %e)
      print("Error: unable to copy file %s" % (filePath))
      l.release()


if __name__ == '__main__':
   numberOfActiveThreads = 0

   # Create two copy threads
   try:
      print("Attempting to start threads")
      lock = Lock()
      #filePath1 = "pickel_272KB.png"
      #filePath2 = "skullDownLeft_108KB.png"
      #destination = "output"
      filePath1 = "E:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F3/pickel_272KB.png"
      filePath2 = "E:/CAPSTONE_PROJECT/CAPSTONE_DATASETS/F3/skullDownLeft_108KB.png"
      destination = "E:/CAPSTONE_PROJECT/output"
      #_thread.start_new_thread( print_time, ("Thread-1", 2, ) )
      #_thread.start_new_thread( print_time, ("Thread-2", 4, ) )
      thread1 = Process(target=copy_file, args=(filePath1,destination, lock))
      thread2 = Process(target=copy_file, args=(filePath2,destination, lock))
      thread1.start()
      thread2.start()
      thread1.join()
      thread2.join()
   except shutil.Error as e:
      print ("Error: %s" %e)

   print ("End")
