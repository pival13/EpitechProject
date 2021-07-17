#pragma once

#include <map>
#include <regex>
#include <array>
#include <deque>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#define debug std::cout << "MESSAGE "
#define error std::cout << "ERROR "

enum GomokuCell : uint8_t { None, Own, Opponent, Error };

typedef std::vector<std::vector<GomokuCell>> GomokuBoard;
typedef std::pair<int, int> Vector2;

static const std::array<Vector2, 8> VECTORS = {{{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}}};

bool operator==(const Vector2 &v1, const Vector2 &v2);
Vector2 operator+(const Vector2 &v1, const Vector2 &v2);
Vector2 operator*(const Vector2 &v1, int c);