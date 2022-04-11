#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int ac, char* av[], char* envp[]) {
    char** new_av = calloc(ac + 2 + 1, sizeof(char *));
    if (!new_av) {
        exit(EXIT_FAILURE);
    }
    new_av[0] = av[0];
    new_av[1] = strdup("-cpu");
    new_av[2] = strdup("max,pauth-impdef=on");
    for (int i = 1; i < ac; ++i) {
        new_av[i+2] = av[i];
    }
    new_av[ac + 2] = NULL;
    execve("/usr/bin/qemu-aarch64-static", new_av, envp);
}
