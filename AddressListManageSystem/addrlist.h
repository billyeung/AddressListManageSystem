#ifndef ADDRLIST_H
#define ADDRLIST_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <string>
#include <QFile>
#include <QTextStream>
#include <QSettings>

using namespace std;

enum TYPE{commom, family, friends, colleague};

typedef struct LNode{
    string group;
    string name;
    string pnum;
    string qnum;
    string email;
    string address;
    struct LNode *next;
}LNode,*PNode;

typedef struct List{
    PNode head;
    int size;
}List,*PList;

class Addrlist
{
private:
    PList list;
    QString path;
    void Writefile(QString, List*);

public:
    Addrlist();
    ~Addrlist();
    QString Getpath();
    PList Getlist();
    void Clearlist();
    bool Readfile(QString);
    void Exportfile(QString);
    void Savefile();
    void Insert(string,string,string,string,string,string);
    void Delete(int);
    void Modify(int,string,string,string,string,string,string);
};

extern Addrlist adlist;
bool isDigitStr(QString);

#endif // ADDRLIST_H
