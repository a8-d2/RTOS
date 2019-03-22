#include"stdio.h"  
#include"stdlib.h"  
#include"sys/types.h"  
#include"sys/socket.h"  
#include"string.h"  
#include"netinet/in.h"  
#include"netdb.h"
#include"unistd.h"
#include "arpa/inet.h"
#include "ctype.h"
#include "time.h"
#define PORT 4444 
#define BUF_SIZE 2000
  
int main(int argc, char**argv) {  
     struct sockaddr_in addr, cl_addr;  
     int sockfd, ret;  
     char buffer[BUF_SIZE];  
     struct hostent * server;
     char * serverAddr;
     
 


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
        

     memset(&addr, 0, sizeof(addr));  
     addr.sin_family = AF_INET;  
     addr.sin_addr.s_addr = inet_addr(serverAddr);
     addr.sin_port = PORT;     

     ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));  
     if (ret < 0) {  
      printf("Error connecting to the server!\n");  
      exit(1);  
     }  
     

 
     while (1) {
          memset(buffer, 0, BUF_SIZE);
          ret = sendto(sockfd, buffer , BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));  
          if (ret < 0) {  
           printf("Error sending data!\n\t-%s", buffer);  
          }

          

          ret = recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);

          
          
          
          if (ret < 0) {  
          
           printf("Error receiving data!\n");    
          
          } else {
           printf(" %s\n", buffer);
           //printf("%f\n", time_taken);
           //fputs(buffer, stdout);
           //printf("\n");
          }  
          
          sleep(2);  



          }
 
 return 0;    
}  
