#include "color.h"
#ifndef IMAGE_H
#define IMAGE_H
#include "lodepng.h"

class Image {
public:
    Image(const std::string& filepath) {
        std::vector<unsigned char> raw_data;

        // Carrega a imagem usando a lodepng
        unsigned error = lodepng::decode(raw_data, width, height, filepath);

        if (error) {
            throw std::runtime_error("Failed to load image");
        }

        // Converte os bytes para floats entre 0 e 1 e armazena em data
        data.resize(raw_data.size());
        for (size_t i = 0; i < raw_data.size(); ++i) {
            data[i] = raw_data[i] / 255.0f;
        }

        channels = 4; // PNG images always have 4 channels
    }
    glm::vec3 getPixel(int x, int y) const {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            throw std::out_of_range("Pixel coordinates out of range");
        }

        int index = (y * width + x) * channels;
        return glm::vec3(data[index], data[index + 1], data[index + 2]);
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }
    

private:
    unsigned width;
    unsigned height;
    int channels;
    std::vector<float> data;
};

#endif

