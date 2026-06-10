#ifndef GRADEDACTIVITY_H
#define GRADEDACTIVITY_H

class GradedActivity
{
protected:
    double score;                       // numeric score
public:
    GradedActivity()            { score = 0.0; }
    GradedActivity(double s)    { score = s; }
    void   setScore(double s)   { score = s; }
    double getScore() const     { return score; }

    virtual char getLetterGrade() const;   // virtual => enables polymorphism
    virtual ~GradedActivity() {}           // virtual destructor (safe base-pointer delete)
};
#endif
