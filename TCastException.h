#ifndef MODUL2_LAB6_TCASTEXCEPTION_H
#define MODUL2_LAB6_TCASTEXCEPTION_H


#include <iostream>
#include <exception>
#include <string>


class TCastException : public std::exception
{

};

class CapacityError : public  TCastException
{

};

class WrongUnit : public  TCastException
{

};



#endif //MODUL2_LAB6_TCASTEXCEPTION_H
