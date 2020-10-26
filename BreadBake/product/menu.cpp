#include "menu.h"

#include <cstdio>
#include <iostream>
#include <sys/select.h>
#include <thread>
#include <unistd.h>

static bool GetCharAvailable(long timeoutInSec)
{
    fd_set readFds;
    FD_ZERO(&readFds);
    FD_SET(fileno(stdin), &readFds);

    struct timeval timeout;
    timeout.tv_sec = timeoutInSec;
    timeout.tv_usec = 0;

    int result = select(FD_SETSIZE, &readFds, NULL, NULL, &timeout);
    if (result < 0)
    {
        perror("Select call failed");
    }
    return result > 0;
}

void ShowMenu(void)
{
    const char *strings[] =
        {
            "\n\nMenu\n",
            "====\n",
            "(1) Menu button\n",
            "(2) Menu button long press\n",
            "(3) Timer up button\n",
            "(4) Timer down button\n",
            "(5) Start button\n",
            "(6) Set oven temperature\n",
            "-----------------------\n",
            "(q) QUIT\n",
            "Enter: repeat previous choice\n\n",
            "Choice : "};
    const size_t NrMenuStrings = sizeof(strings) / sizeof(strings[0]);
    for (size_t i = 0; i < NrMenuStrings; i++)
    {
        std::cout << strings[i];
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }

    fflush(stdout);
}

char GetUserInput(char oldChoice)
{
    const char EnterKey = 10;
    char choice = '\0';

    bool charAvailable = GetCharAvailable(3);
    if (charAvailable)
    {
        const int MaxBufferSize = 2;
        char buf[MaxBufferSize];
        read(fileno(stdin), buf, MaxBufferSize);
        if (buf[0] == EnterKey)
        {
            // repeat previous command
            choice = oldChoice;
        }
        else
        {
            choice = buf[0];
        }
        fflush(stdin);
    }

    return choice;
}
