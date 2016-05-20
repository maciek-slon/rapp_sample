#include <iostream>
#include <map>

#include <rapp/objects/pose_stamped/pose_stamped.hpp>

#include <rapp-robots-api/info/info.hpp>
#include <rapp-robots-api/vision/vision.hpp>
#include <rapp-robots-api/navigation/navigation.hpp>
#include <rapp-robots-api/communication/communication.hpp>

#include <rapp-cloud-api/face_detection.hpp>
#include <rapp-cloud-api/face_recognition.hpp>

using cp = rapp::robot::vision::camera_params;
using cr = rapp::robot::vision::camera_resolution; 


#define host "roman"
#define user "rapp"

int main(int argc, char * argv[]) {
    namespace ro = rapp::object;
    
    // create info module
    rapp::robot::info info(argc, argv);
    
    // create vision module
    rapp::robot::vision vis(argc, argv); 
    
    // create communication module
    rapp::robot::communication comm(argc, argv);
    
    // create navigation module
    rapp::robot::navigation nav(argc, argv);
 
    auto pic = vis.capture_image(0, cr::vga, "png");
    auto faces = rapp::cloud::face_detection(pic, false, host);
    
    if (faces.size() > 0) {
        comm.text_to_speech(std::to_string(faces.size()) + " faces found.");
    } else {
        comm.text_to_speech("I can't see any faces");
    }
    for (auto f : faces) {
        std::cout << "Face center: " << f.cx() << "," << f.cy() << "\n";
    }

    std::vector<std::string> names = {
        "Scarlett Johansson",
        "Jason Statham",
        "Mila Kunis",
        "Ryan Reynolds",
        "Christian Bale"
    };

    auto ret = rapp::cloud::face_recognition("faces", pic, "/home/mstefanc/rapp_platform_files/faces/actors.yml", faces, host, "9090", false);
    for (auto i : ret) {
        comm.text_to_speech(names[i]);
    }

    return 0;
}
