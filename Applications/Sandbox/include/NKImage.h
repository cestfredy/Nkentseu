#pragma once
#include <vector>
#include <string>
#include <fstream>

struct NkImage {
    int w, h;

    // Buffer RGB (3 octets par pixel)
    std::vector<unsigned char> data;

    NkImage(int w_, int h_) : w(w_), h(h_), data(w_*h_*3, 255) {}

    // Écriture d'un pixel avec vérification des bornes
    void SetPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
        if(x < 0 || x >= w || y < 0 || y >= h) return;
        int idx = (y * w + x) * 3;
        data[idx] = r;
        data[idx+1] = g;
        data[idx+2] = b;
    }

    // Sauvegarde au format PPM (P6 binaire, très simple à générer)
    void SavePPM(const std::string& filename) {
        std::ofstream f(filename, std::ios::binary);

        // En-tête PPM : format, dimensions, max value
        f << "P6\n" << w << " " << h << "\n255\n";

        // Dump brut du buffer RGB
        f.write(reinterpret_cast<const char*>(data.data()), w * h * 3);
    }

    // Tracé de ligne (algorithme de Bresenham, sans flottants)
    void DrawLine(int x0, int y0, int x1, int y1, unsigned char r = 0, unsigned char g = 0, unsigned char b = 0) {
        int dx = std::abs(x1 - x0), dy = -std::abs(y1 - y0);
        int sx = x0 < x1 ? 1 : -1;
        int sy = y0 < y1 ? 1 : -1;
        int err = dx + dy;

        while(true) {
            SetPixel(x0, y0, r, g, b);

            if(x0 == x1 && y0 == y1) break;

            int e2 = 2 * err;

            if(e2 >= dy) { err += dy; x0 += sx; }
            if(e2 <= dx) { err += dx; y0 += sy; }
        }
    }
};