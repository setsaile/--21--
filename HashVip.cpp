#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstring>
#include<string.h>
using namespace std;
//��ϣ��ʵ�ַɻ�vip�ͻ��ķ���
//���ó���������(ȡ1510��ģ����)1600�����ݱض��������ͻ

struct Passenger1   //������ʽ�������ͻ
{
    char Idcard[20];    //�ͻ������֤����
    char Name[6];   //�ͻ�������
    char Flightid[6];   //�������Ϣ
    char year[6]; //���ʱ��������
    char month[4];
    char day[4];
    char Distance[6];    //�˴η��е�����ʱ��
    int judge;  //�ж����λ���ǲ����Ѿ��г˿�,���ڲ鿴�Ƿ�ʹ�ó�ͻ�㷨
    Passenger1 *next;
};
struct HashTable1
{
    Passenger1 *elem;   //�洢��̬�Ļ���ַ
    int count;  //��ʱ�����˶��ٸ�����
    int tablesize;  //��ϣ����ܳ���
};  

struct K_Passenger  //���ÿ���ʽ�������ͻ
{
    char Idcard[20];    //�ͻ������֤����
    char Name[6];   //�ͻ�������
    char Flightid[6];   //�������Ϣ
    char year[6]; //���ʱ��������
    char month[4];
    char day[4];
    char Distance[6];    //�˴η��е�����ʱ��
    int judge;  //�ж����λ���ǲ����Ѿ��г˿�,���ڲ鿴�Ƿ�ʹ�ó�ͻ�㷨
};
struct K_HashTable
{
    K_Passenger *elem;   //�洢��̬�Ļ���ַ
    int count;  //��ʱ�����˶��ٸ�����
    int tablesize;  //��ϣ����ܳ���
};  

 

int InsertData(HashTable1 *H,int&sum,K_HashTable*KH);  //�������ϣ����ȡ��������
bool collision(HashTable1 *&H,int x,Passenger1 *p); //�������ϣ�����λ�ô�������
void Findvip(K_HashTable *H);    //ȥ�����з���vip
int Judgevip(K_HashTable *H,int x,char *p);   //�ж��ǲ���vip�ͻ�
int CollisionChongxuan(K_HashTable*H,int x,K_Passenger *p,int jJs);

int main()
{
    cout<<"       ���չ�˾Hash������ͻ����,�����¶�λһ����"<<endl;
    //��ʽ�����ͻ
    HashTable1 *H1=new HashTable1;    
    H1->elem=new Passenger1[1600]; //��ϣ��ĳ���
    H1->count=0;
    H1->tablesize=1600;
    for(int i=0;i<1600;i++)  //��һ����ʼ�������ϣ��
    {
        H1->elem[i].next=NULL;  //��ʼ��ʱ����ָ���˿�ָ��
        H1->elem[i].judge=0; //�ж����λ���Ƿ��Ѿ�����ռλ
    }

    //����ѡַ�����ͻ
    K_HashTable* K_H=new K_HashTable;
    K_H->elem=new K_Passenger[1600]; //��ϣ��ĳ���
    K_H->count=0;
    K_H->tablesize=1600;
    for(int i=0;i<1600;i++)  //��һ����ʼ�������ϣ��
    {
        K_H->elem[i].judge=0; //��ʼ������û����ռλ
    }
    int chongxindingwei;
    int jsCollison=1;
    chongxindingwei=InsertData(H1,jsCollison,K_H);
    jsCollison--;
    cout<<"������ͻ�Ĵ���:";
    cout<<jsCollison<<endl;
    cout<<"�����ض�λ���ܴ�����";
    cout<<chongxindingwei<<endl;
    cout<<"         ���չ�˾����vip�û�ϵͳ"<<endl;
   
    cout<<"������Ǳ��vip����ͻ�(�˻�Ƶ�ʴ��ڵ�������)"<<endl;
    Findvip(K_H);
    delete []K_H->elem; //�ͷ���Ӧ�ÿռ�
    delete []H1->elem;   //��ʱ�ͷ��Ҹ������Ĵ���ռ�
    delete H1;
    return 0;
}

int InsertData(HashTable1 *H,int&tongji,K_HashTable * KH)  //�������ϣ����ȡ��������
{
    int sumChong=0;
    vector<string> Name;    //���˿͵Ĳ��ظ������֤д�뵽�µ�����֮��
    fstream file;
    file.open("Hashvip\\Passenger.txt",ios::in);
    if(!file)
    {
        cout<<"�ļ���ʧ��";
        exit(0);
    }
    Passenger1 *temp=new Passenger1;
    temp->judge=1;  //���λ���Ѿ���ֵ������
    temp->next=0;   //��һ������ڵ��ǿ�ָ��
    K_Passenger *linshi=new K_Passenger;
    int js=0;
    int sum=1;
    while(!file.eof())
    {
        int xiabiao=0;   //�鿴���������һ��λ��֮��
        file>>temp->Idcard;
        file>>temp->Name;
        file>>temp->Flightid;
        file>>temp->year;
        file>>temp->month;
        file>>temp->day;
        file>>temp->Distance;  
        
        strcpy(linshi->day,temp->day);
        strcpy(linshi->Distance,temp->Distance);
        strcpy(linshi->Flightid,temp->Flightid);
        strcpy(linshi->Idcard,temp->Idcard);
        strcpy(linshi->year,temp->year);
        strcpy(linshi->month,temp->month);
        strcpy(linshi->Name,temp->Name);
        if(file.fail()) //������β��Ҫֱ���˳�
        {
            break;
        }

        if(js==0)
        {
            Name.push_back(temp->Idcard);
        }
        else
        {
            int judeg=0;    //�ж��Ƿ����ظ������
            for(int k=0;k<Name.size();k++)
            {
                if(Name[k]==temp->Idcard)
                {
                    judeg=1;    //�����Ѿ�����ͬ��id,�����ٴ�д��������ȥ
                    break;
                }
            }
            if(judeg==0)    //���ظ������ٴ�д���ȥ
            {
                Name.push_back(temp->Idcard);
            }
        }
        for(int i=14;i<18;i++)
        {
            xiabiao=(xiabiao+(int(temp->Idcard[i])-48))*10;
        }
        xiabiao=xiabiao/10;
        xiabiao=xiabiao%1510;  //����ȡ����ȡ��1510
        //cout<<xiabiao<<endl;
        if(collision(H,xiabiao,temp))  //���ϣ����ȡ��������    
        {
            sum++;
        }   
        int linshix=sumChong;       
        sumChong=sumChong+CollisionChongxuan(KH,xiabiao,linshi,tongji);
        if(sumChong>linshix)
        {
            tongji++;
        }
        js++;
    }
    file.close();   //����֮��ر��ļ����ͷſռ�
    delete temp; 
    file.open("Hashvip\\IdNorepeat.txt",ios::out);
    for(int j=0;j<Name.size();j++) //�����ظ������֤��Ϣ���뵽�µ��ļ���ȥ,�������ù�ϣ���ҷ���vip
    {
        file<<Name[j]<<endl;
    }
    file.close();   //�ٴιر��ļ�
    return sumChong;
}

bool collision(HashTable1 *&H,int x,Passenger1 *p) //�������ϣ�����λ�ô�������
{
    if(H->elem[x].judge==0) //֮ǰ�ǿ�λֱ�Ӹ�ֵ��ȥ
    {
        H->elem[x].judge++;
        strcpy(H->elem[x].year,p->year);
        strcpy(H->elem[x].month,p->month);
        strcpy(H->elem[x].day,p->day);
        strcpy(H->elem[x].Flightid,p->Flightid);
        strcpy(H->elem[x].Distance,p->Distance);
        strcpy(H->elem[x].Idcard,p->Idcard);
        strcpy(H->elem[x].Name,p->Name);
        H->elem[x].next=NULL;
        return false;   //û�з�����ͻ
    }
    else    //ֱ�ӿ��ڱ�ͷ�к��漴��
    {
        H->elem[x].judge++; //�������λ�þ����ж��ٵ�����
        p->next=H->elem[x].next;
        H->elem[x].next=p;
        return true;
    }
}
int CollisionChongxuan(K_HashTable*H,int x,K_Passenger *p,int jJs)  //��ֵ������Ŷ�ַ,���ҷ����ض�λ����
{
    int js=0;
    int i;
    if(H->elem[x].judge==0)
    {
        H->elem[x].judge++;
        strcpy(H->elem[x].year,p->year);
        strcpy(H->elem[x].month,p->month);
        strcpy(H->elem[x].day,p->day);
        strcpy(H->elem[x].Flightid,p->Flightid);
        strcpy(H->elem[x].Distance,p->Distance);
        strcpy(H->elem[x].Idcard,p->Idcard);
        strcpy(H->elem[x].Name,p->Name);
    }
    else
    {
        for(i=1;;i++)
        {
            js++;   //ֻҪ�г�ͻ����Ҫ���¶�λ
            if(H->elem[x+i*i].judge==0) //�������¶�λ�Ĵ���
            {
                break;
            }           
        }
        H->elem[x+i*i].judge++;
        strcpy(H->elem[x+i*i].year,p->year);
        strcpy(H->elem[x+i*i].month,p->month);
        strcpy(H->elem[x+i*i].day,p->day);
        strcpy(H->elem[x+i*i].Flightid,p->Flightid);
        strcpy(H->elem[x+i*i].Distance,p->Distance);
        strcpy(H->elem[x+i*i].Idcard,p->Idcard);
        strcpy(H->elem[x+i*i].Name,p->Name);
    }
    if(js>=1)
    {
        cout<<"��"<<jJs<<"�γ�ͻ����,�������¶�λ��"<<js<<"�Ρ�"<<endl;
    }
    return js;
}



void Findvip(K_HashTable *H)    //ȥ�����з���vip
{
    fstream file;
    file.open("Hashvip\\IdNorepeat.txt",ios::in);
    if(!file)
    {
        cout<<"�ļ���ʧ��";
        exit(0);
    }
    char id[20];
    while(!file.eof())
    {
        file>>id;
        if(file.fail())
        {
            break;
        }
        int xiabiao=0;
        for(int i=14;i<18;i++)
        {
            xiabiao=(xiabiao+(int(id[i])-48))*10;
        }
        xiabiao=xiabiao/10;
        xiabiao=xiabiao%1510;   //����ȡ��ȡ��1510,����ᳬ������÷�Χ!!!
        int xjs=Judgevip(H,xiabiao,id);
        if(xjs>1)  //�����vip
        {
            int total=0;
            int linshi=0;   //��¼�ܵľ����ֵ                     
            for(int i=0;;i++)
            {
                if(H->elem[xiabiao+i*i].judge==0)   //��ʱ���λ��Ϊ��,������ѭ��
                {
                    break;
                }
                if(strcmp(H->elem[xiabiao+i*i].Idcard,id)==0)
                {
                    linshi=0;   //����ʱ��ֵ���г�ʼ��
                    for(int j=0;H->elem[xiabiao+i*i].Distance[j]!='\0';j++)
                    {
                        linshi=(linshi+int(H->elem[xiabiao+i*i].Distance[j])-48)*10;
                    }
                    linshi=linshi/10; 
                    total=total+linshi;                 
                }
            }
            for(int i=0;;i++)
            {
                if(strcmp(H->elem[xiabiao+i*i].Idcard,id)==0)
                {
                    cout<<"�û�������"<<H->elem[xiabiao+i*i].Name<<" ";
                    cout<<"�û�id��"<<H->elem[xiabiao+i*i].Idcard<<" ";
                    cout<<"������˻�Ƶ�ʣ�"<<xjs<<" ";                 
                    cout<<"���������"<<total<<endl;
                    break;
                }
            }
        }
    }
    file.close();
    return;
}

int Judgevip(K_HashTable *H,int x,char *p)   //�ж��ǲ���vip�ͻ�
{
    
    if(H->elem[x].judge==0)   //ֻ��һ�γ˻���¼����vip
    {
        return (-1);
    }
    else
    {
        int js=0;
        if(strcmp(H->elem[x].Idcard,p)==0)  //���ֵ�鿴��ͻ
        {
            js++;
        }
        for(int i=1;;i++)
        {
            if(H->elem[x+i*i].judge==0) //��λ������ѭ��
            {
                break;
            }
            if(strcmp(H->elem[x+i*i].Idcard,p)==0)  //һ����js++
            {
                js++;
            }
        }
        return js;
    }
}
