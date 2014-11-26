// grader_main.cc
#include <algorithm>
#include <iostream>
#include <vector>
#include "grader.h"

inline bool CompareStudent(const pair<string, double>& a, const pair<string, double>& b) {
  // 여기에 성적 내림차순으로 정렬되도록 대소비교문 작성.
  return a.second < b.second;
}

double GetNumberGrade(const string& str) {
  if (str == "A" || str == "P") return 4.0;
  if (str == "B") return 3.0;
  if (str == "C") return 2.0;
  if (str == "D") return 1.0;
  return 0.0;
}

int main() {
  SubjectPassFail subject1("Seminar", 1, 70);
  SubjectGrade subject2("C++", 6, 90, 80, 70, 60);
  SubjectGrade subject3("Calculus", 3, 80, 60, 40, 20);
  SubjectGrade subject4("Statistics", 2, 80, 70, 60, 50);
  const int total_credit = subject1.credit() + subject2.credit() + subject3.credit() + subject4.credit();
  string cmd;
  vector<pair<string, double> > student_grades;

  while (cmd != "quit") {
    cin >> cmd;
    if (cmd == "eval") {

      string name;
      int score1, score2, score3, score4;
      cin >> name >> score1 >> score2 >> score3 >> score4;
      string grade1 = subject1.GetGrade(score1);
      string grade2 = subject2.GetGrade(score2);
      string grade3 = subject3.GetGrade(score3);
      string grade4 = subject4.GetGrade(score4);

      cout << name << " " << grade1 << " " << grade2 << " " << grade3 << " " << grade4 << endl;

      double average_grade =
          (GetNumberGrade(grade1) * subject1.credit() +
           GetNumberGrade(grade2) * subject2.credit() +
           GetNumberGrade(grade3) * subject3.credit() +
           GetNumberGrade(grade4) * subject4.credit()) / total_credit;

      student_grades.push_back(make_pair(name, average_grade));
    }
  }

  sort(student_grades.begin(), student_grades.end(), CompareStudent);

  for (size_t i = 0; i < student_grades.size(); ++i) {
    // 여기에서 학점 출력이 소숫점 두자리만 되도록 cout의 멤버함수 호출
   cout << student_grades[i].first << " " << cout.precision(3) << student_grades[i].second << endl;
  }

  return 0;
}
