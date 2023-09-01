/**
 * @file cube2png.cpp
 * @author CS
 * @brief
 * @version 0.1
 * @date 2023-08-08
 *
 * 这是一个使用C++编写的程序，用于将3D LUT文件解析为图像数据，并将解析后的3D LUT应用到图像上。以下是程序的实现步骤：
	1.首先，程序使用正则表达式解析3D LUT文件的标题、大小和值。
	2.然后，程序创建一个字符串数组，用于存放3D LUT的值。
	3.遍历字符串数组，将每一行的值转换为float类型。
	4.使用解析后的3D LUT值lookupLinear函数计算图像数据的每个像素值。
	5.将计算得到的像素值转换为unsigned char类型，并将其存储在图像数据中。
	6.将图像数据保存为PNG格式文件。
	7.显示处理后的图像。
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <sstream>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define QUARD_SIZE 33 // 每个小方格边长
#define IMG_WH (QUARD_SIZE*8) // 整张大图边长

class LUTCube
{
public:
	LUTCube(int size, const vector<float>& array) : size(size), array(array) {}

	vector<float> lookup(int ir, int ig, int ib)
	{
		int index = 3 * (ir + size * (ig + size * ib));
		return vector<float>(array.begin() + index, array.begin() + index + 3);
	}

	vector<float> lookupNearest(float r, float g, float b)
	{
		int ir = (int)round(r * (size - 1));
		int ig = (int)round(g * (size - 1));
		int ib = (int)round(b * (size - 1));
		return lookup(ir, ig, ib);
	}

	vector<float> lookupLinear(float r, float g, float b)
	{
		float sizeMinus2 = size - 2;
		int ir = (int)floor(r * sizeMinus2);
		int ig = (int)floor(g * sizeMinus2);
		int ib = (int)floor(b * sizeMinus2);
		float fr = (float)fmod(r * sizeMinus2, 1.0f);
		float fg = (float)fmod(g * sizeMinus2, 1.0f);
		float fb = (float)fmod(b * sizeMinus2, 1.0f);

		vector<float> v000 = lookup(ir, ig, ib);
		vector<float> v001 = lookup(ir, ig, ib + 1);
		vector<float> v010 = lookup(ir, ig + 1, ib);
		vector<float> v011 = lookup(ir, ig + 1, ib + 1);
		vector<float> v100 = lookup(ir + 1, ig, ib);
		vector<float> v101 = lookup(ir + 1, ig, ib + 1);
		vector<float> v110 = lookup(ir + 1, ig + 1, ib);
		vector<float> v111 = lookup(ir + 1, ig + 1, ib + 1);

		vector<float> result(3);
		for (int i = 0; i < 3; i++)
		{
			result[i] = lerp(
				lerp(
					lerp(v000[i], v001[i], fb),
					lerp(v010[i], v011[i], fb),
					fg),
				lerp(
					lerp(v100[i], v101[i], fb),
					lerp(v110[i], v111[i], fb),
					fg),
				fr);
		}
		return result;
	}

private:
	int size;
	vector<float> array;

	float lerp(float a, float b, float t)
	{
		return b * t + a * (1.0f - t);
	}
};

LUTCube parseLUTCube(const string& str)
{
	// 使用正则表达式匹配标题
	regex regexLineTitle("^TITLE \"(.*)\"$", regex_constants::ECMAScript);
	// 使用正则表达式匹配3D LUT的大小
	regex regexLineSize("^LUT_3D_SIZE (\\d+)$", regex_constants::ECMAScript);
	// 使用正则表达式匹配3D LUT的值
	regex regexLineValue("^([\\d\\.Ee-]+) ([\\d\\.Ee-]+) ([\\d\\.Ee-]+)$");

	// 使用正则表达式查找字符串中的标题
	smatch resultTitle;
	regex_search(str, resultTitle, regexLineTitle);
	string title = resultTitle.size() > 1 ? resultTitle[1].str() : "";
	// 使用正则表达式查找字符串中的3D LUT的大小
	smatch resultSize;
	regex_search(str, resultSize, regexLineSize);
	int size = resultSize.size() > 1 ? stoi(resultSize[1].str()) : 32;
	cout << "TITLE:" << title << endl;
	cout << "LUT_3D_SIZE:" << size << endl;

	// 创建一个字符串数组，用于存放3D LUT的值
	vector<string> lines;
	istringstream iss(str);
	string line;
	while (getline(iss, line))
	{
		lines.push_back(line);
	}

	// 初始化3D LUT的索引
	int index = 0;
	// 如果字符串数组中没有匹配的3D LUT的值，则继续查找
	while (index < 10 && !std::regex_search(lines[index], regexLineValue))  // lines.size()  --> 只检测前10行
	{
		index++;
	}

	// 删除字符串数组中的第一个元素
	lines.erase(lines.begin(), lines.begin() + index);
	// 重新设置字符串数组的大小
	lines.resize(size * size * size);

	// 创建一个float数组，用于存放3D LUT的值
	vector<float> array;
	// 遍历字符串数组，将每一行的值转换为float类型
	cout << "开始解析float数据···" << endl;
	for (string& line : lines)
	{
		// 法一：较慢
		//smatch result;
		//regex_search(line, result, regexLineValue);
		//array.push_back(stof(result[1].str()));
		//array.push_back(stof(result[2].str()));
		//array.push_back(stof(result[3].str()));
		// 法二：较快
		istringstream iss(line);
		string word;
		while (iss >> word)
		{
			array.push_back(stof(word));
		}
	}
	cout << "解析float数据完成." << endl;
	// 返回3D LUT
	return LUTCube(size, array);
}

void fillLUTOnCanvas(LUTCube& lut, vector<unsigned char>& data)
{
	int width = IMG_WH;
	int height = IMG_WH;

	for (int ir = 0; ir < QUARD_SIZE; ir++)
	{
		for (int ig = 0; ig < QUARD_SIZE; ig++)
		{
			for (int ib = 0; ib < 64; ib++)
			{
				int x = ir + (ib % 8) * QUARD_SIZE;
				int y = ig + (ib / 8) * QUARD_SIZE;
				vector<float> value = lut.lookupLinear(ir / (QUARD_SIZE - 1.0f), ig / (QUARD_SIZE - 1.0f), ib / 63.0f);
				int dataIndex = 4 * (x + width * y);
				data[dataIndex + 0] = (unsigned char)round(255.0f * value[0]);
				data[dataIndex + 1] = (unsigned char)round(255.0f * value[1]);
				data[dataIndex + 2] = (unsigned char)round(255.0f * value[2]);
				data[dataIndex + 3] = 255;
			}
		}
	}
}

int main()
{
	clock_t start, end;
	double time_taken;
	start = clock(); // 记录开始时间
	printf("begin···\n");

	ifstream file("D:/Users/Desktop/lut/Canon C-Log.cube");
	string str((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	file.close();

	LUTCube lutCube = parseLUTCube(str);
	vector<unsigned char> imageData(4 * IMG_WH * IMG_WH);

	fillLUTOnCanvas(lutCube, imageData);

	// Save imageData as PNG or display it on screen
	Mat image(IMG_WH, IMG_WH, CV_8UC4, (void*)imageData.data());
	// 修改通道顺序为BGRA
	cvtColor(image, image, COLOR_RGBA2BGRA);

	end = clock();												  // 记录结束时间
	time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // 计算毫秒数
	printf("1程序运行时间: %.2f 毫秒\n", time_taken);


	imshow("Cubu2PNG", image);
	waitKey(0);

	imwrite("D:/Users/Desktop/lut/output.png", image);

	return 0;
}
