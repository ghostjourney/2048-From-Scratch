#include "game2048/tile.hpp"

#include "gfs/graphics.hpp"


Game2048::Tile::Tile(const gfs::RVector<float, 2> pos, const gfs::RVector<float, 2> dimensions) {
    mPos = pos;
    mDimensions = dimensions;
}

void Game2048::Tile::Draw(std::vector<gfs::Vertex2D>& vertices) {
    gfs::Vertex2D* start = gfs::DrawRectangleVertex2D::Allocate(vertices);
    gfs::RVector<float, 2> origin{400.0, 400.0};
    gfs::DrawRectangleVertex2D::WriteVertices(start, origin, 200.0f, 200.0f);
    auto color = gfs::RVector<float, 4>{0.0f, 1.0f, 0.0, 1.0};
    gfs::DrawRectangleVertex2D::WriteColor(start, color);
}
