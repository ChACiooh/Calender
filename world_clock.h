#ifndef WORLD_CLOCK_H_INCLUDED
#define WORLD_CLOCK_H_INCLUDED

#include <map>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class WorldClock {
 public:
  WorldClock();
  WorldClock(int hour, int minute, int second);

  void Tick(int seconds = 1);
  // �߸��� �� �Է½� false �����ϰ� ���� �ð��� �ٲ��� ����.
  bool SetTime(int hour, int minute, int second);
  void SetTimeDifference(int time) { time_difference_ = time; }

  static bool LoadTimezoneFromFile(const string& file_path);
  static void SaveTimezoneToFile(const string& file_path);
  static void AddTimezoneInfo(const string& city, int diff);

  // �߸��� �� �Է½� false �����ϰ� ���� �ð��� �ٲ��� ����.
  bool SetTimezone(const string& timezone);

  int hour() const;
  int minute() const;
  int second() const;
  int time_difference() const { return time_difference_; }

 private:
  // ���⿡ �ð� ���� ��� ���� ����. (GMT �ð��� ���)
  int hour_;
  int minute_;
  int second_;
  // Timezone ���� ������ �Ʒ� ������ ����. ������ �ð� �����θ� ���.
  int time_difference_;
  static map<string, int> timezone_;
};

//map<string, int> WorldClock::timezone_;

struct InvalidTimeException {
  string input_time;
  InvalidTimeException(const string& str) : input_time(str) {}
};

// hh:mm:ss �������� �����. ǥ�ؽð� �ƴ� ��� (+xx)/(-xx) �������� ������ ǥ��.
ostream& operator<<(ostream& os, const WorldClock& c);

// hh:mm:ss �� �Է¹���.
// ����� �Է� ������ >> operator�� InvalidDateException�� �߻��� �� ����.
istream& operator>>(istream& is, WorldClock& c);

#endif // WORLD_CLOCK_H_INCLUDED
