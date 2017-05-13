#ifndef CLASS_H
#define CLASS_H

enum GROUP { COMMON, FAMILY, FRIEND, COLLEAGUE };

typedef struct LNode{
	char name[20];
	char pnum[15];
	char qnum[15];
	GROUP group;
}LNode, *PNode;

typedef struct List{
	PNode head;
}*PList;

class Address{
private:
	PList adlist;
public:
	Address();
	void Insert(PNode);
	void Delet(PNode);
	void Modify(PNode);
};

#endif //CLASS_H