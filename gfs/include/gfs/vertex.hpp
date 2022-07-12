#pragma once

#include "gfs/matrix.hpp"

namespace gfs {

#ifdef __APPLE__
#undef __cplusplus
#define _Bool bool
#include <simd/simd.h>
#undef _Bool
#define __cplusplus
struct Vertex2D {
    simd_float2 pos;
    simd_float4 color;
    simd_float2 tex;

    inline void SetPos(float x, float y) noexcept {
        pos = simd_make_float2(x, y);
    }

    inline void SetPos(gfs::RVector<float, 2>& v) noexcept {
        pos = simd_make_float2(v[0], v[1]);
    }

    inline void SetTex(float x, float y) noexcept {
        tex = simd_make_float2(x, y);
    }

    inline void SetTex(gfs::RVector<float, 2> v) noexcept {
        tex = simd_make_float2(v[0], v[1]);
    }

    inline void SetColor(gfs::RVector<float, 4>& v) noexcept {
        color = simd_make_float4(v[0], v[1], v[2], v[3]);
    }

};
struct Vertex3D {
    simd_float3 pos;
    simd_float4 color;
    simd_float2 tex;

    inline void SetPos(float x, float y, float z) noexcept {
        pos = simd_make_float3(x, y, z);
    }

    inline void SetPos(RVector<float, 3> v) noexcept {
        pos = simd_make_float3(v[0], v[1], v[2]);
    }

    inline void SetTex(float x, float y) noexcept {
        tex = simd_make_float2(x, y);
    }

    inline void SetTex(gfs::RVector<float, 2> v) noexcept {
        tex = simd_make_float2(v[0], v[1]);
    }

    inline void SetColor(gfs::RVector<float, 4>& v) noexcept {
        color = simd_make_float4(v[0], v[1], v[2], v[3]);
    }
};
#else
struct Vertex2D {
    std::array<float, 2> pos;
    std::array<float, 4> color;
    std::array<float, 2> tex;
    
    inline void SetPos(float x, float y) noexcept {
        
    }

    inline void SetPos(gfs::RVector<float, 2>& v) noexcept {
       
    }

    inline void SetTex(float x, float y) noexcept {
        
    }

    inline void SetTex(gfs::RVector<float, 2> v) noexcept {
        
    }

    inline void SetColor(gfs::RVector<float, 4>& v) noexcept {
        
    }

};

struct Vertex3D {
    std::array<float, 3> pos;
    std::array<float, 4> color;
    std::array<float, 2> tex;

    inline void SetPos(float x, float y) noexcept {
        
    }

    inline void SetPos(gfs::RVector<float, 2>& v) noexcept {
        
    }

    inline void SetTex(float x, float y) noexcept {
       
    }

    inline void SetTex(gfs::RVector<float, 2> v) noexcept {
        
    }

    inline void SetColor(gfs::RVector<float, 4>& v) noexcept {
        
    }

};

#endif
};
