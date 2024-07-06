# PPM to PNG Converter

Converts PPM (Portable Pixel Map) images to PNG (Portable Network Graphics) format using C++.

## Dependencies

### Sample Files

- [gist:stungeye/Sample PPM File](https://gist.github.com/stungeye/9c57dc4cfd2d541e3f0c330102d63d31): A sample PPM file that can be used for testing purposes.

> [!NOTE]
> The sample PPM file is provided by [stungeye](https://gist.github.com/stungeye) on Gist.

### Required Libraries

- **libpng**: Required for PNG file I/O operations.

Ensure `libpng` is installed on your system before building the project.

### Setting Up CMakeLists.txt

In your `CMakeLists.txt`, specify the include directories for `libpng`:

```cmake
# ... other configurations

# Specify the include directories for libpng
set(PNG_INCLUDE_DIRS /opt/homebrew/Cellar/libpng/1.6.43/include)

find_package(PNG REQUIRED)

include_directories(${PNG_INCLUDE_DIRS} include)

# ... other configurations
```

## Supported Formats

The converter supports the following PPM formats:

- **P1**: Portable Bitmap format (PBM), monochrome (black and white) images.
- **P3**: Portable Pixmap format, ASCII (plain text) RGB images.
- **P6**: Portable Pixmap format, binary RGB images.

## How to Use

1. **Build the Project**
   Run the following commands to build the project:

    ```bash
   ./build.sh
    ```

2. **Convert PPM to PNG**
   Execute the compiled program with two arguments: input PPM file and output PNG file.
      ```bash
      ./build/ppm_to_png input.ppm output.png
      ```

## Sample Output

Assuming `input.ppm` is a valid PPM (P1, P3, or P6) file, the program will convert it to a PNG file named `output.png`.

```bash
$ ./build/ppm_to_png input.ppm output.png
Conversion successful. PNG file saved as output.png
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
