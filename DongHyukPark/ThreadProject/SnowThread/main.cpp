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
    //Start
    for (int i = 0; i < MAX_WORKER_THREAD; ++i)
    {
        vecWorkerTherad.emplace_back(new CWorkerThread(i));
    }

    //Wait
    for (auto workerThrad : vecWorkerTherad)
    {
        workerThrad->WaitForThread();
    }

    //Delete
    for (auto workerThrad : vecWorkerTherad)
    {
        SAFE_DELETE(workerThrad);
    }
    vecWorkerTherad.clear();


    std::cout << "End Main\n";
}