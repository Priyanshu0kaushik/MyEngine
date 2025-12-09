//
//  MessageQueue.h
//  MyEngine
//
//  Created by Priyanshu Kaushik on 09/12/2025.
//

#pragma once
#include "Message.h"

class MessageQueue
{
public:
    void Push(std::unique_ptr<Message> msg)
    {
        mQueue.push(std::move(msg));
    }

    std::unique_ptr<Message> Pop()
    {
        if (mQueue.empty()) return nullptr;

        auto msg = std::move(mQueue.front());
        mQueue.pop();
        return msg;
    }

private:
    std::queue<std::unique_ptr<Message>> mQueue;
};

