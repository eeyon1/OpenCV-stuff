#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    // Create named windows for displaying output
    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Mask", WINDOW_AUTOSIZE);

    // Set up camera
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        cout << "Error: Could not open camera." << endl;
        return -1;
    }

    // Define colour ranges
    Scalar lower_red = Scalar(0, 0, 100);
    Scalar upper_red = Scalar(10, 10, 255);

    Scalar lower_green = Scalar(0, 100, 0);
    Scalar upper_green = Scalar(10, 255, 10);

    Scalar lower_blue = Scalar(100, 0, 0);
    Scalar upper_blue = Scalar(255, 10, 10);

    Scalar lower_yellow = Scalar(0, 100, 100);
    Scalar upper_yellow = Scalar(10, 255, 255);

    Scalar lower_black = Scalar(0, 0, 0);
    Scalar upper_black = Scalar(10, 10, 10);

    while (true)
    {
        // Capture a frame from the camera
        Mat frame;
        cap >> frame;

        // Convert the frame to the HSV colour space
        Mat hsv_frame;
        cvtColor(frame, hsv_frame, COLOR_BGR2HSV);

        // Create masks for each colour
        Mat red_mask, green_mask, blue_mask, yellow_mask, black_mask;
        inRange(hsv_frame, lower_red, upper_red, red_mask);
        inRange(hsv_frame, lower_green, upper_green, green_mask);
        inRange(hsv_frame, lower_blue, upper_blue, blue_mask);
        inRange(hsv_frame, lower_yellow, upper_yellow, yellow_mask);
        inRange(hsv_frame, lower_black, upper_black, black_mask);

        // Combine the masks into one image
        Mat mask = red_mask | green_mask | blue_mask | yellow_mask | black_mask;

        // Display the original image and the mask
        imshow("Original", frame);
        imshow("Mask", mask);

        // Exit the loop if the user presses the "q" key
        if (waitKey(1) == 'q')
            break;
    }

    // Release the camera and destroy the windows
    cap.release();
    destroyAllWindows();

    return 0;
}
