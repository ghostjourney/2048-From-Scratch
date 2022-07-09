#pragma once

#include "gfs/matrix.hpp"

#include "gfs/buffer.hpp"

namespace Game2048 {

class Tile {
    public:
    Tile(const gfs::RVector<float, 2> pos, const gfs::RVector<float, 2> dimensions);
    void Draw(gfs::Buffer<float, 2>& vertices);

    private:
    /// dimensions: x, y
    gfs::RVector<float, 2> mPos;

    /// dimensions: width, height
    gfs::RVector<float, 2> mDimensions;
};
};
