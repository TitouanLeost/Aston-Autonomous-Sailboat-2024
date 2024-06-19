import os
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches


def readLog(file):
    ######################################
    ########## Initialize lists ##########
    ######################################
    data = []
    timestamp = []
    yaw = []
    yaw_raw = []
    wind_dir = []
    wind_dir_raw = []
    true_wind_dir = []
    wind_speed = []
    satellites = []
    course = []
    speed = []
    lat = []
    lon = []
    x = []
    y = []
    rudder_cmd = []
    sail_cmd = []
    rc_status = []
    wp = []


    ######################################
    ########### Read the file ############
    ######################################
    file.readline()
    file.readline()

    line = file.readline()
    nb_wp, wp_radius = line.split(',')

    file.readline()

    for i in range(int(nb_wp)):
        line = file.readline()
        wp.append((float(line.split(',')[0]), float(line.split(',')[1])))

    file.readline()

    for line in file:
        if line == 'END':
            break

        timestamp.append(int(line.split(',')[0])/1000)
        yaw.append(float(line.split(',')[1]))
        yaw_raw.append(float(line.split(',')[2]))
        wind_dir.append(float(line.split(',')[3]))
        wind_dir_raw.append(float(line.split(',')[4]))
        true_wind_dir.append(float(line.split(',')[5]))
        wind_speed.append(float(line.split(',')[6]))
        satellites.append(int(line.split(',')[7]))
        course.append(float(line.split(',')[8]))
        speed.append(float(line.split(',')[9]))
        lat.append(float(line.split(',')[10]))
        lon.append(float(line.split(',')[11]))
        x.append(float(line.split(',')[12]))
        y.append(float(line.split(',')[13]))
        rudder_cmd.append(float(line.split(',')[14]))
        sail_cmd.append(float(line.split(',')[15]))
        rc_status.append(int(line.split(',')[16]))

    timestamp = [t - timestamp[0] for t in timestamp]
    
    data.append(timestamp)
    data.append(yaw)
    data.append(yaw_raw)
    data.append(wind_dir)
    data.append(wind_dir_raw)
    data.append(true_wind_dir)
    data.append(wind_speed)
    data.append(satellites)
    data.append(course)
    data.append(speed)
    data.append(lat)
    data.append(lon)
    data.append(x)
    data.append(y)
    data.append(rudder_cmd)
    data.append(sail_cmd)
    data.append(rc_status)
    data.append(wp)
    data.append(nb_wp)
    data.append(wp_radius)

    return data


def plotYaw(data, date, time):
    plt.figure('yaw')
    plt.title('Yaw vs Time')
    plt.xlabel('Time (s)')
    plt.ylabel('Yaw (°)')
    plt.grid()

    plt.plot(data[0][:], data[2][:], label='Yaw raw')
    plt.plot(data[0][:], data[1][:], label='Yaw filtered')
    plt.plot(data[0][:], data[8][:], label='GPS Course')

    plt.legend()

    plt.savefig(f'logs/plots/{date}/{time}/yaw.png')


def plotWindDir(data, date, time):
    plt.figure('wind_dir')
    plt.title('Wind Direction vs Time')
    plt.xlabel('Time (s)')
    plt.ylabel('Wind Direction (°)')
    plt.grid()

    plt.plot(data[0][:], data[4][:], label='Wind Direction raw')
    plt.plot(data[0][:], data[3][:], label='Wind Direction filtered')
    plt.plot(data[0][:], data[5][:], label='True Wind Direction')

    plt.legend()

    plt.savefig(f'logs/plots/{date}/{time}/wind_dir.png')


def plotWindSpeed(data, date, time):
    plt.figure('wind_speed')
    plt.title('Wind Speed vs Time')
    plt.xlabel('Time (s)')
    plt.ylabel('Wind Speed (kph)')
    plt.grid()

    plt.plot(data[0][:], data[6][:])

    plt.savefig(f'logs/plots/{date}/{time}/wind_speed.png')


def plotXY(data, date, time):
    plt.figure('xy')
    plt.title('Boat Path')
    plt.xlabel('X (m)')
    plt.ylabel('Y (m)')

    val = data[16][0]
    indice = 0
    label_added = 0
    colors = ['blue', 'magenta']
    labels = ['Boat Path', 'RC Mode']
    linestyles = ['-', '--']
    for i, status in enumerate(data[16]):
        if status != val:
            plt.plot(data[12][indice:i+1], data[13][indice:i+1], color=colors[val], ls=linestyles[val], label=labels[val] if label_added <= 1 else None)
            val = status
            indice = i
            label_added += 1

    # Plot the remaining data (useful if status doesn't change)
    plt.plot(data[12][indice:], data[13][indice:], color=colors[val], ls=linestyles[val], label=labels[val] if label_added <= 1 else None)

    label_added = False
    for i, sat in enumerate(data[7][:]):
        if sat < 3:
            if not label_added:
                plt.plot(data[12][i], data[13][i], 'rx', label='Satellite lost')
                label_added = True
            else:
                plt.plot(data[12][i], data[13][i], 'rx')

    wp_list = data[17]
    nb_wp = int(data[18])
    wp_radius = float(data[19])
    for i in range(nb_wp):
        x, y = latLonToXY(wp_list[i][0], wp_list[i][1])
        plt.plot(x, y, 'yo')
        circle = patches.Circle((x, y), wp_radius, fill=False)
        plt.gca().add_patch(circle)

    plt.legend()

    plt.savefig(f'logs/plots/{date}/{time}/xy.png')


def plotCmd(data, date, time):
    plt.figure('cmd')
    plt.title('Servomotors Commands')
    plt.xlabel('Time (s)')
    plt.ylabel('Command (%)')
    plt.grid()

    val = data[16][0]
    indice = 0
    label_added = 0
    colors = ['blue', 'magenta', 'orange', 'pink']
    labels = ['Rudder Command', 'RC Mode', 'Sail Command', 'RC Mode']
    linestyles = ['-', '--']
    for i, status in enumerate(data[16]):
        if status != val:
            plt.plot(data[0][indice:i+1], data[14][indice:i+1], color=colors[val], ls=linestyles[val], label=labels[val] if label_added <= 1 else None)
            plt.plot(data[0][indice:i+1], data[15][indice:i+1], color=colors[val+2], ls=linestyles[val], label=labels[val+2] if label_added <= 1 else None)
            val = status
            indice = i
            label_added += 1

    # Plot the remaining data (useful if status doesn't change)
    plt.plot(data[0][indice:], data[14][indice:], color=colors[val], ls=linestyles[val], label=labels[val] if label_added <= 1 else None)
    plt.plot(data[0][indice:], data[15][indice:], color=colors[val+2], ls=linestyles[val], label=labels[val+2] if label_added <= 1 else None)

    label_added = False
    for i, sat in enumerate(data[7][:]):
        if sat < 3:
            if not label_added:
                plt.plot(data[0][i], data[14][i], 'rx', label='Satellite lost')
                plt.plot(data[0][i], data[15][i], 'rx')
                label_added = True
            else:
                plt.plot(data[0][i], data[14][i], 'rx')
                plt.plot(data[0][i], data[15][i], 'rx')

    plt.legend()

    plt.savefig(f'logs/plots/{date}/{time}/cmd.png')


def displayLog(file, date, time):
    data = readLog(file)

    output_dir = f'logs/plots/{date}/{time}'
    os.makedirs(output_dir, exist_ok=True)

    plotYaw(data, date, time)
    plotWindDir(data, date, time)
    plotWindSpeed(data, date, time)
    plotXY(data, date, time)
    plotCmd(data, date, time)

    plt.show()

    print('Log displayed and saved successfully')


def latLonToXY(lat, lon):
    REF_LAT = 52.486252
    REF_LON = -1.889658
    EARTH_RADIUS = 6371000

    if lat == 99999 or lon == 99999:
        return 0, 0

    x = EARTH_RADIUS * np.cos(lat*np.pi/180) * (lon - REF_LON) * np.pi/180
    y = EARTH_RADIUS * (lat - REF_LAT) * np.pi/180

    return x, y


if __name__ == '__main__':
    date = input('Enter the date of the log in the format DDMMYY: ')
    time = input('Enter the time of the log in the format HHMMSS: ')
    file = open(f'logs/{date}/{time}.txt', 'r')
    displayLog(file, date, time)
