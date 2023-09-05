# import numpy as np
# import matplotlib.pyplot as plt

# # 创建一个宽度为6，高度为1的图像
# fig, ax = plt.subplots(figsize=(6, 1))

# # 设置每个矩形区域的颜色
# colors = [(255, 0, 0), (0, 255, 0), (0, 0, 255), (255, 255, 0), (0, 255, 255), (255, 0, 255)]

# # 将RGB颜色值转换为范围在0到1之间的浮点数
# colors = np.array(colors) / 255.0

# # 在图像上绘制矩形区域
# for i in range(6):
#     ax.add_patch(plt.Rectangle((i/6, 0), 1/6, 1, color=colors[i]))

# # 隐藏坐标轴
# ax.axis('off')

# # 保存图像
# plt.savefig('save6colors.png')


# ----------------------------------------------------------------------------
import numpy as np
import cv2

# 创建一个宽度为600，高度为100的图像
image = np.zeros((1000, 1000, 3), dtype=np.uint8)

# 设置每个矩形区域的颜色
colors = [(255, 0, 0), (0, 255, 0), (0, 0, 255), (255, 255, 0), (0, 255, 255), (255, 0, 255)]

# 计算每个矩形的宽度
rectangle_width = image.shape[1] // len(colors)

# 在图像上绘制矩形区域
for i, color in enumerate(colors):
    start_x = i * rectangle_width
    end_x = (i + 1) * rectangle_width
    cv2.rectangle(image, (start_x, 0), (end_x, image.shape[0]), color, -1)

# 保存图像
cv2.imwrite("save6colors.png", image)