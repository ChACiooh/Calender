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
    return score >= cutA_ ? "A" :
             score >= cutB_ ? "B" :
             score >= cutC_ ? "C" :
             score >= cutD_ ? "D" : "F";
}
