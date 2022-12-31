//
//  nonstd/File.h
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#pragma once

#include "nonstd/string.h"

#include <fstream>
#include <algorithm>
#include <stdio.h>

//#include "g/Logger.h"
const char WINDOWS_FILEPATH_SEPARATOR = '\\';
const char UNIX_FILEPATH_SEPARATOR = '/';

#if defined(WINVER) || defined(_MSC_VER)
const char NORMAL_FILEPATH_SEPARATOR = WINDOWS_FILEPATH_SEPARATOR;
const char OTHER_FILEPATH_SEPARATOR = UNIX_FILEPATH_SEPARATOR;
#else
const char NORMAL_FILEPATH_SEPARATOR = UNIX_FILEPATH_SEPARATOR;
const char OTHER_FILEPATH_SEPARATOR = WINDOWS_FILEPATH_SEPARATOR;
#endif

// TODO: This is a hack !!!

class FileName {
public:
    FileName() : filename(), filepath_separator(NORMAL_FILEPATH_SEPARATOR) {}
    FileName(nonstd::string filename, char const& delimiters = NORMAL_FILEPATH_SEPARATOR) : filename(FileName::normalize(filename)), filepath_separator(delimiters) {
    }

    FileName& operator = (FileName& filename) {
        this->filename = filename;
        return *this;
    }

    enum Platform { UNIX, WINDOWS, MACOSX };
    const char filepath_separator = NORMAL_FILEPATH_SEPARATOR;

    operator nonstd::string() const {
        return filename;
    }
    operator std::string() const {
        return filename;
    }
    nonstd::string toString() const {
        return filename;
    }

    operator const char* () {
        return filename.c_str();
    }

    static nonstd::string normalize(nonstd::string filepath) {
        std::string result;
        std::transform(filepath.cbegin(), filepath.cend(), std::back_inserter(result),
            [](unsigned char c) {
                return (c == OTHER_FILEPATH_SEPARATOR) ? NORMAL_FILEPATH_SEPARATOR : c;
        });

        return result;
    }

    nonstd::string base_filename() const {
        return filename.substr(filename.find_last_of(filepath_separator) + 1);
    }
    nonstd::string remove_extension() const {
        return remove_extension(filename);
    }
    static nonstd::string remove_extension(nonstd::string name) {
        nonstd::string::size_type const pos(name.find_last_of('.'));
        return pos > 0 && pos != std::string::npos ? name.substr(0, pos) : name;
    }
    nonstd::string base_name() const {
        return remove_extension(base_filename());
    }
    nonstd::string escape() const {
        return filename.escape();
    }
    friend bool operator == (FileName& lhs, FileName& rhs) {
        return lhs.filename == rhs.filename;
    }

protected:
    nonstd::string filename;
};

//
//
//

template<class type>
class File;

template<>
class File<FILE*> {
public:
    File(nonstd::string filename) : filename(filename), handle(nullptr) {}
    File(FileName filename) : filename(filename), handle(nullptr) {}

    bool open() {
#if defined(WINVER) || defined(_MSC_VER)
        fopen_s(&handle, filename, "rb");
#else
        handle = fopen(filename, "rb");
#endif
        if (handle)
            return true;
        else
            return false;
    }
    void close() {
        fclose(handle);
    }

    FILE* getHandle() { return handle; }
    operator FILE* () { return handle; }

	FileName getFilename() const { return filename; }

    size_t size() {
        long position = ftell(handle);
        fseek(handle, 0, SEEK_END);
        long length = ftell(handle);
        fseek(handle, position, SEEK_SET);
        return length;
    }
    void read(char *buffer) {
        fread(buffer, size(), 1, handle);
    }
private:
    FILE *handle;
    FileName filename;
};

template<>
class File<std::ostream> : public std::ofstream {
public:
    File() {}
    File(nonstd::string _filename) : filename(_filename) { open();  }
    ~File() { close(); }

    bool open(std::ios_base::openmode mode = std::ios_base::out & std::ios_base::binary) {
        std::ofstream::open(filename, mode);
        return std::ofstream::is_open();
    }
    bool open(std::string _filename, std::ios_base::openmode mode = std::ios_base::out & std::ios_base::binary) {
        filename = _filename;
        std::ofstream::open(filename, mode);
        return std::ofstream::is_open();
    }
    void close() {
        std::ofstream::close();
    }
    std::ostream& getStream() { return *this; }
//    operator std::ostream& () { return *this; }

private:
	nonstd::string filename;
};
/*
template<>
class File<std::ofstream> {
public:
    File() {}
    File(std::string _filename) : filename(_filename) {}

    bool open(std::ios_base::openmode mode = std::ios_base::out & std::ios_base::binary) {
        stream.open(filename, mode);
        return stream.is_open();
    }
    bool open(std::string _filename, std::ios_base::openmode mode = std::ios_base::out & std::ios_base::binary) {
        filename = _filename;
        stream.open(filename, mode);
        return stream.is_open();
    }
    void close() {
        stream.close();
    }
    std::ofstream& getStream() { return stream; }

private:
    std::ofstream stream;
    std::string filename;
};
*/
template<>
class File<std::ifstream> {
public:
    File(nonstd::string _filename) : filename(_filename) {}

    bool open() {
        stream.open(filename);
        return stream.is_open();
    }
    void close() {
        stream.close();
    }
    size_t size() {
        std::streamoff position = stream.tellg();
        stream.seekg(0, stream.end);
        size_t length = (size_t)stream.tellg();
        stream.seekg(position, stream.beg);
        return length;
    }

    void read(char *buffer) {
        stream.read(buffer, size());
    }
    std::ifstream& getStream() { return stream; }

private:
    std::ifstream stream;
    std::string filename;
};

/*
class FileNotFound : public ErrorObject {
public:
    FileNotFound(message_type type, std::string type_name, int number, std::string file, int line) :
    ErrorObject(number, std::string(), file, line) {}

    virtual std::string generateMessage() {
        message = "File Not Found";
    }
};
*/

template<class T>
inline T base_filename(T const & path, T const & delims = "/\\")
{
    return path.substr(path.find_last_of(delims) + 1);
}

template<class T>
inline T remove_extension(T const & filename)
{
    typename T::size_type const p(filename.find_last_of('.'));
    return p > 0 && p != T::npos ? filename.substr(0, p) : filename;
}

template<class T>
inline T base_name(T const & path, T const & delims = "/\\")
{
    return remove_extension(base_filename(path));
}

// End nonstd/File.h
