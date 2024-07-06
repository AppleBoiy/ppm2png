#ifndef PPM_TO_PNG_H
#define PPM_TO_PNG_H

#include <vector>
#include <string>

struct PPMImage {
    int width;
    int height;
    int maxColorValue;
    std::vector<unsigned char> pixels;
};

PPMImage readPPM(const std::string& filename);
void writePNG(const std::string& filename, const PPMImage& image);

#endif // PPM_TO_PNG_H
