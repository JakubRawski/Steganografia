#include "Errors.h"
#include "help.h"
#include "info.h"
#include "check.h"
#include "Engine.h"

#include <string>
#include <fmt/core.h>




auto main(int argc, char *argv[]) -> int {

    if(argc == 1){
        help();
        return 0;
    }
        std::string flag = argv[1];
    if(flag == "-i" or flag == "--info"){
        if(argc != 3){
            errArg();
        }
        Info(argv[2]);
    } else if(flag == "-c" or flag == "--check"){
        if(argc != 4){
            errArg();
        }
        Check(argv[2],argv[3]);
    } else if (flag == "-e" or flag == "--encrypt"){
        if(argc != 4){
            errArg();
        }
        Encrypt(argv[2] , argv[3]);
    } else if (flag == "-d" or flag == "--decrypt"){
        if(argc != 3){
            errArg();
        }

        auto res = Decrypt(argv[2]);
        fmt::println("Decrypted message: {}",res);
    } else if(flag == "-h" or flag == "--help"){
        if(argc != 2){
            errArg();
        }
        help();
    } else{
        errFlag();
    }
}
