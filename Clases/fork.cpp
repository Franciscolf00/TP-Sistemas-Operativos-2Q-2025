#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

using namespace std;

int main() {

    pid_t pidHijo = fork();

    if (pidHijo == 0)
    {
        cout << "Soy el proceso hijo" << endl;
        sleep(10);
    }
    else if (pidHijo > 0)
    {
        wait(NULL);
        cout << "Soy el proceso padre" << endl;
    }
    else
    {
        cout << "fork() dio error" << endl;
    }

    cout << "Terminé, soy el PID" << getpid() << endl;

    pid_t pid = fork() * fork() * fork();

    if (pid == 0){
        printf("*\n");
    }



    return EXIT_SUCCESS;
}