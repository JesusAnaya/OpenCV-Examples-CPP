#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

int main()
{
    std::string imagePath{"./data/images/threshold.png"};
    cv::Mat image{cv::imread(imagePath, cv::IMREAD_GRAYSCALE)};
    const int thresh{128};
    const int maxValue{128};

    if (image.empty())
    {
        std::cout << "Could not read the image: " << imagePath << std::endl;
        return 1;
    }

    cv::imshow("Original Image", image);

    cv::Mat dest;

    // Normal Thresholding
    cv::threshold(image, dest, thresh, maxValue, cv::THRESH_BINARY);
    cv::imshow("Threshold Image", dest);

    // Inverse Thresholding
    cv::threshold(image, dest, thresh, maxValue, cv::THRESH_BINARY_INV);
    cv::imshow("Inverse Threshold Image", dest);

    // Truncate Thresholding
    cv::threshold(image, dest, thresh, maxValue, cv::THRESH_TRUNC);
    cv::imshow("Truncate Threshold Image", dest);

    // Threshold to Zero
    cv::threshold(image, dest, thresh, maxValue, cv::THRESH_TOZERO);
    cv::imshow("Threshold to Zero Image", dest);

    // Inverse Threshold to Zero
    cv::threshold(image, dest, thresh, maxValue, cv::THRESH_TOZERO_INV);
    cv::imshow("Inverse Threshold to Zero Image", dest);

    // Adaptive Thresholding
    cv::adaptiveThreshold(image, dest, maxValue, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 11, 2);
    cv::imshow("Adaptive Threshold Image", dest);

    // Otsu's Thresholding
    cv::threshold(image, dest, 0, maxValue, cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::imshow("Otsu's Threshold Image", dest);

    // Gaussian Otsu's Thresholding
    cv::GaussianBlur(image, image, cv::Size(5, 5), 0);
    cv::threshold(image, dest, 0, maxValue, cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::imshow("Gaussian Otsu's Threshold Image", dest);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}