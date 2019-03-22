#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
int n;
sem_t len[2];


void * read1(void* data)
{
		//printf(" Entering inside thread1\n");
		
		//generate random number 1 to 7
		int c;
		c = (rand() % 6) + 1;
		printf("rv_t1 = %d\n", c);
		sem_wait(&len[0]);
		//store in n;
		n = c;

	
}


void * read2(void* data)
{
		//printf(" Entering inside thread2\n");
		//generate random number 1 to 7
		int d;
		d = (rand() % 6) + 1;
		printf("rv_t2 =  %d\n", d);
		sem_wait(&len[1]);
		//store in n;
		n = d;
	
}


int main()
{
	
	//int status;
	pthread_t tr, tw;
	
	int iter = 1;
	int total[2] = {0,0};
	

	do {	
		//int cmp[2] = {-1,-1};

		printf("iter %d\n", iter);
		pthread_create(&tr,NULL,read1, NULL);
		pthread_create(&tw,NULL,read2, NULL);
		//scanf(" %[^\n]s",n);
		if(1)
		{
		sem_post(&len[0]);
		pthread_join(tr,NULL);
		printf("random value from thread1 is: %d\n" , n); 
		//cmp[0] = n;
		total[0] = total[0] + n; 
		}
		
		if(1) {
		sem_post(&len[1]);
		pthread_join(tw,NULL);
		printf("random value from thread2 is: %d\n" , n);
		//cmp[1] = n;
		total[1] = total[1] + n;
		}
		
		iter = iter + 1;
	
	}while( (total[0] < 100) && (total[1] < 100) );

	//printf("\nfinal check value is: %d\n" , check);
	printf("Total_th1 = %d | Total_th2 = %d\n", total[0], total[1]);
	printf("Winner is : \t");
	if(total[0]>total[1])
		printf("1\n");
	else
		printf("2\n");
}





/*
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
*/


//while(1){
			/*
			printf("Searching prefix:%s\n", data);
			printf("Waiting for string from user (enter any string)\n");
			sem_wait(&len[0]);

			if ( myStrStr(n,data) )
				printf("yes substring %s found in %s\n", data,n);
			else 
				printf("not found\n");
			*/
//char str1[20] = "dear";
	//char str2[20] = "jane";


	//int check = 0;
	//int flag = -1;
/*
	//while(1){	
			printf("Searching prefix:%s\n", data);
			printf("Waiting for string from user (enter any string)\n");
			sem_wait(&len[1]);

			if ( myStrStr(n,data) )
				printf("yes substring %s found in %s\n", data,n);
			else 
				printf("not found\n");
	*/
	//printf("Winner is %d\n",flag);


/*
		if (cmp[0]>cmp[1]){
			check = check + cmp[0];
			flag = 1;
		}
		else
		{
			check = check + cmp[1];
			flag = 2;
		}
		*/
		//printf("Do you want to continue : (1 for YES ; 0 for NO)\n");
		//scanf(" %d", &check);





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
