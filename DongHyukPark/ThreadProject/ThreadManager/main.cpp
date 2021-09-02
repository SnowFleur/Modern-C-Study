#include<iostream>
//#include"ThreadManager.h"
#include"SnowThread.h"

void ThreadFunction(int value1, int value2) {
    //PDH- 내부적으로 반복문을 돌고 있음

    std::cout << "뜨뜨뜨뜨레드: ";
    std::cout << value1 << " " << value2 << "\n";
}

int main() {

    std::cout << " ######## ##     ## ########  ########    ###    ########     ##     ##  ######   ########       " << std::endl;
    std::cout << "    ##    ##     ## ##     ## ##         ## ##   ##     ##    ###   ### ##    ##  ##     ##      " << std::endl;
    std::cout << "    ##    ##     ## ##     ## ##        ##   ##  ##     ##    #### #### ##        ##     ##      " << std::endl;
    std::cout << "    ##    ######### ########  ######   ##     ## ##     ##    ## ### ## ##   #### ########       " << std::endl;
    std::cout << "    ##    ##     ## ##   ##   ##       ######### ##     ##    ##     ## ##    ##  ##   ##        " << std::endl;
    std::cout << "    ##    ##     ## ##    ##  ##       ##     ## ##     ##    ##     ## ##    ##  ##    ##       " << std::endl;
    std::cout << "    ##    ##     ## ##     ## ######## ##     ## ########     ##     ##  ######   ##     ##      " << std::endl;


    CSnowThread thread(ThreadFunction, 5, 1);
    thread.Join();
}