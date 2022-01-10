#include<iostream>
#include<vector>
#include<fstream>
#include<string.h>
#include <cstring>
#include<string>
using namespace std;
//�Ͼ�������·ͼ
//����������վ�㣬����ת���������ٵĳ˳�·��
//����������վ�㣬��������վ�����ٵĳ˳�·��

struct Lnodestation
{
    int Busnumber;  //�������վ��Ĺ�����·
    int index;  //��ʱ���վ��ı��
    Lnodestation*Nextstation;
};

struct Graph
{
    int Totalstation;   //����վ̨��������
    vector<Lnodestation> Busroute;  //һ���������е�վ��
    vector<Lnodestation> Vexnode;   //����վ����ڽӱ�
    vector<Lnodestation> ZdVexnode; //�ܹ�ֱ����ڽӱ�
    vector<string> StationName; //վ̨������
    vector<vector<int> > Busnums;   //���Ծ������վ�Ĺ�����·
};

struct BFSCount //BFS����ʱ�õ���������¼��ֵ
{
    int index;
    int pre_index;
};

int returnBusnum(string name);  //���ַ���ת��������
int Findappear(Graph G,string name);    //������ǰ�Ƿ���ֹ�,û�з���-1
bool judgepreN(Graph G,int str1,int str2);    //�ж�֮ǰ�Ƿ�����
bool judgezdpreN(Graph G,int str1,int str2);    //�ж�֮ǰ�Ƿ�ֱ��
void Shortesrway(Graph G,int str1,int str2);    //���·��
void Shortesthuancheng(Graph G,int str1,int str2);  //��̻��˳�

int main()
{
    Graph G;    //�������ͼ     
    G.Totalstation=0;
    fstream file;
    file.open("C:\\Codefield\\CODE_C\\CDesign\\NjBusPath\\Njbus.txt",ios::in);
    if(!file)
    {
        cout<<"�ļ���ʧ��";
        exit(0);
    }
    vector<int> tempvec;    //��ʱ����
    while(1)
    {      
        int Busnum; //��һ·���Ĺ�����·
        int flag=0; //����һ��վ��ʱ����Ҫ������վ��������
        string num;
        file>>num;
        if(file.eof())
        {
            break;  //������β������ѭ��
        }
        char Kongge=' ';
        Busnum=returnBusnum(num);
        Lnodestation *L=new Lnodestation;
        L->Busnumber=Busnum;    //L�Ǽ�¼����������·����Ϣ
        L->Nextstation=0;
        G.Busroute.push_back(*L);  
        while(Kongge==' ')  //���м�Ŀո��ȫ������
        {
            file.get(Kongge);
        }
        while(1)    //��ʼ����������������
        {
            string tempname;    //��¼���վ������
            string pretempname; //��¼���վ���ǰһ��վ������
            while(Kongge!=','&&Kongge!='\n')
            {
                tempname=tempname+Kongge;   //�����վ������һ��һ������
                file.get(Kongge);
            }
            int location=Findappear(G,tempname);
            if(location==-1)
            {
                
                G.StationName.push_back(tempname);
                Lnodestation *l1=new Lnodestation;
                l1->Nextstation=NULL;
                l1->index=G.Totalstation;           
                G.Vexnode.push_back(*l1);
                G.ZdVexnode.push_back(*l1);
                G.Busnums.push_back(tempvec);
                G.Busnums[G.Totalstation].push_back(Busnum);
                G.Totalstation++;
                delete l1;
            }
            else
            {
                G.Busnums[location].push_back(location);
            }
            Lnodestation*l2=new Lnodestation;
            l2->index=location;
            l2->Busnumber=Busnum;
            l2->Nextstation=L->Nextstation;
            L->Nextstation=l2;
            L=L->Nextstation;
            delete l2;
            if(flag!=0)
            {
                int bianhao1=Findappear(G,pretempname);
                int bianhao2=Findappear(G,tempname);
                if(judgepreN(G,bianhao1,bianhao2)==0)
                {
                    Lnodestation*l3=new Lnodestation;
                    l3->Busnumber=Busnum;
                    l3->index=bianhao2;
                    l3->Nextstation=G.Vexnode[bianhao1].Nextstation;
                    G.Vexnode[bianhao1].Nextstation=l3;

                    Lnodestation*l4=new Lnodestation;
                    l4->Busnumber=Busnum;
                    l4->index=bianhao1;
                    l4->Nextstation=G.Vexnode[bianhao2].Nextstation;
                    G.Vexnode[bianhao2].Nextstation=l4;
                    delete l3;
                    delete l4;
                }
            }
            flag++;
            pretempname=tempname;
            
            if(Kongge=='\n')
            {
                break;
            }
            else
            {
                file.get(Kongge);
            }            
        }
    }
    file.close();
    for(int i=0;i<G.Busroute.size();i++)
    {
        Lnodestation *l5=G.Busroute[i].Nextstation;
        Lnodestation *l6;
        while(l5->Nextstation)
        {
            l6=l5->Nextstation;
            while(l6)
            {
                if(judgezdpreN(G,l5->index,l6->index)==0)
                {
                    Lnodestation * temp1=new Lnodestation;
                    temp1->index=l6->index;
                    temp1->Nextstation=G.ZdVexnode[l5->index].Nextstation;
                    G.ZdVexnode[l5->index].Nextstation=temp1;

                    Lnodestation * temp2=new Lnodestation;
                    temp2->index=l5->index;
                    temp2->Nextstation=G.ZdVexnode[l6->index].Nextstation;
                    G.ZdVexnode[l6->index].Nextstation=temp2;
                    
                    delete temp1;
                    delete temp2;
                    
                }
                l6=l6->Nextstation;
            }
            l5=l5->Nextstation;
        }
        delete l5;
        delete l6;
    }
    char ch;
    cout<<"           ��ӭʹ���Ͼ�������·��ѯϵͳ"<<endl;
    while(1)
    {
        cout<<"��������㣺";
        string Name1;
        cin>>Name1;
        int judge1;
        judge1=Findappear(G,Name1);
        while(judge1==-1)
        {
        cout<<"�������վ��,�����䣺";
        cin>>Name1;
        judge1=Findappear(G,Name1);
        }
        cout<<"�������յ㣺";
        cin>>Name1;
        int judge2;
        judge2=Findappear(G,Name1);
        while(judge2==-1)
        {
            cout<<"�������վ��,�����䣺";
            cin>>Name1;
            judge2=Findappear(G,Name1);
        }
        cout<<"��̻���·��(�м��¼����վ):";
        Shortesthuancheng(G,judge1,judge2);
        cout<<endl;
        cout<<"��̹���վ·��:";
        Shortesrway(G,judge1,judge2);
        cout<<endl;
        cout<<endl;
        cout<<"�Ƿ�Ҫ��������:(y or n)";
        cin>>ch;
        if(ch=='n')
        {
            break;
        }
    }
}

int returnBusnum(string name)  //���ַ���ת��������
{
    int sumnum=0;
    for(int i=0;name[i]>=48&&name[i]<=57;i++)
    {
        sumnum=sumnum+int(name[i])-48;
        sumnum=sumnum*10;
    }
    sumnum=sumnum/10;
    return sumnum;
}


int Findappear(Graph G,string name)    //������ǰ�Ƿ���ֹ�,û�з���-1
{
    for(int i=0;i<G.Totalstation;i++)
    {
        if(G.StationName[i]==name)
        {
            return i;   //�ҵ�������Ӧ�ı��
        }
    }
    return (-1);    //û���ҵ�����-1
}

bool judgepreN(Graph G,int str1,int str2)    //�ж�֮ǰ�Ƿ�����
{
    Lnodestation *p=G.Vexnode[str1].Nextstation;
    while(p)
    {
        if(p->index==str2)
        {
            return 1;
        }
        p=p->Nextstation;
    }
    return 0;
}
bool judgezdpreN(Graph G,int str1,int str2)    //�ж�֮ǰ�Ƿ�ֱ��
{
    Lnodestation* p;
    p = G.Vexnode[str1].Nextstation;
    while (p)
    {
        if (p->index == str2)
            return 1;
        p = p->Nextstation;
    }
    return 0;
}

void Shortesrway(Graph G,int str1,int str2)
{
    if(str1==str2)
    {
        cout<<"���ʱ�������յ�һ��";
        return;
    }
    vector<BFSCount> lnode;
    BFSCount l1,l2;
    Lnodestation *p;
    int base=0,flag=0;
    int vex[10007]={0};
    BFSCount head;
    head.pre_index=-1;
    head.index=str1;
    lnode.push_back(head);
    while(base!=lnode.size()&&!flag)
    {
        l1=lnode[base];
        base++;
        p=G.Vexnode[l1.index].Nextstation;
        flag=0;
        while(p&&!flag)
        {
            if(!vex[p->index])
            {
                l2.pre_index=base-1;
                l2.index=p->index;
                if(p->index==str2)
                {
                    flag=1;
                }
                lnode.push_back(l2);
            }
            p=p->Nextstation;
        }
    }
    if(base==lnode.size())
    {
        cout<<"δ�ҵ�����·��"<<endl;
        return;
    }
    else
    {
        vector<int>pr;
        vector<int>::iterator i;
        while(l2.pre_index!=-1)
        {
            pr.push_back(l2.index);
            l2=lnode[l2.pre_index];
        }
        pr.push_back(l2.index);
        i=pr.end()-1;
        cout<<"��㣺"<<G.StationName[pr.back()];
        for(int j=1;j<pr.size();j++)
        {
            cout<<"->"<<G.StationName[*(i-j)];
            if((j-1)%8==0&&j!=1)
            {
                cout<<endl;
            }
        }
        cout<<endl;
    }
}

void Shortesthuancheng(Graph G,int str1,int str2)   //��̻���
{
    if(str1==str2)
    {
        cout<<"���ʱ�������յ�һ��";
        return;
    }
    vector<BFSCount> lnode;
    BFSCount l1,l2;
    Lnodestation *p;
    int base=0,flag=0;
    int vex[10007]={0};
    BFSCount head;
    head.pre_index=-1;
    head.index=str1;
    lnode.push_back(head);
    while(base!=lnode.size()&&!flag)
    {
        l1=lnode[base];
        base++;
        p=G.ZdVexnode[l1.index].Nextstation;
        flag=0;
        while(p&&!flag)
        {
            if(!vex[p->index])
            {
                l2.pre_index=base-1;
                l2.index=p->index;
                if(p->index==str2)
                {
                    flag=1;
                }
                lnode.push_back(l2);
            }
            p=p->Nextstation;
        }
    }
    if(base==lnode.size())
    {
        cout<<"δ�ҵ�����·��"<<endl;
        return;
    }
    else
    {
        vector<int>pr;
        vector<int>::iterator i;
        while(l2.pre_index!=-1)
        {
            pr.push_back(l2.index);
            l2=lnode[l2.pre_index];
        }
        pr.push_back(l2.index);
        i=pr.end()-1;
        cout<<"��㣺"<<G.StationName[pr.back()];
        for(int j=1;j<pr.size();j++)
        {
            cout<<"->"<<G.StationName[*(i-j)];
            if((j-1)%8==0&&j!=1)
            {
                cout<<endl;
            }
        }
        cout<<endl;
    }
}
