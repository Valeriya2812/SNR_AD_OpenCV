// SNR_AD.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <math.h>
#include <opencv2\opencv.hpp>


double findSNR(IplImage* image, IplImage* image_noise) {

	int y, x, z;
	unsigned long int sumIm = 0;
	unsigned long int sumDiff = 0;
	long int diff;
	for (y = 0; y <image->height; y++)
	{
		uchar* ptrImage = (uchar*)(image->imageData + y * image->widthStep);
		uchar* ptrImage_noise = (uchar*)(image_noise->imageData + y * image_noise->widthStep);

		for (x = 0; x < image->width; x++)
		{
			sumIm += pow(ptrImage[3 * x + 2], 2);
			sumIm += pow(ptrImage[3 * x + 1], 2);
			sumIm += pow(ptrImage[3 * x], 2);
			diff = ptrImage[3 * x + 2] - ptrImage_noise[3 * x + 2];
			sumDiff += pow(diff, 2);
			diff = ptrImage[3 * x + 1] - ptrImage_noise[3 * x + 1];
			sumDiff += pow(diff, 2);
			diff = ptrImage[3 * x] - ptrImage_noise[3 * x];
			sumDiff += pow(diff, 2);

		}


	}
	double result = (double)sumIm / (double)sumDiff;
	return result;
}


double findAD(IplImage* image, IplImage* image_noise) {

	int y, x, z;
	double r = 1.0 / (image->width * 3 * image->height);

	int sumDiff = 0;
	int diff;
	for (y = 0; y <image->height; y++)
	{
		uchar* ptrImage = (uchar*)(image->imageData + y * image->widthStep);
		uchar* ptrImage_noise = (uchar*)(image_noise->imageData + y * image_noise->widthStep);

		for (x = 0; x < image->width; x++)
		{
			diff = ptrImage[3 * x + 2] - ptrImage_noise[3 * x + 2];
			sumDiff += abs(diff);
			diff = ptrImage[3 * x + 1] - ptrImage_noise[3 * x + 1];
			sumDiff += abs(diff);
			diff = ptrImage[3 * x] - ptrImage_noise[3 * x];
			sumDiff += abs(diff);

		}


	}

	double result = r*sumDiff;
	return result;
}




int main()
{

	char* filename = "D:\\valeriya\\1\\eye008.jpg";
	IplImage* image = cvLoadImage(filename, 1);
	char* filename_noise = "D:\\valeriya\\1\\eye007.jpg";
	IplImage* image_noise = cvLoadImage(filename_noise, 1);
	std::cout << filename << std::endl;
	std::cout << image->width << "x" << image->height << std::endl;



	std::cout << "AD \t\t" << "SNR \t\t" << std::endl;
	std::cout << findAD(image, image_noise) << "\t";
	std::cout << findSNR(image, image_noise) << " \t";


	std::cin.get();


	return 0;
}
