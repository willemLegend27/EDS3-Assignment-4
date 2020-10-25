#include "BreadBaker.h"
#include "Program.h"


#include <thread>

BreadBaker::BreadBaker(IEventGenerator& eventGenerator, ITimer& timer, IOven& oven, IStartButtonLed& startButton, IDisplay& display, IExtraIngredientsTray& extras, IYeastTray& yeast, IKneadMotor& kneadMotor)
    : eventGenerator(eventGenerator), timer(timer), oven(oven), startButton(startButton), display(display), extras(extras), yeast(yeast), kneadMotor(kneadMotor)
{
    currentState=Standby;    
}

void BreadBaker::Run(volatile bool* quit)
{
    while (!*quit)
    {      
        Events ev = eventGenerator.GetEvent();
        HandleEvent(ev);    
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

// parameter name in comment to prevent compiler warning as it is unused for now
void BreadBaker::HandleEvent(Events ev)
{    
    switch (currentState)
    {  
    case Standby:    
        if(enterState==true){
            display.DisplayOff();
            startButton.LedOff();      
            enterState=false;
        }                
        if(ev==MenuBtnPressed){                    
            currentState=Setup;
            enterState=true;
        }
        break;
    case Setup:
        if(enterState==true){
            //entry
            enterState=false;
        }  
        if(ev==MenuBtnLongPressed){
            currentState=Standby;
        }else if(ev==StartBtnPressed){
            currentState=Producing;
        }
        break;
    case Producing:
        if(enterState==true){
            
            enterState=false;
        }  
        if(ev==MenuBtnLongPressed){
            currentState=Standby;
        }
        break;
    default:
        
        break;
    }
    
     
}
