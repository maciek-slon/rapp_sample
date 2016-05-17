#include <iostream>

#include <chrono>
#include <thread>

#include <rapp-robots-api/info/info.hpp>

#include <rapp/objects/picture/picture.hpp>
#include <rapp-robots-api/vision/vision.hpp>

#include <rapp-robots-api/communication/communication.hpp>

#include <opencv2/opencv.hpp>

int main(int argc, char * argv[]) {
    // create info module
    rapp::robot::info info(argc, argv);
    // create communication module
    rapp::robot::communication comm(argc, argv);
    // create vision module
    rapp::robot::vision vis(argc, argv);

    comm.text_to_speech("Show me something!");
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    rapp::object::picture::Ptr picture;
    picture = vis.capture_image(0, 3, "png");

    comm.text_to_speech("Ok");

    // convert captured image to OpenCV format
    cv::Mat img;
    img = cv::imdecode(picture->bytearray(), -1);

    // change color space to HSV
    cv::cvtColor(img, img, CV_BGR2HSV);

    // check image size and cut middle part
    cv::Size s = img.size();
    int sx = s.width * 0.3;
    int sy = s.height * 0.3;
    int w = 0.4 * s.width;
    int h = 0.4 * s.height;

    img = img(cv::Rect(sx, sy, w, h));

    // create ranges for histogram; note, that hue values are divided by 2 in OpenCV
    int hbins = 7; 
    int histSize[] = { hbins }; // set number of histogram bins
    float hranges[] = {0, 10, 29, 35, 85, 126, 160, 181};
    const float * ranges[] = { hranges };
    int channels[] = { 0 }; // use only H channel
    int numImages = 1; // we have only one image
    bool uniform = false; // non-uniform bin ranges
    bool accumulate = false; // do not accumulate output values
    int dims = 1; // we compute histogram for only one channel

    // calculate histogram for hue channel
    cv::MatND hist;
    cv::calcHist(&img, numImages, channels, cv::Mat(), hist, dims, histSize, ranges, uniform, accumulate);

    // add first and last bin, as both are for red color
    hist.at<float>(0) += hist.at<float>(hbins-1);

    // find maximum value
    float max = -1;
    int maxid = -1;
    for (int i = 0; i < hbins - 2; ++i) {
        if (hist.at<float>(i) > max) {
            max = hist.at<float>(i);
            maxid = i;
        }
    }

    // tell the name of the dominant color
    std::vector<std::string> colors = {"red", "orange", "yelow", "green", "blue", "violet", "red"};
    comm.text_to_speech(colors[maxid]);

    return 0;
}
