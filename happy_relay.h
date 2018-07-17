#ifndef happy_relay_h
#define happy_relay_h

#include "Arduino.h"
#include <PubSubClient.h>

class happy_relay
{
    public:
        happy_relay(int pin, PubSubClient client);
        void setId(char* id);
        void process(char* topic, byte* payload);
    private:
        int _pin;
        int _state;
        char *relayConfigTopic;
        char *relayConfig;
        char *relaySetTopic;
        char *relayStateTopic;
        PubSubClient _client;
};

#endif