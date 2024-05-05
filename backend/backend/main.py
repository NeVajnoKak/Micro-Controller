# import serial.tools.list_ports
#
# ports = serial.tools.list_ports.comports()
# for port, desc, hwid in sorted(ports):
#     print(f"{port}: {desc}")
# /dev/cu.usbserial-1140: USB Serial
# /dev/cu.Bluetooth-Incoming-Port: n/a
# /dev/cu.wlan-debug: n/a
import serial
import tkinter as tk

# Указываем порт, который используется для связи с Arduino
commPort = '/dev/cu.usbserial-1140'
ser = serial.Serial(commPort, baudrate=9600, timeout=1)

# Функция для отправки команды на ардуино
def send_command(command):
    ser.write(command.encode())

# Создаем графический интерфейс Tkinter
root = tk.Tk()
root.title('Arduino Audio Player Control')

# Кнопки для управления аудиоплеером
btn_play_pause = tk.Button(root, text="Play/Pause", command=lambda: send_command('p'))
btn_play_pause.pack()

btn_next = tk.Button(root, text="Next", command=lambda: send_command('n'))
btn_next.pack()

btn_previous = tk.Button(root, text="Previous", command=lambda: send_command('b'))
btn_previous.pack()

btn_volume_up = tk.Button(root, text="Volume Up", command=lambda: send_command('u'))
btn_volume_up.pack()

btn_volume_down = tk.Button(root, text="Volume Down", command=lambda: send_command('d'))
btn_volume_down.pack()


# Запускаем цикл обработки событий Tkinter
root.mainloop()
