#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

struct msgbuf{
    long mtype;
    char Data[256];
} Message;
int main(int argc, char **argv)
{
    key_t key;
    int msgid;
    key = ftok("/usr/mash",'s');
    msgid = msgget(key, 0666 | IPC_CREAT);
    for(;;) {
        msgrcv(msgid, (struct msgbuf*) (&Message), 256, 0, 0);
        if ((Message.Data[0]=='e') && (Message.Data[1]=='n')&& (Message.Data[2]=='d')){
            Message.Data[0] = 1;
            Message.mtype = 2;
            msgsnd(msgid, (struct msgbuf*)(&Message),1, 0);
            break;
        }
        printf("\n имя программы = %s \n Message: %s",argv[0],Message.Data);
    }
return 0;
}
