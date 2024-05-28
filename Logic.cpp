



#include"Logic.h"
#include <atomic>

// Need to have it in class
std::atomic<bool> exit_thread_flag{ false };

void MouseButtonClicksLogic(Connection& connection, Mouse_Handler& mouse){
    std::string str;
    while(true){
        if (!exit_thread_flag) { // we can do it in while statement
                
            try
            {
                str = mouse.GetMouseButtonClick();
                if(str=="0"){//Middle button pressed -> exit thread
                    exit_thread_flag = true;
                    break;
                }
                connection.Send(str);
            } 
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }else{
            break;
        }
    }
}




void MouseMoveLogic(Connection& connection, Mouse_Handler& mouse){
    std::string str;
        while(true){
            if (!exit_thread_flag) {
                std::chrono::milliseconds delay(500); 
                std::this_thread::sleep_for(delay);

                try
                {
                    str = mouse.GetCoordinates();
                    connection.Send(str);
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
            }else{
                break;
            }
        }
    
}