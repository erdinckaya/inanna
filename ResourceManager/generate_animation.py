from PIL import Image
import sys


import glob, os
os.chdir("./Kyo_Little_Kick")
for filename in glob.glob("*.png"):
    img = Image.open(filename)
    img = img.resize((img.size[0] * 2,img.size[1] * 2), Image.ANTIALIAS)
    filename = "Frame" + filename
    print(filename)
    img.save(filename)


