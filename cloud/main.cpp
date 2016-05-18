#include <iostream>

#include <map>

#include <rapp/objects/picture/picture.hpp>

#include <rapp-robots-api/info/info.hpp>
#include <rapp-robots-api/vision/vision.hpp>
#include <rapp-robots-api/navigation/navigation.hpp>
#include <rapp-robots-api/communication/communication.hpp>

#include <rapp-cloud-api/upload_file.hpp>
#include <rapp-cloud-api/hazard_detection_door_check.hpp>
#include <rapp-cloud-api/hazard_detection_light_check.hpp>

using cp = rapp::robot::vision::camera_params;
using cr = rapp::robot::vision::camera_resolution; 

#define host "roman"

int main(int argc, char * argv[]) {
    // create info module
    rapp::robot::info info(argc, argv);
    
    // create vision module 
    rapp::robot::vision vis(argc, argv); 
    
    // create communication module
    rapp::robot::communication comm(argc, argv);
    
    // create navigation module
    rapp::robot::navigation nav(argc, argv);
 
    std::map<int, int> camera_params;

    // change camera parameters
    camera_params[cp::auto_exposure] = 1;
    vis.set_camera_params(0, camera_params);

    // capture image
    rapp::object::picture::Ptr pic = vis.capture_image(0, cr::vga, "png");

    // call cloud service
    int door_angle = rapp::cloud::hazard_detection_door_check(pic, host);
    
    if (door_angle > 1)
        comm.text_to_speech("You've left the door open!");

    // change camera parameters
    camera_params[cp::auto_exposure] = 0; 
    camera_params[cp::exposure] = 10;
    vis.set_camera_params(0, camera_params);

    // capture image
    pic = vis.capture_image(0, cr::vga, "png"); 

    // call cloud service
    int light_level = rapp::cloud::hazard_detection_light_check(pic, host);

    if (light_level > 30)
        comm.text_to_speech("Don't forget to turn off the lights!");

    return 0;
}
