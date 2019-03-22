#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "string.h"
#include "netinet/in.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "ctype.h"
#include "time.h"

#define PORT 4444					
#define CLADDR_LEN 100			
#define BUF_SIZE 2000			

void main(){
	
	struct sockaddr_in addr, cl_addr;
	int i, sockfd, len, ret, newsockfd;

	char clientAddr[CLADDR_LEN]; 
	char buffer[BUF_SIZE]= "";
	char find_time[50];
	char files[5][25] = {"sensor1.txt" , "sensor2.txt" , "sensor3.txt" ,"sensor4.txt" ,"sensor5.txt"};


	pid_t childpid;
	time_t t; 
	struct tm* tmp;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		printf("Error creating socket!\n");
		exit(1);
	}

	printf("Socket created...\n");

	//////////////////////////////
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = PORT;
	////////////////////////////////
	

	ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));

	if (ret < 0){
		printf("Error binding!\n");
		exit(1);
	}

	printf("Binding done...\n");
	printf("Waiting for a connection...\n");
	
	
	listen(sockfd, 5);

	

	while(1){



		len = sizeof(cl_addr);

		//new client accpet
		newsockfd = accept(sockfd, (struct sockaddr*)&cl_addr, &len);

		if (newsockfd < 0){
			printf("Error accepting connection!\n");
			exit(1);
		}

		printf("Connection accepted...\n");

		inet_ntop(AF_INET,  &(cl_addr.sin_addr), clientAddr, CLADDR_LEN);

		if ((childpid = fork()) == 0){
			//creating a child process
			close(sockfd);


			while(1){
				


				memset(buffer, 0, BUF_SIZE);
				ret = recvfrom(newsockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &cl_addr, &len);

				if (ret < 0){
					printf("Error receiving data!\n");
					exit(1);
				}

				

				//opening and reading from the sensor files

				

				time(&t);

				tmp = localtime(&t);

				strftime(find_time, sizeof(find_time), "%Y-%m-%d %H:%M:%S", tmp);
				strcat(buffer, find_time);
				strcat(buffer, ",");

				char value [2000];
				int counter = 0;

				FILE* fptr;
				for (i=0; i<5; i++){
					fptr = fopen(files[i], "r");

					while((value[counter++] = fgetc(fptr)) != EOF);
					value[counter-1] = ',';
					fclose(fptr);
				}

				value[counter-1] = ',';
				value[counter++] = '\0';

				strcat(buffer, value);

				
				printf(" %s\n", buffer);
				
				ret = sendto(newsockfd, buffer, BUF_SIZE, 0, (struct sockaddr*)&cl_addr, len);

				if(ret < 0){
					printf("Error sending data!\n");
					exit(1);
				}

				


			}

		}

		close(newsockfd);
	} 

}