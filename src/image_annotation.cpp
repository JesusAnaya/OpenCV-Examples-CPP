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

    // Draw bounding box around the face
    cv::Mat imageCopy{image.clone()};
    cv::rectangle(imageCopy, cv::Point(170, 40), cv::Point(320, 200), cv::Scalar(0, 255, 0), 2, cv::LINE_8);

    // Draw a circle around the face
    cv::Mat imageCopy1{image.clone()};
    cv::circle(imageCopy1, cv::Point(245, 120), 80, cv::Scalar(0, 0, 255), 2, cv::LINE_AA);

    cv::imshow("Bounding box", imageCopy);
    cv::imshow("Circle", imageCopy1);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}