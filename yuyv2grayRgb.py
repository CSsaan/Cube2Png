import numpy as np
import cv2

def convert_yuyv(yuv_file, output_dir, save_gray):
    yuv_file = open(yuv_file, 'rb')
    frame_len = 1920 * 1080 * 2
    shape2 = (1080, 1920, 2)  # 用于yuv转bgr，对于yuyv格式，需要2通道
    raw = yuv_file.read(int(frame_len))
    yuv = np.frombuffer(raw, dtype=np.uint8)
    yuv = yuv.reshape(shape2)
    if(is_gray):
        cv_type = cv2.COLOR_YUV2GRAY_YUYV
    else:
        cv_type = cv2.COLOR_YUV2BGR_YUYV
    bgr = cv2.cvtColor(yuv, cv_type)
    cv2.imwrite(output_dir + "/Image.jpg", bgr)


if __name__ == '__main__':
    # 示例用法
    input_file = "yuy2.yuv"
    output_file = "pic"
    save_gray = bool(1)
    convert_yuyv(input_file, output_file, save_gray)