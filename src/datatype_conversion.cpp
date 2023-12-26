#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

int main()
{
    std::string imagePath{"./data/images/boy.jpg"};
    cv::Mat image{cv::imread(imagePath, cv::IMREAD_COLOR)};

    if (image.empty())
    {
        std::cout << "Could not read the image: " << imagePath << std::endl;
        return 1;
    }

    // Converting data type to float32
    cv::Mat imageFloat32;
    image.convertTo(imageFloat32, CV_32FC3, 1.0 / 255);

    // Convert again to uint8
    cv::Mat imageUint8;
    imageFloat32.convertTo(imageUint8, CV_8UC3, 255.0);

    cv::imshow("Original Image", image);
    cv::imshow("Float32 Image", imageFloat32);
    cv::imshow("Uint8 Image", imageUint8);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}