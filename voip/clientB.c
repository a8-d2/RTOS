#include"stdio.h"  
#include"stdlib.h"  
#include"sys/types.h"  
#include"sys/socket.h"  
#include"string.h"  
#include"netinet/in.h"  
#include"netdb.h"
#include<unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <errno.h>
#define PORT 4444 
#define BUF_SIZE 2000 

#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse/gccmacro.h>

#define BUFSIZE 1024

/* A simple routine calling UNIX write() in a loop */
static ssize_t loop_write(int fd, const void*data, size_t size) {
    ssize_t ret = 0;

    while (size > 0) {
        ssize_t r;

        if ((r = write(fd, data, size)) < 0)
            return r;

        if (r == 0)
            break;

        ret += r;
        data = (const uint8_t*) data + r;
        size -= (size_t) r;
    }

    return ret;
}


  
int main(int argc, char**argv) {  
	 struct sockaddr_in addr, cl_addr;  
	 int sockfd, ret;  
	 char buffer[BUF_SIZE];  
	 struct hostent * server;
	 char * serverAddr;


	if (argc < 2) {
	  printf("usage: client < ip address >\n");
	  exit(1);  
	 }

	 serverAddr = argv[1]; 
	 
	 sockfd = socket(AF_INET, SOCK_STREAM, 0);  
	 if (sockfd < 0) {  
	  printf("Error creating socket!\n");  
	  exit(1);  
	 }  
	 //printf("Socket created...\n");   

	 memset(&addr, 0, sizeof(addr));  
	 addr.sin_family = AF_INET;  
	 addr.sin_addr.s_addr = inet_addr(serverAddr);
	 addr.sin_port = PORT;     

	 ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));  
	 if (ret < 0) {  
	  printf("Error connecting to the server!\n");  
	  exit(1);  
	 }  
	 //printf("Connected to the server...\n");  

	 //memset(buffer, 0, BUF_SIZE);
	 //printf("Enter your message(s): ");
	 
	//fgets(buffer, BUF_SIZE, stdin) != NULL


	//////////////////////////////////////////////////////////////////////////////
	 
	/* The sample type to use */
	 
	 for (;;) {
	static const pa_sample_spec ss = {
		.format = PA_SAMPLE_S16LE,
		.rate = 44100,
		.channels = 2
	 };
	 pa_simple *s = NULL;
	 int rett = 1;
	 int error;

	    /* Create the recording stream */
	 if (!(s = pa_simple_new(NULL, argv[0], PA_STREAM_RECORD, NULL, "record", &ss, NULL, NULL, &error))) {
		fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
		goto finish;
	    }

        uint8_t buf[BUFSIZE];

        /* Record some data ... */
         if (pa_simple_read(s, buf, sizeof(buf), &error) < 0) {
            fprintf(stderr, __FILE__": pa_simple_read() failed: %s\n", pa_strerror(error));
            goto finish;
        }
	
        /* And write it to STDOUT */
	/*        
	 if (loop_write(STDOUT_FILENO, buf, sizeof(buf)) != sizeof(buf)) {
            fprintf(stderr, __FILE__": write() failed: %s\n", strerror(errno));
            goto finish;
        }
    	*/

        rett = 0;

finish:

    	if (s)
        	pa_simple_free(s);

    	//strcpy(&buffer,'empty');
	
//////////////////////////////////////////////////////////////////////////////	
	 

	  strcpy(buffer,buf);
	  ret = sendto(sockfd, &buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));  
	  if (ret < 0) {  
	   printf("Error sending data!\n\t-%s", buffer);  
	  }

	  
	  /*
	  ret = recvfrom(sockfd, &buffer, BUF_SIZE, 0, NULL, NULL);  
	  
	  if (ret < 0) {  
	   printf("Error receiving data!\n");    
	  } else {

	  printf("%s\n", buffer);
	  	}  
	*/
	}

	 return 0;    
}  
