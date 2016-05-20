#include <iostream>

#include <map>

#include <rapp/objects/picture/picture.hpp>

#include <rapp-robots-api/info/info.hpp>
#include <rapp-robots-api/vision/vision.hpp>
#include <rapp-robots-api/navigation/navigation.hpp>
#include <rapp-robots-api/communication/communication.hpp>

#include <rapp-cloud-api/upload_file.hpp>
#include <rapp-cloud-api/object_recognition_learn.hpp>
#include <rapp-cloud-api/object_recognition_detect.hpp>
#include <rapp-cloud-api/object_recognition_load.hpp>
#include <rapp-cloud-api/object_recognition_clear.hpp>

using cp = rapp::robot::vision::camera_params;
using cr = rapp::robot::vision::camera_resolution; 
namespace ro = rapp::object;

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

    std::vector<std::string> names = {"dog", "cow", "cat"};
    std::vector<std::string> models;
    
    for (const auto & n : names) {
        models.push_back(info.get_path("share/whats_this/" + n + ".jpg"));
    }
    
    std::vector<ro::object> objs;
    
    rapp::cloud::object_recognition_clear("maciek", host, "9090");

    rapp::cloud::object_recognition_learn("maciek", pic, "cat", host, "9090");
    
    rapp::cloud::object_recognition_load("maciek", {"cat"}, host, "9090");
    
    objs = rapp::cloud::object_recognition_detect("maciek", pic, 1, host, "9090");
    std::cout << "Found " << objs.size() << " objects.\n";
    for(const auto & o : objs)
        std::cout << "\t" << o.name() << ", " << o.score() << "\n";
    
    objs = rapp::cloud::object_recognition_detect("dudek", pic, 1, host, "9090");
    std::cout << "Found " << objs.size() << " objects.\n";
    for(const auto & o : objs)
        std::cout << "\t" << o.name() << ", " << o.score() << "\n";





    rapp::cloud::object_recognition_clear("rapp", host, "9090");
    names = {"ahmad", "dilmah", "lipton", "ahmad2"};
    for (const auto & n : names) {
        auto pic = std::make_shared<ro::picture>(info.get_path("share/whats_this/" + n + ".png"));
        rapp::cloud::object_recognition_learn("rapp", pic, n, host, "9090", false);
    }
    
    rapp::cloud::object_recognition_load("rapp", names, host, "9090");
    
    auto scn = std::make_shared<ro::picture>(info.get_path("share/whats_this/scene2.png"));
    objs = rapp::cloud::object_recognition_detect("rapp", pic, 1, host, "9090");
    std::cout << "Found " << objs.size() << " objects.\n";
    for(const auto & o : objs)
        std::cout << "\t" << o.name() << ", " << o.score() << "\n";
        
    return 0;
}
