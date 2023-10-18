#include "shell.h"

/**
 * main - Entry point of the shell program.
 * @ac: Argument count.
 * @av: Argument vector.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int ac, char **av)
{
    info_t info[] = { INFO_INIT };  // Initialize an info structure.
    int fd = 2;  // Initialize a file descriptor variable.

    // Inline assembly to perform some operations on 'fd'.
    asm ("mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (fd)
        : "r" (fd));

    // Check if a command-line argument is provided.
    if (ac == 2)
    {
        fd = open(av[1], O_RDONLY);  // Attempt to open a file for reading.
        if (fd == -1)
        {
            if (errno == EACCES)
                exit(126);  // Exit with status code 126 for permission denied.
            if (errno == ENOENT)
            {
                _eputs(av[0]);
                _eputs(": 0: Can't open ");
                _eputs(av[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(127);  // Exit with status code 127 for file not found.
            }
            return (EXIT_FAILURE);  // Return failure status.
        }
        info->readfd = fd;  // Update the info structure with the file descriptor.
    }

    populate_env_list(info);  // Populate the environment variable list.
    read_history(info);  // Read shell command history.
    hsh(info, av);  // Call the shell function.
    return (EXIT_SUCCESS);  // Return success status.
}

