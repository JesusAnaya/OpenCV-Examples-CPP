#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

int main()
{
    std::string imagePath{"./data/images/musk.jpg"};
    std::string glassesPath{"./data/images/sunglasses.png"};

    cv::Mat image{cv::imread(imagePath, cv::IMREAD_COLOR)};
    cv::Mat glasses{cv::imread(glassesPath, cv::IMREAD_UNCHANGED)};

    if (image.empty() or glasses.empty())
    {
        std::cout << "Could not read the image: " << imagePath << std::endl;
        return 1;
    }

    cv::resize(glasses, glasses, cv::Size(300, 100));
    std::cout << "Image dimensions: " << glasses.size() << std::endl;
    std::cout << "Number of channels: " << glasses.channels() << std::endl;

    // Separate the Color and alpha channels
    cv::Mat glassRGBAChannels[4];
    cv::Mat glassRGBChannels[3];
    cv::split(glasses, glassRGBAChannels);

    for (int i = 0; i < 3; ++i)
    {
        glassRGBChannels[i] = glassRGBAChannels[i];
    }

    cv::Mat glassesBGR, glassesMask1;
    cv::merge(glassRGBChannels, 3, glassesBGR);
    glassesMask1 = glassRGBAChannels[3];

    // Get the masked outputs
    cv::Mat eyeRoi = image(cv::Range(150, 250), cv::Range(140, 440));

    cv::Mat glassesMask;
    cv::Mat glassesMaskChannels[] = {glassesMask1, glassesMask1, glassesMask1};
    cv::merge(glassesMaskChannels, 3, glassesMask);

    // Use the mask to create the masked eye region
    cv::Mat eye;
    cv::Mat glassesMaskNot;
    cv::bitwise_not(glassesMask1, glassesMaskNot);

    cv::Mat eyeChannels[3];
    cv::Mat eyeRoiChannels[3];
    cv::Mat maskedGlasses;
    cv::Mat eyeRoiFinal;

    cv::split(eyeRoi, eyeRoiChannels);

    for (int i = 0; i < 3; ++i)
    {
        cv::bitwise_and(eyeRoiChannels[i], glassesMaskNot, eyeChannels[i]);
    }
    cv::merge(eyeChannels, 3, eye);

    cv::Mat glassesMaskNotChannels[] = {glassesMaskNot, glassesMaskNot, glassesMaskNot};
    cv::Mat glassesMaskNotMerged;
    cv::merge(glassesMaskNotChannels, 3, glassesMaskNotMerged);

    cv::bitwise_and(eyeRoi, glassesMaskNotMerged, eye);

    // Use the mask to create the masked glasses region
    cv::Mat sunglasses;
    cv::Mat glassesChannels[3];
    cv::Mat glassesBGRChannels[3];

    cv::split(glassesBGR, glassesBGRChannels);

    for (int i = 0; i < 3; ++i)
    {
        cv::bitwise_and(glassesBGRChannels[i], glassesMask1, glassesChannels[i]);
    }
    cv::merge(glassesChannels, 3, sunglasses);

    // Multiply the glasses with the mask
    cv::multiply(glassesBGR, glassesMask, maskedGlasses);

    // Combine the glasses in the Eye Region to get the augmented image
    cv::bitwise_or(eye, sunglasses, eyeRoiFinal);

    // Replace the eye ROI with the output from the previous section
    eyeRoiFinal.copyTo(eyeRoi);

    // Replace the eye ROI to the original image
    eyeRoi.copyTo(image(cv::Range(150, 250), cv::Range(140, 440)));

    cv::imshow("Original Image", image);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}