#ifndef PASSFAILACTIVITY_H
#define PASSFAILACTIVITY_H
#include "GradedActivity.h"

class PassFailActivity : public GradedActivity
{
protected:
    double minPassingScore;             // minimum passing score
public:
    PassFailActivity() : GradedActivity()        { minPassingScore = 0.0; }
    PassFailActivity(double mps) : GradedActivity() { minPassingScore = mps; }
    void   setMinPassingScore(double mps)        { minPassingScore = mps; }
    double getMinPassingScore() const            { return minPassingScore; }

    virtual char getLetterGrade() const;         // overrides base
};
#endif
