#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

int main()
{
    std::string imagePath{"./data/images/boy.jpg"};
    cv::Mat image{cv::imread(imagePath, cv::IMREAD_COLOR)};

    if (image.empty())
    {
        std::cout << "Could not read the image: " << imagePath << std::endl;
        return 1;
    }

    cv::Mat imageCopy1{image.clone()};
    cv::Mat imageRoi{imageCopy1(cv::Range(40, 200), cv::Range(170, 320))};
    int roiHeight{imageRoi.size().height};
    int roiWidth{imageRoi.size().width};

    // Copy to left of face
    imageRoi.copyTo(imageCopy1(cv::Range(40, 40 + roiHeight), cv::Range(10, 10 + roiWidth)));

    // Copy to right of face
    imageRoi.copyTo(imageCopy1(cv::Range(40, 40 + roiHeight), cv::Range(330, 330 + roiWidth)));

    cv::imshow("Original Image", imageCopy1);

    // Copy image and resize it
    cv::Mat imageCopy2{image.clone()};
    cv::resize(imageCopy2, imageCopy2, cv::Size(), 1.5, 1.5);
    cv::imshow("Resized Image", imageCopy2);

    // Copy image using and resize it using a different interpolation method
    cv::Mat imageCopy3{image.clone()};
    cv::resize(imageCopy3, imageCopy3, cv::Size(), 1.5, 1.5, cv::INTER_NEAREST);
    cv::imshow("Resized Image using INTER_NEAREST", imageCopy3);

    // Creating a mask using inRange function
    cv::Mat imageCopy4{image.clone()};
    cv::Mat mask;
    cv::inRange(imageCopy4, cv::Scalar(0, 0, 150), cv::Scalar(100, 100, 255), mask);
    cv::imshow("Mask", mask);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}