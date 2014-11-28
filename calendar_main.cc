#include "calendar.h"

int main()
{
    string cmd;
    Date A_Live;
    do
    {
        cin >> cmd;
        if(cmd == "set")
        {
            try
            {
                cin >> A_Live;
            } catch(InvalidDateException IDE)
            {
                cout << "Invalid date: " << IDE.input_date << endl;
                continue;
            }
            cout << A_Live;
        }
        else if(cmd == "next_day")
        {
            if(A_Live.day() == 0) continue;
            A_Live.NextDay();
            cout << A_Live;
        }
        else if(cmd == "next")
        {
            int num;
            cin >> num;
            if(A_Live.day() == 0) continue;
            A_Live.NextDay(num);
            cout << A_Live;
        }
    } while(cmd != "quit");
    return 0;
}


