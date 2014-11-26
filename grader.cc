#include "grader.h"

SubjectPassFail::SubjectPassFail(const string& name, int credit, int pass_score) : Subject(name, credit), pass_score_(pass_score) {}
SubjectPassFail::~SubjectPassFail() {}
string SubjectPassFail::GetGrade(int score) const
{
    return score >= pass_score_ ? "P" : "F";
}

SubjectGrade::SubjectGrade(const string& name, int credit, int cutA, int cutB, int cutC, int cutD)
: Subject(name, credit), cutA_(cutA), cutB_(cutB), cutC_(cutC), cutD_(cutD) {}
SubjectGrade::~SubjectGrade() {}
string SubjectGrade::GetGrade(int score) const
{
    return score >= 4 ? "A" :
             score >= 3 ? "B" :
             score >= 2 ? "C" :
             score >= 1 ? "D" : "F";
}
