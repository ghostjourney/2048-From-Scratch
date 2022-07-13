#pragma once

#include "gfs/matrix.hpp"

#ifdef __cplusplus
#include <simd/simd.h>
#endif

namespace gfs {

/**
 * Vertex2D
 *
 * Holds data for a 2D Vertex
 */
struct Vertex2D {
#ifdef __APPLE__
    simd_float2 pos;
    simd_float4 color;
    simd_float2 tex;
#else
    std::array<float, 2> pos;
    std::array<float, 4> color;
    std::array<float, 2> tex;
#endif

    /**
     * Set the position coordinates
     * \param x x coordinate
     * \param y y coordinate
     */
    inline void SetPos(float x, float y) noexcept {
#ifdef __APPLE__
        pos = simd_make_float2(x, y);
#else
        pos[0] = x;
        pos[1] = y;
#endif
    }

    inline void SetPos(gfs::RVector<float, 2>& v) noexcept {
#ifdef __APPLE__
        pos = simd_make_float2(v[0], v[1]);
#else
        pos[0] = v[0];
        pos[1] = v[1];
#endif
    }

    inline void SetTex(float x, float y) noexcept {
#ifdef __APPLE__
        tex = simd_make_float2(x, y);
#else
        tex[0] = x;
        tex[1] = y;
#endif
    }

    inline void SetTex(gfs::RVector<float, 2> v) noexcept {
#ifdef __APPLE__
        tex = simd_make_float2(v[0], v[1]);
#else
        tex[0] = v[0];
        tex[1] = v[1];
#endif
    }

    inline void SetColor(gfs::RVector<float, 4>& v) noexcept {
#ifdef __APPLE__
        color = simd_make_float4(v[0], v[1], v[2], v[3]);
#else
        color[0] = v[0];
        color[1] = v[1];
        color[2] = v[2];
        color[3] = v[3];
#endif
    }

};

/**
 * Vertex3D
 *
 * Holds data for a 3D Vertex
 */
struct Vertex3D {
#ifdef __APPLE__
    simd_float3 pos;
    simd_float4 color;
    simd_float2 tex;
#else
    std::array<float, 3> pos;
    std::array<float, 4> color;
    std::array<float, 2> tex;
#endif
    
    /**
     * Set the position coordinates
     * \param x x coordinate
     * \param y y coordinate
     * \param z z coordinate
     */
    inline void SetPos(float x, float y, float z) noexcept {
#ifdef __APPLE__
        pos = simd_make_float3(x, y, z);
#else
        pos[0] = x;
        pos[1] = y;
        pos[2] = z;
#endif
    }

    inline void SetPos(RVector<float, 3> v) noexcept {
#ifdef __APPLE__
        pos = simd_make_float3(v[0], v[1], v[2]);
#else
        pos[0] = v[0];
        pos[1] = v[1];
        pos[2] = v[2];
#endif
    }

    inline void SetTex(float x, float y) noexcept {
#ifdef __APPLE__
        tex = simd_make_float2(x, y);
#else
        tex[0] = x;
        tex[1] = y;
#endif
    }

    inline void SetTex(gfs::RVector<float, 2> v) noexcept {
#ifdef __APPLE__
        tex = simd_make_float2(v[0], v[1]);
#else
        tex[0] = v[0];
        tex[1] = v[1];
#endif
    }

    inline void SetColor(gfs::RVector<float, 4>& v) noexcept {
#ifdef __APPLE__
        color = simd_make_float4(v[0], v[1], v[2], v[3]);
#else
        color[0] = v[0];
        color[1] = v[1];
        color[2] = v[2];
        color[3] = v[3];
#endif
    }
};
};
