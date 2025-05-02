#ifndef UTILS_H
#define UTILS_H

void fillInc(int*, int);
void fillDec(int*, int);
void fillRand(int*, int);
int checkSum(const int*, int);
int runNumber(const int*, int);
int theoreticalMplusC(int);
int theoreticalMplusC_Bubble(int);
int measureBubble(void (*fill)(int*, int), int n);


#endif
