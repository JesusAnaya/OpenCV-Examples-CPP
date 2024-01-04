#include <cmath>
#include <opencv2/opencv.hpp>

// Points to store the center of the circle and a point on the circumference
static cv::Point center, circumference;
// Source image
static cv::Mat source;

// function which will be called on mouse input
void drawCircle(int action, int x, int y, int, void*)
{
    // Action to be taken when left mouse button is pressed
    if (action == cv::EVENT_LBUTTONDOWN)
    {
        center = cv::Point(x, y);
        // Mark the center
        cv::circle(source, center, 1, cv::Scalar(255, 255, 0), 2, cv::LINE_AA);
    }
    // Action to be taken when left mouse button is released
    else if (action == cv::EVENT_LBUTTONUP)
    {
        circumference = cv::Point(x, y);
        // Calculate radius of the circle
        double radius{std::sqrt(std::pow(center.x - circumference.x, 2) +
                                std::pow(center.y - circumference.y, 2))};
        // Draw the circle
        cv::circle(source, center, static_cast<int>(radius), cv::Scalar(0, 255, 0), 2, cv::LINE_AA);
        cv::imshow("Window", source);
    }
}

int main()
{
    source = cv::imread("./data/images/sample.jpg", 1);
    // Make a dummy image, will be useful to clear the drawing
    cv::Mat dummy{source.clone()};
    cv::namedWindow("Window");

    // highgui function called when mouse events occur
    cv::setMouseCallback("Window", drawCircle);

    // loop until escape character is pressed
    int key{0};
    while (key != 27)
    {
        cv::imshow("Window", source);
        cv::putText(source, "Choose center, and drag, Press ESC to exit and c to clear",
                    cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);

        key = cv::waitKey(20) & 0xFF;
        if (key == 'c' || key == 'C')
        {
            // Another way of cloning
            dummy.copyTo(source);
        }
    }
    return 0;
}