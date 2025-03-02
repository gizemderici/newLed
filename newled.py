from PIL import ImageGrab
import os
import numpy as np

img = ImageGrab.grab()


save_path = os.path.join(os.getcwd(), "screenshot.png")
img.save(save_path)
print(f"Ekran görüntüsü kaydedildi: {save_path}")


img = img.resize([5, 3])


pixel = np.array(img)


ustkenar = pixel[0, :] 
altkenar = pixel[-1, :]
solkenar = pixel[1:-1, 0] 
sagkenar = pixel[1:-1, -1]

print("Sol Kenar\n", solkenar)
print("Sağ Kenar\n", sagkenar)
print("Üst Kenar\n", ustkenar)
print("Alt Kenar\n", altkenar)


small = os.path.join(os.getcwd(), "resize.jpg")
img.save(small)
print(f"\n📸 Küçültülmüş ekran görüntüsü kaydedildi: {small}")