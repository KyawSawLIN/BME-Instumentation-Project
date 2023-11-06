import pyautogui
import time
import serial

arduino = serial.Serial(port='COM8', baudrate=9600, timeout=.1) 

while True:
    line = arduino.readline().decode('utf-8').strip()
    print(type(line))
    if line == 'a':
        print("a")
        pyautogui.moveTo(x=80, y=580 )
        time.sleep(0.3)
        arduino.write(b'a')
        time.sleep(0.5)
        pyautogui.moveTo(x=80, y=450 )
        pyautogui.moveTo(x=90,y=440)
