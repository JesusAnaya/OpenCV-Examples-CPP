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

    cv::Mat glassesRGBAChannel[4];
    cv::Mat glassesRGBChannels[3];
    cv::split(glasses, glassesRGBAChannel);

    // Copy from RGBA to RGB channels
    for (int i = 0; i < 3; ++i)
    {
        glassesRGBChannels[i] = glassesRGBAChannel[i];
    }

    cv::Mat glassesBGR, glassesMask1;
    cv::merge(glassesRGBChannels, 3, glassesBGR);
    glassesMask1 = glassesRGBAChannel[3];

    // Using Naive Replace
    cv::Mat faceWithGlassesNaiveReplace{image.clone()};
    cv::Mat faceRoi{faceWithGlassesNaiveReplace(cv::Range(150, 250), cv::Range(140, 440))};
    glassesBGR.copyTo(faceRoi);

    cv::imshow("Face with glasses using naive replace", faceWithGlassesNaiveReplace);

    // Using Arithmetic Operations and alpha mask
    cv::Mat glassesMask;
    cv::Mat glassesMaskChannels[] = {glassesMask1, glassesMask1, glassesMask1};
    cv::merge(glassesMaskChannels, 3, glassesMask);

    // Make the values [0, 1] since we are using arithmetic operations
    glassesMask = glassesMask / 255;

    // Make a copy
    cv::Mat faceWithGlassesArithmetic{image.clone()};
    faceRoi = faceWithGlassesArithmetic(cv::Range(150, 250), cv::Range(140, 440));

    cv::Mat eyeRoiChannels[3];
    cv::split(faceRoi, eyeRoiChannels);

    cv::Mat maskedEyeRoiChannels[3];
    cv::Mat maskedEye;

    for (int i = 0; i < 3; ++i)
    {
        // Use the mask to create the masked eye region
        cv::multiply(eyeRoiChannels[i], (1 - glassesMaskChannels[i]), maskedEyeRoiChannels[i]);
    }

    cv::merge(maskedEyeRoiChannels, 3, maskedEye);

    cv::Mat maskedGlasses;
    cv::multiply(glassesBGR, glassesMask, maskedGlasses);

    cv::Mat eyeRoiFinal;
    cv::add(maskedEye, maskedGlasses, eyeRoiFinal);

    // Replace the eye ROI with the output from the previous section
    eyeRoiFinal.copyTo(faceRoi);

    // Now do the same operation using bitwise operations
    cv::Mat faceWithGlassesBitwise{image.clone()};
    faceRoi = faceWithGlassesBitwise(cv::Range(150, 250), cv::Range(140, 440));

    cv::Mat eyeChannelsBitwise[3];
    cv::Mat eyeRoiChannelsBitwise[3];
    cv::Mat maskedGlassesBitwise;
    cv::Mat eyeRoiFinalBitwise;

    cv::split(faceRoi, eyeChannelsBitwise);

    for (int i = 0; i < 3; ++i)
    {
        cv::bitwise_and(eyeChannelsBitwise[i], glassesMaskChannels[i], eyeRoiChannelsBitwise[i]);
    }


    cv::imshow("Masked eye region", maskedEye);
    cv::imshow("Masked glasses", maskedGlasses);
    cv::imshow("Final eye ROI", eyeRoiFinal);
    cv::imshow("Face with glasses using arithmetic operations", faceWithGlassesArithmetic);
    cv::imshow("Face with glasses using bitwise operations", faceWithGlassesBitwise);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}