#include "threadsir.h"
#include"processer.h"
#include"sx.h"
ThreadSir::ThreadSir()
{



}
void ThreadSir::close(){

    Sx::closeStatu = true;
    quit();

}
void ThreadSir::run(){

    while(1){
        if(Sx::closeStatu == 999){

            break;
        }
        int mainCode = Sx::Instance()->mainCode;
        int subCode = Sx::Instance()->subCode;

        Processer::Instance->threadEvent(mainCode,subCode);
    }

}
