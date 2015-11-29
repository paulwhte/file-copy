import datetime

if __name__ == '__main__':
    with open("E:/CAPSTONE_PROJECT/output/No_Label_Output_File_%s.txt" % datetime.datetime.now().strftime("%m-%d-%y-%H-%M-%f"), "w") as noLabelOutputFile:
        noLabelOutputFile.write("asdf")
        noLabelOutputFile.close()
