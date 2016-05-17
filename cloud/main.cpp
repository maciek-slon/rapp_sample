#include <iostream>

#include <chrono>
#include <thread>

#include <rapp-robots-api/info/info.hpp>

#include <rapp/objects/picture/picture.hpp>
#include <rapp-robots-api/vision/vision.hpp>

#include <rapp-robots-api/communication/communication.hpp>

#include <rapp-cloud-api/hazard_detection_door_check.hpp>

#include <opencv2/opencv.hpp>

int main(int argc, char * argv[]) {
    // create info module
    rapp::robot::info info(argc, argv);
    
    // create vision module 
    rapp::robot::vision vis(argc, argv); 
    
    // create communication module
    rapp::robot::communication comm(argc, argv);
 
    rapp::object::picture::Ptr picture;
    picture = vis.capture_image(0, 3, "png"); 

    int door_angle = rapp::cloud::hazard_detection_door_check(picture); 

    if (door_angle >= 2)
        comm.text_to_speech("Door left open");
    else
        comm.text_to_speech("Door closed");

    return 0;
}
