//
//  nonstd/DefaultValues.h
//

// Usage:
//   nonstd::traits<T>::default_value
//

#pragma once

#include <string>
namespace nonstd {

    template <typename T>
    struct traits {
        static constexpr T default_value = T();
    };

    //    template <typename T>
    //    T traits<T>::default_value = T();

    //    template <typename T, T U = std::enable_if_t<std::is_scalar<T>::value>>
    //    struct traits<T> {
    //      static constexpr unsigned int default_value = 0;
    //    };

    template <>
    struct traits<bool> {
        static constexpr bool default_value = false;
    };

    template <>
    struct traits<char> {
        static constexpr char default_value = 0;
    };

    template <>
    struct traits<signed char> {
        static constexpr signed char default_value = 0;
    };

    template <>
    struct traits<unsigned char> {
        static constexpr unsigned char default_value = 0;
    };

    template <>
    struct traits<short int> {
        static constexpr short int default_value = 0;
    };

    template <>
    struct traits<int> {
        static constexpr int default_value = 0;
    };

    template <>
    struct traits<long int> {
        static constexpr long int default_value = 0;
    };

    template <>
    struct traits<long long int> {
        static constexpr long long int default_value = 0;
    };

    template <>
    struct traits<unsigned int> {
        static constexpr unsigned int default_value = 0;
    };

    template <>
    struct traits<unsigned long int> {
        static constexpr unsigned long int default_value = 0;
    };

    template <>
    struct traits<unsigned long long int> {
        static constexpr unsigned long long int default_value = 0;
    };

    template <>
    struct traits<float> {
        static constexpr float default_value = 0.0;
    };

    template <>
    struct traits<double> {
        static constexpr double default_value = 0.0;
    };

    template <>
    struct traits<long double> {
        static constexpr long double default_value = 0.0;
    };

    template <>
    struct traits<char16_t> {
        static constexpr char16_t default_value = 0x00;
    };

    template <>
    struct traits<char32_t> {
        static constexpr char32_t default_value = 0x00;
    };

    template <>
    struct traits<wchar_t> {
        static constexpr wchar_t default_value = 0;
    };

    template <>
    struct traits<std::string> {
        static std::string default_value;
    };

//    std::string traits<std::string>::default_value;  // TODO: find soultion ?  

};

// end nonstd/DefaultValues.h
