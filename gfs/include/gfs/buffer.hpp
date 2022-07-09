#pragma once

#include <memory>

#include <algorithm>

namespace gfs {

template<typename T, int width>
class Buffer {
    public:
    Buffer() : mSize{0}, mCapacity{width*10} {
        mData = std::make_unique<T[]>(mCapacity);
    }

    ~Buffer() {

    }

    Buffer(const Buffer&)=delete;

    Buffer& operator=(const Buffer&)=delete;

    T* GetData() const noexcept {
        return mData.get();
    }

    size_t GetSize() const noexcept {
        return mSize;
    }

    size_t GetCapacity() const noexcept {
        return mCapacity;
    }

    size_t GetDataSize() const noexcept {
        return sizeof(T);
    }

    inline T& operator[](size_t pos) const noexcept {
        return mData[pos];
    }

    inline bool HasCapacity(size_t size) const noexcept {
        return (size + mSize) <= mCapacity;
    }

    inline bool Resize(size_t next_capacity) {
        auto next_data = std::make_unique<T[]>(next_capacity);
        std::copy(&mData[0], &mData[mSize], &next_data[0]);
        mCapacity = next_capacity;
        mData = std::move(next_data);
    }

    inline T* BlockAllocate(size_t size) {
        size_t start = mSize;
        if(!HasCapacity(size)) {
            Resize((size*width) + (mCapacity * 2));
        }
        mSize = size;
        return &mData[start];
    }

    inline size_t GetWidth(void) const noexcept {
        return width;
    }


    private:
    /// buffer
    std::unique_ptr<T[]> mData;

    /// buffer size
    size_t mSize;

    /// buffer capacity
    size_t mCapacity;
};
};
