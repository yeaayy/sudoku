#include "group_generator.hpp"

#include "constraint_no_duplicate.hpp"

void GroupGenerator::apply(ConstraintNoDuplicate *dst)
{
    int tmp[groupSize];
    for(int i = 0; i < groupCount; i++) {
        getGroup(tmp, i);
        for(int j = 0; j < groupSize; j++) {
            for(int k = 0; k < groupSize; k++) {
                if(j == k) continue;
                dst[tmp[j]].addNeigbour(tmp[k]);
            }
        }
    }
}
