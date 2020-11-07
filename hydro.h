#ifndef HYDRO_H
#define HYDRO_H


void displayHeader();
int readData(FlowList & x);
int menu();
void display(const FlowList &x, int av, int med);
int addData(FlowList &x);
int removeData(FlowList &x);
double average(const FlowList &x);
double median(const FlowList &x, const int items);
void saveData (const FlowList & x);
void pressEnter();

#endif