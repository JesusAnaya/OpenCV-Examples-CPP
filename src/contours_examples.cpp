#include <iostream>
#include <string>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"


int main() {

    std::string imagePath = "./data/images/Contour.png";

    cv::Mat image = cv::imread(imagePath);

    if (image.empty()) {
        std::cout << "Could not read the image: " << imagePath << std::endl;
        return 1;
    }

    cv::Mat imageGray;
    cv::cvtColor(image, imageGray, cv::COLOR_BGR2GRAY);

    // Find the contours Retrieve external means only the outer contours
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(imageGray, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
    cv::drawContours(image, contours, -1, cv::Scalar(0, 255, 0), 3);
    cv::imshow("Image with contours", image);

    // Center of mass or Centroid
    cv::Mat imageCopy_1 = image.clone();
    for (const auto& contour : contours) {
        cv::Moments moments = cv::moments(contour);
        cv::Point center(static_cast<int>(moments.m10 / moments.m00),
                         static_cast<int>(moments.m01 / moments.m00));

        cv::circle(imageCopy_1, center, 10, cv::Scalar(255, 0, 0), -1);

        // Put text
        std::string text = "(" + std::to_string(center.x) + ", " + std::to_string(center.y) + ")";
        cv::putText(imageCopy_1, text, center, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 2);
    }
    cv::imshow("Image with contours and centroids", imageCopy_1);

    // Adding bounding boxes
    cv::Mat imageCopy_2 = image.clone();
    for (const auto& contour : contours) {
        cv::Rect boundingBox = cv::boundingRect(contour);
        cv::rectangle(imageCopy_2, boundingBox, cv::Scalar(255, 0, 255), 2);
    }
    cv::imshow("Image with contours and bounding boxes", imageCopy_2);

    // Adding rotated bounding boxes
    cv::Mat imageCopy_3 = image.clone();
    for (const auto& contour : contours) {
        cv::RotatedRect rotatedBoundingBox = cv::minAreaRect(contour);
        cv::Point2f vertices[4];
        rotatedBoundingBox.points(vertices);
        for (int i = 0; i < 4; ++i) {
            cv::line(imageCopy_3, vertices[i], vertices[(i + 1) % 4], cv::Scalar(0, 255, 255), 2);
        }
    }
    cv::imshow("Image with contours and rotated bounding boxes", imageCopy_3);

    cv::waitKey(0);

    return 0;
}