#include "calender.h"

int main()
{
    string cmd;
    Date date;
    do
    {
        cin >> cmd;
        if(cmd == "set")
        {
            try
            {
                cin >> date;
            } catch(InvalidDateException IDE)
            {
                cout << "Invalid date: " << IDE.input_date << endl;
                continue;
            }
            cout << date;
        }
        else if(cmd == "next_day")
        {
            if(date.day() == 0) continue;
            date.NextDay();
            cout << date;
        }
        else if(cmd == "next")
        {
            int num;
            cin >> num;
            if(date.day() == 0) continue;
            date.NextDay(num);
            cout << date;
        }
    } while(cmd != "quit");
    return 0;
}


