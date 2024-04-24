


#ifndef MOUSE_HANDLER_H
#define MOUSE_HANDLER_H

#include <unistd.h> 

#include <string>
#include <fcntl.h>
#include <chrono>
#include <thread>
#include<iostream>
#include <linux/input.h>



class Mouse_Handler{
private:
    int fd, bytes;
    unsigned char data[4]={0,0,0,0};

    const char *pDevice = "/dev/input/mice";

    int left, middle, right;
    signed char x, y;


    std::string CommandToPipe(const char* cmd);

     bool Middleflag = 0;


public:

    Mouse_Handler();

    std::string GetCoordinates();

    std::string GetMouseButtonClick();

    



};


#endif