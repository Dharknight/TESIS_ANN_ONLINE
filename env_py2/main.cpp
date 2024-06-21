#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>

using namespace std;

int main() {
    int to_child_pipe[2];
    int from_child_pipe[2];
    pid_t cpid;
    char buf[1024];

    if (pipe(to_child_pipe) == -1 || pipe(from_child_pipe) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {    /* Proceso hijo */
        close(to_child_pipe[1]);          /* Cierra el descriptor de escritura del pipe de entrada */
        dup2(to_child_pipe[0], STDIN_FILENO);  /* Redirige la entrada estándar al descriptor de lectura del pipe de entrada */
        close(to_child_pipe[0]);

        close(from_child_pipe[0]);        /* Cierra el descriptor de lectura del pipe de salida */
        dup2(from_child_pipe[1], STDOUT_FILENO);  /* Redirige la salida estándar al descriptor de escritura del pipe de salida */
        close(from_child_pipe[1]);

        execlp("/home/abel/env_py2/env_py3/bin/python3", "python3", "/home/abel/env_py2/env_py3/nn_script.py", (char *) NULL); // Cambia las rutas a las correctas
        perror("execlp");
        _exit(EXIT_FAILURE);
    } else {            /* Proceso padre */
        close(to_child_pipe[0]);          /* Cierra el descriptor de lectura del pipe de entrada */
        close(from_child_pipe[1]);        /* Cierra el descriptor de escritura del pipe de salida */
        
        string message = "HOLA PYTHON, DESDE C++";
        write(to_child_pipe[1], message.c_str(), message.length());
        close(to_child_pipe[1]);          /* Cierra el descriptor de escritura; envía EOF al hijo */

        wait(NULL);                /* Espera a que termine el hijo */
        
        read(from_child_pipe[0], buf, sizeof(buf) - 1);  /* Leer la respuesta del hijo */
        buf[sizeof(buf) - 1] = '\0';  /* Asegura que la cadena esté terminada en nulo */
        cout << "Recibo en C++, recibiste: " << buf << endl;
        close(from_child_pipe[0]);
    }

    return 0;
}
