#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // Open webcam
    cv::VideoCapture cap(0);
    cv::Mat frame;
    int key{0};

    // Detect if webcam is working properly
    if (!cap.isOpened())
    {
        std::cout << "Unable to detect webcam " << std::endl;
        return 0;
    }
    else
    {
        while (cap.isOpened())
        {
            // Capture frame
            cap >> frame;

            if (key == 27)
                break;

            // The following if-else block is used to check which key is pressed.
            // We use the waitKey() function to detect the input and
            // respond only if either ‘e’ or ‘z’ is pressed.
            // ‘ESC’(ASCII code = 27) is used to exit the program.

            // Identify if 'e' or 'E' is pressed
            if (key == 101 || key == 69)
            {
                cv::putText(frame, "E is pressed, press Z or ESC", cv::Point(100, 180),
                            cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 3);
            }

            // Identify if 'z' or 'Z' is pressed or not
            if (key == 90 || key == 122)
            {
                cv::putText(frame, "Z is pressed", cv::Point(100, 180), cv::FONT_HERSHEY_SIMPLEX, 1,
                            cv::Scalar(0, 255, 0), 3);
            }

            cv::imshow("Image", frame);

            // Wait key is increased so that the display is shown
            key = cv::waitKey(10000) & 0xFF;
        }
    }
    cap.release();
    cv::destroyAllWindows();
    return 0;
}