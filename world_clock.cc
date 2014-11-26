#include "world_clock.h"
#include <vector>
#include <cstdio>

/*** WorldClock ***/
WorldClock::WorldClock() : time_difference_(0) {}
WorldClock::WorldClock(int hour, int minute, int second):hour_(hour), minute_(minute), second_(second), time_difference_(0) {}
map<string, int> WorldClock::timezone_;

void WorldClock::Tick(int second)
{
    int value = hour_*3600 + minute_*60 + second_ + second;
    while(value < 0)    value += 24*3600;
    hour_ = value / 3600 % 24;
    value %= 3600;
    minute_ = value / 60;
    second_ = value % 60;
}

bool WorldClock::SetTime(int hour, int minute, int second)
{
    if(hour >= 24 || minute >= 60 || second >= 60)
    {
        return false;
    }
    hour_ = hour;
    minute_ = minute;
    second_ = second;
    return true;
}

bool WorldClock::LoadTimezoneFromFile(const string& file_path)
{
  ifstream input_file;
  input_file.open(file_path.c_str(), ifstream::in);
  string city;
  int time_diff;
  while(input_file.good())
  {
      try
      {
          input_file >> city >> time_diff;
          timezone_.insert(make_pair(city, time_diff));
      } catch(exception e)  { return false; }
  }
  input_file.close();
  return true;
}

void WorldClock::SaveTimezoneToFile(const string& file_path)
{
  ofstream output_file;
  output_file.open(file_path.c_str());
  for(map<string, int>::const_iterator it = timezone_.begin(); it != timezone_.end(); it++)
  {
      if(it -> first == "") continue;
      output_file << it->first << " " << it->second << endl;
  }
  output_file.close();
}

void WorldClock::AddTimezoneInfo(const string& city, int diff)
{
  map<string, int>::iterator it = timezone_.find(city);
  if(it != timezone_.end())
  {
      it -> second = diff;
      return;
  }
  timezone_.insert(make_pair(city, diff));
}

  // 잘못된 값 입력시 false 리턴하고 원래 시간은 바뀌지 않음.
bool WorldClock::SetTimezone(const string& timezone)
{
  if(timezone_.find(timezone) == timezone_.end()) return false;
  int hour = hour_ + timezone_[timezone] - time_difference_;
  while(hour < 0)   hour += 24;
  hour %= 24;
  SetTime(hour, minute_, second_);
  SetTimeDifference(timezone_[timezone]);
  return true;
}

int WorldClock::hour() const { return hour_; }
int WorldClock::minute() const { return minute_; }
int WorldClock::second() const { return second_; }


// hh:mm:ss 형식으로 입출력. 표준시가 아닌 경우 (+xx)/(-xx) 형식으로 시차를 표시.
ostream& operator<<(ostream& os, const WorldClock& c)
{
    int h, m, s, td;
    h = c.hour();
    m = c.minute();
    s = c.second();
    td = c.time_difference();
    os << h << ":" << m << ":" << s << " ";
    if(td)  os << "(" << (td > 0 ? "+" : "") << td << ")";
    return os;
}

// hh:mm:ss 로 입력받음.
// 사용자 입력 오류시 >> operator는 InvalidDateException을 발생할 수 있음.

void split(vector<string>& res, const string& base, const char& token)
{
   size_t i, j;
   for(i = j = 0; i < base.length(); i++)
   {
       if(base[i] == token)
       {
           string subs = base.substr(j, i-j);
           res.push_back(subs);
           j = i + 1;
       }
   }
   res.push_back(base.substr(j, i-j));
}

istream& operator>>(istream& is, WorldClock& c)
{
    string time;
    vector<string> time_series;
    is >> time;
    const char colon = ':';

    split(time_series, time, colon);
    if(time_series.size() != 3)
    {
        throw InvalidTimeException(time);
        return is;
    }
    int factor[3];

    for(size_t i = 0; i < time_series.size(); i++)
    {
        try
        {
            sscanf(time_series[i].c_str(), "%d", &factor[i]);
        } catch(exception e) {
            throw InvalidTimeException(time);
            return is;
        }
    }
    if(!c.SetTime(factor[0], factor[1], factor[2])) throw InvalidTimeException(time);
    return is;
}
