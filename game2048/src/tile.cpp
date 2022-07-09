#include "game2048/tile.hpp"


Game2048::Tile::Tile(const gfs::RVector<float, 2> pos, const gfs::RVector<float, 2> dimensions) {
    mPos = pos;
    mDimensions = dimensions;
}

void Game2048::Tile::Draw(gfs::Buffer<float, 2>& vertices) {
    float* buffer = vertices.BlockAllocate(6);

    buffer[0] = 0.0;
    buffer[1] = 1.0;

    buffer[2] = 0.0;
    buffer[3] = 0.0;

    buffer[4] = 1.0;
    buffer[5] = 0.0;

    buffer[6] = 0.0;
    buffer[7] = 1.0;

    buffer[8] = 1.0;
    buffer[9] = 0.0;

    buffer[10] = 1.0;
    buffer[11] = 1.0;
}
