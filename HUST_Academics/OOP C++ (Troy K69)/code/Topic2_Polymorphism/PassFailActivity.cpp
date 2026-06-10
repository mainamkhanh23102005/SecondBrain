#include "PassFailActivity.h"

char PassFailActivity::getLetterGrade() const
{
    return (score >= minPassingScore) ? 'P' : 'F';
}
