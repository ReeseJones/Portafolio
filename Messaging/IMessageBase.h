#pragma once

/******************************************************************************
    Description: The Base of a message. This class is the pivot for
    every message.
******************************************************************************/
class IMessageBase
{
    public:
        virtual ~IMessageBase(void) {}
        virtual const char* MessageName(void) const = 0;
};