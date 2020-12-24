#pragma once

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace aoc {

template <typename T>
bool in_range(const T& val, const T& low_incl, const T& high_excl)
{
    return val >= low_incl && val < high_excl;
}

template <size_t SIZE>
struct Vec
{
    union
    {
        struct
        {
            int x, y, z, w;
        };
        struct
        {
            int elements[SIZE];
        };
    };

    Vec()
    {
    }

    Vec(int x_, int y_) : x(x_), y(y_)
    {
    }

    Vec(int x_, int y_, int z_) : x(x_), y(y_), z(z_)
    {
    }

    Vec(int x_, int y_, int z_, int w_) : x(x_), y(y_), z(z_), w(w_)
    {
    }

    Vec(const Vec<SIZE>& other) = default;

    int operator()(size_t i) const
    {
        assert(i < SIZE);
        return elements[i];
    }

    int& operator()(size_t i)
    {
        assert(i < SIZE);
        return elements[i];
    }

    Vec<SIZE> operator+(const Vec<SIZE>& other) const
    {
        Vec<SIZE> res;
        for (size_t i{0}; i < SIZE; i++)
            res(i) = (*this)(i) + other(i);
        return res;
    }

    void operator+=(const Vec<SIZE>& other)
    {
        for (size_t i{0}; i < SIZE; i++)
            (*this)(i) += other(i);
    }

    Vec<SIZE> operator-(const Vec<SIZE>& other) const
    {
        Vec<SIZE> res;
        for (size_t i{0}; i < SIZE; i++)
            res(i) = (*this)(i)-other(i);
        return res;
    }

    Vec<SIZE> operator*(const Vec<SIZE>& other) const
    {
        Vec<SIZE> res;
        for (size_t i{0}; i < SIZE; i++)
            res(i) = (*this)(i)*other(i);
        return res;
    }

    Vec<SIZE> operator/(const Vec<SIZE>& other) const
    {
        Vec<SIZE> res;
        for (size_t i{0}; i < SIZE; i++)
            res(i) = (*this)(i) / other(i);
        return res;
    }

    bool operator<(const Vec<SIZE>& other) const
    {
        for (size_t i{0}; i < SIZE; i++)
        {
            if ((*this)(i) < other(i))
                return true;
            if ((*this)(i) > other(i))
                return false;
        }
        return false;
    }

    bool operator==(const Vec<SIZE>& other) const
    {
        for (size_t i{0}; i < SIZE; i++)
            if (other(i) != (*this)(i))
                return false;
        return true;
    }

    bool operator<=(const Vec<SIZE>& other) const
    {
        return *this < other || *this == other;
    }

    bool operator!=(const Vec<SIZE>& other) const
    {
        return !(*this == other);
    }

    bool operator>(const Vec<SIZE>& other) const
    {
        return !(*this <= other);
    }

    bool operator>=(const Vec<SIZE>& other) const
    {
        return *this == other || *this > other;
    }
};

template <size_t SIZE>
bool in_range(const Vec<SIZE>& val, const Vec<SIZE>& low_incl, const Vec<SIZE>& high_excl)
{
    for (size_t i{0}; i < SIZE; i++)
        if (!in_range(val(i), low_incl(i), high_excl(i)))
            return false;
    return true;
}

template <size_t SIZE>
std::ostream& operator<<(std::ostream& out, const Vec<SIZE>& vec)
{
    out << '[';
    for (size_t i{0}; i < SIZE; i++)
    {
        out << vec(i);
        if (i < SIZE - 1)
            out << ", ";
    }
    out << ']';
    return out;
}

using Vec2 = Vec<2>;
using Vec3 = Vec<3>;
using Vec4 = Vec<4>;

const std::array<Vec2, 8> directions_diag_2{{
    {0, -1},
    {0, 1},
    {1, 0},
    {-1, 0},
    {1, 1},
    {-1, -1},
    {1, -1},
    {-1, 1},
}};

const std::array<Vec2, 8> directions_2{{
    {0, -1},
    {0, 1},
    {1, 0},
    {-1, 0},
    {1, 1},
    {-1, -1},
    {1, -1},
    {-1, 1},
}};

inline std::vector<Vec2> neighbours(const Vec2& pos, bool diagonal = false)
{
    std::vector<Vec2> result;
    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++)
            if (in_range(abs(i) + abs(j), 1, 2 + diagonal))
                result.emplace_back(pos.x + i, pos.y + j);
    return result;
}

inline std::vector<Vec3> neighbours(const Vec3& pos, bool diagonal = false)
{
    std::vector<Vec3> result;
    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++)
            for (int k = -1; k < 2; k++)
                if (in_range(abs(i) + abs(j) + abs(k), 1, 2 + diagonal * 2))
                    result.emplace_back(pos.x + i, pos.y + j, pos.z + k);
    return result;
}

inline std::vector<Vec4> neighbours(const Vec4& pos, bool diagonal = false)
{
    assert(diagonal);
    std::vector<Vec4> result;
    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++)
            for (int k = -1; k < 2; k++)
                for (int l = -1; l < 2; l++)
                    if (i != 0 || j != 0 || k != 0 || l != 0)
                        result.emplace_back(pos.x + i, pos.y + j, pos.z + k, pos.w + l);
    return result;
}

inline std::vector<std::string> split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> result;
    size_t start = 0, pos = 0;
    while ((pos = str.find(delim, start)) != std::string::npos)
    {
        result.push_back(str.substr(start, pos - start));
        start = pos + delim.length();
    }
    result.push_back(str.substr(start, str.length() - start));
    return result;
}

inline std::string read_file(std::ifstream& file)
{
    assert(file.good());
    std::stringstream buf;
    buf << file.rdbuf();
    return buf.str();
}

}  // namespace aoc

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec)
{
    out << '[';
    const auto size = vec.size();
    for (size_t i{0}; i < size; i++)
    {
        out << vec[i];
        if (i < size - 1)
            out << ", ";
    }
    out << ']';
    return out;
}

using i32 = int32_t;
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u8 = uint8_t;

template <size_t SIZE>
aoc::Vec<SIZE> operator*(const aoc::Vec<SIZE>& vec, int scalar)
{
    aoc::Vec<SIZE> res;
    for (size_t i{0}; i < SIZE; i++)
        res(i) = vec(i) * scalar;
    return res;
}

template <size_t SIZE>
aoc::Vec<SIZE> operator*(int scalar, const aoc::Vec<SIZE>& vec)
{
    return vec * scalar;
}


namespace std {

template <size_t SIZE>
struct hash<aoc::Vec<SIZE>>
{
    size_t operator()(const aoc::Vec<SIZE>& vec) const
    {
        size_t res = 0;
        for (size_t i{0}; i < SIZE; i++)
            res ^= hash<int>()(vec(i));
        return res;
    }
};
}  // namespace std