#include<stdio.h>
#include<string.h>
#include<semaphore.h>
#include<pthread.h>

pthread_t t1,t2,t3,t4,t5;
pthread_mutex_t l1,l2;
int n,NOP=0,m;


void *staff()
{
	printf("\nYou have access to use system at any time\n");
	printf("Please Enter the Time in 24 format :");
	scanf("%d",&m);
	if(m>=0&&m<=24)
	{
		pthread_mutex_lock(&l2);
		NOP++;
		printf("\nSTAFF is PLAYING\n");
		pthread_mutex_unlock(&l2);
		pthread_exit(NULL);
	}
}
void staff1()
{
		pthread_mutex_lock(&l2);
		NOP++;
		printf("STAFF is PLAYING\n");
		pthread_mutex_unlock(&l2);
		pthread_exit(NULL);
}
void *teacher()
{  
	
	printf("\nPlease Enter the Time in 24 Format :");
	scanf("%d",&m);
	if(m>=17&&m<=22)
	{  
		pthread_mutex_lock(&l1);
		printf("\nTEACHER is PLAYING\n");
		NOP++;
		pthread_mutex_unlock(&l1);
		staff1();
		pthread_exit(NULL);
	}
	else
	printf("You are not able to access the game at this time\n");
	staff1();
}
void *student()
{
	printf("\nPlease Enter the Time in 24 Format :");
	scanf("%d",&m);
	if(m<=6||m>=22)
	{
		
		pthread_mutex_lock(&l1);
		NOP++;
		printf("\nSTUDENT is PLAYING\n");
		pthread_mutex_unlock(&l1);
		sleep(1);
    	staff1();
		pthread_exit(NULL);
    		
	}
	else
	printf("Sorry ,You are not allowed to play game at this time\n");
	staff1();
	
}
void *begin()
{
	M:
printf("\n\nEnter Your Choice:\n\n1.STAFF     2.STUDENT      3.TEACHER        4.FOR EXIT\n");
scanf("%d",&n);
switch(n){
	case 1:	
		pthread_create(&t3,NULL,staff,NULL);
		pthread_join(t3,NULL);
		break;
	case 2:
		printf("You have access between 10 pm to 6 am only");
		pthread_create(&t4,NULL,student,NULL);
		pthread_join(t4,NULL);		
		break;
	case 3:
	    printf("You have access between 5 pm to 8 pm only ");
		pthread_create(&t5,NULL,teacher,NULL);
		pthread_join(t5,NULL);
		break;
	case 4:
	    pthread_exit(NULL);
	default: 
			printf("\nWrong Entry Try Again\n");
	         goto M;
	         		break;
	         }
	pthread_exit(NULL);
	}
void main()
{
	int i;
	printf("\n\n                                ***************WELCOME TO GAMING WORLD***********");
	printf("\n\n\nWho are You?");
	for(i=0;i<6;i++)
	{
		pthread_create(&t1,NULL,begin,NULL);
		pthread_join(t1,NULL);
		printf("TOTAL NO. OF USERS %d",NOP);
	}
}
