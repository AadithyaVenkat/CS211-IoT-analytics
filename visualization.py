import matplotlib.pyplot as plt

#Goal here is twofold: parse files and then visualize the output

# Class that just holds the network stats corresponding to a load time
class DataPoint:
    def __init__(self):
        self.rsrp = 0
        self.rsrq = 0
        self.sinr = 0
        self.rssi = 0
        self.load_time = 0

# name of the file to open
# Files from the long drive were drive_to_mullholland.txt and drive_home.txt
FILENAME = 'drive_to_mullholland.txt'

input_file = open(FILENAME, 'r')

# The timer for drive_home and drive_to_mullholland was broken because I didn't reset it
# in between runs. You can still get accurate times it just takes a little more work
last_timestamp = 0
if FILENAME == 'drive_home.txt':
    last_timestamp = 989.480591

current_rssi = 0

all_datapoints = []


# Go through each line in the log
for line in (input_file):

    #Once we see a loading time, we know we are at the end, create and save the datapoint
    if 'loading time: ' in line:
        #strip out the loading time and make a
        load_time_string = line.split("loading time: ",1)[1]
        load_timestamp = float(load_time_string)

        new_datapoint = DataPoint()

        # Comment out "-last_timestamp" if not using one of the broken logs
        new_datapoint.load_time = load_timestamp - last_timestamp
        new_datapoint.rssi = current_rssi
        all_datapoints.append(new_datapoint)
        last_timestamp = load_timestamp

    elif 'AT%MEAS=' in line and 'Signal Quality' in line:
        rssi_string_raw = line.split("RSSI = ",1)[1]
        # pull off the last space and the letters "OK"
        refined_rssi_string = rssi_string_raw[:-4]
        # print(refined_rssi_string)

        # One of the logs crashed and had 'N/A' returned, ignore that
        if (refined_rssi_string != 'N/A'):
            current_rssi = int(refined_rssi_string)


print('Number of Readings: ' + str(len(all_datapoints)))
# for x in all_datapoints:
#     print(x.load_time)
#     print(x.rssi)


# Plotting
all_load_times = []
all_rssi_values = []
for x in all_datapoints:
    all_load_times.append(x.load_time)
    all_rssi_values.append(x.rssi)
plt.scatter(all_rssi_values, all_load_times)
plt.show()
