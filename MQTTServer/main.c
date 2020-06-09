#include <stdio.h>
#include <mosquitto.h>
#include <stdlib.h>
#include <string.h>

#define SUB_TOPIC_COUNT 4
#define HOSTNAME "localhost"

const char* sub_topics[] = {
        "right_window/rain_detector",
        "right_window/moisture_sensor",
        "right_window/reed_contact",
        "right_window/error"
};

struct mosquitto* create_instance(const char*, const char*, const char*, const char*);
void on_receive(struct mosquitto*, void*, const struct mosquitto_message*);
void destroy_instance(struct mosquitto*);
void cleanup(struct mosquitto*);

struct mosquitto* create_instance(const char* name, const char* username, const char* pw, const char* host)
{
    struct mosquitto* mosq = mosquitto_new(name,false,0);

    if(!mosq) {
        printf("Initialization of new MQTT client instance failed\n");
        cleanup(mosq);
    }

    if(mosquitto_username_pw_set(mosq, username, pw) != MOSQ_ERR_SUCCESS) {
        printf("Initialization of instance password and username failed\n");
        cleanup(mosq);
    }

    if(mosquitto_connect(mosq,host,1883,60) != MOSQ_ERR_SUCCESS) {
        printf("Couldn't connect to broker service.\n");
        cleanup(mosq);
    }

    mosquitto_message_callback_set(mosq, &on_receive);

    if(mosquitto_loop_start(mosq) != MOSQ_ERR_SUCCESS) {
        printf("Unable to start client background loop\n");
        cleanup(mosq);
    }

    return mosq;
}

void on_receive(struct mosquitto* mosq, void* obj, const struct mosquitto_message* msg)
{
    char* subtopic = (char*) malloc(sizeof(char) * strlen(msg->topic));
    char* tmp_free_ptr = subtopic;      // Save the memory location of subtopic for later free'ing
    strcpy(subtopic, msg->topic);
    strsep(&subtopic,"/");

    if(strstr(msg->topic,"right_window")) {
        if(!strcmp(subtopic,"rain_detector")) {
            printf("%s\n", (char*) msg->payload);
        }
        else if(!strcmp(subtopic,"moisture_sensor")) {

        }
        else if(!strcmp(subtopic,"reed_contact")) {

        }
        else if(!strcmp(subtopic,"error")) {

        }
    }
    else if(strstr(msg->topic,"left_window")) {

    }
    else if(strstr(msg->topic,"table")) {

    }
    else if(strstr(msg->topic,"door")) {

    }

    free(tmp_free_ptr);
}

void destroy_instance(struct mosquitto* mosq)
{
    for(int i = 0; i < SUB_TOPIC_COUNT; i++) {
        if(mosquitto_unsubscribe(mosq,0,sub_topics[i]) != MOSQ_ERR_SUCCESS)
            printf("Unsubscription to topic %s failed %d\n", sub_topics[i]);
        else
            printf("Unsubscription to topic %s succeeded\n", sub_topics[i]);
    }

    if(mosquitto_disconnect(mosq) != MOSQ_ERR_SUCCESS) {
        printf("Service disconnect failed\n");
    }

    if(mosquitto_loop_stop(mosq,0) != MOSQ_ERR_SUCCESS) {
        printf("Client background loop couldn't be stopped\n");
    }

    mosquitto_destroy(mosq);
}

void cleanup(struct mosquitto* mosq)
{
    mosquitto_lib_cleanup();
    destroy_instance(mosq);
    exit(0);
}

int main()
{
    // Setup
    mosquitto_lib_init();
    struct mosquitto* mosq = create_instance("handler","handler","handler_pw",HOSTNAME);

    // Working area

    for(int i = 0; i < SUB_TOPIC_COUNT; i++) {
        if(mosquitto_subscribe(mosq,0,sub_topics[i],0) != MOSQ_ERR_SUCCESS)
            printf("Subscription to topic %s failed\n", sub_topics[i]);
        else
            printf("Subscription to topic %s succeeded\n", sub_topics[i]);
    }

    mosquitto_publish(mosq,0,"test/message",3,"elo2",0,1);

    while(1);

    // Cleanup
    cleanup(mosq);
}
