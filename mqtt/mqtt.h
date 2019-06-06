#include <iostream>
#include <mosquitto.h>
#include <mosquittopp.h>
#include <thread>
#include <chrono>
#include <list>

class Mqtt_client : public mosqpp::mosquittopp
{
public:
    Mqtt_client(const char *id, const char *host, int port);
    virtual ~Mqtt_client();
    static std::string topic_a_u;
    void on_connect(int rc);
    void on_subscribe(int mid, int qos_count, const int *granted_qos);
    

    void set_on_message_callback(void (*callback)(const struct mosquitto_message *message));
    void set_on_subscribe_callback(void (*callback)(int mid, int qos_count, const int *granted_qos));
    void set_on_connect_callback(void (*callback)(int rc));

    static void send_list(uint16_t* array, int s,  std::string topic, mosqpp::mosquittopp sender);
    static void test(int*);


private:
    void (*on_message_callback)(const struct mosquitto_message *message);
    void (*on_subscribe_callback)(int mid, int qos_count, const int *granted_qos);
    void (*on_connect_callback)(int rc);
    void on_message(const struct mosquitto_message *message);
};

void send_in_thread(uint16_t*,int, std::string, Mqtt_client*);