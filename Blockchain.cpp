#include<iostream>
#include<string.h>
#include<stdbool.h>
#include<fstream>
using namespace std;
//������
//�ڵ��е���Ϣʼ�ն���\0����ʾ����,�����Ǵ���Ļ���뻹�Ǵ��ļ�����
//�����������Ϣ��,ʼ�ձ�֤���ֵ������Ҫ���
struct LNode
{
    int Idnum;  //������ݵı��
    char * information; //������Ϣ
    int Checknum;   //У����
    LNode * next;
};

struct LInklist
{
    LNode * head;
    int sumnums;
};

void InitLink(LInklist *L); //��ʼ���������
void InsertData(LInklist *L,char *data);    //��������������Ϣ
bool judgeYes(LInklist*L);  //�ж���������Ƿ���Ч
void EditLink(LInklist *L,int num); //�����ض������Ϣ
void PrintLink(LInklist *L);    //��������е�����ȫ����ӡ����
void DeleteLink(LInklist * L);  //�ͷſռ�
void strcpylist(LInklist *L,int id,char *a,int cnum);   //���ļ��е�ֱ�Ӵ��ȥ
int main()
{
    fstream file;
    file.open("C:\\Codefield\\CODE_C\\CDesign\\Blockchain\\Blockr.txt",ios::in);
    if(!file)   //����Ƿ���ļ�cc
    {
        cout<<"���ļ�ʧ�ܡ�";
        exit(0);
    } 
    int id; //���
    int cnum;   //У��ֵ
    char * p=new char[128];   //��Ϣ
    LInklist * list=new LInklist;
    InitLink(list);
    while(!file.eof())  //�жϹ���Ƿ񵽴���β��,.eof�Ǵ����β
    {
        file>>id;
        file>>p;
        file>>cnum;
        if(file.fail()) //�ж��Ƿ��ȡʧ��
        {
            break;
        }
        strcpylist(list,id,p,cnum); //���ļ���ԭ֭ԭζ����������
    }
    file.close();

    int choice;
    while(1)
    {
        cout<<"\t\t������"<<endl;
        cout<<"1.չʾ��������"<<endl;
        cout<<"2.�����������Ƿ���Ч"<<endl;
        cout<<"3.�޸�ĳ���������"<<endl;
        cout<<"4.�������Ϣ"<<endl;
        cout<<"5.�������������ݴ浽�ļ���,�����˳�����"<<endl;
        cout<<endl;
        cout<<"ѡ��";
        cin>>choice;
        switch (choice)
        {
            case 1:
                PrintLink(list);
                break;
            case 2:
                if(judgeYes(list))
                {
                    cout<<"������Ч��"<<endl;
                    cout<<endl;
                }
                break;
            case 3:
                cout<<"����Ҫ�޸ĵ����ݵı�ţ�";
                int da;
                cin>>da;
                EditLink(list,da);
                break;
            case 4:
                cout<<"����Ϣ����(������������)��";
                cin>>p;
                InsertData(list,p); 
                break;
            case 5:
                file.open("C:\\Codefield\\CODE_C\\CDesign\\Blockchain\\Blockw.txt",ios::out);
                LNode * lp=list->head;
                while(lp)   //���޸�֮����������´����ļ���ȥ
                {
                    file<<lp->Idnum<<" "<<lp->information<<" "<<lp->Checknum<<endl;
                    lp=lp->next;
                }
                file.close();   //�ر��ļ�
                DeleteLink(list);   //�ͷ�����Ŀռ�
                exit(0);
        }
    }
}



void InitLink(LInklist *L) //��ʼ���������
{
    L->sumnums=0;
    L->head=0;
}

void InsertData(LInklist *L,char *data)    //����������������
{
    int length=0;   //�����Ϣ�ĳ���
    int sum=0;
    for(int i=0;;i++)   //���������Ϣ�ĳ���
    {
        if(data[i]==92&&data[i+1]==48)
        {
            length=i;   
            break;
        }
    }
    if(L->sumnums==0)
    {
        
        LNode *p=new LNode;
        p->Idnum=L->sumnums;    //���ֱ����������
        p->next=0;
        p->information=new char[length+1];  //�����ռ�
        strcpy(p->information,data);
        p->information[length]='\0';    //�����һλ��\0������
        //У��ֱֵ�ӿ��˹�����
        for(int i=0;i<length;i++)
        {
            sum=sum+int(p->information[i]); //�������Ϣת����Ϊ����
        }
        p->Checknum=sum%113;    //�洢У����
        L->head=p;  //��ͷָ�븳ֵ��Ϊ���
        L->sumnums++;
        return; 
    }
    LNode *p=new LNode;
    p->Idnum=L->sumnums;    //���ֱ���ǳ���
    p->next=NULL;
    p->information=new char[length+1];
    strcpy(p->information,data);    //��Ϣ
    p->information[length]='\0';    //�ý����һλ��\0��ʾ����
    for(int i=0;i<length;i++)
    {
        sum=sum+int(p->information[i]);
    }
    LNode * linshi=L->head;
    while(linshi->next) //�ҵ����һ��ָ��ڵ�
    {
        linshi=linshi->next;
    }
    p->Checknum=(linshi->Checknum+p->Idnum+sum)%113;    //У����ĳ������
    linshi->next=p; //��һ����ž���p
    linshi=p;
    L->sumnums++;   //���������1
    return;
}

bool judgeYes(LInklist*L) //�ж���������Ƿ���Ч
{
    LNode * p=L->head;
    int length;
    int sum=0;
    length=strlen(p->information);
    //����һ���ڵ�
    for(int i=0;i<length;i++)
    {
        sum=sum+p->information[i];
    }
    sum=sum%113;
    if(p->Checknum!=sum)
    {
        cout<<"��Ч�ڵ㣺"<<p->Idnum<<endl;
        cout<<endl;
        return false;
    }
    //���֮��Ľڵ�
    int old=p->Checknum;
    p=p->next;
    while(p)
    {
        int sum=0;
        length=strlen(p->information);
        for(int i=0;i<length;i++)
        {
            sum=sum+p->information[i];
        }
        sum=(sum+old+p->Idnum)%113;
        if(sum!=p->Checknum)
        {
            cout<<"��Ч�ڵ㣺"<<p->Idnum<<endl;
            cout<<endl;
            return false;
        }
        old=p->Checknum;    //�����У��ֵ��������������һ������ʹ��
        p=p->next;  //��Ҫ���������½����ƶ�
    }
    return true;    //ȫ���������,������Ч��
}

void EditLink(LInklist *L,int num) //�۸��ض������Ϣ
{
    int sum=0;
    int js=0;   
    LNode *p=L->head;
    LNode *pa;
    if(num!=0)  //�����׸���ĸʱ,����������ǰһ��λ��,����pa������
    {
        while(p)    //������ض����ҳ���
        {
            if(js==num-1)   //��ǰһ���ڵ��ҳ���;
            {
                pa=p;
            }
            if(js==num)
            {
                break;
            }
            p=p->next;
            js++;
        }
    }
    int a;
    cout<<"����Ϣ�ĳ���(����������־)��";
    cin>>a;
    char * chuan=new char[a+1];
    cout<<"����Ϣ(��������־)��";
    for(int i=0;i<a;i++)
    {
        cin>>chuan[i];
        sum=sum+int(chuan[i]);  //���������Ϣֵ��¼����
    }
    sum=sum-92-48;  //��Ҫ������\0��ռ��ascall����м�ȥ
    chuan[a-2]='\0';  //��β������

    strcpy(p->information,chuan);   //�ı�����Ϣ,����Ҫ�ı���Ӧ��У��ֵ
    int older=p->Checknum;    //�������У��ֵ��¼
    if(num==0)
    {
        p->Checknum=sum%113;    //���޸�λ������λ��ʱ
    }
    else    //�����׸�λ���޸�
    {
        p->Checknum=(pa->Checknum+p->Idnum+sum)%113;    //���¸���У��ֵ
    }
    int chazhi=p->Checknum-older;   //�޸�ǰ��Ĳ�ֵ,���ں����޸���Ӧ��У��ֵ
    p=p->next;
    //���º����У��ֵ
    while(p)        //��һ��ѭ����ס����һ��ѭ��
    {
        older=p->Checknum;  //ԭ�ȵ�У��ֵ 
        p->Checknum=(p->Checknum+chazhi)%113;   //���и���
        chazhi=p->Checknum-older;   //Ϊ��һ��������׼��
        p=p->next;
    }
    return ;    //�����еĶ����º�۸����
}

void PrintLink(LInklist *L)    //��������е�����ȫ����ӡ����
{
    LNode * p=L->head;
    while(p)
    {
        cout<<"��ţ�"<<p->Idnum<<endl;
        cout<<"��Ϣ��"<<p->information<<endl;
        cout<<"У���룺"<<p->Checknum<<endl;
        cout<<endl;
        p=p->next;
    }
}
void DeleteLink(LInklist * L)  //�ͷſռ�
{
    LNode *p;
    while(L->head->next)
    {
        p=L->head->next;
        delete L->head;
        L->head=p;
    }
    delete L->head; //�����пռ�����ͷ�
}

void strcpylist(LInklist *L,int id,char *a,int cnum)   //���ļ��е�ֱ�Ӵ��ȥ
{
    LNode *p=L->head;
    int length;
    for(int i=0;;i++)   //���������Ϣ�ĳ���
    {
        if(a[i]==92&&a[i+1]==48)
        {
            length=i;   
            break;
        }
    }
    if(L->sumnums==0)
    {
        LNode *pp=new LNode;
        pp->Idnum=0;
        pp->Checknum=cnum;
        pp->information=new char[length+1];
        strcpy(pp->information,a);
        pp->information[length]='\0';
        pp->next=0;
        L->head=pp;
        L->sumnums++;
        return ;
    }
    while(p->next)
    {
        p=p->next;
    }
    LNode *pp=new LNode;
    pp->Idnum=id;
    pp->Checknum=cnum;
    pp->information=new char[length+1]; //Ҫ��ʱ���ռ�
    strcpy(pp->information,a);  
    pp->information[length]='\0';
    pp->next=0;
    p->next=pp;
    p=pp;
    L->sumnums++;
    return;
}
