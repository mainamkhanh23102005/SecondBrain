#ifndef PASSFAILEXAM_H
#define PASSFAILEXAM_H
#include "PassFailActivity.h"

class PassFailExam : public PassFailActivity
{
private:
    int    numQuestions;
    double pointsEach;
    int    numMissed;
public:
    PassFailExam() : PassFailActivity()
        { numQuestions = 0; pointsEach = 0.0; numMissed = 0; }

    PassFailExam(int questions, int missed, double mps) : PassFailActivity(mps)
        { set(questions, missed); }

    void   set(int, int);                        // defined in .cpp
    double getNumQuestions() const { return numQuestions; }
    double getPointsEach()   const { return pointsEach; }
    int    getNumMissed()    const { return numMissed; }
};
#endif
