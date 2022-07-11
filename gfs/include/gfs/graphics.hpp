#pragma once

#include "gfs/matrix.hpp"

#include "gfs/vertex.hpp"

namespace gfs {

struct DrawRectangleVertex2D {

    constexpr static size_t GetSize() noexcept {
        return 6;
    }
    
    static Vertex2D* Allocate(std::vector<Vertex2D>& vec) {
        for(int i = 0; i < 6; ++i) {
            vec.emplace_back(Vertex2D());
        }
        return &vec[vec.size()-6];
    }

    static void WriteColor(Vertex2D* buffer, RVector<float, 4>& color) noexcept {
        for(int i = 0; i < 6; ++i) {
            buffer[i].SetColor(color);
        }
    }

    static void WriteVertices(Vertex2D* buffer, const RVector<float, 2>& origin, const float height, const float width) noexcept {
        float x = origin.GetX();
        float y = origin.GetY();
        buffer[0].SetPos(x, y+height);
        buffer[1].SetPos(x, y);
        buffer[2].SetPos(x + width, y);
        buffer[3].SetPos(x, y + height);
        buffer[4].SetPos(x + width, y);
        buffer[5].SetPos(x + width, y + height);
    }
};

};
