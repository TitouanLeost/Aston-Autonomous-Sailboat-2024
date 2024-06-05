import serial
import time
import os


arduino_port = '/dev/ttyACM0'  # Modify according to the port used by your Arduino
baud_rate = 9600
# output_file = "brouillons/data_from_sd.txt"
timeout_duration = 5  # Time in seconds without reception before considering the end of the transmission

try:
    ser = serial.Serial(arduino_port, baud_rate, timeout=1)
    time.sleep(2)

    line = ser.readline().decode('utf-8')
    log_date = line.split('_')[0]
    log_time = line.split('_')[1]
    output_dir = f"logs/{log_date}"
    output_file = f"logs/{log_date}/{log_time}.txt"

    os.makedirs(output_dir, exist_ok=True)

    with open(output_file, 'w') as file:
        start_time = time.time()
        while True:
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8')
                file.write(line)
                print(line, end='')
                start_time = time.time()
            elif time.time() - start_time > timeout_duration:
                break

except serial.SerialException as e:
    print(f"Error connecting to the serial port: {e}")

finally:
    if 'ser' in locals() and ser.is_open:
        ser.close()
