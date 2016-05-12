#include <iostream>
#include <fstream>
#include <rapp-robots-api/localization/localization.hpp>

int main() {
	rapp::robot::localization loc;
	rapp::object::qr_code_map qr_map;
	std::ifstream ifstr("../share/rapp_navigation/example_qr_map.xml");
	qr_map = loc.load_qr_code_map(ifstr);
	std::cout<<qr_map.labels.at(0)<<std::endl;
	std::cout<<qr_map.labels.at(3)<<std::endl;
	return 0;
}
