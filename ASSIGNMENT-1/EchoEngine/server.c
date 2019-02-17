/*
 * server.c: Server program           
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define SERVER_KEY_PATHNAME "/tmp/mqueue_server_key"
#define PROJECT_ID 'M'
#define QUEUE_PERMISSIONS 0660

struct message_text {
    int qid;
    char buf ;
};

struct message {
    long message_type;
    struct message_text message_text;
};

int main (int argc, char **argv)
{
    key_t msg_queue_key;
    int qid;
    struct message message;

    if ((msg_queue_key = ftok (SERVER_KEY_PATHNAME, PROJECT_ID)) == -1) {
        perror ("ftok");
        exit (1);
    }

    if ((qid = msgget (msg_queue_key, IPC_CREAT | QUEUE_PERMISSIONS)) == -1) {
        perror ("msgget");
        exit (1);
    }

    printf ("Server: Hello, World!\n");

    while (1) {
        // read an incoming message
        if (msgrcv (qid, &message, sizeof (struct message_text), 0, 0) == -1) {
            perror ("msgrcv");
            exit (1);
        }

        printf ("Server: message received.\n");

        
        
        int length = 1;
        //change uppercase alphabets to lowercase OR vice versa OR 
        //convert all lowercase characters to uppercase
        
        if(isalpha(message.message_text.buf))
        {
            if( isupper(message.message_text.buf) )    
                message.message_text.buf = tolower(message.message_text.buf);
            else if( islower(message.message_text.buf) )    
                message.message_text.buf = toupper(message.message_text.buf);
        }
    
        int client_qid = message.message_text.qid;
        message.message_text.qid = qid;

        // send reply message to client
        if (msgsnd (client_qid, &message, sizeof (struct message_text), 0) == -1) {  
            perror ("msgget");
            exit (1);
        }

        printf ("Server: response sent to client.\n");
    }
}