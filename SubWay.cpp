#include<iostream>
using namespace std;
//����վ�޽�
//�㷨˼�룺�ҳ�ȫ����·��,ͳ�Ƴ����м�·���ĺ�ʱ,�����ǽ��бȽ�,ֵ��С��Ϊ����޽�ʱ�䡣
struct Arcnode  //�����޽�ʱ��Ľṹ��
{
    int endstation;
    int daytime;
    Arcnode *next;
};
struct Vexnode
{
    int startstation;
    Arcnode *first;
};
struct Graph
{
    Vexnode * vex;
    int vexnum,arcnum;  //��¼�������ͱ���
};
void Desory(Graph *G,int x);  //�ͷſռ�
void FindMintime(Graph *G,int sta,int over,int d,int *path,int &time,int *vist); //�ҵ����������޽�ʱ��

int main()
{
    int n,m;
    cin>>n>>m;
    Graph *G=new Graph;
    G->vexnum=n;    //��Ŧ�������ڶ������
    G->arcnum=m;    //����������ڱ���
    G->vex=new Vexnode[n+1];
    for(int i=1;i<=n;i++)   //�������߽�����Ӧ�ĳ�ʼ��
    {
        G->vex[i].first=NULL;
    }
    int start,end,daytime;
    Arcnode *p;
    for(int i=0;i<m;i++)    //����ͼ��ģ��
    {
        cin>>start>>end>>daytime;
        
        p=new Arcnode;
        p->endstation=end;
        p->daytime=daytime;

        p->next=G->vex[start].first;    //��p���뵽����ڽӱ���ȥ
        G->vex[start].first=p;
    }
    int Time=1000;
    int Path[128];
    int visit[n+1];
    for(int i=1;i<=n;i++)   //visit�Ǹ��������ʾ��û�����ʹ�
    {
        visit[i]=0;
    }
    FindMintime(G,1,n,0,Path,Time,visit);
    cout<<Time;
    Desory(G,n);    //�ͷ���Ӧ�Ŀռ�
    return 0;
}

void Desory(Graph *G,int x)  //�ͷſռ�
{
    Arcnode*p;
    Arcnode*q;
    for(int i=1;i<=G->vexnum;i++)   //�����²�ɾ�������ϲ���ܱ�֤�ռ䱻�ͷ����
    {
        p=G->vex[i].first;   //p��ֵΪ�ڽӱ�ĵ�һ���ڵ�
        //���ܵ�һ���ڵ���ǿ�ָ��,�Ͳ��ܽ�����һ��,������쳣����,��ֹ�ն�!!!
        if(p==NULL) //����ǹ���������ɾ��,ֱ��������һ��ѭ��!!!
        {
            continue;
        }
        while(p->next)  //���ڽӱ�Ľڵ�ռ�һһ�ͷ�
        {
            q=p->next;   //qΪp����һ���ڵ�ռ�
            delete p;   //��p����ռ�ɾ��
            p=q;    //p�ֵ�����һ���ռ�
        }
        delete p;   //���������ɾ�����һ���ռ�
    } 
    delete G->vex;
    delete G;   //�����ɾ�������ռ�
}

//����Ѱ��ȫ����·��������Сʩ������
void FindMintime(Graph *G,int sta,int over,int d,int *path,int &time,int *vist) //�ҵ����������޽�ʱ��
{
    Arcnode *p;
    path[d]=sta;    //����ǰλ�÷Ž�ȥ
    vist[sta]=1;
    if(sta==over)
    {
        int linshitime=0;
        Arcnode *p2;
        for(int i=0;i<=d;i++)
        {
            p2=G->vex[path[i]].first;
            while(p2)
            {
                if(p2->endstation==path[i+1])   //�����������һ������ͬʱ���ҵ���ȷ��ʱ��
                {
                    if(linshitime<p2->daytime)
                    {
                        linshitime=p2->daytime; //�ҵ��ʱ��,��Ϊ����·�Ĺ���
                        break;
                    }
                }
                p2=p2->next;
            }           
        }
        if(time>linshitime) //����С���ڴ���time��
        {
            time=linshitime;
        }
    }
    else
    {
        p=G->vex[sta].first;
        while(p)
        {
            if(vist[p->endstation]==0)  //����㻹û������
            {
                FindMintime(G,p->endstation,over,d+1,path,time,vist);
                vist[p->endstation]=0;  //�ָ����ʱ��,��Ϊ�Ѿ��ƶ�����һ�������
            }
            p=p->next;
        }
    }
}
