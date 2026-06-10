#include "PassFailExam.h"

void PassFailExam::set(int questions, int missed)
{
    numQuestions = questions;
    numMissed    = missed;
    pointsEach   = 100.0 / numQuestions;
    double numericScore = 100.0 - (missed * pointsEach);
    setScore(numericScore);              // inherited mutator
}
