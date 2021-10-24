#include<iostream>
#include<vector>
#include"WorkerThread.h"

constexpr int MAX_WORKER_THREAD = 10;


int main() {

    std::cout << " ######## ##     ## ########  ########    ###    ########  " << std::endl;
    std::cout << "    ##    ##     ## ##     ## ##         ## ##   ##     ## " << std::endl;
    std::cout << "    ##    ##     ## ##     ## ##        ##   ##  ##     ## " << std::endl;
    std::cout << "    ##    ######### ########  ######   ##     ## ##     ## " << std::endl;
    std::cout << "    ##    ##     ## ##   ##   ##       ######### ##     ## " << std::endl;
    std::cout << "    ##    ##     ## ##    ##  ##       ##     ## ##     ## " << std::endl;
    std::cout << "    ##    ##     ## ##     ## ######## ##     ## ########  " << std::endl;
 

    std::vector<CWorkerThread*> vecWorkerTherad;

    for (int i = 0; i < MAX_WORKER_THREAD; ++i) 
    {
    
    
    }

}