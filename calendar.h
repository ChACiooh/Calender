#ifndef CALENDER_H_INCLUDED
#define CALENDER_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>

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
  // ������ �Ǵ��Ͽ� �־��� ������ �ش��ϴ� ��¥ ��(365 �Ǵ� 366)�� ����.
  static int GetDaysInYear(int year);
  // �ش� ��¥�� �ش� ������ ó��(1�� 1��)���� ��ĥ°������ ���.
  static int ComputeDaysFromYearStart(int year, int month, int day);
  int year_, month_, day_;

};


struct InvalidDateException {

  string input_date;
  InvalidDateException(const string& str) : input_date(str) {}

};

// yyyy.mm.dd �������� �����.
// ����� �Է� ������ >> operator�� InvalidDateException�� �߻��� �� ����.
void split(vector<string>& res, string base, char token);
ostream& operator<<(ostream& os, const Date& c);
istream& operator>>(istream& is, Date& c);


#endif // CALENDER_H_INCLUDED