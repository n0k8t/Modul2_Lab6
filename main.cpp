#include "TCastException.h"
#include <cmath>

template<typename T>
T FromString(const char* data);

template<>
int FromString(const char*  data)
{
    long long result = 0;
    long long digit = 1;

    for(int i = ((int)strlen(data) - 1); i >= 0; i--)
    {
        if(data[i] == '-')
        {   if( i == 0 )
            {
                break;
            }else
            {
                throw WrongUnit();
            }
        }

        if (isdigit(data[i]))
        {
            result = result + (digit * (data[i] - '0'));
            digit = digit * 10;
        } else
        {
            throw WrongUnit();
        }
    }


    if(data[0] == '-')
    {
        result *= -1;
    }


    if (result > 2147483647)
    {
        throw CapacityError();
    }else if(result < -2147483648)
    {
        throw CapacityError();
    }

    return result;
} // int+

template<>
bool FromString(const char *data)
{
    std::string checker(data);
    float k = checker.size();
    int i = 0;

    while (i!=k)
    {
        checker[i]=char( tolower(data[i]) );
        i++;
    }

    if ( !checker.compare("true") || !checker.compare("1") )
    {
        return true;
    } else if ( !checker.compare("false") || !checker.compare("0") )
    {
        return false;
    }
    else throw WrongUnit();
} // logic+

template<>
float FromString(const char*  data)
{
    float result = 0;
    float digit = 1;
    float _digit = powf(10,-1);
    int dot = -1;
    int count = 0;


    for(int i = ((int)strlen(data) - 1); i >= 0; i--)
    {
        if (data[i] == '.' || data[i] == ',')
        {
            dot = i;
            count++;
        }
    }

    if(count > 1)
    {
        throw WrongUnit();
    }


    for(int i = dot - 1; i >= 0; i--)
    {
        if (isdigit(data[i]))
        {
            result = result + (digit * float(data[i] - '0'));
            digit = digit * 10;
        }else if (data [i] == '-')
        {

        }else
        {
            throw WrongUnit();
        }
    }



    for(int i = dot + 1; i < (int)strlen(data) - 1; i++)
    {
        if (isdigit(data[i]))
        {
            result = result + (_digit * float(data[i] - '0'));
            _digit = _digit * powf(10,-1);
        }else
        {
            throw WrongUnit();
        }
    }

    if(data[0] == '-')
    {
        result *= -1;
    }


    if (result > MAXFLOAT)
    {
        throw CapacityError();
    }else if(result < -MAXFLOAT)
    {
        throw CapacityError();
    }

    return result;
} // float +?




int main()
{
    FromString<int>("-00214748364");
    FromString<int>("-002147483648");
    FromString<int>("002147483647");
    FromString<int>("-2147483648");

    try {
        FromString<int>("-002147483649");
    }
    catch (CapacityError &exc) {
        exc.what();
        std::cout << "Capacity ERROR"<< std::endl;
    }
    try {
        FromString<int>("-0021f48364");
    }
    catch (WrongUnit &exc) {
        exc.what();
        std::cout << "Element ERROR"<< std::endl;
    }


    try
    {
        FromString<bool>("FalseTrue");
    }
    catch (WrongUnit &e)
    {
        std::cout<<"It's not a bool"<< std::endl;
    }


    try
    {
        FromString<float>("i0.123");
    }
    catch (WrongUnit &e)
    {
        std::cout << "It's not a float"<< std::endl;
    }

    return 0;
}