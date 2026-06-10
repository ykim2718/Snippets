"""
y, 2021.12.28
PIL - getbbox.py
https://stackoverflow.com/questions/9870876/getbbox-method-from-python-image-library-pil-not-working
"""

from PIL import Image, ImageOps  # pip install Pillow
import numpy as np

image = Image.open('test.png')
image.load()
imageSize = image.size

# remove alpha channel
invert_im = image.convert("RGB")

# invert image (so that white is 0)
invert_im = ImageOps.invert(invert_im)
image_box = invert_im.getbbox()
print(image_box)  # (98, 29, 1731, 1345)
padding = (-20, -20, 20, 20)
image_box = tuple(np.asarray(image_box) + padding)
print(image_box)  # (108, 39, 1741, 1355)

cropped = image.crop(image_box)
# print(filePath, "Size:", imageSize, "New Size:", image_box)
cropped.save('cropped.png')
