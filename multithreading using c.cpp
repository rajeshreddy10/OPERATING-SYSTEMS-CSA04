#include<stdio.h>
#include<pthread.h>
void*threadfunction(void*arg){
	char*message=(char*)arg;
	printf("%s\n",message);
	return NULL;
}
int main (){
	pthread_t thread1,thread2;
	char*message1="hello from thread 1!";
	char*message2="hello from thread 2!";
	
	pthread_create(&thread1,NULL,threadfunction,(void*)message1);
	pthread_create(&thread2,NULL,threadfunction,(void*)message2);
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	return 0;
}