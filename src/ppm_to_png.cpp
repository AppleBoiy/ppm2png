#include "ppm_to_png.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <png.h>

PPMImage readPPM(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open file");
    }

    std::string line;
    std::string magicNumber;
    std::getline(file, line);
    std::istringstream iss(line);
    iss >> magicNumber;
    if (magicNumber != "P6" && magicNumber != "P3" && magicNumber != "P1") {
        throw std::runtime_error("Invalid PPM format");
    }

    // Skip comments
    do {
        std::getline(file, line);
    } while (line[0] == '#');

    int width, height;
    std::istringstream iss2(line);
    iss2 >> width >> height;

    int maxColorValue = 255;
    if (magicNumber == "P3") {
        file >> maxColorValue;
        file.ignore(256, '\n'); // Skip the newline character after the header
    }

    std::vector<unsigned char> pixels(width * height * 3);

    if (magicNumber == "P6") {
        file.read(reinterpret_cast<char*>(pixels.data()), pixels.size());
    } else if (magicNumber == "P3") {
        int r, g, b;
        for (int i = 0; i < width * height * 3; i += 3) {
            file >> r >> g >> b;
            pixels[i] = static_cast<unsigned char>(r * 255 / maxColorValue);
            pixels[i + 1] = static_cast<unsigned char>(g * 255 / maxColorValue);
            pixels[i + 2] = static_cast<unsigned char>(b * 255 / maxColorValue);
        }
    } else if (magicNumber == "P1") {
        for (int i = 0; i < width * height; ++i) {
            int pixel;
            file >> pixel;
            unsigned char value = pixel == 1 ? 0 : 255;
            pixels[i * 3 + 0] = value; // Red
            pixels[i * 3 + 1] = value; // Green
            pixels[i * 3 + 2] = value; // Blue
        }
    }

    return {width, height, maxColorValue, pixels};
}

void writePNG(const std::string& filename, const PPMImage& image) {
    FILE *fp = fopen(filename.c_str(), "wb");
    if (!fp) {
        throw std::runtime_error("Could not open file for writing");
    }

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        fclose(fp);
        throw std::runtime_error("Could not create PNG write struct");
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_write_struct(&png, nullptr);
        fclose(fp);
        throw std::runtime_error("Could not create PNG info struct");
    }

    if (setjmp(png_jmpbuf(png))) {
        png_destroy_write_struct(&png, &info);
        fclose(fp);
        throw std::runtime_error("Error during PNG creation");
    }

    png_init_io(png, fp);

    png_set_IHDR(
            png, info, image.width, image.height, 8,
            PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT
    );
    png_write_info(png, info);

    std::vector<png_bytep> row_pointers(image.height);
    for (int y = 0; y < image.height; ++y) {
        row_pointers[y] = const_cast<png_bytep>(&image.pixels[y * image.width * 3]);
    }

    png_write_image(png, row_pointers.data());
    png_write_end(png, nullptr);

    png_destroy_write_struct(&png, &info);
    fclose(fp);
}
