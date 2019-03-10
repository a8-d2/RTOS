#include"stdio.h"  
#include"stdlib.h"  
#include"sys/types.h"  
#include"sys/socket.h"  
#include"string.h"  
#include"netinet/in.h"  
#include"netdb.h"
#include<unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <time.h>
#define PORT 4444 
#define BUF_SIZE 2000 
  
int main(int argc, char**argv) {  
 struct sockaddr_in addr, cl_addr;  
 int sockfd, ret;  
 char buffer[BUF_SIZE];  
 struct hostent * server;
 char * serverAddr;
 char dup[10];
 clock_t t;
 if (argc < 2) {
  printf("Enter: client < ip address > as argument \n");
  exit(1);  
 }

 serverAddr = argv[1]; 
 
 sockfd = socket(AF_INET, SOCK_STREAM, 0);  
 if (sockfd < 0) {  
  printf("Error creating socket!\n");  
  exit(1);  
 }  
 printf("Socket created...\n");   

 memset(&addr, 0, sizeof(addr));  
 addr.sin_family = AF_INET;  
 addr.sin_addr.s_addr = inet_addr(serverAddr);
 addr.sin_port = PORT;     

 ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));  
 if (ret < 0) {  
  printf("Error connecting to the server!\n");  
  exit(1);  
 }  
 printf("Connected to the server...\n");  

 memset(buffer, 0, BUF_SIZE);
 
 printf("Enter the file name : ");
 fgets(dup, 10, stdin);
 

 //int i=1;
 while (1) {
  //strcpy(buffer,"hello");
  strcpy(buffer,dup);
  //printf("before sending buffer: %s\n", buffer);

  int length = strlen (buffer);
  if (buffer[length - 1] == '\n')
           buffer[length - 1] = '\0';

  ret = sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));  
  if (ret < 0) {  
   printf("Error sending data!\n\t-%s", buffer);  
  }

  t = clock();

  ret = recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);

  t = clock() - t;
  double time_taken = ( ((double)t)/CLOCKS_PER_SEC )*1000; // in milli-seconds   
  
  if (ret < 0) {  
   printf("Error receiving data!\n");    
  } else {
   printf("%f\n", time_taken);
   //fputs(buffer, stdout);
   //printf("\n");
  }  

  //i=i+1;
 }
 
 return 0;    
}  
