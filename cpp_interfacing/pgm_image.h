#ifndef __PGM_IMAGE_H__
#define __PGM_IMAGE_H__

#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>

enum class pgm_t { P1=1, P2, P3, P4, P5, P6 };

uint8_t *read_pgm_image(int *width, int *height, std::string filename) {
    pgm_t format;
    std::ifstream in(filename);
    std::string line;
    std::stringstream ss;

    /* first line = image format */
    getline(in, line);
    if (line.length() < 2 || line[0]!='P' || (int)(line[1]-'0')>6) {
        std::cerr << "read_pgm_image: expected image format specification" << std::endl;
        exit(EXIT_FAILURE);
    }
    format = (pgm_t)(line[1]-'0');

    /* second line = comment */
    getline(in, line);
    if (line.length() < 1  || line[0] != '#') {
        std::cerr << "read_pgm_image: comment expected in second line" << std::endl;
        exit(EXIT_FAILURE);
    }

    /* third line = width and height of image */
    /* forth line = max. value for intensity */
    int max;
    ss << in.rdbuf();
    ss >> *width >> *height >> max;

    size_t elems = *width * *height;
    switch (format) {
        default: break;
        case pgm_t::P3: case pgm_t::P6: elems *= 3; break;
    }

    uint8_t *img = new uint8_t[elems];

    // data
    switch (format) {
        default:
            for (size_t i=0; i<elems; ++i) ss >> img[i];
            break;
        case pgm_t::P4: case pgm_t::P5: case pgm_t::P6:
            in.read((char *)img, elems); break;
    }

    int mincolor = 255, maxcolor = 0;
    for (size_t i=0; i<elems; ++i) {
        auto tmp = img[i];
        if (tmp > maxcolor) { maxcolor = tmp; }
        if (tmp < mincolor) { mincolor = tmp; }
    }
    std::cerr << "read_pgm_image('" << filename << "', P" << (int)format << ", "
              << *width << "x" << *height << " [" << mincolor << ".."
              << maxcolor << "]|" << max << "|)" << std::endl;
    in.close();

    return img;
}


void write_pgm_image(const uint8_t *img, int width, int height, std::string filename, pgm_t format=pgm_t::P2) {
    size_t elems = width * height;
    switch (format) {
        default: break;
        case pgm_t::P3: case pgm_t::P6: elems *= 3; break;
    }

    int mincolor = 255, maxcolor = 0;
    for (size_t i=0; i<elems; ++i) {
        auto tmp = img[i];
        if (tmp > maxcolor) { maxcolor = tmp; }
        if (tmp < mincolor) { mincolor = tmp; }
    }
    std::cerr << "write_pgm_image('" << filename << "', P" << (int)format << ", "
              << width << "x" << height << " [" << mincolor << ".."
              << maxcolor << "])" << std::endl;

    std::ofstream out(filename);
    out << "P" << (int)format << std::endl
        << "# custom PNM reader/writer" << std::endl
        << width << " " << height << std::endl;

    // depth
    switch (format) {
        default:          out << maxcolor << std::endl; break;
        case pgm_t::P1: case pgm_t::P4: out << "1" << std::endl;      break;
    }

    // data
    switch (format) {
        default:
            for (size_t i=0; i<elems; ++i) out << " " << img[i];
            break;
        case pgm_t::P4: case pgm_t::P5: case pgm_t::P6:
            out.write((const char *)img, elems); break;
    }

    out.close();
}

#endif /* __PGM_IMAGE_H__ */

