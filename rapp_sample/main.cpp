#include <iostream>

#include <rapp-robots-api/info/info.hpp>

int main(int argc, char * argv[]) {
    rapp::robot::info info(argc, argv);
    std::cout << "Hello world! Application is run from: " << info.base_path() << "\n";
    return 0;
}
