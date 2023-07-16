//
// Created by Aadithyaa Sridharbaskari  on 7/15/23.
//

#include "ImagePreprocessing.h"
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

std::vector<PIX*> convertROIsToPIX(const cv::Mat& image, const std::vector<cv::Rect>& boundingBoxes) {
    std::vector<PIX*> pixROIs;

    for (const auto& rect : boundingBoxes) {
        // Extract the ROI from the image using the bounding box
        cv::Mat roi = image(rect);

        // Convert the ROI to PIX
        PIX* pixROI = matToPix(roi);

        pixROIs.push_back(pixROI);
    }

    return pixROIs;
}



cv::Mat preprocessImage(const cv::Mat &inputImage) {
    cv::Mat processedImage = inputImage.clone();

    // Convert image to grayscale
    cv::cvtColor(processedImage, processedImage, cv::COLOR_RGB2GRAY);

    // Add Gaussian blur to image
    cv::GaussianBlur(processedImage, processedImage, cv::Size(5, 5), 0);

    // Apply binary thresholding
    cv::threshold(processedImage, processedImage, 127, 255, cv::THRESH_BINARY);

    return processedImage;
}

std::vector<cv::Rect> detectTextRegions(const cv::Mat &preprocessedImage) {
    cv::Mat processedImage = preprocessedImage.clone();
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(preprocessedImage, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    std::vector<cv::Rect> boundingBoxes;
    for (const auto& contour : contours) {
        auto boundingBox = cv::boundingRect(contour);
        boundingBoxes.push_back(boundingBox);
    }
    return boundingBoxes;
}



PIX *matToPix(const cv::Mat &mat) {
    return nullptr;
}


