import os
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib.animation as animation 
from matplotlib.legend_handler import HandlerPatch


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
    ref = []
    wp = []


    ######################################
    ########### Read the file ############
    ######################################
    file.readline()
    file.readline()

    line = file.readline()
    ref.append(float(line.split(',')[0]))
    ref.append(float(line.split(',')[1]))

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

    for i in range(int(nb_wp)):
        wp_x, wp_y = latLonToXY(wp[i][0], wp[i][1], ref)
        wp[i] = (wp_x, wp_y)


    ######################################
    ########### Save the data ############
    ######################################

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
    data.append(ref)
    data.append(wp)
    data.append(nb_wp)
    data.append(wp_radius)

    return data


def latLonToXY(lat, lon, ref):
    REF_LAT = ref[0]
    REF_LON = ref[1]
    EARTH_RADIUS = 6371000

    if lat == 99999 or lon == 99999:
        return 0, 0

    x = EARTH_RADIUS * np.cos(lat*np.pi/180) * (lon - REF_LON) * np.pi/180
    y = EARTH_RADIUS * (lat - REF_LAT) * np.pi/180

    return x, y


def plot_segments(x, y, label, color, ls='-', lw=1.5):
    y_segments = np.split(y, np.where(np.abs(np.diff(y)) > 250)[0] + 1)
    x_segments = np.split(x, np.where(np.abs(np.diff(y)) > 250)[0] + 1)
    for i, (xs, ys) in enumerate(zip(x_segments, y_segments)):
        plt.plot(xs, ys, c=color, ls=ls, lw=lw, label=label)
        label = None
        if i < len(x_segments) - 1:
            plt.plot([x_segments[i][-1], x_segments[i+1][0]], [y_segments[i][-1], y_segments[i+1][0]], c=color, ls=ls, lw=lw, alpha=0.2)


def plotYaw(data, date, time):
    plt.figure('yaw', figsize=(16, 9), dpi=100)
    plt.title('Yaw vs Time')
    plt.xlabel('Time (s)')
    plt.ylabel('Yaw (°)')
    plt.grid()

    plt.axhline(y=360, color='grey', ls=(0, (7, 3)))
    plt.axhline(y=0, color='grey', ls=(0, (7, 3)))
    plot_segments(data[0][:], data[2][:], 'Yaw raw', '#1f77b4')
    plot_segments(data[0][:], data[1][:], 'Yaw filtered', '#ff7f0e')
    plot_segments(data[0][:], data[8][:], 'GPS Course', '#2ca02c', ls='-.', lw=2)

    plt.legend()

    plt.savefig(f'logs/plots/{date}/{time}/yaw.svg')


def plotWindDir(data, date, time):
    plt.figure('wind_dir', figsize=(16, 9), dpi=100)
    plt.title('Wind Direction vs Time')
    plt.xlabel('Time (s)')
    plt.ylabel('Wind Direction (°)')
    plt.grid()

    plt.axhline(y=360, color='grey', linestyle=(0, (7, 3)))
    plt.axhline(y=0, color='grey', linestyle=(0, (7, 3)))
    plot_segments(data[0][:], data[4][:], 'Wind Direction raw', '#1f77b4')
    plot_segments(data[0][:], data[3][:], 'Wind Direction filtered', '#ff7f0e')
    plot_segments(data[0][:], data[5][:], 'True Wind Direction', '#2ca02c', ls='-.', lw=2)

    plt.legend()

    plt.savefig(f'logs/plots/{date}/{time}/wind_dir.svg')


def plotWindSpeed(data, date, time):
    plt.figure('wind_speed',  figsize=(16, 9), dpi=100)
    plt.title('Wind Speed vs Time')
    plt.xlabel('Time (s)')
    plt.ylabel('Wind Speed (km/h)')
    plt.grid()

    plt.plot(data[0][:], data[6][:])

    plt.savefig(f'logs/plots/{date}/{time}/wind_speed.svg')


def plotBoatSpeed(data, date, time):
    plt.figure('boat_speed',  figsize=(16, 9), dpi=100)
    plt.title('Boat Speed vs Time')
    plt.xlabel('Time (s)')
    plt.ylabel('Boat Speed (km/h)')
    plt.grid()

    plt.plot(data[0][:], data[9][:])

    plt.savefig(f'logs/plots/{date}/{time}/boat_speed.svg')


def plotXY(data, date, time):
    plt.figure('xy', figsize=(16, 9), dpi=100)
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

    # Plot the starting position
    plt.plot(data[12][0], data[13][0], 'go', label='Starting position')

    # Waypoints display
    wp_list = data[18]
    nb_wp = int(data[19])
    wp_radius = float(data[20])

    for i in range(nb_wp):
        plt.plot(wp_list[i][0], wp_list[i][1], 'yo')
        circle = patches.Circle((wp_list[i][0], wp_list[i][1]), wp_radius, fill=False)
        plt.gca().add_patch(circle)
        if i > 0:
            plt.plot([wp_list[i-1][0], wp_list[i][0]], [wp_list[i-1][1], wp_list[i][1]], 'g')
        else:
            plt.plot([data[12][0], wp_list[i][0]], [data[13][0], wp_list[i][1]], 'g')

    label_added = False
    gnss_lost = []
    last_index = -10
    for i, sat in enumerate(data[7][:]):
        if sat < 4:
            if i != last_index + 1:
                gnss_lost.append([])
            gnss_lost[-1].append(i)
            last_index = i

    for sublist in gnss_lost:
        plt.plot(data[12][sublist[0]], data[13][sublist[0]], 'rx')
        plt.plot(data[12][sublist[-1]], data[13][sublist[-1]], 'rx')
        plt.plot([data[12][i] for i in sublist], [data[13][i] for i in sublist], 'r', lw=2, label='GNSS lost' if not label_added else None)
        label_added = True

    plt.gca().set_aspect('equal', adjustable='box')

    plt.legend(loc='best')

    plt.savefig(f'logs/plots/{date}/{time}/xy.svg')


def plotCmd(data, date, time):
    plt.figure('cmd',  figsize=(16, 9), dpi=100)
    plt.title('Servomotors Commands')
    plt.xlabel('Time (s)')
    plt.ylabel('Command (%)')
    plt.grid()

    plt.axhline(y=1, color='grey', linestyle=(0, (7, 3)))
    plt.axhline(y=0, color='grey', linestyle=(0, (7, 3)))

    val = data[16][0]
    indice = 0
    label_added = 0
    colors = ['blue', 'magenta', 'orange', 'magenta']
    labels = ['Rudder Command', 'RC Mode', 'Sail Command', 'RC Mode']
    linestyles = ['-', '-.', (0, (10, 3)), '-.']
    for i, status in enumerate(data[16]):
        if status != val:
            plt.plot(data[0][indice:i+1], data[14][indice:i+1], color=colors[val], ls=linestyles[val], label=labels[val] if label_added <= 1 else None)
            plt.plot(data[0][indice:i+1], data[15][indice:i+1], color=colors[val+2], ls=linestyles[val+2], label=labels[val+2] if (label_added <= 1 and status != 0) else None)
            val = status
            indice = i
            label_added += 1

    # Plot the remaining data (useful if status doesn't change)
    plt.plot(data[0][indice:], data[14][indice:], color=colors[val], ls=linestyles[val], label=labels[val] if label_added <= 1 else None)
    plt.plot(data[0][indice:], data[15][indice:], color=colors[val+2], ls=linestyles[val+2], label=labels[val+2] if label_added <= 1 else None)

    label_added = False
    gnss_loss = []
    last_index = -10
    for i, sat in enumerate(data[7][:]):
        if sat < 4:
            if i != last_index + 1:
                gnss_loss.append([])
            gnss_loss[-1].append(i)
            last_index = i

    for sublist in gnss_loss:
        plt.axvspan(data[0][sublist[0]], data[0][sublist[-1]], color='red', alpha=0.2, label='GNSS lost' if not label_added else None)
        label_added = True

    plt.legend()

    plt.savefig(f'logs/plots/{date}/{time}/cmd.svg')


def createVid(data, date, time):
    x = data[12]
    y = data[13]
    wp_list = data[18]
    nb_wp = int(data[19])
    wp_radius = float(data[20])
    sat = data[7]
    wd = data[5]
    ws = data[6]
    timestamp = data[0]

    fig = plt.figure()
    xmin = min(np.min(x), np.min([wp[0] for wp in wp_list]) - wp_radius) - 5
    xmax = max(np.max(x), np.max([wp[0] for wp in wp_list]) + wp_radius) + 5
    ymin = min(np.min(y), np.min([wp[1] for wp in wp_list]) - wp_radius) - 5
    ymax = max(np.max(y), np.max([wp[1] for wp in wp_list]) + wp_radius) + 5
    ax = plt.axes(xlim=(xmin, xmax), ylim=(ymin, ymax))
    ax.set_xlabel('X (m)')
    ax.set_ylabel('Y (m)')
    ax.set_title('Sailboat Trajectory')

    # Waypoints display
    for i in range(nb_wp):
        ax.plot(wp_list[i][0], wp_list[i][1], 'yo')
        circle = patches.Circle((wp_list[i][0], wp_list[i][1]), wp_radius, fill=False)
        ax.add_patch(circle)
        if i > 0:
            ax.plot([wp_list[i-1][0], wp_list[i][0]], [wp_list[i-1][1], wp_list[i][1]], 'g')
        else:
            ax.plot([x[0], wp_list[i][0]], [y[0], wp_list[i][1]], 'g')

    # Add the north arrow
    arrow_north = patches.FancyArrowPatch((0.93, 0.85), (0.93, 0.93), mutation_scale=20, color='black', arrowstyle='wedge', transform=ax.transAxes)
    ax.add_patch(arrow_north)
    ax.text(0.93, 0.95, 'North', transform=ax.transAxes, ha='center', va='center', fontsize=12, color='black')

    # Add the wind direction arrow
    wind_arrow = patches.FancyArrowPatch((0, 0), (0, 0), mutation_scale=20, color='blue', arrowstyle='->', transform=ax.transAxes)
    ax.add_patch(wind_arrow)

    # Initialize the animation
    full_path, = ax.plot([], [], lw = 2, c='grey', alpha=0.5, label='Boat path')
    path, = ax.plot([], [], lw = 2, c='r')
    last_point, = ax.plot([], [], 'ko')
    gnss_lost, = ax.plot([], [], 'r', label='GNSS lost')
    wind_text = ax.text(0.03, 0.97, '', transform=ax.transAxes, ha='left', va='top', fontsize=8, c='k', bbox=dict(facecolor='white', alpha=0.7))


    def init():
        full_path.set_data([], [])
        path.set_data([], [])
        last_point.set_data([], [])
        gnss_lost.set_data([], [])
        wind_arrow.set_positions((0, 0), (0, 0))
        return full_path, path, last_point, gnss_lost, wind_arrow


    xdata, ydata = [], []
    xsat, ysat = [], []


    def animate(i):
        xdata.append(x[i])
        ydata.append(y[i])
        full_path.set_data(xdata, ydata)
        path.set_data(xdata[-20:], ydata[-20:])
        last_point.set_data(x[i], y[i])
        if sat[i] < 4:
            xsat.append(x[i])
            ysat.append(y[i])
            gnss_lost.set_data(xsat, ysat)

        # Update wind direction
        wind_angle = np.deg2rad(wd[i])
        x_arrow = (x[i] - xmin)/(xmax - xmin)
        y_arrow = (y[i] - ymin)/(ymax - ymin)
        wind_arrow.set_positions((x_arrow, y_arrow), (x_arrow + 0.1 * np.cos(wind_angle), y_arrow + 0.1 * np.sin(wind_angle)))

        wind_text.set_text(f'Wind speed: {ws[i]:.2f} km/h\nTime: {timestamp[i]:.1f}s')

        return full_path, path, last_point, gnss_lost, wind_text, wind_arrow
    

    def make_legend_arrow(legend, orig_handle, xdescent, ydescent, width, height, fontsize):
        p = patches.FancyArrow(0, 0.5 * height, width, 0, length_includes_head=True, head_width=0.75 * height)
        return p


    custom_lines = [patches.FancyArrowPatch((0, 0), (0.1, 0), mutation_scale=20, color='blue')]
    ax.legend(handles=[full_path, gnss_lost, custom_lines[0]], labels=['Boat path', 'GNSS lost', 'Wind direction'], loc='lower left', handler_map={patches.FancyArrowPatch: HandlerPatch(patch_func=make_legend_arrow)})

    plt.gca().set_aspect('equal', adjustable='box')

    # calling the animation function	 
    anim = animation.FuncAnimation(fig, animate, init_func = init, 
                                frames = len(x), interval = 20, blit = True) 

    # saves the animation in our desktop 
    anim.save(f'logs/plots/{date}/{time}/videoxy.mp4', writer = 'ffmpeg', fps = 60) 


def displayLog(file, date, time, video=False):
    data = readLog(file)

    output_dir = f'logs/plots/{date}/{time}'
    os.makedirs(output_dir, exist_ok=True)

    plotYaw(data, date, time)
    plotWindDir(data, date, time)
    plotWindSpeed(data, date, time)
    plotBoatSpeed(data, date, time)
    plotXY(data, date, time)
    plotCmd(data, date, time)

    print(f'Log successfully saved in logs/plots/{date}/{time}/')

    plt.show()

    if video:
        print('Creating video...')
        createVid(data, date, time)
        print(f'Video created and saved successfully as logs/plots/{date}/{time}/videoxy.mp4')


if __name__ == '__main__':
    date = input('Enter the date of the log in the format DDMMYY: ')
    time = input('Enter the time of the log in the format HHMMSS: ')
    file = open(f'logs/{date}/{time}.txt', 'r')
    video = input('Do you want to create a video of the log? (y/n) ')
    if video == 'y':
        video = True
    else:
        video = False
    displayLog(file, date, time, video)
    file.close()
