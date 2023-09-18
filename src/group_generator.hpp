#pragma once

class ConstraintNoDuplicate;

class GroupGenerator
{
public:
    void apply(ConstraintNoDuplicate *dst);
    GroupGenerator(int groupCount = 9, int groupSize = 9);
    virtual void getGroup(int *dst, int index) = 0;

    const int groupCount;
    const int groupSize;
};

#define MakeGeneratorClass(__NAME__, __GROUP_COUNT__, __GROUP_SIZE__, __VALUE__) \
class __NAME__:public GroupGenerator{public:__NAME__():GroupGenerator(__GROUP_COUNT__, __GROUP_SIZE__){}void getGroup(int *dst, int y){for(int x=0;x<9;x++){dst[x]=__VALUE__;}}}

