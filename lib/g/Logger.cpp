//
//  g/Logger.cpp - Logger sub system
//
//  Property and Copyright (c) 2015-2022 Aaron Nathaniel Gray
//

#include "g/Logger.h"

std::string LoggerObject::generateMessage(Logger* logger) {
    std::stringstream ss;
    ss << logger->getFilename() << "(" << line << "," << character << "): " << type_name << " " << logger->getProgram() << number << ": " << message << std::endl;
    return ss.str();
}

void Logger::LogError(ErrorObject *errorObject) {
    logTarget->queueObject(this, errorObject);
}

void Logger::LogError(int _number, std::string _message, int _line) {
    logTarget->queueObject(this, new ErrorObject(_number, _message, filename, _line));
}

void Logger::LogWarning(WarningObject *warningObject) {
    warningObject->setFilename(filename);
    logTarget->queueObject(this, warningObject);
}

void Logger::LogWarning(int _number, std::string _message, int _line) {
    logTarget->queueObject(this, new WarningObject(_number, _message, filename, _line));
}

void Logger::Message(LoggerObject::message_type _type, std::string _type_name, int _number, std::string _message, size_t _line, size_t _character) {
    logTarget->queueObject(this, new MessageObject(_type, _type_name, _number, _message, filename, _line, _character));
}

// g/Logger.cpp - Logger sub system

