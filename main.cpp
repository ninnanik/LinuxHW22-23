#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int
do_command(const char* argv[])
{
    int child = fork ();
    if (0 == child) {
        const int resultCode = execlp(argv[0], argv[1], argv[2], argv[3], nullptr);
        if (resultCode != 0) {
            perror("exec bad :(");
            exit(resultCode);
        }
        ///exit (0);
    } else if (0 > child) {
        perror ("fork failed((");
        exit (-1);
    }
    int exit_status;
    waitpid (child, &exit_status, 0);
    if (WIFEXITED(exit_status)) {
        std::cout << "The process exited with status code " << WIFEXITED (exit_status) << std::endl;
    } else if (WIFSIGNALED(exit_status)) {
        std::cout << "The process was removed with status code " << WIFSIGNALED (exit_status) << std::endl;
    }
    return 0;
}

int
main ()
{
    const char* program[4];
    program[0] = "ls";
    program[1] = "-a";
    program[2] = "-l";
    program[3] = nullptr;
    do_command(program);

    return 0;
}
