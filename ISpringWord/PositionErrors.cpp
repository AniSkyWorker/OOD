#include "stdafx.h"
#include "PositionErrors.h"

InvalidPositionError::InvalidPositionError(size_t position)
    : logic_error("Position: " + std::to_string(position) + " more than elemenets in doc.")
{
}

InvalidPositionError::InvalidPositionError()
    : logic_error("Invalid position, more than items")
{
}

UnexpectedPosition::UnexpectedPosition(const std::string& expected)
    : runtime_error("Excpected position index or " + expected)
{
}

UnexpectedPosition::UnexpectedPosition()
    : runtime_error("Excpected position index")
{
}
