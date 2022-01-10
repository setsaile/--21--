#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
//���õݹ�ͻ��ݽ����Թ�·�ߵ�Ѱ��
//��ά������0Ϊ�����ߵ�·,1Ϊǽ��ס��·
//ͨ�������·��������ʾ·��
struct stack
{
    int number[1280];  
    int total;  //��ʼֵΪ-1,�ܵ�����Ϊtotal+1
};
void Initstack(stack*L);    //��ʼ�����ջ
int top(stack*L);   //��ʾջ��Ԫ��
void pop(stack*L);  //��ջ
void push(stack*L,int number);  //ѹջ
void Findpath(char **p,stack *hangL,stack* lieL,int s1,int s2,int egderow,int egdecol,int &js);  //�ݹ�����ҳ�ȫ��·��
void Printsum(stack*hangL,stack*lieL);  //����·��ӡ����

int main()
{
    char **arc;
    arc=new char*[64];   //������Թ����ļ�֮���Ƴ���
    for(int i=0;i<64;i++)
    {
        arc[i]=new char[64];
    }
    fstream file;
    file.open("C:\\Codefield\\CODE_C\\CDesign\\Maze\\Maze.txt",ios::in);    //���ļ�
    if(!file)
    {
        cout<<"�ļ���ȡʧ��";
        exit(0);
    }
    int js=0;    
    while(!file.eof())
    {
        file.getline(arc[js],12);   //����ά�Թ�һ��һ�еĶ��뵽������ά������
        js++;
    }
    file.close();
    int col;    //�Թ���
    int row;    //�Թ���
    row=js; //�о����м���ָ���ȡ������,�������һ����row-1
    col=strlen(arc[0]); //�о���һ��ָ�����ַ�������,������������ұߵ�һ����col-1
    stack * rowstack=new stack;
    stack * colstack=new stack;
    Initstack(rowstack);    //��������ջ���г�ʼ��
    Initstack(colstack);
    cout<<"�Թ�ͼ�Σ�"<<endl;
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            cout<<arc[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<endl;
    int start1,start2,end1,end2;
    cout<<"�����������к��У�";
    cin>>start1>>start2;
    cout<<"�������յ���к��У�";
    cin>>end1>>end2;
    push(rowstack,end1);  //���յ�Ԫ�ؽ���ѹջ����
    push(colstack,end2);
    int count=0;
    if(arc[end1][end2]=='1'||arc[start1][start2]=='1')
    {
        cout<<"û��·���ܵ��";
    }
    else
    {
        Findpath(arc,rowstack,colstack,start1,start2,row-1,col-1,count);
        cout<<endl;
        cout<<"һ���У�"<<count<<"��·�ߡ�";
    }  
    for(int i=0;i<64;i++)   //�ͷ��ڴ���ռ�Ŀռ�
    {
        delete []arc[i];
    }
    delete arc;
    delete rowstack;
    delete colstack;
    
    return 0;
}

void Initstack(stack*L)    //��ʼ�����ջ
{
    L->total=-1; 
}
int top(stack*L)   //��ʾջ��Ԫ��
{
    return L->number[L->total]; //ֱ�ӷ���ջ��Ԫ��
}
void pop(stack*L)  //��ջ
{
    L->total--; //ֱ�Ӽ�1��Ϊ��ջ
}
void push(stack*L,int number)  //ѹջ   
{
    L->total++;
    L->number[L->total]=number;
}

void Findpath(char **p,stack *hangL,stack* lieL,int s1,int s2,int egderow,int egdecol,int &js)  //�ݹ�����ҳ�ȫ��·��
{
    int heng,shu;
    if(hangL->number[hangL->total]==s1&&lieL->number[lieL->total]==s2)
    {   //�ҵ�һ��ֵ����Ҫ����������ҵ�ջ����
        Printsum(hangL,lieL);   //������е�һ����·����,ÿ��·�߶����ʹ����Щ��·�Եú�����       
        pop(hangL);
        pop(lieL);
        js++;
        return;
    }
    //�����������ϵݹ�
    if(hangL->number[hangL->total]!=0)  //����Ƿ������ϱ߽�
    {   int judge=0;     
        heng=hangL->number[hangL->total]-1; //��ʱ������������λ��
        shu=lieL->number[lieL->total];
        if(p[heng][shu]=='0')   //����Ƿ���·��������
        {
            for(int i=0;i<=hangL->total;i++)    //ȷ�����·���Ǽ�·��,�������ظ�һЩ���·��
            {
                if(hangL->number[i]==heng&&lieL->number[i]==shu)
                {
                    judge=1;
                    break;
                }
            }
            if(judge==0)
            {
                push(hangL,heng);  //�������������ѹջ����
                push(lieL,shu);
                Findpath(p,hangL,lieL,s1,s2,egderow,egdecol,js); 
            }
        }        
    }
    //�����������µݹ�
    if(hangL->number[hangL->total]!=egderow)  //����Ƿ������±߽�
    { 
        int judge=0;       
        heng=hangL->number[hangL->total]+1; //��ʱ������������λ��
        shu=lieL->number[lieL->total];
        if(p[heng][shu]=='0')   //����Ƿ���·��������
        {
            for(int i=0;i<=hangL->total;i++)    //ȷ�����·���Ǽ�·��,�������ظ�һЩ���·��
            {
                if(hangL->number[i]==heng&&lieL->number[i]==shu)
                {
                    judge=1;
                    break;
                }
            }
            if(judge==0)
            {
                push(hangL,heng);  //�������������ѹջ����
                push(lieL,shu);
                Findpath(p,hangL,lieL,s1,s2,egderow,egdecol,js); 
            }
        }        
    }
    //�����������ҵݹ�
    if(lieL->number[lieL->total]!=egdecol)  //����Ƿ������ұ߽�
    {    
        int judge=0;    
        heng=hangL->number[hangL->total]; //��ʱ������������λ��
        shu=lieL->number[lieL->total]+1;
        if(p[heng][shu]=='0')   //����Ƿ���·��������
        {
            for(int i=0;i<=hangL->total;i++)    //ȷ�����·���Ǽ�·��,�������ظ�һЩ���·��
            {
                if(hangL->number[i]==heng&&lieL->number[i]==shu)
                {
                    judge=1;
                    break;
                }
            }
            if(judge==0)
            {
                push(hangL,heng);  //�������������ѹջ����
                push(lieL,shu);
                Findpath(p,hangL,lieL,s1,s2,egderow,egdecol,js); 
            }
        }        
    }
    //������������ݹ�
    if(lieL->number[lieL->total]!=0)  //����Ƿ�������߽�
    {       
        int judge=0; 
        heng=hangL->number[hangL->total]; //��ʱ������������λ��
        shu=lieL->number[lieL->total]-1;
        if(p[heng][shu]=='0')   //����Ƿ���·��������
        {
            for(int i=0;i<=hangL->total;i++)    //ȷ�����·���Ǽ�·��,�������ظ�һЩ���·��
            {
                if(hangL->number[i]==heng&&lieL->number[i]==shu)
                {
                    judge=1;
                    break;
                }
            }
            if(judge==0)
            {
                push(hangL,heng);  //�������������ѹջ����
                push(lieL,shu);
                Findpath(p,hangL,lieL,s1,s2,egderow,egdecol,js); 
            }
        }        
    }    
    pop(hangL); //һ�εݹ������Ҫ��ջ���е�ջ����!!!
    pop(lieL);  //Ŀ���ǽ��л���
}

void Printsum(stack*hangL,stack*lieL)  //����·��ӡ����
{
    cout<<"·��Ϊ��";
    for(int i=hangL->total;i>=0;i--)    //���Թ�·�ߴ�ӡ����
    {
        if(i==0)
            cout<<"("<<hangL->number[i]<<","<<lieL->number[i]<<")"<<endl;       
        else
            cout<<"("<<hangL->number[i]<<","<<lieL->number[i]<<")->";
        
    }
}
