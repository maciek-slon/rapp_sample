#include <iostream>
#include <fstream>
#include <string>

#include <rapp-robots-api/info/info.hpp>
#include <rapp-robots-api/localization/localization.hpp>


int main(int argc, char * argv[]) {
    rapp::robot::info info(argc, argv);
    rapp::robot::localization loc;
    rapp::object::qr_code_map qr_map;
    std::ifstream ifstr(info.get_path("share/rapp_navigation/example_qr_map.xml"));
    qr_map = loc.load_qr_code_map(ifstr);
    std::cout<<qr_map.labels.at(0)<<std::endl;
    std::cout<<qr_map.labels.at(3)<<std::endl;
    return 0;
}
