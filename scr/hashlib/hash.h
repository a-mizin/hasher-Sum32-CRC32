#pragma once

#include <cstdint>
#include <istream>

uint32_t getCRC32(std::istream& in);
uint32_t getSum32(std::istream& in);