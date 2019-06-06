#include <iostream>
#include "mqtt/mqtt.h"


int connect_stat;
char topic[] = "/CPP/TEST";
char host[] = "localhost";
int port = 1883;

void on_connect(int rc);
void on_message(const struct mosquitto_message *message);
void on_subscribe(int mid, int qos_count, const int *granted_qos);

int main(int argc, char* argv[])
{
    Mqtt_client *client;
    mosqpp::lib_init();
    client = new Mqtt_client("cpp",host,port);
    client->subscribe(NULL,topic);

    client->set_on_connect_callback(on_connect);
    client->set_on_message_callback(on_message);
    client->set_on_subscribe_callback(on_subscribe);

    client->loop_forever();
    
    while(1){
        connect_stat = client->loop();
        if(connect_stat){
            client->reconnect();
            std::cout << "reconnect:" << connect_stat << std::endl;
            client->subscribe(NULL,topic);
        }else{
            std::cout << "subscribe: " << topic << connect_stat << std::endl;
        }
    }
    mosqpp::lib_cleanup();
}

void on_message(const struct mosquitto_message *message){
    std::cout << "on message from main" << std::endl;

    int len = message->payloadlen;
    std::string p;
    char* value = static_cast<char*>(message->payload);
    for(int i=0; i<len; i++){
        std::cout << value[i];
    }
    std::cout << p  << std::endl;
}

void on_subscribe(int mid, int qos_count, const int *granted_qos){
    std::cout << "Subscribe done" << std::endl;
}

void on_connect(int rc){
    std::cout << "connect done" << std::endl;
}