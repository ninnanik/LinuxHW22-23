#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int
main()
{
    std::string* xargs ;
    xargs = new std::string [3];
    for (int i = 0; i < 3; ++i) {
        std::cin >> xargs[i];
    }
    int process = fork();
    if(0 == process)
    {
        const int resultCode = execlp("xargs", xargs[0], xargs[1], xargs[2], nullptr);
        if (resultCode != 0) {
            perror ("kneres exbayr( / exec bad");
            exit(EXIT_FAILURE);
        }
    } else if (process > 0) {
        perror("hazar angam kneres exbayr(/fork failed");
        exit (-1);
    }
    int exit_status;
    waitpid (process, &exit_status, 0);
    if (WIFEXITED(exit_status)) {
        std::cout << "The process exited with status code " << WIFEXITED (exit_status) << std::endl;
    } else if (WIFSIGNALED(exit_status)) {
        std::cout << "The process was removed with status code " << WIFSIGNALED (exit_status) << std::endl;
    }
      
    return 0;
}

