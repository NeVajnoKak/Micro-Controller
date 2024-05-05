import serial

# Указываем порт, который используется для связи с Arduino
commPort = '/dev/cu.usbserial-1130'
ser = serial.Serial(commPort, baudrate=9600, timeout=1)

# Функция для отправки команды на Arduino
def send_command(command):
    ser.write(command.encode())