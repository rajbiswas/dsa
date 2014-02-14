#include<QtCore/QFile>
#include<QtCore/QTextStream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include<conio.h>
#include<string.h>
#include<fstream>
#include<ctype.h>
#include<math.h>
#include<time.h>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::out_refresh(QString a,int o)
{
    if(o==1)
        ui->textBrowser->setText(a);
    else if(o==2)
        ui->textBrowser_2->setText(a);
    else if(o==3)
        ui->textBrowser_3->setText(a);
    else if(o==4)
        ui->textBrowser_4->setText(a);
}
void MainWindow::out(QString a,int o)
{
    if(o==1)
        ui->textBrowser->insertPlainText(a);
    else if(o==2)
        ui->textBrowser_2->insertPlainText(a);
    else if(o==3)
        ui->textBrowser_3->insertPlainText(a);
    else if(o==4)
        ui->textBrowser_4->insertPlainText(a);
}
void MainWindow::outln(QString a,int o)
{
    if(o==1)
        ui->textBrowser->append(a);
    else if(o==2)
        ui->textBrowser_2->append(a);
    else if(o==3)
        ui->textBrowser_3->append(a);
    else if(o==4)
        ui->textBrowser_4->append(a);
}
int Table_size=600,Table_size1=600,Table_size2=1000,Table_size3=1000;                                          //Size of hash table equal to the no. of words in text file
typedef struct DICT_WORD
{
    int key;                                                  //Contains hashing index
    int word_count=0;                                         //No. of repetitions of a word
    int position[200];                                        //Position of word in text file
    char value[20]="";
    DICT_WORD *next;                                          //Address for linking other words with same hash index
}dict_word;
dict_word *Trav_node,*Trav_node1,*Trav_node2,*Trav_node3;                                         //Used for traversing through words
dict_word *word=new dict_word [Table_size];                   //Main hash table
dict_word *word1=new dict_word [Table_size1];
dict_word *word2=new dict_word [Table_size2];
dict_word *word3=new dict_word [Table_size3];
int search_flag=0,search_flag1=0,search_flag2=0,search_flag3;
int imp=0,imp1=0,imp2=0,imp3=0;
int word_pos=0,word_pos1=0,word_pos2=0,word_pos3=0;
int Track_pos=0,Track_pos1=0,Track_pos2=0,Track_pos3=0;                                              //Keeps track of the position of the word being inserted
QString qst,line,line1,line2,line3;
int MainWindow::hash_index1(char *s)
{
    int hash_val;
    double k=0.0,l,d,intpart;
    for(int i=0;s[i]!=NULL;i++)
    {
        k=k+s[i];                                  //Summing the ASCII value of all letters
    }
    float a;
    l=strlen(s);
    d=modf((k/l),&intpart);
    hash_val=Table_size1*d;
    return hash_val;
}
int MainWindow::hash_index(char *s)
{
 int hash_val=0;                                                //Stores hashing index
 for(int i=0;s[i]!=NULL;i++)
 {
     hash_val=hash_val+s[i];                                  //Summing the ASCII value of all letters
 }
 return hash_val%Table_size;                                  //Returning the hashing index
}
void MainWindow::insertHash(char *s,int pos)                             //Inserting words  to the hash table
{
    int hash_val=hash_index(s);
    if(strcmp(word[hash_val].value,"")==0)                    //Condition for inserting first word at an index
    {
        strcpy((word[hash_val].value),s);
        word[hash_val].position[word[hash_val].word_count]=pos;
        word[hash_val].word_count++;
        word[hash_val].next=NULL;
    }
    else                                                      //Condition for inserting subsequent words at an index
    {
        Trav_node=&word[hash_val];
        while(Trav_node!=NULL)
        {
            if(strcmp(Trav_node->value,s)==0)                 //Inserting a previously inserted word
            {
                Trav_node->position[Trav_node->word_count]=pos;
                Trav_node->word_count++;
                search_flag=1;
                break;
            }
            Trav_node=Trav_node->next;
        }
        Trav_node=&word[hash_val];
        if(search_flag==0)                                    //Creating new word in the same index
        {
            dict_word *temp=new dict_word;
            while(Trav_node!=NULL)
            {
                if(Trav_node->next==NULL)
                    break;
                Trav_node=Trav_node->next;                   //Traversing till the last word
            }
            Trav_node->next=temp;
            Trav_node=Trav_node->next;                       //Initiating the new word
            strcpy(Trav_node->value,s);
            Trav_node->position[Trav_node->word_count]=pos;
            Trav_node->word_count++;
            Trav_node->next=NULL;
        }
    }
    word_pos++;
    search_flag=0;                                           //Resetting search flag for reusage
}
void MainWindow::insertHash1(char *s,int pos)                             //Inserting words  to the hash table
{
    int hash_val=hash_index1(s);
    if(strcmp(word1[hash_val].value,"")==0)                    //Condition for inserting first word at an index
    {
        strcpy((word1[hash_val].value),s);
        word1[hash_val].position[word1[hash_val].word_count]=pos;
        word1[hash_val].word_count++;
        word1[hash_val].next=NULL;
    }
    else                                                      //Condition for inserting subsequent words at an index
    {
        Trav_node1=&word1[hash_val];
        while(Trav_node1!=NULL)
        {
            if(strcmp(Trav_node1->value,s)==0)                 //Inserting a previously inserted word
            {
                Trav_node1->position[Trav_node1->word_count]=pos;
                Trav_node1->word_count++;
                search_flag1=1;
                break;
            }
            Trav_node1=Trav_node1->next;
        }
        Trav_node1=&word1[hash_val];
        if(search_flag1 ==0)                                    //Creating new word in the same index
        {
            dict_word *temp=new dict_word;
            while(Trav_node1!=NULL)
            {
                if(Trav_node1->next==NULL)
                    break;
                Trav_node1=Trav_node1->next;                   //Traversing till the last word
            }
            Trav_node1->next=temp;
            Trav_node1=Trav_node1->next;                       //Initiating the new word
            strcpy(Trav_node1->value,s);
            Trav_node1->position[Trav_node1->word_count]=pos;
            Trav_node1->word_count++;
            Trav_node1->next=NULL;
        }
    }
    word_pos1++;
    search_flag1=0;                                           //Resetting search flag for reusage
}
void MainWindow::insertHash2(char *s,int pos)                             //Inserting words  to the hash table
{
    int hash_val=hash_index1(s);
    if(strcmp(word2[hash_val].value,"")==0)                    //Condition for inserting first word at an index
    {
        strcpy((word2[hash_val].value),s);
        word2[hash_val].position[word2[hash_val].word_count]=pos;
        word2[hash_val].word_count++;
        word2[hash_val].next=NULL;
    }
    else                                                      //Condition for inserting subsequent words at an index
    {
        Trav_node2=&word2[hash_val];
        while(Trav_node2!=NULL)
        {
            if(strcmp(Trav_node2->value,s)==0)                 //Inserting a previously inserted word
            {
                Trav_node2->position[Trav_node2->word_count]=pos;
                Trav_node2->word_count++;
                search_flag2=1;
                break;
            }
            else if(strcmp(Trav_node2->value,"")==0)
            {
                strcpy((word2[hash_val].value),s);
                word2[hash_val].position[word2[hash_val].word_count]=pos;
                word2[hash_val].word_count++;
                word2[hash_val].next=NULL;
                break;
            }
            else
            {
                hash_val++;
                if(hash_val==1000)
                    hash_val=0;
                Trav_node2=&word2[hash_val];
            }
        }
    }
    word_pos2++;
    search_flag2=0;                                           //Resetting search flag for reusage
}
void MainWindow::insertHash3(char *s,int pos)                             //Inserting words  to the hash table
{
    int hash_val=hash_index1(s),par=1;
    if(strcmp(word3[hash_val].value,"")==0)                    //Condition for inserting first word at an index
    {
        strcpy((word3[hash_val].value),s);
        word3[hash_val].position[word3[hash_val].word_count]=pos;
        word3[hash_val].word_count++;
        word3[hash_val].next=NULL;
    }
    else                                                      //Condition for inserting subsequent words at an index
    {
        Trav_node3=&word3[hash_val];
        while(Trav_node3!=NULL)
        {
            if(strcmp(Trav_node3->value,s)==0)                 //Inserting a previously inserted word
            {
                Trav_node3->position[Trav_node3->word_count]=pos;
                Trav_node3->word_count++;
                search_flag3=1;
                break;
            }
            else if(strcmp(Trav_node3->value,"")==0)
            {
                strcpy((word3[hash_val].value),s);
                word3[hash_val].position[word3[hash_val].word_count]=pos;
                word3[hash_val].word_count++;
                word3[hash_val].next=NULL;
                break;
            }
            else
            {
                hash_val=hash_val+(par*par);
                par++;
                if(hash_val>=1000)
                    hash_val=hash_val%1000;
                Trav_node3=&word3[hash_val];
            }
        }
    }
    word_pos3++;
    search_flag3=0;                                           //Resetting search flag for reusage
}
void MainWindow::disp()                                                  //Displaying words as stored in hash table
{
    for(int i=0;i<Table_size;i++)
    {
        if(strcmp(word[i].value,"")!=0)                      //If the node is not empty then entering and displaying
        {
            Trav_node=&word[i];
            while(Trav_node!=NULL)
            {
                qst=QString::fromStdString(Trav_node->value);
                out(qst,1);
                out("->",1);
                Trav_node=Trav_node->next;
            }
            outln("",1);
        }
        else                                                 //If node is empty then continuing to next node
            continue;
    }
}
void MainWindow::disp1()                                                  //Displaying words as stored in hash table
{
    for(int i=0;i<Table_size1;i++)
    {
        if(strcmp(word1[i].value,"")!=0)                      //If the node is not empty then entering and displaying
        {
            Trav_node1=&word1[i];
            while(Trav_node1!=NULL)
            {
                qst=QString::fromStdString(Trav_node1->value);
                out(qst,2);
                out("->",2);
                Trav_node1=Trav_node1->next;
            }
            outln("",2);
        }
        else                                                 //If node is empty then continuing to next node
            continue;
    }
}
void MainWindow::disp2()                                                  //Displaying words as stored in hash table
{
    for(int i=0;i<Table_size2;i++)
    {
        if(strcmp(word2[i].value,"")!=0)                      //If the node is not empty then entering and displaying
        {
            Trav_node2=&word2[i];
            qst=QString::fromStdString(Trav_node2->value);
            outln(qst,3);
        }
        else                                                 //If node is empty then continuing to next node
        {
            outln("",3);
            continue;
        }
    }
}
void MainWindow::disp3()                                                  //Displaying words as stored in hash table
{
    for(int i=0;i<Table_size3;i++)
    {
        if(strcmp(word3[i].value,"")!=0)                      //If the node is not empty then entering and displaying
        {
            Trav_node3=&word3[i];
            qst=QString::fromStdString(Trav_node3->value);
            outln(qst,4);
        }
        else                                                 //If node is empty then continuing to next node
        {
            outln("",4);
            continue;
        }
    }
}
void MainWindow::disp_order()
{
    mark:
    while(Track_pos!=word_pos)
    {
        for(int i=0;i<Table_size;i++)
        {
            Trav_node=&word[i];
            while(Trav_node!=NULL)
            {
                for(int j=0;j<Trav_node->word_count;j++)
                {
                    if(Trav_node->position[j]==Track_pos+1)
                    {
                        qst=QString::fromStdString(Trav_node->value);
                        out(qst,1);
                        out(" ",1);
                        Track_pos++;
                        goto mark;
                    }
                }
                Trav_node=Trav_node->next;
            }
        }
    }
    Track_pos=0;
}
void MainWindow::disp_order1()
{
    mark:
    while(Track_pos1!=word_pos)
    {
        for(int i=0;i<Table_size;i++)
        {
            Trav_node1=&word1[i];
            while(Trav_node1!=NULL)
            {
                for(int j=0;j<Trav_node1->word_count;j++)
                {
                    if(Trav_node1->position[j]==Track_pos1+1)
                    {
                        qst=QString::fromStdString(Trav_node1->value);
                        out(qst,2);
                        out(" ",2);
                        Track_pos1++;
                        goto mark;
                    }
                }
                Trav_node1=Trav_node1->next;
            }
        }
    }
    Track_pos1=0;
}
void MainWindow::search_word(char *s)                                      //Searching a word in hash table
{
    int hash_val=hash_index(s);                                 //Obtaining hash value of string
    Trav_node=&word[hash_val];
    while(Trav_node!=NULL)
    {
        if(strcmp(Trav_node->value,s)==0)                       //Checking if the same string exists
        {
            out(s,1);
            out(" has been found at positions:",1);
            for(int i=0;i<Trav_node->word_count;i++)            //Printing the positions at which the string exists
            {
                qst=QString::number(Trav_node->position[i]);
                out(qst,1);
                out(" ",1);
            }
            search_flag=1;
            break;
        }
        else
        {
            Trav_node=Trav_node->next;
        }
    }
    if(search_flag==0)
    {
        out_refresh("Word not found!!",1);
    }
    search_flag=0;                                              //Resetting search flag for reusage
}
void MainWindow::search_word1(char *s)                                      //Searching a word in hash table
{
    int hash_val=hash_index1(s);                                 //Obtaining hash value of string
    Trav_node1=&word1[hash_val];
    while(Trav_node1!=NULL)
    {
        if(strcmp(Trav_node1->value,s)==0)                       //Checking if the same string exists
        {
            out(s,2);
            out(" has been found at positions:",2);
            for(int i=0;i<Trav_node1->word_count;i++)            //Printing the positions at which the string exists
            {
                qst=QString::number(Trav_node1->position[i]);
                out(qst,2);
                out(" ",2);
            }
            search_flag1=1;
            break;
        }
        else
        {
            Trav_node1=Trav_node1->next;
        }
    }
    if(search_flag1==0)
    {
        out_refresh("Word not found!!",2);
    }
    search_flag1=0;                                              //Resetting search flag for reusage
}
void MainWindow::search_word2(char *s)                                      //Searching a word in hash table
{
    int hash_val=hash_index1(s);                                 //Obtaining hash value of string
    Trav_node2=&word2[hash_val];
    while(Trav_node2!=NULL)
    {
        if(strcmp(Trav_node2->value,s)==0)                       //Checking if the same string exists
        {
            out(s,3);
            out(" has been found at positions:",3);
            for(int i=0;i<Trav_node2->word_count;i++)            //Printing the positions at which the string exists
            {
                qst=QString::number(Trav_node2->position[i]);
                out(qst,3);
                out(" ",3);
            }
            search_flag2=1;
            break;
        }
        else if(strcmp(Trav_node2->value,"")==0)
        {
            out_refresh("Word not found!!",3);
            break;
        }
        else
        {
            hash_val++;
            if(hash_val==1000)
                hash_val=0;
            Trav_node2=&word2[hash_val];
        }
    }
    search_flag2=0;                                              //Resetting search flag for reusage
}
void MainWindow::search_word3(char *s)                                      //Searching a word in hash table
{
    int hash_val=hash_index1(s),par=1;                                 //Obtaining hash value of string
    Trav_node3=&word3[hash_val];
    while(Trav_node3!=NULL)
    {
        if(strcmp(Trav_node3->value,s)==0)                       //Checking if the same string exists
        {
            out(s,4);
            out(" has been found at positions:",4);
            for(int i=0;i<Trav_node3->word_count;i++)            //Printing the positions at which the string exists
            {
                qst=QString::number(Trav_node3->position[i]);
                out(qst,4);
                out(" ",4);
            }
            search_flag3=1;
            break;
        }
        else if(strcmp(Trav_node3->value,"")==0)
        {
            out_refresh("Word not found!!",4);
            break;
        }
        else
        {
            hash_val=hash_val+(par*par);
            par++;
            if(hash_val>=1000)
                hash_val=hash_val%1000;
            Trav_node3=&word3[hash_val];
        }
    }
    search_flag3=0;                                              //Resetting search flag for reusage
}
void MainWindow::extract_file()
{
    QFile myFile(":/hey.txt");
    myFile.open(QIODevice::ReadOnly);
    QTextStream textStream(&myFile);
    line=textStream.readAll();
    QString q,p="";
    char *t;
    myFile.close();
    ui->textBrowser->setPlainText(line);
    int i=0,b=line.length();
    while(i<b)
    {
        if(line[i]==' '||line[i]=='.'||line[i]==','||line[i]=='?'||line[i]=='!'||line[i]==';'||line[i]==':'||line[i]=='&')
        {
                QByteArray ba = q.toLatin1();
                t=ba.data();
                insertHash(t,word_pos+1);
                q="";
                i++;
                continue;
        }
        else
        {
            q.append(line[i]);
            i++;
        }
    }
}
void MainWindow::extract_file1()
{
    QFile myFile1(":/hey.txt");
    myFile1.open(QIODevice::ReadOnly);
    QTextStream textStream(&myFile1);
    line1=textStream.readAll();
    QString q,p="";
    char *t;
    myFile1.close();
    ui->textBrowser_2->setPlainText(line1);
    int i=0,b=line1.length();
    while(i<b)
    {
        if(line1[i]==' '||line1[i]=='.'||line1[i]==','||line1[i]=='?'||line1[i]=='!'||line1[i]==';'||line1[i]==':'||line1[i]=='&')
        {
                QByteArray ba = q.toLatin1();
                t=ba.data();
                insertHash1(t,word_pos1+1);
                q="";
                i++;
                continue;
        }
        else
        {
            q.append(line1[i]);
            i++;
        }
    }
}
void MainWindow::extract_file2()
{
    QFile myFile2(":/hey.txt");
    myFile2.open(QIODevice::ReadOnly);
    QTextStream textStream(&myFile2);
    line2=textStream.readAll();
    QString q,p="";
    char *t;
    myFile2.close();
    ui->textBrowser_3->setPlainText(line2);
    int i=0,b=line2.length();
    while(i<b)
    {
        if(line2[i]==' '||line2[i]=='.'||line2[i]==','||line2[i]=='?'||line2[i]=='!'||line2[i]==';'||line2[i]==':'||line2[i]=='&')
        {
                QByteArray ba = q.toLatin1();
                t=ba.data();
                insertHash2(t,word_pos2+1);
                q="";
                i++;
                continue;
        }
        else
        {
            q.append(line2[i]);
            i++;
        }
    }
}
void MainWindow::extract_file3()
{
    QFile myFile3(":/hey.txt");
    myFile3.open(QIODevice::ReadOnly);
    QTextStream textStream(&myFile3);
    line3=textStream.readAll();
    QString q,p="";
    char *t;
    myFile3.close();
    ui->textBrowser_4->setPlainText(line3);
    int i=0,b=line3.length();
    while(i<b)
    {
        if(line3[i]==' '||line3[i]=='.'||line3[i]==','||line3[i]=='?'||line3[i]=='!'||line3[i]==';'||line3[i]==':'||line3[i]=='&')
        {
                QByteArray ba = q.toLatin1();
                t=ba.data();
                insertHash3(t,word_pos3+1);
                q="";
                i++;
                continue;
        }
        else
        {
            q.append(line3[i]);
            i++;
        }
    }
}
void MainWindow::on_search_clicked()
{
    QString qst1;
    clock_t t1,t2;
    ui->textBrowser->setText("");
    char *a;
    QString qst;
    qst=ui->lineEdit->text();
    QByteArray ba = qst.toLatin1();
    a=ba.data();
    t1=clock();
    MainWindow::search_word(a);
    t2=clock();
    float dif=((float)t2-(float)t1);
    dif=dif/CLOCKS_PER_SEC;
    qst1=QString::number(dif,'g',5);
    ui->textBrowser_5->append("Search:");
    ui->textBrowser_5->insertPlainText(qst1);
    ui->lineEdit->clear();
}

void MainWindow::on_hash_disp_clicked()
{
    ui->textBrowser->setText("");
    disp();
}

void MainWindow::on_file_disp_clicked()
{
    ui->textBrowser->setText("");
    disp_order();
}

void MainWindow::on_exit_clicked()
{
    QString qst;
    clock_t t1,t2;
    if(imp==0)
    {
        imp=1;
        ui->textBrowser->setText("");
        t1=clock();
        extract_file();
        t2=clock();
        float dif=((float)t2-(float)t1);
        dif=dif/CLOCKS_PER_SEC;
        qst=QString::number(dif,'g',5);
        ui->textBrowser_5->append("Import:");
        ui->textBrowser_5->insertPlainText(qst);
    }
    else
    {
        ui->textBrowser->setText(line);
    }
}

void MainWindow::on_search1_clicked()
{
    QString qst1;
    clock_t t1,t2;
    ui->textBrowser_2->setText("");
    char *a;
    QString qst;
    qst=ui->lineEdit_2->text();
    QByteArray ba = qst.toLatin1();
    a=ba.data();
    t1=clock();
    MainWindow::search_word1(a);
    t2=clock();
    float dif=((float)t2-(float)t1);
    dif=dif/CLOCKS_PER_SEC;
    qst1=QString::number(dif,'g',5);
    ui->textBrowser_5->append("Search:");
    ui->textBrowser_5->insertPlainText(qst1);
    ui->lineEdit_2->clear();
}

void MainWindow::on_hash_disp1_clicked()
{
    ui->textBrowser_2->setText("");
    disp1();
}

void MainWindow::on_file_disp_2_clicked()
{
    ui->textBrowser_2->setText("");
    disp_order1();
}

void MainWindow::on_pushButton_4_clicked()
{
    QString qst;
    clock_t t1,t2;
    if(imp1==0)
    {
        imp1=1;
        ui->textBrowser_2->setText("");
        t1=clock();
        extract_file1();
        t2=clock();
        float dif=((float)t2-(float)t1);
        dif=dif/1000;
        qst=QString::number(dif,'g',5);
        ui->textBrowser_5->append("Import 1:");
        ui->textBrowser_5->insertPlainText(qst);
    }
    else
    {
        ui->textBrowser_2->setText(line1);
    }
}

void MainWindow::on_import2_clicked()
{
    QString qst;
    clock_t t1,t2;
    if(imp2==0)
    {
        imp2=1;
        ui->textBrowser_3->setText("");
        t1=clock();
        extract_file2();
        t2=clock();
        float dif=((float)t2-(float)t1);
        dif=dif/1000;
        qst=QString::number(dif,'g',5);
        ui->textBrowser_5->append("Import 2:");
        ui->textBrowser_5->insertPlainText(qst);
    }
    else
    {
        ui->textBrowser_3->setText(line2);
    }
}

void MainWindow::on_search2_clicked()
{
    QString qst1;
    clock_t t1,t2;
    ui->textBrowser_3->setText("");
    char *a;
    QString qst;
    qst=ui->lineEdit_3->text();
    QByteArray ba = qst.toLatin1();
    a=ba.data();
    t1=clock();
    MainWindow::search_word2(a);
    t2=clock();
    float dif=((float)t2-(float)t1);
    dif=dif/CLOCKS_PER_SEC;
    qst1=QString::number(dif,'g',5);
    ui->textBrowser_5->append("Search 2:");
    ui->textBrowser_5->insertPlainText(qst1);
    ui->lineEdit_3->clear();
}

void MainWindow::on_hash_disp2_clicked()
{
    ui->textBrowser_3->setText("");
    disp2();
}

void MainWindow::on_search3_clicked()
{
    QString qst1;
    clock_t t1,t2;
    ui->textBrowser_4->setText("");
    char *a;
    QString qst;
    qst=ui->lineEdit_4->text();
    QByteArray ba = qst.toLatin1();
    a=ba.data();
    t1=clock();
    MainWindow::search_word3(a);
    t2=clock();
    float dif=((float)t2-(float)t1);
    dif=dif/CLOCKS_PER_SEC;
    qst1=QString::number(dif,'g',5);
    ui->textBrowser_5->append("Search 3:");
    ui->textBrowser_5->insertPlainText(qst1);
    ui->lineEdit_4->clear();
}

void MainWindow::on_hash_disp3_clicked()
{
    ui->textBrowser_4->setText("");
    disp3();
}

void MainWindow::on_import3_clicked()
{
    if(imp3==0)
    {
        QString qst;
        clock_t t1,t2;
        imp3=1;
        ui->textBrowser_4->setText("");
        t1=clock();
        extract_file3();
        t2=clock();
        float dif=((float)t2-(float)t1);
        dif=dif/1000;
        qst=QString::number(dif,'g',5);
        ui->textBrowser_5->append("Import 3:");
        ui->textBrowser_5->insertPlainText(qst);
    }
    else
    {
        ui->textBrowser_4->setText(line3);
    }
}
