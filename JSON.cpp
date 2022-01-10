#include<iostream>
#include<string.h>
#include<stdbool.h>
#include<string.h>
#include<fstream>
using namespace std;
//���ֵܺ��������õ���Ӧ�ļ�����Ӧ��ֵ�Ľ��
struct NormalTree
{
    char key[256];  //�����
    char value[256];    //���������Ӧ��ֵ
    int judgestring;   //�ж�ֵ��һ���������ַ���(1���ַ���,0�Ƕ���)
    NormalTree *leftChild;  //��������,ֻ��Ƕ�׵�ʱ��Ż��������
    NormalTree *rightBrother;   //���еľͽ����ұߺ���
};
bool InsertData(NormalTree *&T,char *p,int high,int judge,int nowhigh); //���еݹ������
void DeleteTree(NormalTree *&T);    //ɾ�����ͷ��ڴ�
bool Findvalue(NormalTree*T,char *p,NormalTree *&Rtree);  //��������ֵ
int main()
{
    int n,m;
    char ch;
    fstream file;
    file.open("C:\\Codefield\\CODE_C\\CDesign\\JSON\\JSON.txt",ios::in);
    if(!file)
    {
        cout<<"���ļ�ʧ�ܡ�";
        exit(0);
    }
    file>>n;
    file>>m;    
    file>>ch;    //����һ�������Ŵ����ȥ
    file.ignore();
    NormalTree *tree=NULL;  //����һ������
    char shuzu[256];
    int cengci=0;
    for(int i=1;i<n-1;i++)  
    {
        int judgevalue; //�ж�ֵ��һ���������ַ���
        file.getline(shuzu,256);   
        if(shuzu[0]==125)   //�����Ų������κβ���
        {
            cengci--;   //����߽������Ȳ�μ�С
            continue;
        }   
        for(int j=0;;j++)
        {
            if(shuzu[j]==58&&shuzu[j+1]==32)
            {
                if(shuzu[j+2]==123) //�����������˵��ֵ����һ���ַ�������һ������
                {
                    judgevalue=0;   //���ֵ�Ƕ���Ϊ0
                }
                else 
                {
                    judgevalue=1;    //���ֵ���ַ���Ϊ1
                }
                break;
            }
        }
        InsertData(tree,shuzu,cengci,judgevalue,0);
        if(judgevalue==0)   //�ں���һ�����Ҫ����߽����ƶ�,�����һ�㻹�Ǵ���ԭ����һ��ȥ
        {
            cengci++;
        }
    }
    file>>ch;
    file.ignore();   //�����з��Ž���ȥ��
    for(int i=0;i<m;i++)
    {
        int judge=0;
        file.getline(shuzu,256);
        for(int j=0;;j++)
        {
            if(shuzu[j]=='\0')
            {
                break;
            }
            if(shuzu[j]==46)
            {
                judge++;    //judge++���ǲ�Ӧ���˳�,Ӧ�ü�¼�ܵ�.�ĸ���
            }
        }
        NormalTree * ppt=NULL;

        if(judge==0)    //����м�û�г���.��Ȳ���ʱ
        {
            Findvalue(tree,shuzu,ppt);
            if(ppt==NULL)
            {
                cout<<"NOTEXIST"<<endl;
            }
            else
            {
                if(ppt->judgestring==0)
                {
                    cout<<"OBJECT"<<endl;
                }
                else
                {
                    cout<<"STRING "<<ppt->value<<endl;
                }
            }
        }

        else    //����м����.��Ȳ���ʱ
        {
            NormalTree *PPT=NULL;
            char **mvp=new char*[judge+1];    //ֱ�ӹ�����άָ�� 
            for(int i=0;i<=judge;i++)
            {
                mvp[i]=new char[256];
            }
            int js=0;   //��ָ�븳ֵ�ռ�
            int deep=0;    //�жϵ���ڼ���ָ��
            int isz=0;  //�����˳��
            while(1)
            {
                if(shuzu[isz]=='\0')    //ʲôʱ������������
                {
                    mvp[deep][js]='\0'; //�����ֵ���з��,���ܸ��õıȽ�
                    break;
                }
                if(shuzu[isz+1]==46)    //�������е��ʱ��,��Ҫ�����黻����һ��
                {
                    mvp[deep][js]=shuzu[isz];
                    js++;
                    mvp[deep][js]='\0';
                    js=0;   //���¸���һ�����鸳ֵ
                    deep++;
                    isz=isz+2;
                }
                else
                {
                    mvp[deep][js]=shuzu[isz]; //��ͨ�Ĵ�������
                    js++;
                    isz++;
                }
            }
            int judgeyn=1;  //�ж��ܲ����ҵ���Ӧ��ֵ
            NormalTree *linshiPPT=NULL;
            for(int i=0;i<=judge;i++)
            {                               
                if(i==0)
                {
                    if(!Findvalue(tree,mvp[i],PPT))   //��ʾû���ҵ���Ӧ��ֵ
                    {
                        judgeyn=0;  
                        break;
                    }
                }
                else
                {
                    linshiPPT=PPT->leftChild;   //����߽�����ȱ���
                    if(!Findvalue(linshiPPT,mvp[i],PPT))
                    {
                        judgeyn=0;  //û������Ӧ�Ĳ���ҵ���Ӧ��ֵ
                        break;
                    }
                }
            }
            if(judgeyn==0)
            {
                cout<<"NOTEXIST"<<endl;
            }
            else
            {                
                if(PPT->judgestring==0)
                {
                    cout<<"OBJECT"<<endl;
                }
                else
                {
                    cout<<"STRING "<<PPT->value<<endl;
                }
            }
            for(int i=0;i<=judge;i++)
            {
                delete []mvp[i];    //��ÿһ��ָ��Ŀռ���ͷ�
            }
            delete mvp; //������ָ�붼�ͷ�
        }
    }
    DeleteTree(tree);
    return 0;
    
}
//T��Ҫ�������,p����һ���ַ���,high���߼���������,judge���ж��Ƿ��ֵ
//nowhigh���жϴ�ʱ�ڵڼ���
bool InsertData(NormalTree *&T,char *p,int high,int judge,int nowhigh) //���еݹ������
{
    if(T==NULL&&nowhigh!=high)  //������һ����ֱ��������β��
    {
        return false;   
    }
    if(T==NULL&&judge==1)   //ֱ�Ӵ����ֵ�����
    {
        T=new NormalTree;
        T->leftChild=T->rightBrother=0;
        T->judgestring=1;
        int i=1;
        int js=0;
        //��¼���ľ���ֵ
        while(1)
        {
            if((p[i]==34&&p[i-1]!=92)||(p[i]==34&&p[i-1]==92&&p[i-2]==92))   //����һ�����ݼ�¼���ʱ,˫����ǰ�治�Ƿ�б��
            {   //("\"\\")��("hello")���ֽ�β�ķ�ʽ
                T->key[js]='\0';
                js=0;   //Ϊ����ֵ���г�ʼ��
                i=i+4;
                break;
            }
            if(p[i]==92)    //���ַ�б�ܵ�ģʽ
            {
                T->key[js]=p[i+1];
                js++;
                i=i+2;
            }
            else    //��������ģʽ
            {
                T->key[js]=p[i];
                js++;
                i++;
            }
        }
        //��¼ֵ�ľ���ֵ
        while(1)
        {
            if((p[i]==34&&p[i-1]!=92)||(p[i]==34&&p[i-1]==92&&p[i-2]==92))   //����һ�����ݼ�¼���ʱ,˫����ǰ�治�Ƿ�б��
            {   //("\"\\")��("hello")���ֽ�β�ķ�ʽ
                T->value[js]='\0';
                js=0;   //Ϊ����ֵ���г�ʼ��
                break;
            }
            if(p[i]==92)    //���ַ�б�ܵ�ģʽ
            {
                T->value[js]=p[i+1];
                js++;
                i=i+2;
            }
            else    //��������ģʽ
            {
                T->value[js]=p[i];
                js++;
                i++;
            }
        }
        return true;
    }


    if(T==NULL&&judge==0)   //����ֵ��Ӧ�Ƕ�������
    {
        T=new NormalTree;
        T->leftChild=T->rightBrother=0;
        T->judgestring=0;
        int i=1;
        int js=0;
        //��¼���ľ���ֵ
        while(1)
        {
            if((p[i]==34&&p[i-1]!=92)||(p[i]==34&&p[i-1]==92&&p[i-2]==92))   //����һ�����ݼ�¼���ʱ,˫����ǰ�治�Ƿ�б��
            {   //("\"\\")��("hello")���ֽ�β�ķ�ʽ
                T->key[js]='\0';
                break;
            }
            if(p[i]==92)    //���ַ�б�ܵ�ģʽ
            {
                T->key[js]=p[i+1];
                js++;
                i=i+2;
            }
            else    //��������ģʽ
            {
                T->key[js]=p[i];
                js++;
                i++;
            }
        }
        return true;
    }
    //ֱ�����ұ�̽���ײ�
    //��������Ӧ�Ĳ��,������������ȥ�洢
    if(!InsertData(T->rightBrother,p,high,judge,nowhigh))   
    {
        while(1)
        {
            nowhigh++;
            if(InsertData(T->leftChild,p,high,judge,nowhigh))   //ֱ�����������ݲŽ��е���
            {
                return true;    //ֱ����������ݹ�ѭ��
            }
        }
    }   
    return true;    //�����������Ӧ��ֱ�ӷ���true,����ʵ�����
}

void DeleteTree(NormalTree *&T)    //ɾ�����ͷ��ڴ�
{
    if(T)
    {
        DeleteTree(T->leftChild);
        DeleteTree(T->rightBrother);
        delete T;
    }
}

bool Findvalue(NormalTree*T,char *p,NormalTree * &Rtree)  //��������ֵ
{
    NormalTree *linshiT=T;  //ֻ����һ����ȥѰ��
    while(linshiT)
    {
        if(strcmp(linshiT->key,p)==0)
        {
            Rtree=linshiT;
            return true;    //�ҵ��򷵻�true
        }
        linshiT=linshiT->rightBrother;
    }
    return false;   //û�ҵ��򷵻�false
    
}

