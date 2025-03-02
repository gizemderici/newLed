from PIL import ImageGrab , ImageEnhance , Image , ImageFilter
import os
import numpy as np
import serial
import time

img = ImageGrab.grab()
img = ImageEnhance.Contrast(img)
img = img.enhance(100)

# img = img.filter(ImageFilter.BoxBlur(4))

img.show()