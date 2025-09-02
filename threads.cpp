#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <mutex>
#include <thread>

using namespace std;

mutex mutexPantalla;
int a = 1;
string nombre = "Francisco";

void tareaHilo(int id)
{
    for (int i = 1; i <= 5; i++)
    {
        //P(mutexPantalla)
        mutexPantalla.lock();
        cout << "[tareaHilo]" << id << " dice " << i << endl;

        //V(mutexPantalla)
        mutexPantalla.unlock();
    }
}

int main()
{

cout << "Hilos en C++" << endl;

thread hilo1(tareaHilo, 0); //POSIX threads - pthread
thread hilo2(tareaHilo, 1); //pthread_create(...)
thread hilo3(tareaHilo, 2);
thread hilo4(tareaHilo, 3); // thread hilo4 = new thread(tareaHilo, 3)

mutexPantalla.lock();
cout << "Esperando al hilo 1" << endl;
mutexPantalla.unlock();

hilo1.join();
hilo2.join();
hilo3.join();
hilo4.join();

cout << "Fin main" << endl;

return EXIT_SUCCESS;

}