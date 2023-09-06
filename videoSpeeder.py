# 使用安装的ffmpeg来进行处理
#

import subprocess

def change_video_speed(input_file, output_file):
    # 使用FFmpeg命令将视频变速至2倍，并加速处理音频
    command = f'ffmpeg -i {input_file} -filter_complex "[0:v]setpts=0.5*PTS[v];[0:a]atempo=2[a]" -map "[v]" -map "[a]" {output_file}'
    # 执行命令
    subprocess.call(command, shell=True)
    print("done.")

if __name__ == '__main__':
    # 调用函数进行视频变速处理
    change_video_speed('data/input.mp4', 'output/output.mp4')