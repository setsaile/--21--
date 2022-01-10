#include<iostream>
#include<fstream>
#include<math.h>
using namespace std;
//ƽ��������Ĳ�������ʾ
//���Ҳ����ɾ��
struct  BBT
{
    int num;    //���ƽ���������ֵ
    int judge;  //���ƽ���������������ȵĲ�ֵ
    BBT * lchild,* rchild;  
};
int BBTDepth(BBT *T);   //����������ĸ߶�
int BBTDifhigh(BBT *T); //�ж���������������Ĳ�ֵ
BBT * LLAdjust(BBT *A); //LL�͵�������
BBT * RRAdjust(BBT *A); //RR�͵�������
BBT * LRAdjust(BBT *A); //LR�͵�������
BBT * RLAdjust(BBT *A); //RL�͵�������
BBT * BSTInsert(BBT * T,int x); //����ж����������Ĳ�����ȥ������Ӧ��ֵ
void Update(BBT * T);  //����ÿһ���ڵ��ƽ���
bool Isbanlance(BBT * T); //�жϴ�ʱ������ǲ��ǲ���ƽ����
BBT * FindNoBanlance(BBT * T);  //�ҵ������治����ƽ��ĵ�
BBT * BBTInsert(BBT * T,int x);  //ֲ��ƽ�������
BBT * EditTree(BBT * T); //�������ƽ����
BBT * FindDingdian(BBT *T,int x); //�ҵ��ض�����ĸ���
void Printxianxu(BBT *T);
BBT *BSTDelete(BBT*T,int key);  //ɾ�������������Ľڵ�,�ݹ��㷨
BBT *BBTDelete(BBT*T,int key);  //ɾ��ƽ��������Ľڵ�,�ݹ��㷨
BBT *FindBenshen(BBT *T,int key);   //�������ֵ
BBT* DELETEBST(BBT* T);
int main()
{
    int choice;
    fstream file;
    file.open("BBT\\BBT.txt",ios::in);  
    if(!file)
    {
        cout<<"error";
        exit(0);
    }
    int temp;
    BBT *T=NULL;
    BBT *T1=0;
    while(!file.eof())  //�����ƽ����������д���
    {
        file>>temp;
        if(file.fail())
        {
            break;
        }        
        T=BBTInsert(T,temp);
        T1=BSTInsert(T1,temp);       
    }
    while(1)
    {
        cout<<"         ƽ�����������ʾ"<<endl;
        cout<<"1.չʾ�������ƽ�������"<<endl;
        cout<<"2.��������Ҫ�ĸ��ڵ㲢���������������"<<endl;
        cout<<"3.��������ֵ"<<endl;
        cout<<"4.ɾ�����д��ڵ�ֵ"<<endl;
        cout<<"5.�˳���ʾ"<<endl;
        cout<<endl;
        cout<<"����������Ҫ�Ĳ���:";
        cin>>choice;
        if(choice==5)
        {
            break;
        }
        switch(choice)
        {
            case 1:
            {
                Printxianxu(T1);
                cout<<endl;
                if(Isbanlance(T1))
                {
                    cout<<"����һ��ƽ�������"<<endl;
                }
                else
                {
                    cout<<"��ֻ��һ����ͨ�����������"<<endl;
                }
                Printxianxu(T);
                cout<<endl;
                if(Isbanlance(T))
                {
                    cout<<"����һ��ƽ�������"<<endl;
                }
                else
                {
                    cout<<"��ֻ��һ����ͨ�����������"<<endl;
                }
                cout<<endl;
                cout<<endl;
                break;
            }
            case 2:
            {
                cout<<"����Ҫ���ҵ�ֵ��";
                int x1;
                
                cin>>x1;
                BBT * newtree=new BBT;
                newtree=FindBenshen(T,x1);
                if(newtree==0)
                {
                    cout<<"���ƽ����������������ֵ";
                }
                else
                {
                    cout<<"������㼰�����Ӻ��ӵ�ֵ��";
                    Printxianxu(newtree);
                }
                cout<<endl;
                cout<<endl;
                break;
            }
            case 3:
            {
                cout<<"����������Ҫ�����ֵ��";
                int xxx;
                cin>>xxx;
                T1=BSTInsert(T1,xxx);
                T=BBTInsert(T,xxx);
                cout<<"���������������չʾ:";
                Printxianxu(T1);
                cout<<endl;
                cout<<"������ƽ�������չʾ��";
                Printxianxu(T);
                cout<<endl;
                cout<<endl;
                cout<<endl;
                break;
            }     
            case 4:
            {
                cout<<"����Ҫɾ����ֵ��";
                int zhi;
                cin>>zhi;
                BBT *TTemp;
                TTemp=FindBenshen(T,zhi);
                if(TTemp==0)
                {
                    cout<<"û���ҵ�����Ҫɾ����ֵ"<<endl;
                }
                else
                {
                    cout<<"ɾ�����ƽ�������:";
                    BBTDelete(T,zhi);
                    Printxianxu(T);
                    cout<<endl;
                    cout<<endl;
                }
                break;
            }         
        }
    }

    file.close();   
    delete T;
    delete T1; 
    return 0;
}

int BBTDifhigh(BBT *T) //�ж���������������Ĳ�ֵ
{
    int sum;
    int Lhigh,Rhigh;
    //̽��������������
    if(T->lchild==0)    
    {
        Lhigh=0;
    }
    else
    {
        Lhigh=BBTDepth(T->lchild);
    }
    //̽���ұ����������
    if(T->rchild==0)
    {
        Rhigh=0;
    }
    else
    {
        Rhigh=BBTDepth(T->rchild);
    }
    sum=Lhigh-Rhigh;   //sumΪ�����������ĸ߶Ȳ�
    return sum;
}
int BBTDepth(BBT *T)   //����������ĸ߶�
{
    int lefthigh,righthigh;
    if(T==0)
    {
        return 0;
    }
    else
    {
        lefthigh=BBTDepth(T->lchild);
        righthigh=BBTDepth(T->rchild);
        return (lefthigh>righthigh)?(lefthigh+1):(righthigh+1);   //����������ĸ߶�
    }
}

BBT * LLAdjust(BBT *A) //LL�͵�������
{
    BBT * B=A->lchild;      //��B��ʼΪA������
    A->lchild=B->rchild;    //��A�������滻��B���Һ���
    B->rchild=A;    //��B���Һ���ָ��A,��Ϊ��B���ҽ�����תһȦ�ﵽƽ��
    //�������,�����Ǹ����������ڵ��ƽ���ֵ
    int Diff;
    Diff=BBTDifhigh(B);
    B->judge=Diff;
    Diff=BBTDifhigh(B->rchild);
    B->rchild->judge=Diff;
    return B;
}

BBT * RRAdjust(BBT *A) //RR�͵�������
{
    BBT * B=A->rchild;
    A->rchild=B->lchild;
    B->lchild=A;
    //��ʱ����A��B�����ֵ
    B->judge=BBTDifhigh(B);
    B->lchild->judge=BBTDifhigh(B->lchild);
    return B;
}

BBT * LRAdjust(BBT *A) //LR�͵�������
{
    A->lchild=RRAdjust(A->lchild);  //�Ƚ�������,��ΪRR��
    return LLAdjust(A); //�ٽ�����ѡ,��ΪLL��
}

BBT * RLAdjust(BBT *A)  //RL�͵�������
{
    A->rchild=LLAdjust(A->rchild);  //�Ƚ��ұ߽�������,��ΪLL
    return RRAdjust(A); //�ٽ�������,��ΪRR
}

BBT * BSTInsert(BBT * T,int x) //����ж����������Ĳ�����ȥ������Ӧ��ֵ
{
    if(T==NULL) //���ǿ�ʱ����Ҫ���в���,�������ֵ�϶���Ҷ�ӽ��,��������������û��
    {
        T=new BBT;
        T->num=x;
        T->lchild=T->rchild=NULL;
        return T;
    }
    else if(T->num==x)
    {
        return T;   //ֱ�ӷ���������ڵ�,����Ҫ�����κ�ֵ
    }
    else if(T->num<x) //�����ҽڵ�ȥ���в���
    {
        T->rchild=BSTInsert(T->rchild,x);
    }
    else    //������ڵ���в���
    {
        T->lchild=BSTInsert(T->lchild,x);
    }
    return T;
}

void Update(BBT * T)  //����ÿһ���ڵ��ƽ���
{
    if(T==0)    //������������Ľ��ȥ�������ƽ���
    {
        return;
    }
    T->judge=BBTDifhigh(T);
    Update(T->lchild);
    Update(T->rchild);
}   

bool Isbanlance(BBT * T) //�жϴ�ʱ������ǲ��ǲ���ƽ����
{
    if(T)
    {
        if(abs(T->judge)>1)  //��ʱ���ֲ�ƽ��
        {
            return false;
        }
        if(!Isbanlance(T->lchild))    //�����߲�����,��ֱ�ӷ���false
        {
            return false;
        }
        if(!Isbanlance(T->rchild))    //����ұ߲�����,Ҳֱ�ӷ���false
        {
            return false;
        }
    }
    return true;    //��TΪNULLֱ�ӷ���true,��������������Ҳ�Ƿ���true
}

BBT * FindNoBanlance(BBT * T)  //�ҵ������治����ƽ��ĵ�
{
    BBT *temp=NULL;
    if(T)   //������������,�ҵ���һ���������ֵ������Ҫ������ƽ���
    {
        temp=FindNoBanlance(T->lchild); //������ߵ�ֵ
        if(temp!=0)
        {
            return temp;
        }
        temp=FindNoBanlance(T->rchild); //�����ұߵ�ֵ
        if(temp!=0)
        {
            return temp;
        }
        if(abs(T->judge)>1)
        {
            temp=T;
            return temp;
        }
    }
    return temp;
}

BBT * BBTInsert(BBT *T,int x)  //ֲ��ƽ�������
{
    T=BSTInsert(T,x);
    Update(T);  //�����������ƽ�����Ϣ
    BBT * Linshi=T; //��һ����ʱ�����������
    if(Isbanlance(T))   //���ƽ��ֱ�ӷ���
    {
        return T;
    }   
    else    //�����ƽ��,����ת����ƽ��
    {
        int cjudge;     //�ж��������Ҫ�ı��λ���ǲ����ٸ��ڵ�
        int jss;    //�ж���������׵����ӻ����Һ�����Ҫ�ı�
        BBT *tempT=FindNoBanlance(Linshi);  //�ҵ������治ƽ��ĵ�(�������)
        BBT *fathertemp;    //��Ҫ�޸ĵĵ�ĸ��׽ڵ�
        if(T==tempT)    
        {
            cjudge=0;   //=0�Ǹ��ڵ㱻�޸�
        }
        else
        {
            cjudge=1;   
            fathertemp=FindDingdian(Linshi,tempT->num); //�ҵ��޸ĵ�ĸ���
            if(fathertemp->lchild->num==tempT->num) //������߱��޸ļ���0
            {
                jss=0;  
            }
            else    //�����ұ߱��޸ļ���1
            {
                jss=1;
            }               
        }                   
        tempT=EditTree(tempT);  //�����������ƽ������
        if(cjudge==0)   //���ڵ�ֱ�ӷ����������޸ĺ��ֵ
        {
            T=tempT;
        }
        if(cjudge==1)   //���Ǹ��ڵ�
        {
            if(jss==0)  //����������ֱ������ָ���޸ĵ�ֵ
            {
                fathertemp->lchild=tempT;
            }
            if(jss==1)  //�ұ��Һ��ӱ�ָ���޸ĺ��ֵ
            {
                fathertemp->rchild=tempT;
            }
        }       
    }
    Update(T);
    return T;
}

BBT * EditTree(BBT * T) //�������ƽ����
{
    
    if(T->judge>1)  //���-�ұ�>1(LL����LR)
    {
        int num;
        num=BBTDifhigh(T->lchild);
        if(num==1)  //ΪLL���͵Ĳ�ƽ��
        {
            T=LLAdjust(T);            
        }
        else    //ΪLR���͵Ĳ�ƽ��
        {
            T=LRAdjust(T);            
        }
    }
    if(T->judge<-1)  //���-�ұ�<1(RR����RL)
    {
        int num;
        num=BBTDifhigh(T->rchild);
        if(num==-1) //ΪRR�Ͳ�ƽ��
        {
            T=RRAdjust(T);           
        }
        else    //ΪRL��ƽ��
        {
            T=RLAdjust(T);   
        }
    }
    return T;
}

void Printxianxu(BBT *T)
{
    if(T)
    {
        cout<<T->num<<" ";      
        Printxianxu(T->lchild);
        Printxianxu(T->rchild);
    }
}

BBT * FindDingdian(BBT *T,int x) //�ҵ��ض�����ĸ���,�����޸ĺ󽫺����ָ��ָ���޸ĺ��ֵ
{
    BBT *temp=NULL;
    if(T==0)
    {
        return NULL;
    }
    
    else if(T->lchild->num==x||T->rchild->num==x)
    {
        temp=T;
        return temp;
    }
    else
    {
        temp=FindDingdian(T->lchild,x); //����ҵ����ֵ�Ͳ���������
        if(temp)
        {
            return temp;
        }
        temp=FindDingdian(T->rchild,x); //��������ұ�ȥ��
    }
    return temp;
}

BBT *BSTDelete(BBT*T,int key)  //ɾ�������������Ľڵ�,�ݹ��㷨
{
    BBT *p;
    if(T==NULL)  //������Ѿ��ǿ�ָ����
    {
        return T;
    }
    else if(T->num==key)    //���������Ҫɾ���Ľڵ�
    {
        if(T->lchild==NULL&&T->rchild==NULL)    //�������Ҷ�ӽڵ�ֱ��ɾ��
        {
            delete T;
            return NULL;    
        }
        else if(T->lchild==NULL&&T->rchild!=NULL)   //����ڵ���һ����Ҷ�ӽڵ�
        {
            p=T->rchild;    //ֱ��ָ��������ָ��
            delete T;
            return p;   //������ڵ�ɾ��,ֱ��ָ���Լ���������
        }
        else if(T->lchild!=NULL&&T->rchild==NULL)   //����ڵ�ֻ��һ�����ӽڵ�
        {
            p=T->lchild;    //ֱ��ָ��������ָ��
            delete T;
            return p;
        }
        else    //���������Ҳ���Һ���
        {
            p=T->lchild;    //��������������,��������ӵ����ֵȥ�滻�������ڵ�
            while(p->rchild)    //�Ƶ������½�,��Ϊ��������е����ֵ
            {
                p=p->rchild;
            }
            T->num=p->num;  //�����ֵȥ�滻�������
            T->lchild=BSTDelete(T->lchild,p->num);  //��������,ȥ������滻��ֵɾ��
            return T;   //��Ҫ�����T��Ϊ����ֵ
        }
    }
    else if(T->num<key)
    {
        T->rchild=BSTDelete(T->rchild,key);
    }
    else
    {
        T->lchild=BSTDelete(T->lchild,key);
    }
    return T;
}

BBT *BBTDelete(BBT*T,int key)  //ɾ��ƽ��������Ľڵ�,�ݹ��㷨
{
    T=BSTDelete(T,key);
    Update(T);  //�����������ƽ�����Ϣ
    BBT * Linshi=T; //��һ����ʱ�����������
    if(Isbanlance(T))   //���ƽ��ֱ�ӷ���
    {
        return T;
    }   
    else    //�����ƽ��,����ת����ƽ��
    {
        int cjudge;     //�ж��������Ҫ�ı��λ���ǲ����ٸ��ڵ�
        int jss;    //�ж���������׵����ӻ����Һ�����Ҫ�ı�
        BBT *tempT=FindNoBanlance(Linshi);  //�ҵ������治ƽ��ĵ�(�������)
        BBT *fathertemp;    //��Ҫ�޸ĵĵ�ĸ��׽ڵ�
        if(T==tempT)    
        {
            cjudge=0;   //=0�Ǹ��ڵ㱻�޸�
        }
        else
        {
            cjudge=1;   
            fathertemp=FindDingdian(Linshi,tempT->num); //�ҵ��޸ĵ�ĸ���
            if(fathertemp->lchild->num==tempT->num) //������߱��޸ļ���0
            {
                jss=0;  
            }
            else    //�����ұ߱��޸ļ���1
            {
                jss=1;
            }               
        }                   
        tempT=EditTree(tempT);  //�����������ƽ������
        if(cjudge==0)   //���ڵ�ֱ�ӷ����������޸ĺ��ֵ
        {
            T=tempT;
        }
        if(cjudge==1)   //���Ǹ��ڵ�
        {
            if(jss==0)  //����������ֱ������ָ���޸ĵ�ֵ
            {
                fathertemp->lchild=tempT;
            }
            if(jss==1)  //�ұ��Һ��ӱ�ָ���޸ĺ��ֵ
            {
                fathertemp->rchild=tempT;
            }
        }       
    }
    Update(T);
    return T;
}



BBT *FindBenshen(BBT *T,int key)   //�������ֵ
{
    if(T==NULL) //���ڿյ�ʱ����Ƿ��ؿ�
    {
        return NULL;
    }
    else if(T->num==key)    //��ȵ�ʱ��ͷ������ֵ
    {
        return T;
    }
    else if(T->num<key) //�����ʱ������ݸ�С�����������ȥѰ������ڵ��λ��
    {
        return (FindBenshen(T->rchild,key));  
    }
    else
    {
        return FindBenshen(T->lchild,key);    //�����ʱ������ݸ��������������ȥ����
    }   
}
BBT* DELETEBST(BBT* T) 
{
    if(T)
    {
        T->lchild=DELETEBST(T->lchild);
        T->rchild=DELETEBST(T->rchild);
        delete T;
        return NULL;
    }
    return NULL;
}
