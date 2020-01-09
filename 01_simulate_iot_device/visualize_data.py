'''
IoT Simplified
MIT License

Open the csv file and read the data.
'''
import csv
import matplotlib.pyplot as plt
import time

sound_level = []
time_stamp = []

while True:
    time.sleep(10)
    with open('sounddata.csv','r') as readFile:
        readFileReader = csv.reader(readFile)
        count = 0
        for row in readFileReader:
            
            if count > 1:
                sound_level.append(row[1])
                time_stamp.append(row[0])

            count+=1

    plt.plot(time_stamp,sound_level)
    
    plt.show()