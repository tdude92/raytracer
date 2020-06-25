#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    int w = 160, h = 160, n_channels = 3, quality = 100;
    u_int8_t* img = new u_int8_t[w * h * n_channels];

    for (int i = 0; i < w * h * n_channels; i += n_channels) {
        int y = i / 3 / h;
        int x = i / 3 - y * h;

        int x_parity = x / 20 % 2;
        int y_parity = y / 20 % 2;

        if (x_parity == y_parity) {
            img[i] = 255;
            img[i + 1] = 255;
            img[i + 2] = 255;
        } else {
            img[i] = 0;
            img[i + 1] = 0;
            img[i + 2] = 0;
        }
    }

    stbi_write_jpg("test.jpg", w, h, n_channels, img, quality);
    return 0;
}