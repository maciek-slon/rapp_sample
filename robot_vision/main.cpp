#include <iostream>

#include <rapp/objects/picture/picture.hpp>
#include <rapp-robots-api/vision/vision.hpp>

int main() {
	rapp::robot::vision vis;
	rapp::object::picture::Ptr picture;
	picture = vis.capture_image(0, 0, "png");
	return 0;
}
