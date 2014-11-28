#include "calendar.h"
#include <cstdlib>

enum months { JANUARY = 1, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER };
const int common_month_date[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date() : year_(0), month_(0), day_(0) {}
Date::Date(int year, int month, int day) : year_(year), month_(month), day_(day) {}

void Date::NextDay(int n)
{
    // value setting
    int value = (year_)*YEAR_TO_DATE_1 + ((year_) / YUN) + 1 + day_ + n;
    if(GetDaysInYear(year_) == YEAR_TO_DATE_2) // 올해가 윤년
    {
        if(month_ <= FEBRUARY) // 2월을 못 넘겼으면
            value -= (YEAR_TO_DATE_2 - YEAR_TO_DATE_1);
    }
    for(int i=JANUARY; i<month_;i++) // 이번달 전달 까지의 일 수를 더한다.
        value += common_month_date[i];

    int temp = value;
    int i;
    for(i = 0; temp >= YEAR_TO_DATE_1; i++)
    {
        if(i%YUN == 0)
        {
            temp -= YEAR_TO_DATE_2;
            if(temp == -1)
            {
                year_ = i;
                month_ = DECEMBER;
                day_ = common_month_date[ DECEMBER ];
                return;
            }
        }
        else    temp -= YEAR_TO_DATE_1;
    }
    year_ = i;
    if(temp == 0) // 전 그 해의 일 수를 모두 소모했단 뜻.
    {
        year_ -= 1;
        month_ = DECEMBER;
        day_ = common_month_date[ DECEMBER ];
        return;
    }
    value = temp;

    // 1월부터 현재 value 값에서 해당 월의 최대 일수를 뺀다.
    // 그 값이 만약 0보다 작거나 같은 경우, 그 new_month가 month가 된다.
    int new_month;
    for(new_month = JANUARY; value - common_month_date[ new_month ] > 0 ; new_month++)
        value -= common_month_date[ new_month ];

    month_ = new_month;
    day_ = value;

} // void Date::NextDay(int n) end.

bool Date::SetDate(int year, int month, int day)
{
    if(year <= 0 || month > MONTH_MAX || month < 1) return false;
    else switch(month)
    {
        case JANUARY:       ////////
        case MARCH:         ////////
        case MAY:           /*31일*/
        case JULY:          /*까지*/
        case AUGUST:        ////////
        case OCTOBER:       ////////
        case DECEMBER:
            if(day > MONTH_TO_DATE_1)   return false;
            break;
        case FEBRUARY:      /* 2월*/
            if(year_ % YUN == 0 && day > 29)    return false;
            else if(year_ % YUN && day > 28)    return false;
            break;
        case APRIL:
        case JUNE:
        case SEPTEMBER:
        case NOVEMBER:
            if(day > MONTH_TO_DATE_2)   return false;
            break;
    } // switch(month) end.

    year_ = year;
    month_ = month;
    day_ = day;

    return true;
} // void Date::SetDate(int, int, int) end.

int Date::year() const { return year_; }
int Date::month() const { return month_; }
int Date::day() const { return day_; }

/*** private static member functions ***/
int Date::GetDaysInYear(int year)
{
    /*** 윤년을 판단하여 주어진 연도에 해당하는 날짜 수를 return. ***/
    if(year % YUN == 0) return YEAR_TO_DATE_2;
    else    return YEAR_TO_DATE_1;
}

int Date::ComputeDaysFromYearStart(int year, int month, int day)
{
    /*** 해당 날짜가 해당 연도의 처음(1월 1일)부터 며칠째인지를 계산. ***/
    if(year % YUN == 0 && month > FEBRUARY)
    {
        // 윤년일 때
        day += (YEAR_TO_DATE_2 - YEAR_TO_DATE_1);
    }
    for(int i=JANUARY; i<month; i++)
        day += common_month_date[i];

    return day;
}

void split(vector<string>& res, string base, char token)
{
    size_t i, j;
    for(i = 0, j = 0; i < base.length(); i++)
    {
        if(base[i] == token)
        {
            res.push_back(base.substr(j, i-j));
            j = i + 1;
        }
    }
    if(j < base.length())   res.push_back(base.substr(j, i-j));
}

// yyyy.mm.dd 형식으로 입출력.
// 사용자 입력 오류시 >> operator는 InvalidDateException을 발생할 수 있음.
ostream& operator<<(ostream& os, const Date& c)
{
    os << c.year() << "." << c.month() << "." << c.day() << endl;
    return os;
}

istream& operator>>(istream& is, Date& c)
{
    string nalJJa;
    vector<string> res;
    is >> nalJJa;
    InvalidDateException IDE(nalJJa);
    try
    {
        split(res, nalJJa, '.');
        if(c.SetDate(atoi(res[0].c_str()), atoi(res[1].c_str()), atoi(res[2].c_str())) == false)
            throw IDE;
    } catch(exception e) { throw IDE; }
    return is;
}
