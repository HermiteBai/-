#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
size_t count = 0;
size_t flag = 1;
char* buffer;
pthread_t pid1, pid2;
char* str1 = "second";
char* str2 = "seconds";
char* str3 = "minute";
char* str4 = "minutes";
char* str5 = "hour";
char* str6 = "hours";
int default_alarm = 1;

void* counter(void* arg)
{
	while (1)
	{
		count++;
		size_t hour = count / 3600;
		size_t minute = (count % 3600) / 60;
		size_t second = (count % 3600) % 60;
		if (flag)
		{
			printf("You have been distracted for %zu %s %zu %s %zu %s\n", 
										hour, 
										(hour <= 1) ? str5 : str6, 
										minute, 
										(minute <= 1) ? str3: str4,
										second,
										(second <= 1) ? str1 : str2);
			if (count % 60 * default_alarm == 0) {
				system("say You should work now!");
			}
		}
			
		else
			printf("Working\n");
		sleep(1);
		system("Clear");
	}
}

void* update(void* arg)
{
	size_t length;
	while (getline(&buffer, &length, stdin) != -1)
	{
		flag = !flag;
		count = 0;
	}
	free(buffer);
	return NULL;
}

void handler(int sig)
{
	free(buffer);	
	system("clear");
	exit(0);
}

int main(int argc, char** argv)
{
		if (argc != 2) {
			exit(1);
		}
		default_alarm = atoi(argv[1]);
		signal(SIGINT, handler);
		signal(SIGQUIT, handler);
		system("clear");
		pthread_create(&pid1, NULL, counter, NULL);
		pthread_create(&pid2, NULL, update, NULL);
		pthread_join(pid1, NULL);
		pthread_join(pid2, NULL);
		return 0;
}
