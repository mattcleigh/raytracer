#ifndef IO_H
#define IO_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "float3.h"

// Write the pixels to a file
void write_to_file(const std::vector<std::vector<float3>>& pixels, const std::string filename) {
    std::ofstream file_stream;
    file_stream.open(filename);

    // First line of any PPM file
    int image_h = pixels.size();
    int image_w = pixels[0].size();
    file_stream << "P3\n"
                << image_w << ' ' << image_h << "\n255\n";

    // Loop through all pixels and write the color
    for (int i = image_h; i--;) {
        for (int j = 0; j < image_w; j++) {
            file_stream << pixels[i][j].r() << ' ' << pixels[i][j].g() << ' ' << pixels[i][j].b() << '\n';
        }
    }
    file_stream.close();
}

#endif  // IO_H
