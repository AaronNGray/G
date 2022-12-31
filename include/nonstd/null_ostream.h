#pragma once

#include <streambuf>
#include <iostream>

class NullBuffer : public std::streambuf
{
public:
    int overflow(int c) { return c; }
};

