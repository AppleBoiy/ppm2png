#include "ppm_to_png.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " input.ppm output.png\n";
        return 1;
    }

    try {
        PPMImage image = readPPM(argv[1]);
        writePNG(argv[2], image);

        std::cout << "Conversion successful. PNG file saved as " << argv[2] << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
