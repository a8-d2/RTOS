#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
char n[20];
sem_t len[2];


int myStrStr(char * str, char * sub)
{
	int flag = 0;
	
	int i=0,len1=0,len2=0;
	
	len1 = strlen(str);
	len2 = strlen(sub);
	
	while(str[i] != '\0')
	{
			if(str[i] == sub[0])
			{
					if((i+len2)>len1)
						break;
						
					if(strncmp(str+i,sub,len2)==0)
					{
						flag = 1;
						break;
					}
			}
			i++;
	}
	
	return flag;
}


void * read1(void* data)
{
	//while(1){
			
			printf("Searching prefix:%s\n", data);
			printf("Waiting for string from user (enter any string)\n");
			sem_wait(&len[0]);

			if ( myStrStr(n,data) )
				printf("yes substring %s found in %s\n", data,n);
			else 
				printf("not found\n");
}



void * read2(void* data)
{
	//while(1){
			
			printf("Searching prefix:%s\n", data);
			printf("Waiting for string from user (enter any string)\n");
			sem_wait(&len[1]);

			if ( myStrStr(n,data) )
				printf("yes substring %s found in %s\n", data,n);
			else 
				printf("not found\n");
}


int main()
{
	
	//int status;
	pthread_t tr, tw;
	int check;
	char str1[20] = "dear";
	char str2[20] = "jane";

	do {	
	pthread_create(&tr,NULL,read1, (void *)str1);
	pthread_create(&tw,NULL,read2, (void *)str2);
	scanf(" %[^\n]s",n);

	sem_post(&len[0]);
	pthread_join(tr,NULL);

	sem_post(&len[1]);
	pthread_join(tw,NULL);
	//pthread_join(tw,NULL);
	printf("Do you want to continue : (1 for YES ; 0 for NO)\n");
	scanf(" %d", &check);
	
	}while(check == 1);


}





//}

/*
void * write1()
{
	while(1)
		{
		sem_wait(&len);
		printf("\nThread-2:The string entered is :");
		printf("==== %s\n",n);
		}
}
*/





//char *ptr ;
	//const int x = 100;
	//ptr = (char*) malloc(100);
	//printf("Address of pointer variable is %x ", &ptr);
	//printf("Address on heap is %x ", ptr);
	//printf("Address on const is %x ", &x);
	//printf("Address on global is %x ", &len);

	//pthread_create(&tr,NULL,read1,NULL);
	//pthread_create(&tw,NULL,write1,NULL);
	//printf("Pthread value = %d\n", tr);
	//printf("Pthread value = %d\n", tw);
	
	//sending data to thread
