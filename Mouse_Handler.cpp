

#include <bitset>
#include"Mouse_Handler.h"

// enum class Buttons {
//     LEFT = 1 << 0,
//     RIGHT = 1 << 1,
//     MIDDLE = 1 << 2
// }

    //Passing a command to the shell command line across a newly created pipe and returning the result of the command
    std::string Mouse_Handler::CommandToPipe(const char* command) { 
        std::array<char, 128> buffer; 
        std::string result; 
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command, "r"), pclose); // awesome
        if (!pipe) { 
            throw std::runtime_error("popen() failed!"); 
        } 
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) { 
            result += buffer.data(); 
        } 
        return result; 
    }


    //Preparation work before mouse reading
    Mouse_Handler::Mouse_Handler(){
        fd = open(pDevice, O_RDWR);
        if(fd == -1)
        {
            printf("\nERROR Opening %s\n", pDevice);
            throw std::runtime_error("Mouse_HandlerOpening failure!"); 
            
        }

        bytes = read(fd, data, sizeof(data)); // Why do we need it here?

       
        if((data[0]& 0x4)==4){
            Middleflag = 1; // bool should be assigned with true/false
        }else{
            Middleflag = 0;
        }

    }

    // I don't see
    std::string Mouse_Handler::GetCoordinates(){
        std::string str = CommandToPipe("xdotool getmouselocation --shell"); // what if xdotool doesn't exist?
        std::string str2;
        int i = 0;

        // You can just read 2 lines
        while(str[i]!='S'){//We need to extract all information before some "moment"
            if(str[i]=='\n'){
                str2+=' ';
            }else{
                str2+=str[i];
            }
            i++;
        }

        return str2;

    }


    std::string Mouse_Handler::GetMouseButtonClick(){
        

        while(true){
            bytes = read(fd, data, sizeof(data));
            if(bytes > 0)
            {
                left = data[0] & 0x1; // give naming to this constants
                right = data[0] & 0x2;
                middle = data[0] & 0x4;

                x = data[1];
                y = data[2];

                // std::bitset<sizeof(data)> bs(data);
                // std::cout << bs << std::endl;

                if(left==1){
                    return GetCoordinates()+" LMK(Left Mouse click)";
                }
                if(right==2){
                    return GetCoordinates()+" RMK(Right Mouse click)";
                }
                // Strange logic
                if((middle==0 && Middleflag==1)||(middle==4&&Middleflag==0) ){//Middle button pressed
                    return "0";
                }

            }
        }
    }


