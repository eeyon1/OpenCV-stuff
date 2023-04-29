#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// Define function for comparing images
double compareImages(Mat image1, Mat image2)
{
    // Define matrices
    Mat image1_gray, image2_gray;

    // Convert to grayscale
    cvtColor(image1, image1_gray, COLOR_BGR2GRAY);
    cvtColor(image2, image2_gray, COLOR_BGR2GRAY);

    // Initialise mean squared error
    double mse = 0.0;

    // Get number of rows and columns in grayscale image
    int rows = image1_gray.rows;
    int cols = image1_gray.cols;

    // Calculate mean squared error between the two grayscale images
    for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                mse += pow((image1_gray.at<uchar>(i, j) - image2_gray.at<uchar>(i, j)), 2);
            }
        }

    // Divide mean squared error by the total number of pixels
    mse /= (rows * cols);

    // Calculate peak signal-noise ratio from mean squared speed value
    double psnr = 10.0 * log10((255.0 * 255.0) / mse);

    return psnr;
}

int main()
{
    // Load the input image
    Mat inputframe = imread("C:/LABS/Umbrella (Yellow Line).png");

    // Define input points
    Point2f inputPoints[4];
    inputPoints[0] = Point2f(0, 0);
    inputPoints[1] = Point2f(0, 350);
    inputPoints[2] = Point2f(350, 0);
    inputPoints[3] = Point2f(350, 350);

    // Define output points
    Point2f outputPoints[4];
    outputPoints[0] = Point2f(0, 0);
    outputPoints[1] = Point2f(0, 350);
    outputPoints[2] = Point2f(350, 0);
    outputPoints[3] = Point2f(350, 350);

    // Compute the transformation matrix
    Mat transformationMatrix = getPerspectiveTransform(inputPoints, outputPoints);

    // Define an output image
    Mat outputImage;

    // Apply the perspective transformation
    warpPerspective(inputframe, outputImage, transformationMatrix, inputframe.size());

    // Load the four symbols
    Mat image1 = imread("C:/LABS/Circle (Red Line).png");
    Mat image2 = imread("C:/LABS/Star (Green Line).png");
    Mat image3 = imread("C:/LABS/Triangle (Blue Line).png");
    Mat image4 = imread("C:/LABS/Umbrella (Yellow Line).png");

    // Define an array of the four images
    Mat images[] = {image1, image2, image3, image4};

    // Set the threshold value
    double threshold = 25.0;

    // Define an array of the four image names
    string imageNames[] = {"Circle", "Star", "Triangle", "Umbrella"};

    // Loop over the four images
    for (int i = 0; i < 4; i++)
        {
            // Compute the similarity between the input image and the output image
            double similarity = compareImages(outputImage, images[i]);

            // Display the similarity value
            cout << imageNames[i] << " Similarity: " << similarity << endl;

            // Compare the similarity value to the threshold
            if (similarity > threshold)
                {
                    cout << imageNames[i] << " matches the input symbol\n" << endl;
                }
            else
                {
                    cout << imageNames[i] << " does not match the input symbol\n" << endl;
                }
        }

    // Display input symbol
    imshow("Input Symbol", inputframe);

    // Wait until a key is pressed
    waitKey(0);

    return 0;
}
