#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

 struct msgbuf{
     long mtype;
     char Data[256];
} Message;

int main(int argc, char **argv){
    
    int file,MAX,i;
    printf ("сколько будет получателей = ");
    scanf("%d",&MAX);
    
    if (argc == 2){
        file = open(argv[1], O_RDONLY);
        if (file != -1){
            dup2(file,0);
            close(file);
        }
    }
    else {
        printf ("Error in argc введите название текстого файла в командной строке\n");
        return 1;
    }
    
    key_t key;
    int msgid;
    char str[256];
    key = ftok("/usr/mash",'s');
    msgid = msgget(key, 0666 | IPC_CREAT);
    
    for(;;) {
        gets(str);
        strcpy(Message.Data, str);
        
        if((str[0]=='e')&&(str[1] == 'n')&&(str[2] == 'd')){
            for(i = 0;i<MAX;i++){
                msgsnd(msgid, (struct msgbuf*)(&Message), strlen(str) + 1, 0);
            }
            i = 0;
            while(i != MAX){
                msgrcv(msgid, (struct msgbuf*) (&Message), 256, 2, 0);
                i = i + Message.Data[0];
            }
            msgctl(msgid, IPC_RMID, NULL);
            printf ("Программа завершена успешно\n");
            return 0;
        }
        Message.mtype = 1;
        for(i = 0;i<MAX;i++){
            msgsnd(msgid, (struct msgbuf*)(&Message), strlen(str) + 1, 0);
        }
     }
}
