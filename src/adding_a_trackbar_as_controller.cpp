#include <iostream>
#include <opencv2/opencv.hpp>

static int maxScaleUp{100};
static int scaleFactor{1};
static int scaleType{0};
static int maxType{1};

const std::string windowName{"Resize Image"};
const std::string trackbarValue{"Scale"};
const std::string trackbarType{"Type: \n 0: Scale Up \n 1: Scale Down"};

static cv::Mat image;

void scaleImage(int, void*);

int main()
{
    // load an image
    image = cv::imread("./data/images/truth.png");

    // Create a window to display results
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);

    // Create Trackbars and associate a callback function
    cv::createTrackbar(trackbarValue, windowName, &scaleFactor, maxScaleUp, scaleImage);

    // This track bar is a kind of switch between Upscale and Downscale, it should have only two
    // values
    cv::createTrackbar(trackbarType, windowName, &scaleType, maxType, scaleImage);

    scaleImage(0, nullptr);

    while (cv::waitKey(20) != 27);

    return 0;
}

// Callback functions
void scaleImage(int, void*)
{
    // Get the scale factor from the trackbar
    double scaleFactorDouble;

    if (scaleType == 0)
    {
        // Scale up the image
        scaleFactorDouble = 1 + scaleFactor / 100.0;
    }
    else
    {
        // Scale down the image, I added a limit of 50% less that the scale up
        // because at 100% less (scaleFactor = 100) the image is not visible
        scaleFactorDouble = 1 - scaleFactor / 200.0;
    }

    // Validate minimum and maximum scale factor
    if (scaleFactorDouble <= 0)
    {
        scaleFactorDouble = 0.01;
    }

    // Resize the image
    cv::Mat scaledImage;
    cv::resize(image, scaledImage, cv::Size(), scaleFactorDouble, scaleFactorDouble,
               cv::INTER_LINEAR);

    // Display the image
    cv::imshow(windowName, scaledImage);
}