/*
 * server.c: Server program
 *           
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define SERVER_KEY_PATHNAME "/tmp/mqueue_server_key"
#define PROJECT_ID 'M'
#define QUEUE_PERMISSIONS 0660

struct message_text {
    int qid;
    char buf [2000];
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

        
        FILE *fptr; 
  
        char str[20] = "Cannot open file";
        
        char c; 
        
        // Open file 
        fptr = fopen(message.message_text.buf, "r"); 
        if (fptr == NULL) 
        { 
            
        int num;
        for (num=0; str[num]!='\0' ; num++)
            {   
                message.message_text.buf[num] = str[num];    

            }
        message.message_text.buf[num] = '\0';


        } 
  
        else // Read contents from file 
        {
            c = fgetc(fptr); 
            int iter = 0;
            while (c != EOF) 
            { 
            message.message_text.buf[iter] = c;
            
            c = fgetc(fptr); 
            
            iter = iter + 1;
            } 
            message.message_text.buf[iter] = '\0';


            fclose(fptr);
          
        
        }



        int length = strlen (message.message_text.buf);
        
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

