import os
import matplotlib.pyplot as plt


def readLog(file):
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
        y.append(float(line.split(',')[13]).strip())

    timestamp = [t - timestamp[0] for t in timestamp]
    
    data.append(timestamp)
    data.append(yaw)
    data.append(yaw_raw)
    data.append(wind_dir)
    data.append(wind_dir_raw)
    data.append(true_wind_dir)
    data.append(wind_speed)

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
    plt.title('X vs Y')
    plt.xlabel('X (m)')
    plt.ylabel('Y (m)')

    plt.plot(data[12][:], data[13][:])
    plt.plot(data[12][0], data[13][0], 'ro', label='Start point')
    plt.plot(data[12][-1], data[13][-1], 'go', label='End point')

    for i, sat in enumerate(data[7][:]):
        if sat < 3:
            plt.plot(data[12][i], data[13][i], 'rx', label='Satellite lost')

    plt.legend()

    plt.savefig(f'logs/plots/{date}/{time}/xy.png')


def displayLog(file, date, time):
    data = readLog(file)

    output_dir = f'logs/plots/{date}/{time}'
    os.makedirs(output_dir, exist_ok=True)

    plotYaw(data, date, time)
    plotWindDir(data, date, time)
    plotWindSpeed(data, date, time)
    plotXY(data, date, time)

    plt.show()

    print('Log displayed and saved successfully')


if __name__ == '__main__':
    date = input('Enter the date of the log in the format DDMMYY: ')
    time = input('Enter the time of the log in the format HHMMSS: ')
    file = open(f'logs/{date}/{time}.txt', 'r')
    displayLog(file, date, time)
