#include <iostream>
#include <map>

#include <rapp/objects/pose_stamped/pose_stamped.hpp>

#include <rapp-robots-api/info/info.hpp>
#include <rapp-robots-api/vision/vision.hpp>
#include <rapp-robots-api/navigation/navigation.hpp>
#include <rapp-robots-api/communication/communication.hpp>

#include <rapp-cloud-api/upload_file.hpp>
#include <rapp-cloud-api/path_planning_upload_map.hpp>
#include <rapp-cloud-api/path_planning_plan.hpp>

#include <rapp-cloud-api/face_detection.hpp>
#include <rapp-cloud-api/face_recognition.hpp>

#include <rapp-cloud-api/speech_detection_sphinx4.hpp>

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
 
    rapp::cloud::path_planning_upload_map(info.get_path("share/lets_go/empty.yaml"), info.get_path("share/lets_go/empty.png"), user, "empty", host, "9090", false);
    
    ro::pose_stamped start(
        ro::header(), 
        ro::pose(
            ro::point(1, 1, 0), 
            ro::quaternion()
        )
    );
    
    ro::pose_stamped goal(
        ro::header(), 
        ro::pose(
            ro::point(2, 2, 0), 
            ro::quaternion()
        )
    );
    
    auto path = rapp::cloud::path_planning_plan(user, "empty", "NAO", "dijkstra", start, goal, host, "9090", false);
    
    nav.moveAlongPath(path);

    return 0;
}
