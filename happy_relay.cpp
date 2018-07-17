#include "Arduino.h"
#include "happy_relay.h"

happy_relay::happy_relay(int pin, PubSubClient client)
{
    pinMode(pin, OUTPUT);
    _pin = pin;
    _client = client;
}

void happy_relay::setId(char* id)
{
    relayConfigTopic = (char*)malloc(strlen(id) + 28 + 35 + 1);
    snprintf(relayConfigTopic, strlen(id) + 28 + 35, "homeassistant/switch/%s-relay/config", id);
    
    relayConfig = (char*)malloc(strlen(id) + 122 + 1);
    snprintf(relayConfig, strlen(id) + 122, "{\"name\": \"%s-relay\", \"command_topic\": \"homeassistant/switch/%s-relay/set\"}", id, id);
    
    relaySetTopic = (char*)malloc(strlen(id) + 31 + 28 + 1);
    snprintf(relaySetTopic, strlen(id) + 31 + 28, "homeassistant/switch/%s-relay/set", id);
   
    relayStateTopic = (char*)malloc(strlen(id) + 31 + 30 + 1);
    snprintf(relayStateTopic, strlen(id) + 31 + 30, "homeassistant/switch/%s-relay/state", id);
   
    _client.subscribe(relaySetTopic);
    
    digitalWrite(_pin, 0);
    _client.publish(relayStateTopic, "OFF");
    
    _client.publish(relayConfigTopic, relayConfig, true);
}

void happy_relay::process(char* topic, byte* payload)
{
    Serial.print("Topic:");
    Serial.println(topic);
    Serial.print("Payload:");
    Serial.println((char*)payload);
    
    if(strncmp(topic, relaySetTopic, 28) == 0)
    {
        if(strcmp((char*)payload, "ON") == 0)
        {
            digitalWrite(_pin, 1);
            _client.publish(relayStateTopic, "ON");
        }
        else if(strcmp((char*)payload, "OFF") == 0)
        {
            digitalWrite(_pin, 0);
            _client.publish(relayStateTopic, "OFF");
        }
    }
}