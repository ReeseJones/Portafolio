#pragma once

/******************************************************************************
    Description: A Binding binds an object's method to receive a specific
    event message. When the event occurs, the event's data is passed
    to the bound specific object's method that processes the data.
******************************************************************************/
template <typename ObjectType, typename MessageType, typename Function>
class Binding : public BindingBase
{
    public:        
        Binding(ObjectType* object,Function method) : BindingBase(),
                                                      m_pMessageCall(method),
                                                      m_pObject(object)
        {
            std::cout << "Binding an object to a message type" << std::endl;
        }

        virtual void DeliverMessage(IMessageBase* message)
        {
            std::cout << "Delivering Message" << std::endl;
            MessageType* actualMessage = reinterpret_cast<MessageType*>(message);            
            (m_pObject->*m_pMessageCall)(actualMessage);
        } 

    private:
        Function m_pMessageCall;
        ObjectType* m_pObject;
};