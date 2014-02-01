#pragma once

#include <vector>
#include <map>

/******************************************************************************
    Description: The message subspace is in charge of holding all
    bindings for all messages as well as deliver triggered event messages
    to the respective bindings.
******************************************************************************/
class MessageSubspace
{
/******************************************************************************
            Public MessageSubspace Constructors and Destructors
******************************************************************************/
    public:
        MessageSubspace(void);
        ~MessageSubspace(void);
        
/******************************************************************************
        Public MessageSubspace Basic Initialization and Cleaning Methods
******************************************************************************/
    public:
        void Initialize(void);
        void BindingCleanUp(void);
/******************************************************************************
              Public MessageSubspace Object-Message Registration
******************************************************************************/
    public:
        void RegisterMessage(const char* messageName);
        //The main function that allows any object with the method ProcessMessage
        //to bind to a certain type of message.
        template <typename MessageType, typename ObjectType>
        void Bind(ObjectType& object,void (ObjectType::*Method)(MessageType*), const char* MessageName);
        
/******************************************************************************
         Private MessageSubspace Object-Message Registration Helpers
******************************************************************************/
    private:
        template <typename ObjectType, typename MessageType>
        void AddNewBinding(ObjectType& object,void (ObjectType::*Method)(MessageType*), const char* MessageName);
/******************************************************************************
              Public MessageSubspace Message Delivery
******************************************************************************/
    public:
        template <typename MessageType>
        void TransmitMessage(MessageType& message);
        
/******************************************************************************
                   Private MessageSubspace Typedefs
******************************************************************************/
    private:
        typedef std::vector<BindingBase*> Bindings; //The binding per object
        typedef std::map<const char*,Bindings> MessageBindings;

    /******************************************************************************
                       Private MessageSubspace Members
    ******************************************************************************/
    private:
        MessageBindings m_Bindings;

/******************************************************************************
         Private MessageSubspace Object-Message Registration Helpers
******************************************************************************/
    private:
        template <typename ObjectType, typename MessageType>
        void AddNewBinding(ObjectType& object,void (ObjectType::*Method)(MessageType*), const char* MessageName);
};