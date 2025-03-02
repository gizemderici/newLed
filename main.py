from PIL import ImageGrab , ImageEnhance
import os
import numpy as np
import serial
import time

ser = serial.Serial("COM3", 115200, timeout=1)
time.sleep(2)

while(1):
    img = ImageGrab.grab()
    # img = ImageEnhance.Contrast(img)
    # img = img.enhance(100)
    img = img.resize([5, 3])

    pixel = np.array(img)


    ustkenar = reversed(pixel[0, :])
    altkenar = pixel[-1, :]
    solkenar = pixel[1:-1, 0] 
    sagkenar = pixel[1:-1, -1]

    for rgb in altkenar:
        ser.write(bytes(rgb))
        time.sleep(0.01)

    for rgb in sagkenar:
        ser.write(bytes(rgb))
        time.sleep(0.01)

    for rgb in ustkenar:
        ser.write(bytes(rgb))
        time.sleep(0.01)

   

   

    for rgb in solkenar:
        ser.write(bytes(rgb))
        time.sleep(0.01)


ser.close()




