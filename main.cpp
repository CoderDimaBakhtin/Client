
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <fcntl.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <linux/input.h>


#include"Logic.h"






int main(int argc, char const* argv[])
{
    // not handled different number of args
    std::string ServerIP_address = argv[1];
    try
    {
        Connection connection(ServerIP_address,8080);

        Mouse_Handler mouse;
    
        std::thread ClickTrackingThread(MouseButtonClicksLogic, std::ref(connection), std::ref(mouse));
    
        std::thread MoveTrackingThread(MouseMoveLogic, std::ref(connection), std::ref(mouse));


        ClickTrackingThread.join(); // If you do it in such way - there is no need to wait in main
        MoveTrackingThread.join();
    }
    catch(const std::invalid_argument& e)
    {
        std::cout <<"Error:"<< e.what() << '\n';
    }
    
    
    
	return 0;
}


