#include <iostream>
#include <stdlib.h>
using namespace std;
#include "list.h"
#include "hydro.h"

FlowList::FlowList()
: headM(0)
{
}

FlowList::FlowList(const FlowList& source)
{
    copy(source);
}

FlowList& FlowList::operator =(const FlowList& rhs)
{
    if (this != &rhs) {
        destroy();
        copy(rhs);
    }
    return *this;
}

FlowList::~FlowList()
{
    destroy();
}

void FlowList::insert(const ListItem& itemW)
{
	
    Node *new_node = new Node;
    new_node->item = itemW;
    
    if (headM == 0 || itemW.year >= headM->item.year ) {
        new_node->next = headM;
        headM = new_node;
    }

    else {
        Node *before = headM;      
        Node *after = headM->next; 
        while(after != 0 && itemW.year < after->item.year) {
            before = after;
            after = after->next;
        }
        new_node->next = after;
        before->next = new_node;
    }
	
}


int FlowList::counter()
{
	int counter=1;
	if (headM!=0)
	travel=headM;
	while (travel->next!=0){
	travel=travel->next;
	counter++;
	}
	return counter;
	
}

Node* FlowList::gethead()const
{
	return headM;
}

void FlowList::sethead(Node* set)
{
	headM=set;
}

int FlowList::remove(const ListItem& itemW)
{
	int val=0;
	Node *doomed_node;
   if (headM == 0 || itemW.year > headM->item.year) 
	    doomed_node = 0;
   val=0; //could not remove
        
    if (itemW.year == headM->item.year) {
        doomed_node = headM;
        headM = headM->next;
		val=1; //succesful removal
    }

    else {
        Node *before = headM;
        Node *maybe = headM->next;
        while(maybe != 0 && itemW.year < maybe->item.year) {
            before = maybe;
            maybe = maybe->next;
        if (maybe->item.year==itemW.year){
        Node *nextone=maybe->next;
		before->next=nextone;
		val=1;
		}
    }
	}
	return val;
}


void FlowList::destroy()
{
     Node *remove = headM;
	while (headM!= NULL)
		{
			headM = headM->next;
			delete remove;
			remove = headM;
		}	
	delete remove;

}

void FlowList::copy(const FlowList& source)
{
    if (source.headM == 0) 
		headM = 0;
	else{
		headM = new Node;
		Node * s = source.headM;
		Node * copy = headM;
		while (s != 0){
			copy -> item = s -> item;
			if (s -> next !=0){
				copy -> next = new Node;
				copy = copy -> next;
				s = s -> next;
			}
			else {
				copy -> next= 0;
				s = 0;
			}
		}
	}
}