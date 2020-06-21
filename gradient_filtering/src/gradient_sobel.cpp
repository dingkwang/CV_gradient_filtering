#include <iostream>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

void gradientSobel()
{
    // TODO: Based on the image gradients in both x and y, compute an image 
    // which contains the gradient magnitude according to the equation at the 
    // beginning of this section for every pixel position. Also, apply different 
    // levels of Gaussian blurring before applying the Sobel operator and compare the results.
    // load image from file
    cv::Mat img;
    // img = cv::imread("../images/img1gray.png");
    img = cv::imread("../images/img1.png");

    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY); //convert from RGB to grey even for original grey image
    // create filter kernel
    float gauss_data[25] = {1, 4, 7, 4, 1,
                            4, 16, 26, 16, 4,
                            7, 26, 41, 26, 7,
                            4, 16, 26, 16, 4,
                            1, 4, 7, 4, 1};
    cv::Mat kernel = cv::Mat(5, 5, CV_32F, gauss_data);

    double sum = accumulate(begin(gauss_data), std::end(gauss_data), 0.0);
    
   for (int i = 0; i < 25; i++)
    {
        gauss_data[i] /= 273;
    }


    // apply filter
    cv::Mat blurred;
    cv::filter2D(img, blurred, -1, kernel, cv::Point(-1, -1),  0.0, cv::BORDER_DEFAULT); //-1 keep orihinsl frpyh

    float sobel_x[9] = {-1, 0, +1, -2, 0, +2, -1, 0, +1};
    cv::Mat kernel_x = cv::Mat(3, 3, CV_32F, sobel_x);

    float sobel_y[9] = {-1, -2, -1, 0, 0, 0, +1, +2, +1};
    cv::Mat kernel_y = cv::Mat(3, 3, CV_32F, sobel_y);

    // apply filter
    cv::Mat result_x, result_y;
    cv::filter2D(blurred, result_x, -1, kernel_x, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
    cv::filter2D(blurred, result_y, -1, kernel_y, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT)

    // compute magnitude image
    int r = 0;
    int c = 0;
    cv::Mat magnitude = img.clone();
    uchar* p;
    for (r = 0; r < img.rows; r++)
    {
        
        // p = magnitude.ptr<uchar>(r);
        for (c = 0; c < img.cols; c++)
        {

            //magnitude.at<unsigned char>(r, c) = 0;
            // p[c] = 0;
            // std::cout <<"  r =";
            // std::cout << r;
            // std::cout <<"  c =  ";
            // std::cout << c << endl;
            // string windowName = "Sobel operator (xy-direction)";
            // cv::namedWindow( windowName, 1 ); // create window 
            // cv::imshow(windowName, magnitude);
            // cv::waitKey(1); // wait for keyboard input before continuing
            magnitude.at<unsigned char>(r, c) = sqrt(pow(result_x.at<unsigned char>(r, c), 2) + pow(result_y.at<unsigned char>(r, c), 2));
            //magnitude.at<unsigned char>(r, c) = result_x.at<unsigned char>(r, c) + result_y.at<unsigned char>(r, c);
        }
    }
    std::cout << "magnitude.rows=";
    std::cout << magnitude.rows;
    std::cout <<"  magnitude.cols= ";
    std::cout << magnitude.cols;
    std::cout <<"  r final=";
    std::cout << r;
    std::cout <<"  c.final=  ";
    std::cout << c;
    // show result
    string windowName = "Sobel operator (xy-direction)";
    cv::namedWindow( windowName, 1 ); // create window 
    cv::imshow(windowName, magnitude);
    cv::waitKey(5000); // wait for keyboard input before continuing
}

int main()
{
    gradientSobel();
}