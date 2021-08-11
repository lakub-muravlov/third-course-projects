#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
#include "pthread.h"

using namespace std;

int run_thread_reader = 0;
const int N = 10;
pthread_mutex_t stdout_mutex;
pthread_mutex_t readers_count_mutex;
pthread_mutex_t update;

struct Node  {
    int key;
    pthread_mutex_t isEdit;
    bool writers;
    int readers_count;
};

Node create_node(int key){
    Node* node = new Node();
    node->key = key;
    node->writers = false;
    node->readers_count = 0;
    pthread_mutex_t isEdit;
    return *node;
}

vector<Node> buff;

void* read(void* id){
    int* reader_id = (int*)id;
    int idx;
    while (true) {
        idx = rand() % N;

        if (buff.at(idx).writers)
            continue;

        pthread_mutex_lock(&update);

        buff.at(idx).readers_count++;
        if (buff.at(idx).readers_count == 1) {
            // give access to item to readers
            pthread_mutex_lock(&buff.at(idx).isEdit);
        }

        pthread_mutex_unlock(&update);

        pthread_mutex_lock(&stdout_mutex);
        cout << "Reader ID: " << (long)id << endl;
        cout << "I look at index " << idx << " and see key: " << buff.at(idx).key << endl;
        pthread_mutex_unlock(&stdout_mutex);

        pthread_mutex_lock(&update);
        buff.at(idx).readers_count--;

        if (buff.at(idx).readers_count == 0)
            pthread_mutex_unlock(&buff.at(idx).isEdit);

        pthread_mutex_unlock(&update);

        // rest
        this_thread::sleep_for(chrono::seconds(rand()%10));
    }
    return NULL;
}

void* write(void* id){
    long writer_id = (long)id;
    int idx;
    while (true) {
        idx = rand() % N;

        buff.at(idx).writers = true;

        pthread_mutex_lock(&buff.at(idx).isEdit);

        buff.at(idx).key = 100;
        pthread_mutex_lock(&stdout_mutex);
        cout << "Writer ID: " << writer_id << endl;
        cout << "Key at index " << idx << " changed to " << buff.at(idx).key << endl;
        pthread_mutex_unlock(&stdout_mutex);

        pthread_mutex_unlock(&buff.at(idx).isEdit);

        buff.at(idx).writers = false;

        this_thread::sleep_for(chrono::seconds(rand()%10));
    }
    return NULL;
}

int fill_buffer(){
    for(int i=0;i<N;i++){
        buff.push_back(create_node(i));
        if (pthread_mutex_init(&buff.at(i).isEdit, NULL) != 0) {
            printf("\n Edit mutex init has failed\n");
            return 1;
        }
    }
    return 0;
}

int main()
{

    fill_buffer();

    pthread_t readers[N];
    pthread_t writers[N];

    if (pthread_mutex_init(&update, NULL) != 0) {
        printf("\n Update reader counter mutex init has failed\n");
        return 1;
    }

    for(long i=0; i < N; i++){
        pthread_create(&writers[i], NULL, &write, (void*)i);
        pthread_create(&readers[i], NULL, &read, (void*)i);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(writers[i], NULL);
        pthread_join(readers[i], NULL);
    }

    for (auto n : buff){
        pthread_mutex_destroy(&n.isEdit);
    }

    pthread_mutex_destroy(&stdout_mutex);

    return 0;
}

