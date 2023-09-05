import struct
from PIL import Image

def convert_yuy2_to_rgb(input_file, output_file, width, height):
    with open(input_file, 'rb') as f:
        yuy2_data = f.read()

    rgb_data = yuy2_to_rgb(yuy2_data, width, height)

    image = Image.frombytes('RGB', (width, height), rgb_data)
    image.save(output_file)

def yuy2_to_rgb(yuy2_data, width, height):
    rgb_data = bytearray()

    for i in range(0, len(yuy2_data), 4):
        y0, u, y1, v = struct.unpack('BBBB', yuy2_data[i:i+4])

        r0, g0, b0 = yuv_to_rgb(y0, u, v)
        r1, g1, b1 = yuv_to_rgb(y1, u, v)

        rgb_data.extend([r0, g0, b0, r1, g1, b1])

    return bytes(rgb_data)

def yuv_to_rgb(y, u, v):
    r = int(y + 1.402 * (v - 128))
    g = int(y - 0.344136 * (u - 128) - 0.714136 * (v - 128))
    b = int(y + 1.772 * (u - 128))

    r = max(0, min(255, r))
    g = max(0, min(255, g))
    b = max(0, min(255, b))

    return r, g, b

# 示例用法
input_file = "yuy2.yuv"
output_file = "output.png"
width = 1920  # 图像宽度
height = 1080  # 图像高度
convert_yuy2_to_rgb(input_file, output_file, width, height)