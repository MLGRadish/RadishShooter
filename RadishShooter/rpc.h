#pragma once
#include <enet/enet.h>
//#include <message.pb.h>

class RPC {
    static uint get_id(ENetPeer* host){ return static_cast<uint>(reinterpret_cast<intptr_t>(host->data)); };

public:
    /*void proc(message::Message *msg, ENetEvent event) {
        printf("[%i] corpus: %i\n", get_id(event.peer), msg->corpus());
        if (msg->corpus() == message::UPDATE) {
            update(msg);
        }
    }*/

private:
    /*void update(message::Message *msg) {
        printf(" x/y/z %f %f %f\n", msg->pos().x(), msg->pos().y(), msg->pos().z());
    }*/
};