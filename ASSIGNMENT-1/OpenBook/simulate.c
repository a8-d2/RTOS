#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
char n[20];
sem_t len;


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
			sem_wait(&len);

			
			//printf(" Received data is ==== : %s\n",n);
			//logic implementation is here 
			//printf("Received sub string is ==== : %s\n",n);
			

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
	char str[20] = "Dear";
	

	do {	
	pthread_create(&tr,NULL,read1, (void *)str);
	//printf("Pthread value = %d\n", tr);

	//printf("Enter the string whose prefix has to be checked\n");
	scanf(" %[^\n]s",n);

	sem_post(&len);
	pthread_join(tr,NULL);

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
