//
//  Maths.h - maths functions
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#pragma once

#ifndef __LG__LIB__MATHS_H__
#define __LG__LIB__MATHS_H__

#include <cmath>

namespace nonstd {

    template <typename T>
    const T& min(const T& lhs, const T& rhs) {
        return (lhs < rhs) ? lhs : rhs;
    }

    template <typename T>
    const T& max(const T& lhs, const T& rhs) {
        return (lhs > rhs) ? lhs : rhs;
    }

    inline unsigned int log_ceiling(unsigned int value, unsigned int base = 10) {
        unsigned int power = 1;
        while (power < value)
            power *= base;

        return (unsigned int)log10(power) + 1;  //TODO: check !!!?
    }

	inline unsigned additionalFactorial(unsigned n) {
		return (n * (n - 1)) / 2;
	}

    // TODO: memorized calculation of powers for given base upto types ceiling

} // end namespace nonstd

#endif // __LG__LIB__MATHS_H__