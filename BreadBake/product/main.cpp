
#include "BreadBaker.h"
#include "Display.h"
#include "EventGenerator.h"
#include "ExtraIngredientsTray.h"
#include "KneadMotor.h"
#include "Log.h"
#include "menu.h"
#include "Oven.h"
#include "StartButtonLed.h"
#include "Tasks.h"
#include "Timer.h"
#include "YeastTray.h"
#include <thread>

#include <iostream>

int main()
{
    Log log;
    Oven oven(log);
    Timer ovenTimer(oven, log);
    oven.AddTimer(ovenTimer);
    KneadMotor motor(log);
    YeastTray yeast(log);
    ExtraIngredientsTray extras(log);
    Display display(log);
    StartButtonLed startButton(log);
    EventGenerator eventGenerator(oven, log);
    Timer mainTimer(eventGenerator, log);
    BreadBaker baker(eventGenerator, ovenTimer, oven, startButton, display, extras, yeast, motor);
    //uint64_t time=100;
    volatile bool quit = false; 
    // TODO: start BreadBaker::Run in a separate thread  
    std::thread bakeThread(&BreadBaker::Run,&baker,&quit);
    // interfaces for simulation
    IUserActions& userAction = eventGenerator;
    IOvenSimulator& ovenSim = oven;
   
    mainTimer.Set(100);
    
    
    char choice = '\0';
    while (!quit)
    {
        ShowMenu();
        choice = GetUserInput(choice);

        switch (choice)
        {
        case '\0':
            // ignore: timeout on user input
            break;
        case '1':
            userAction.MenuPressed();
            break;
        case '2':
            userAction.MenuLongPressed();
            break;
        case '3':
            userAction.TimerUpPressed();
            break;
        case '4':
            userAction.TimerDownPressed();
            break;
        case '5':
            userAction.StartPressed();
            break;
        case '6':
            std::cout << "Please enter the current temperature: ";
            int temp;
            std::cin >> temp;
            std::cin.ignore();
            ovenSim.SetTemperature(temp);
            break;
        case 'q':
            quit = true;
            break;
        default:
            std::cout << "I did not understand your choice (" << choice << ")"
                      << std::endl;
            break;
        }
    }

    return 0;
}
