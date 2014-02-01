#pragma once

/******************************************************************************
    Description: A base used by the MessageSubspace to holds all types
    of message binds.
    A Binding binds an object's method to receive a specific
    event message. When the event occurs, the event's data is passed
    to the bound method that processes the data.
******************************************************************************/
class BindingBase
{
    public:
        virtual ~BindingBase(void) {};
        virtual void DeliverMessage(IMessageBase* message) = 0;
};