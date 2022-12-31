//
//  g/Logger.h - Logger sub system classes
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include "nonstd/File.h"

class Logger;
class LoggerObject;

//
//  LoggerObject's
//

class LoggerObject {
public:
    enum message_type {
        Message,
        Warning,
        Error
    };

    LoggerObject(message_type _type, std::string _type_name, int _number, std::string _message, std::string _file, size_t _line = 1, size_t character = 1) :
        program("G"), type(_type), type_name(_type_name), number(_number), message(_message), file(_file), line(_line), character(character) {}

    LoggerObject(message_type _type, std::string _type_name, int _number, std::string _file, int _line = 1, size_t character = 1) :
        program("G"), type(_type), type_name(_type_name), number(_number), file(_file), line(_line), character(character) {}

    virtual std::string generateMessage(Logger* logger);
    virtual void setMessage(std::string msg) { message = msg; }
    virtual void setFilename(std::string filename) { file = filename; }
private:
    std::string program;
    message_type type;
    std::string type_name;
    int number;
    std::string message;
    std::string file;
    size_t line;
    size_t character;
};

class ErrorObject : public LoggerObject {
public:
    ErrorObject(int _number, std::string _message, std::string _file, size_t _line = 1, size_t _character = 1) :
        LoggerObject(LoggerObject::Error, "Error", _number, _message, _file, _line, _character) {}
};

class WarningObject : public LoggerObject {
public:
    WarningObject(int _number, std::string _message, std::string _file, int _line = 1, size_t _character = 1) :
        LoggerObject(LoggerObject::Warning, "Warning", _number, _message, _file, _line) {}
};

class MessageObject : public LoggerObject {
public:
    MessageObject(message_type _type, std::string _type_name, int _number, std::string _message, std::string _file, int _line = 1, size_t _character = 1) :
        LoggerObject(LoggerObject::Message, _type_name, _number, _message, _file, _line, _character) {}
};

//
//  LogTarget's
//

class LogTarget {
public:
    LogTarget() {}
    virtual void queueObject(Logger* logger, LoggerObject* loggerObject) = 0;
};

class MemoryLogger : public LogTarget {
public:
    MemoryLogger() {}
    void queueObject(Logger* logger, LoggerObject* loggerObject) {
        loggerObjects.push_back(loggerObject);
    }
protected:
    std::vector<LoggerObject*> loggerObjects;
};

class FileLogger : public LogTarget {
public:
    FileLogger(std::string file);   // TODO: class FileLogger
    virtual void queueObject(Logger* logger, LoggerObject* loggerObject) {}
    // ...
};

class StdErrLogger : public LogTarget {
public:
    StdErrLogger() {}
    virtual void queueObject(Logger* logger, LoggerObject* loggerObject) {
        std::cerr << loggerObject->generateMessage(logger) << std::endl;
    }
};

//
//
//

class ParsingErrorObject : public ErrorObject {
public:
    ParsingErrorObject() :
        ErrorObject(2, "Parsing error", "") {}
};

class ExceptionErrorObject : public ErrorObject {
public:
    ExceptionErrorObject(std::string message) :
        ErrorObject(0, "Exception" + message, "") {}
};

class SyntaxErrorObject : public ErrorObject {
public:
    SyntaxErrorObject(std::string message, size_t line = 1, size_t character = 1) :
        ErrorObject(2, message, "", line, character) {}
};

class UndefinedSymbolErrorObject : public ErrorObject {
public:
    UndefinedSymbolErrorObject(std::string symbolName, int line = 1, size_t character = 1) :
        ErrorObject(3, "Undefined Symbol '" + symbolName + "'", "", line, character) {}
};

class UndefinedTerminalSymbolErrorObject : public ErrorObject {
public:
    UndefinedTerminalSymbolErrorObject(std::string symbolName, int line = 1, size_t character = 1) :
        ErrorObject(3, "Undefined Terminal Symbol '" + symbolName + "'", "", line, character) {}
};

//
//  Logger class
//

class Logger {
public:
    Logger(LogTarget* _logTarget, std::string program) : logTarget(_logTarget), program(program) {}
    Logger(LogTarget* _logTarget) : logTarget(_logTarget) {}

    void setFilename(std::string filename) { this->filename = filename; }
    std::string getFilename() { return filename; }
    void setProgram(std::string program) { this->program = program; }
    std::string getProgram() { return program; }

    void LogError(ErrorObject *errorObject);
    void LogError(int _number, std::string _message, int _line);
    void LogWarning(WarningObject *warningObject);
    void LogWarning(int _number, std::string _message, int _line);
    void Message(LoggerObject::message_type _type, std::string _type_name, int _number, std::string _message, size_t _line = 1, size_t _character = 1);
protected:
    LogTarget* logTarget;
    std::string filename;
    std::string program;
};

// End g/Logger.h

