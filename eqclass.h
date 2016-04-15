#ifndef EQCLASS_H
#define EQCLASS_H

struct Column {
    unsigned long nodeId;  
    struct Column* next;
};

struct EqClass {
    struct Column down [20];   
};

void reduce (struct EqClass* eqClass, const unsigned long* nodeIds);

//void insertNodeAtDistance (struct EqClass* eqClass, const unsigned long nodeId, const int distanceFromTerm);

#endif