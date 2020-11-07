#include <iostream>
#include <stdlib.h>
#include <fstream>
#include<iomanip>
using namespace std;
#include "list.h"
#include "hydro.h"
#include "list.cpp"


int main(void) 
{
	 FlowList x;
	int records;
	displayHeader();
	records=readData(x);
	int quit =0;
	int av=average(x);
	int med=median(x,records);
	 
	 while(1)
	 {
		switch(menu())
		{
			case 1: 
				display(x, av, med);
				pressEnter(); // call pressEnter;
				break;
			case 2:
				records = addData (x); // call addData function
				pressEnter(); // call pressEnter;
				break;
			case 3:
				 saveData (x); // call saveData function;
				 pressEnter(); // call pressEnter;
				break;
			case 4:
				records = removeData(x); // call removeData
				pressEnter();// call presenter;
				break;
			case 5:
				cout << "\nProgram terminated!\n\n";
				quit = 1;
				break;
			default:
				cout << "\nNot a valid input.\n";
				pressEnter();// pressEnter();
		}
	if(quit == 1) 
		break;
	}
}

void displayHeader(){
	
	cout << "\nProgram: Flow Studies, Fall 2018."; 
	cout << "\n Version: 1.0";
	cout <<"\n Lab Section: B01";
	cout <<"\n Produced by: Wajeeha Bushra";
	pressEnter();
}

int readData(FlowList & x)
{
	ifstream object;
	object.open("flow.txt");
	
	if (! object)
	{
		cerr<< "Error: cannot open the file <<filename<< endl";
		exit(1);
	}
	
	while (!object.eof())
	{
		ListItem items;
		int yr;
		double flw;
		
		object >> yr >> flw;
		
		items.year= yr;
		items.flow = flw;
		x.insert(items);
	}
	
	return (x.counter());
}

int menu()
{
	int choice; 
	cout<<"Please select on the following operations"<<endl;
	cout<<"		1. Display flow list, average and median"<<endl;
	cout<<"		2. Add data"<<endl;
	cout<<"		3. Save data into the file"<<endl;
	cout<<"		4. Remove data"<<endl;
	cout<<"		5. Quit"<<endl;
	cout<<"		Enter your choice (1, 2, 3, 4, or 5):";
	cin >> choice;
	return choice; 
}

void display(const FlowList &x, int av, int med){
	cout<<"Year          Flow (in billions of cubic meters)"<<endl;
	Node* m=x.gethead();
	while(m)
	{
		cout<< m->item.year <<"		"<< m->item.flow;
		cout<<endl;
		m=m->next;
	}
	cout<<"The annual average of the flow is: "<<av<<" millions cubic meter"<<endl;
	cout<< endl;
	cout<<"The median flow is: "<<med<<" millions cubic meter"<<endl;
}

int addData(FlowList &x)
{
	int yr;
	double flw;
	int val=x.counter();
	cout<<endl<<"Please enter a year:";
	cin>>yr;
	cout<<endl;
	cout<<"Please enter a flow:";
	cin>>flw;
	cout<<endl;
	
	Node* m=x.gethead();
	
	if ( yr <=0 || flw <0)
	{
		cout<<"Invalid year or flow value entered."<<endl;
		return val;
	}
	
	while(m!=0)
	{
		if(m->item.year==yr)
		{
			cout<<"Error: duplicate data."<<endl;
			return val;
		}
		m=m->next;
	}

	ListItem item;
	item.year= yr;
	item.flow = flw;
	x.insert(item);
	cout<<"New record inserted successfully."<<endl;
	return val;
}

int removeData(FlowList &x)
{
	int rec=x.counter();
	int year;
	ListItem item;
	int value;
	cout<<endl<<"Please enter the year that you want to remove: ";
	cin >> year;
	item.year=year;
	
	if (item.year <=0)
	{
		cout<<"Invalid year entered."<<endl;
		return rec;
	}
	value=x.remove(item);
if (value==0){
	cout<<endl<<"Error: No such a data."<<endl<<endl;
	return rec;
}
else {
	cout << endl<<"Record was successfully removed." <<endl;
	rec=rec-1;
}
	return rec;	
}

double average(const FlowList &x)
{
	Node* m=x.gethead();
	if(m==0)
		return 0;
	double counter=0, sum=0;
	while(m)
	{
		sum+=m->item.flow;
		counter++;
		m=m->next;
	}
	return sum/counter;
}

double median(const FlowList &x, const int records)
{
	Node* m=x.gethead();
	if(m==0)
		return 0;
	
	if(records%2==0)
	{
		for(int i=0;i<((records/2)-1);i++)
			m=m->next;
		return (m->item.flow + m->next->item.flow)/2;
	}
	else
	{
		for(int i=0;i<(records/2);i++)
			m=m->next;
		return m->item.flow;
	}
}

void saveData (const FlowList & x)
{
	ofstream outobject;
	outobject.open("flow.txt", std::ofstream::trunc);
	
	if (! outobject)
	{
		cerr<< "Error: cannot open the file" << endl;
		exit(1);
	}
	
	Node* data=x.gethead();
	
	while (data!=NULL)
	{
		outobject<< setw(4) << data->item.year << setw(12) << data->item.flow;
		if (data->next !=NULL)
			outobject<<endl; 
		data=data->next;
	}
	cout<<endl<<"Data is saved into the file."<<endl;
	outobject.close();
}

void pressEnter()
{
	cout <<"\n<<<Press Enter to Continue>>>";
	cin.get();
}