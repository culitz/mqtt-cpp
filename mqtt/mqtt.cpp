#include "mqtt.h"
#include <list>

Mqtt_client::Mqtt_client(const char *id, const char *host, int port) : mosquittopp(id){
    int keepalive = DEFAULT_KEEP_ALIVE;
    connect(host, port, keepalive);
}

Mqtt_client::~Mqtt_client(){

}

void Mqtt_client::on_connect(int rc){
    if (!rc){
        std::cout << "Connected - code " << rc << std::endl;
    }
}

void Mqtt_client::on_subscribe(int mid, int qos_count, const int *granted_qos){
    std::cout << "Subscription succeeded." << std::endl;
}

void Mqtt_client::on_message(const struct mosquitto_message *message){
    on_message_callback(message);
}

void Mqtt_client::send_list(uint16_t* array, int s, std::string topic, mosqpp::mosquittopp sender) {
    const char* mqtt_message;
    for(int i = 0; i < s; i++){
        std::string s_msg = std::to_string(array[i]);
        mqtt_message = s_msg.c_str();
        sender.publish(NULL, topic.c_str(), s, array, false);
    }
}

void Mqtt_client::set_on_message_callback(void (*callback)(const struct mosquitto_message *message)){
    this->on_message_callback = *callback;
}

void Mqtt_client::set_on_connect_callback(void (*callback)(int rc)){
    this->on_connect_callback = *callback;
}

void Mqtt_client::set_on_subscribe_callback(void (*callback)(int mid, int qos_count, const int *granted_qos)){
    this->on_subscribe_callback = *callback;
}

void send_in_thread(uint16_t* array, int size, std::string topic, Mqtt_client* client){
    for(int i = 0; i < size; i++){
        std::string s = std::to_string(array[i]);
        client->publish(NULL, topic.c_str(), s.length(), s.c_str(), 0, false);
    }
}