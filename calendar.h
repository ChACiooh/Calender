#ifndef CALENDER_H_INCLUDED
#define CALENDER_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>

#define YEAR_TO_DATE_1      365
#define YEAR_TO_DATE_2      366
#define MONTH_TO_DATE_1      31
#define MONTH_TO_DATE_2      30
#define YUN_BASE           1996
#define MONTH_MAX            12
#define YUN                   4
#define YUN2				100
#define YUN3				400

using namespace std;

class Date {

 public:
  Date();
  Date(int year, int month, int day);
  void NextDay(int n = 1);
  bool SetDate(int year, int month, int day);

  int year() const;
  int month() const;
  int day() const;

 private:
  // 윤년을 판단하여 주어진 연도에 해당하는 날짜 수(365 또는 366)를 리턴.
  static int GetDaysInYear(int year);
  // 해당 날짜가 해당 연도의 처음(1월 1일)부터 며칠째인지를 계산.
  static int ComputeDaysFromYearStart(int year, int month, int day);
  int year_, month_, day_;

};

struct InvalidDateException {

  string input_date;
  InvalidDateException(const string& str) : input_date(str) {}

};

// yyyy.mm.dd 형식으로 입출력.
// 사용자 입력 오류시 >> operator는 InvalidDateException을 발생할 수 있음.
void split(vector<string>& res, string base, char token);
ostream& operator<<(ostream& os, const Date& c);
istream& operator>>(istream& is, Date& c);

#endif // CALENDER_H_INCLUDED
