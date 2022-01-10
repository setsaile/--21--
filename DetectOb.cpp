#include<iostream>
#include<math.h>
using namespace std;
//�ϰ���̽��

struct Obstacle //�ϰ�����Ϣ
{
    int bianhao;     //�ϰ���ı��     
    //int time;   //�����ϰ����ʱ��(��10sΪһ������)
    int count;  //��¼10s���ϰ�����ֵĴ���(�Ƿ���10s���������ϰ���)
    int firsttime;
    int secondtime;
    int thirdtime;
};

struct Sqlist
{
    Obstacle Obs[8];    //����ϰ����������õĺ�С,���ݲ�����Ҫ�����޸�
    int sumnum;
};

void Initial(Sqlist *L);    //��ʼ������ϰ����б�
void InsertData(Sqlist *L,int t,int dx,int dy,int sy,int Time);  //�����˳�������������
int Isexist(Sqlist*L,int t);   //�ж�����ϰ�����֮ǰ�ǲ����Ѿ����������
void Update(Sqlist *L,int Time); //��λ�����������
bool FindObs(Sqlist * L);
int main()
{
    int N;  //һ�������˶��ٵ���Ϣ
    cin>>N;
    int arcs[N+1];  //����������������
    Sqlist *L=new Sqlist;
    Initial(L);
    int tempnum;
    for(int i=1;i<=N;i++)
    {
        int l,t,dx,dy,sx,sy;
        cin>>tempnum;
        if(tempnum==0)
        {
            Update(L,i);    //ֱ�Ӷ����е�ֵ���и���
        }
        else
        {
            for(int j=1;j<=tempnum;j++)
            {
                cin>>l>>t>>dx>>dy>>sx>>sy;
                InsertData(L,t,dx,dy,sy,i);
            }
        }
        if(FindObs(L))
        {
            arcs[i]=1;
        }
        else
        {
            arcs[i]=0;
        }
    }
    for(int i=1;i<=N;i++)
    {
        cout<<arcs[i]<<" ";
    }
    delete L;
    return 0;
}

void Initial(Sqlist *L)    //��ʼ������ϰ����б�
{
    L->sumnum=0;
    for(int i=0;i<8;i++)    //���ϰ����������г�ʼ��Ϊ0
    {
        L->Obs[i].count=0;
        L->Obs[i].firsttime=-1;
        L->Obs[i].secondtime=-1;
        L->Obs[i].secondtime=-1;
    }
}

void InsertData(Sqlist *L,int t,int dx,int dy,int sy,int Time)  //�����˳�������������
{
    long long distance=abs(dx*dx)+abs(dy*dy);   
    long long ndis=5000*5000;
    if(distance>=ndis||abs(sy)<=300)    //�����������С��50��������ٶȴ���3m/s�����ϰ���
    {
        Update(L,Time);
        return ;
    }

    int js=Isexist(L,t);
    if(js==-1)  //��֮ǰû�����ֵ
    {
        L->Obs[L->sumnum].bianhao=t;
        L->Obs[L->sumnum].firsttime=Time;
        L->sumnum++;        
    }
    else    //֮ǰ���������ŵ�
    {
        if(L->Obs[js].count==1) //����ֵ���и���
        {   
            L->Obs[js].firsttime=L->Obs[js].secondtime;
            L->Obs[js].secondtime=L->Obs[js].thirdtime;
            L->Obs[js].thirdtime=Time;
        }
        else if(L->Obs[js].count==0&&L->Obs[js].secondtime!=-1) //������ڵ�����λ��
        {
            L->Obs[js].count=1;
            L->Obs[js].thirdtime=Time;
        }
        else if(L->Obs[js].firsttime!=-1&&L->Obs[js].secondtime==-1) //������ڵڶ���λ��
        {
            L->Obs[js].secondtime=Time;
        }
    }
}

int Isexist(Sqlist*L,int t)   //�ж�����ϰ�����֮ǰ�ǲ����Ѿ����������
{
    for(int i=0;i<L->sumnum;i++)    //����оͷ�����Ӧ�ı��
    {
        if(L->Obs[i].bianhao==t)
        {
            return i;
        }
    }
    return (-1);    //���û�þ�Ҫ���´���
}

void Update(Sqlist *L,int Time) //��λ�����������
{
    for(int i=0;i<L->sumnum;i++)
    {
        if(L->Obs[i].count==1)
        {
            if(Time-L->Obs[i].firsttime>9)  //������9��Ҫ����Ϊ���ϰ���
            {
                L->Obs[i].count=0;
                L->Obs[i].firsttime=L->Obs[i].secondtime;
                L->Obs[i].secondtime=L->Obs[i].thirdtime;
                L->Obs[i].thirdtime=-1;
            }
        }
        else if(L->Obs[i].secondtime!=-1&&L->Obs[i].count==0)   //ֻ��ǰ2���м�¼
        {
            if(Time-L->Obs[i].firsttime>9)  //������9��Ҫ������Ӧ����
            {
                L->Obs[i].firsttime=L->Obs[i].secondtime;
                L->Obs[i].secondtime=-1;
            }
        }
        else if(L->Obs[i].firsttime!=-1&&L->Obs[i].secondtime==-1)  //ֻ�е�һ��λ���м�¼
        {
            if(Time-L->Obs[i].firsttime>9)  //������9��Ҫ������Ӧ����
            {
                L->Obs[i].firsttime=-1;
            }
        }
    }
}
bool FindObs(Sqlist * L)
{
    for(int i=0;i<L->sumnum;i++)
    {
        if(L->Obs[i].count==1)
        {
            return true;
        }
    }
    return false;
}
