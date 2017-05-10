#pragma once

class InvalidPositionError : public std::logic_error
{
public:
    InvalidPositionError(size_t position);
    InvalidPositionError();
};

class UnexpectedPosition : public std::runtime_error
{
public:
    UnexpectedPosition(const std::string& expected);
    UnexpectedPosition();
};