#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int ac, char* av[], char* envp[]) {
    char** new_av = calloc(ac + 1 + 1, sizeof(char *));
    if (!new_av) {
        exit(EXIT_FAILURE);
    }
    
    new_av[0] = av[0];
    new_av[1] = strdup("-cpu");
    new_av[2] = strdup("max,pauth-impdef=on");
    new_av[3] = av[1];
    // skip av[2], which is the executable name
    for (int i = 3; i < ac; ++i) {
        new_av[i+1] = av[i];
    }
    new_av[ac + 1] = NULL;
    return execve("/usr/bin/qemu-aarch64-static", new_av, envp);
}
