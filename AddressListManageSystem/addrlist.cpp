#include "addrlist.h"

Addrlist adlist;//建立链表

Addrlist::Addrlist()
{
    list = new(List);
    list->size = 0;
    path = "";
    list->head = new(LNode);
    list->head->next = NULL;
}

Addrlist::~Addrlist()
{
    Clearlist();
    delete(list->head);
    delete(list);
}

string emptostr(string str) //使空字符串和"no"互相转换
{
    if(str == "\0") str = "no";
    return str;
}

void Addrlist::Insert(string name, string pnum, string qnum, string email, string address, string group) //向链表插入新结点
{
    PNode newptr = new(LNode);
    if(!newptr) return;
    newptr->next = NULL;
    newptr->name = emptostr(name);
    newptr->pnum = emptostr(pnum);
    newptr->qnum = emptostr(qnum);
    newptr->email = emptostr(email);
    newptr->address = emptostr(address);
    newptr->group = group;
    newptr->next = list->head->next;
    list->head->next = newptr;
    list->size++;
}

PList Addrlist::Getlist() //获取链表
{
    return list;
}

void Addrlist::Clearlist() //清空链表
{
    PNode lastptr=list->head->next, temp=list->head->next;
    while(lastptr)
    {
        temp=temp->next;
        delete(lastptr);
        lastptr=temp;
    }
    list->size = 0;
}

bool Addrlist::Readfile(QString filepath) //读取文件
{
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    QTextStream in(&file);
    QString str;
    PNode lastptr = list->head, newptr = NULL;
    if(in.atEnd()) {
        file.close();
        return false;
    }
    Clearlist();
    while(!in.atEnd())
    {
        newptr = new(LNode);
        if(newptr == NULL) return false;
        newptr->next = NULL;
        in >> str;
        if(str == "no") {
            str = in.readLine();
            continue;
        }
        newptr->name = str.toStdString();
        in >> str;
        if(!isDigitStr(str)) {
            str = in.readLine();
            continue;
        }
        newptr->pnum = str.toStdString();
        in >> str;
        if(!isDigitStr(str)) {
            str = in.readLine();
            continue;
        }
        newptr->qnum = str.toStdString();
        in >> str;
        newptr->email = str.toStdString();
        in >> str;
        newptr->address = str.toStdString();
        in >> str;
        if(str!="de"&&str!="fa"&&str!="fr"&&str!="co") str = "de";
        newptr->group = str.toStdString();
        lastptr->next = newptr;
        list->size++;
        lastptr = newptr;
    }
    file.close();
    path = filepath;
    QSettings settings("config.ini", QSettings::IniFormat);
    settings.beginGroup("Path");settings.setValue("filepath", filepath);
    settings.endGroup();
    return true;
}

void Addrlist::Writefile(QString filepath, List *list) //将数据写入文件
{
    QFile file(filepath);
    file.open( QIODevice::WriteOnly | QIODevice::Text );
    QTextStream out(&file);
    PNode lastptr = list->head->next;
    if(lastptr)
    {
        out << QString::fromStdString(lastptr->name) << ' ' << QString::fromStdString(lastptr->pnum) <<  ' ' << QString::fromStdString(lastptr->qnum)
            << ' ' << QString::fromStdString(lastptr->email) << ' ' << QString::fromStdString(lastptr->address) << ' ' << QString::fromStdString(lastptr->group);
        lastptr = lastptr->next;
    }
    while(lastptr){
        out << endl << QString::fromStdString(lastptr->name) << ' ' << QString::fromStdString(lastptr->pnum) <<  ' ' << QString::fromStdString(lastptr->qnum)
            << ' ' << QString::fromStdString(lastptr->email) << ' ' << QString::fromStdString(lastptr->address) << ' ' << QString::fromStdString(lastptr->group);
        lastptr = lastptr->next;
    }
    file.close();
}

void Addrlist::Exportfile(QString filepath) //导出通讯录
{
    Writefile(filepath, list);
    path = filepath;
    QSettings settings("config.ini", QSettings::IniFormat);
    settings.beginGroup("Path");
    settings.setValue("filepath", filepath);
    settings.endGroup();
}

void Addrlist::Savefile() //保存通讯录
{
    Writefile(path, list);
}

void Addrlist::Delete(int k) //删除结点
{
    PNode lastptr = list->head, temp;
    for(int i=0; i<k; i++) lastptr = lastptr->next;
    temp = lastptr->next;
    lastptr->next = temp->next;
    delete(temp);
    list->size--;
}

void Addrlist::Modify(int k, string name, string pnum, string qnum, string email, string address, string group) //修改结点内容
{
    PNode lastptr = list->head->next;
    for(int i=0; i<k; i++) lastptr = lastptr->next;
    lastptr->name = emptostr(name);
    lastptr->pnum = emptostr(pnum);
    lastptr->qnum = emptostr(qnum);
    lastptr->email = emptostr(email);
    lastptr->address = emptostr(address);
    lastptr->group = group;
}

QString Addrlist::Getpath(){ //获取当前文件路径
    return path;
}

bool isDigitStr(QString src) //判断字符串是否为纯数字
{
    if(!src.isEmpty()){
        QByteArray ba = src.toLatin1();
        const char *s = ba.data();
        while(*s && *s>='0' && *s<='9') s++;
        if (*s) return false;
        else return true;
    }
    else return true;
}
