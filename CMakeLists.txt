cmake_minimum_required(VERSION 3.25)
project(OCRProject)

set(CMAKE_CXX_STANDARD 17)

# OpenCV package
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Set the path of Tesseract and Leptonica manually
include_directories(/opt/homebrew/opt/tesseract/include)
link_directories(/opt/homebrew/opt/tesseract/lib)

# Same for Leptonica if required
include_directories(/opt/homebrew/opt/leptonica/include/)
link_directories(/opt/homebrew/opt/leptonica/lib)

add_executable(OCRProject src/main.cpp src/ImagePreprocessing.cpp)
target_link_libraries(OCRProject ${OpenCV_LIBS} tesseract lept)
