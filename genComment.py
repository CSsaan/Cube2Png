import cv2
import random

Book = " $@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,\"^`'."

def chang(gray):
    if gray > 240:
        return ' '
    unit = 255.0 / len(Book)
    return Book[int(gray / unit)]
 

if __name__ == "__main__":
    pic_name = "pic/save6colors.png"
    txt_name = "output/timg.txt"
    img = cv2.imread(pic_name, 0)
    img = cv2.resize(img, (90,90))
    with open(txt_name, 'w') as Txtout:
        for i in range(img.shape[0]):
            for j in range(img.shape[1]):
                s = img[i, j]
                Txtout.write(chang(s))
                print(chang(s), end='')
            print()
    Txtout.close()