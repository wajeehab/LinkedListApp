#ifndef LIST_H
#define LIST_H

struct ListItem {
	int year;
	double flow;
};

struct Node {
	ListItem item;
	Node *next;
};

class FlowList {
public:
	FlowList(); 
	FlowList(const FlowList& source);
	FlowList& operator =(const FlowList& rhs);
	~FlowList();
	
	Node* gethead()const;
	void sethead(Node* set);
	int counter();
	void insert(const ListItem& itemA);
	int remove(const ListItem& itemW);
  
private:
	Node *headM;
	Node *travel;
	void destroy(); 
	void copy(const FlowList& source); 
};
#endif
