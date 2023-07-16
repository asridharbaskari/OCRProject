//
// Created by Aadithyaa Sridharbaskari  on 7/15/23.
//

#ifndef OCRPROJECT_IMAGEPREPROCESSING_H
#define OCRPROJECT_IMAGEPREPROCESSING_H


#include <opencv2/opencv.hpp>
#include <leptonica/allheaders.h>

cv::Mat preprocessImage(const cv::Mat& inputImage);
std::vector<cv::Rect> detectTextRegions(const cv::Mat& preprocessedImage);
std::string extractTextFromImage(const cv::Mat& preprocessedImage, const std::vector<cv::Rect>& textRegions);
std::string recognizeText(const cv::Mat& img);

PIX* matToPix(const cv::Mat& mat);

#endif //OCRPROJECT_IMAGEPREPROCESSING_H
