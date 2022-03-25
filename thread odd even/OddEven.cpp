#include <iostream>
#include <thread> 
#include <chrono> 
#include <mutex> 
#include <condition_variable> 

using namespace std;

mutex mu;
condition_variable cond;
int a = 1;

void Odd()
{
    for (; ;)
    {
        unique_lock<mutex> locker(mu); //mengatur penguncian pada thread
        cond.wait(locker, []() { return (a % 2 == 1); }); //untuk mengunci thread
        cout << "Print Odd Number: " << a << endl; //mencetak nilai variabel
        this_thread::sleep_for(chrono::milliseconds(1000)); //pemberian jeda waktu 
        a++; //looping for
        locker.unlock(); //membuka thread yang terkunci
        cond.notify_all(); //untuk meneruskan thread
    }
}

void Even()
{
    for (; ;)
    {
        unique_lock<mutex> locker(mu); //mengatur penguncian pada thread
        cond.wait(locker, []() { return (a % 2 == 0); });//untuk mengunci thread
        cout << "Print Even Number: " << a << endl; //mencetak nilai variabel
        this_thread::sleep_for(chrono::milliseconds(2500)); //pemberian jeda waktu 
        a++; //looping for
        locker.unlock(); //membuka thread yang terkunci
        cond.notify_all(); //untuk meneruskan thread
    }
}

int main()
{
    thread t1(Odd); //untuk memulai thread
    thread t2(Even); //untuk memulai thread
    t1.join(); //memastikan thread selesai
    t2.join(); //memastikan thread selesai
    return 0;
}