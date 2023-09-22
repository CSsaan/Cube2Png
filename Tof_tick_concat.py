from PIL import Image

# 加载原始图片
image = Image.open("pic/arrowtick.png")
w, h = image.size[:2]
print("image shape:", w, ",",h)

# 创建透明图像
transparent_image = Image.new("RGBA", (2343, 1388), (0, 0, 0, 0))

# 拼接图像
result = Image.new("RGBA", (w + transparent_image.width, h))
result.paste(transparent_image, (0, 0))
result.paste(image, (transparent_image.width, 0))

# 保存结果图像
result.save("output/arrowtick_result.png")