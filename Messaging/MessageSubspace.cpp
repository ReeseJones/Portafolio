#pragma once

#include "MessageSubspace.h"
#include <iostream>

/******************************************************************************
            Public MessageSubspace Constructors and Destructors
******************************************************************************/
MessageSubspace::MessageSubspace(void)
{
    std::cout << "Constructing MessageSubspace" << std::endl;
}

MessageSubspace::~MessageSubspace(void)
{
    std::cout << "Cleaning up all MessageSusbspace allocated data" << std::endl;
    BindingCleanUp();
}

/******************************************************************************
        Public MessageSubspace Basic Initialization and Cleaning Methods
******************************************************************************/

void MessageSubspace::Initialize(void)
{
    std::cout << "Initializing MessageSubspace" << std::endl;
    RegisterMessage("InputMessage");
}

void MessageSubspace::BindingCleanUp(void)
{
    std::cout << "Binding Object CleanUp" << std::endl;

    auto iter = m_Bindings.begin();
    while(iter != m_Bindings.end())
    {
        auto binding_iter = (iter->second).begin();
        while( binding_iter != (iter->second).end() )
        {
            delete (*binding_iter);
            ++binding_iter;
        }
        (iter->second).clear();
        ++iter;
    }
}

/******************************************************************************
              Public MessageSubspace Object-Message Registration
******************************************************************************/
void MessageSubspace::RegisterMessage(const char* messageName)
{
    //Creates a field with the message name in the message database if the message
    //type name does not exist.
    if(m_Bindings.find(messageName) == m_Bindings.end())
    {
        std::cout << "Creating new binding vector for " << messageName << " messages" << std::endl;
        m_Bindings.insert( std::make_pair(messageName,Bindings()) );
    }
}

//The main function that allows any object with the method ProcessMessage
//to bind to a certain type of message.
template <typename MessageType, typename ObjectType>
void MessageSubspace::Bind(ObjectType& object,void (ObjectType::*Method)(MessageType*), const char* MessageName)
{
    auto iter = m_Bindings.find(MessageName);
    if(iter != m_Bindings.end())
    {
        std::cout << "Binding an object to " << MessageName << std::endl;                
        AddNewBinding(object,Method,MessageName);
    }
}

/******************************************************************************
         Private MessageSubspace Object-Message Registration Helpers
******************************************************************************/
template <typename ObjectType, typename MessageType>
void MessageSubspace::AddNewBinding(ObjectType& object,void (ObjectType::*Method)(MessageType*), const char* MessageName)
{
    typedef void (ObjectType::*MethodType)(MessageType*);
    BindingBase* newBinding = new Binding<ObjectType,MessageType,MethodType>(&object,Method);
    this->m_Bindings[MessageName].push_back(newBinding);
}

/******************************************************************************
              Public MessageSubspace Message Delivery
******************************************************************************/
template <typename MessageType>
void MessageSubspace::TransmitMessage(MessageType& message) 
{
    std::cout << "Transmitting " << message.MessageName() << std::endl;

    auto i_msgBinding = m_Bindings.find(message.MessageName());
    auto iter = (i_msgBinding->second).begin();
    auto end = (i_msgBinding->second).end();
    while(iter != end)
    {
        (*iter)->DeliverMessage(&message);
        ++iter;
    }
}

/******************************************************************************
         Private MessageSubspace Object-Message Registration Helpers
******************************************************************************/

template <typename ObjectType, typename MessageType>
void MessageSubspace::AddNewBinding(ObjectType& object,void (ObjectType::*Method)(MessageType*), const char* MessageName)
{
    typedef void (ObjectType::*MethodType)(MessageType*);
    BindingBase* newBinding = new Binding<ObjectType,MessageType,MethodType>(&object,Method);
    this->m_Bindings[MessageName].push_back(newBinding);
}
