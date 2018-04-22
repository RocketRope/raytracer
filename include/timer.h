#ifndef _TIMER_H_
#define _TIMER_H_

#include <iostream>
#include <chrono> 

class Timer
{
    private:

        std::string msg;
        std::chrono::high_resolution_clock::time_point start_point;

        std::ostream& os;

    public:

        Timer(const std::string& _msg = "Timer", std::ostream& _os = std::cout )
            : msg{_msg} , os{_os}
        {
            start_point = std::chrono::high_resolution_clock::now();
        }

        ~Timer()
        {
            std::chrono::high_resolution_clock::time_point end_point;
            end_point = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> delta_time = end_point - start_point;

            os << std::endl << msg << " : " << delta_time.count() << "s" << std::endl; 
        }
};

#endif // _TIMER_H_