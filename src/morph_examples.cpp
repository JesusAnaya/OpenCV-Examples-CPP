#include <iostream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>


int main() {

    std::string imagePath = "./data/images/opening.png";

    cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);

    if (image.empty()) {
        std::cout << "Could not read the image: " << imagePath << std::endl;
        return 1;
    }

    const int openingSize = 3;
    cv::Mat element = cv::getStructuringElement(cv::MORPH_ELLIPSE,
                                                cv::Size(2 * openingSize + 1, 2 * openingSize + 1),
                                                cv::Point(openingSize, openingSize));

    cv::Mat imageOpened;
    cv::morphologyEx(image, imageOpened, cv::MORPH_OPEN, element, cv::Point(-1, -1), 3);

    cv::Mat imageClosed;
    cv::morphologyEx(image, imageClosed, cv::MORPH_CLOSE, element, cv::Point(-1, -1), 3);

    cv::imshow("Opened Image", imageOpened);
    cv::imshow("Closed Image", imageClosed);
    cv::imshow("Original Image", image);

    cv::waitKey(0);

    return 0;
}