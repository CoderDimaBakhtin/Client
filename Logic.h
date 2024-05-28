

#ifndef LOGIC_H
#define LOGIC_H


#include"Connection.h"
#include"Mouse_Handler.h"

// Improve naming
void MouseButtonClicksLogic(Connection& connection, Mouse_Handler& mouse);

void MouseMoveLogic(Connection& connection, Mouse_Handler& mouse);

#endif