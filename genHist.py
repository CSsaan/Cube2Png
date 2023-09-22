import cv2
import matplotlib.pyplot as plt
import numpy as np

# 读取图像
image_path = 'pic/face6.png'
image = cv2.imread(image_path)

# 将图像转换为灰度图
gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# 计算直方图
histogram = cv2.calcHist([gray_image], [0], None, [256], [0, 256])

# 绘制直方图
plt.bar(np.arange(0, 256, 1), histogram.flatten(), align='center', alpha=0.5)

# 设置图表标题和轴标签
plt.title('Histogram')
plt.xlabel('Pixel Value')
plt.ylabel('Frequency')

# 显示图表
plt.savefig("output/Histout.jpg")