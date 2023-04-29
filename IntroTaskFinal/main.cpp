#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    // Load the image
    Mat image = imread("C:/Open CV/OpenCV Task/Images/BlueCar.bmp");

    // Convert the image to HSV colour space
    Mat hsv;
    cvtColor(image, hsv, COLOR_BGR2HSV);

    // Define colour range for red images
    Scalar lower_red_range = Scalar(0, 100, 100);
    Scalar upper_red_range = Scalar(10, 255, 255);

    // Define the range for green images
    Scalar lower_green = Scalar(35, 50, 50);
    Scalar upper_green = Scalar(75, 255, 255);

    // Define colour range for blue images
    Scalar lower_blue_range = Scalar(100, 50, 50);
    Scalar upper_blue_range = Scalar(130, 255, 255);

    // Threshold the image to get only red/green/blue pixels
    Mat red_mask, green_mask, blue_mask;
    inRange(hsv, lower_red_range, upper_red_range, red_mask);
    inRange(hsv, lower_green, upper_green, green_mask);
    inRange(hsv, lower_blue_range, upper_blue_range, blue_mask);

    // Apply the mask to the original image to get only red/green/blue pixels
    Mat red_image, green_image, blue_image;
    bitwise_and(image, image, red_image, red_mask);
    bitwise_and(image, image, green_image, green_mask);
    bitwise_and(image, image, blue_image, blue_mask);

    // Calculate the percentage of each colour in the image
    double red_percentage = (countNonZero(red_mask) / (double)(image.rows * image.cols)) * 100.0;
    double green_percentage = (countNonZero(green_mask) / (double)(image.rows * image.cols)) * 100.0;
    double blue_percentage = (countNonZero(blue_mask) / (double)(image.rows * image.cols)) * 100.0;

    // Display the colour of the image as text and image based on the percentage of the colour detected
    if (red_percentage > 10)
    {
        imshow("Red Component", red_image);
        cout << "The image is red" << endl;
    }
    else if (green_percentage > 10)
    {
        imshow("Green Component", green_image);
        cout << "The image is green" << endl;
    }
    else if (blue_percentage > 10)
    {
        imshow("Blue Component", blue_image);
        cout << "The image is blue" << endl;
    }
    else
    {
        cout << "Unknown colour" << endl;
    }

    // Display the result
    imshow("Original Image", image);

    waitKey(0);

    return 0;
}
