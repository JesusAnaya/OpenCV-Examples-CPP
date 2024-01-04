#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

int main()
{
    std::string imagePath{"./data/images/opening.png"};
    cv::Mat image{cv::imread(imagePath, cv::IMREAD_GRAYSCALE)};

    if (image.empty())
    {
        std::cout << "Could not read the image: " << imagePath << std::endl;
        return 1;
    }

    // Set some values to a region of the image
    image(cv::Range(20, 50), cv::Range(20, 50)) = 255;

    const int openingSize{3};
    cv::Mat element{cv::getStructuringElement(cv::MORPH_ELLIPSE,
                                              cv::Size(2 * openingSize + 1, 2 * openingSize + 1),
                                              cv::Point(openingSize, openingSize))};

    cv::Mat imageOpened;
    cv::morphologyEx(image, imageOpened, cv::MORPH_OPEN, element, cv::Point(-1, -1), 3);

    cv::Mat imageClosed;
    cv::morphologyEx(image, imageClosed, cv::MORPH_CLOSE, element, cv::Point(-1, -1), 3);

    cv::imshow("Opened Image", imageOpened);
    cv::imshow("Closed Image", imageClosed);
    cv::imshow("Original Image", image);

    cv::namedWindow("Opened Image", cv::WINDOW_NORMAL);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}