#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include "ImagePreprocessing.h"

std::string extractTextFromImage(const cv::Mat& preprocessedImage, const std::vector<cv::Rect>& textRegions) {
    std::string extractedText;

    // Create a Tesseract API object
    tesseract::TessBaseAPI tesseractAPI;

    // Initialize Tesseract with English language (change as per your requirements)
    if (tesseractAPI.Init(nullptr, "eng")) {
        std::cerr << "Failed to initialize Tesseract" << std::endl;
        return extractedText;
    }

    // Iterate over the text regions
    for (const auto& region : textRegions) {
        // Extract the region of interest (ROI) from the preprocessed image
        cv::Mat roi = preprocessedImage(region);

        // Convert the ROI from grayscale to 32-bit RGBA
        cv::Mat rgbaImage;
        cv::cvtColor(roi, rgbaImage, cv::COLOR_GRAY2RGBA);

        // Create a PIX object from the RGBA image
        PIX* pixROI = pixCreate(rgbaImage.cols, rgbaImage.rows, 32); // Assuming 32 bits per pixel

        // Set the image data in the PIX object
        l_uint32* pixData = pixGetData(pixROI);
        memcpy(pixData, rgbaImage.data, rgbaImage.total() * rgbaImage.elemSize());

        // Set the image data in Tesseract API
        tesseractAPI.SetImage(pixROI);

        // Get the recognized text from Tesseract
        char* recognizedText = tesseractAPI.GetUTF8Text();
        if (recognizedText) {
            extractedText += recognizedText;
            extractedText += " ";
        }

        // Clean up the allocated PIX object and recognized text
        pixDestroy(&pixROI);
        delete[] recognizedText;
    }

    // End the Tesseract API session
    tesseractAPI.End();

    return extractedText;
}


void recognizeText(const std::string& imagePath) {
    // Load the input image
    cv::Mat inputImage = cv::imread(imagePath);

    if (inputImage.empty()) {
        std::cout << "Could not open or find the image" << std::endl;
        return;
    }

    // Preprocess the image
    cv::Mat processedImage = preprocessImage(inputImage);

    // Detect text regions
    std::vector<cv::Rect> textRegions = detectTextRegions(processedImage);

    // Extract and recognize text
    std::string extractedText = extractTextFromImage(processedImage, textRegions);

    // Print the extracted text
    std::cout << "Extracted Text: " << extractedText << std::endl;
}


int main(int argc, char** argv) {

    if (argc < 2) {
        std::cout << "Usage: OCRProject <image_path>" << std::endl;
        return 0;
    }

    std::string imagePath = argv[1];
    recognizeText(imagePath);

    return 0;
}

