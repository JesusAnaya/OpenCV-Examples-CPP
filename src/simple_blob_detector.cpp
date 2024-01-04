#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

int main()
{
    std::string imagePath{"./data/images/blob_detection.jpg"};
    cv::Mat image{cv::imread(imagePath, cv::IMREAD_GRAYSCALE)};

    if (image.empty())
    {
        std::cout << "Could not read the image: " << imagePath << std::endl;
        return 1;
    }

    cv::SimpleBlobDetector::Params params{};

    // Change thresholds
    params.minThreshold = 10;
    params.maxThreshold = 200;

    // Filter by Area
    params.filterByArea = true;
    params.minArea = 1500;

    // Filter by Circularity
    params.filterByCircularity = true;
    params.minCircularity = 0.1;

    // Filter by Convexity
    params.filterByConvexity = true;
    params.minConvexity = 0.87;

    // Filter by Inertia
    params.filterByInertia = true;
    params.minInertiaRatio = 0.01;

    cv::Ptr<cv::SimpleBlobDetector> detector{cv::SimpleBlobDetector::create(params)};
    std::vector<cv::KeyPoint> key_points{};

    detector->detect(image, key_points);

    int x, y, radius;

    cvtColor(image, image, cv::COLOR_GRAY2BGR);

    for (const auto& key_point : key_points)
    {
        x = static_cast<int>(key_point.pt.x);
        y = static_cast<int>(key_point.pt.y);
        radius = static_cast<int>(key_point.size / 2.0);

        cv::circle(image, cv::Point(x, y), radius, cv::Scalar(0, 0, 255), 2);
    }

    cv::imshow("Original Image", image);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}