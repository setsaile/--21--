#include<iostream>
#include<string>
#include<string.h>
#include<algorithm>
#include<vector>
using namespace std;
//URLӳ��ƥ�����

struct URL
{
    string address; //��¼URLƥ������
    string Value;   //URL���ƶ�Ӧ��ֵ
};

string FindSum(URL *L,string str,int len);  //�����ֵ��URLӳ����ҳ���
bool judgeHeFa(string str); //�����������Ƿ�Ϸ�
bool judgeisPipei(string str1,string str2); //�ж��ǲ�������ƥ��
int judgeXiangdeng(string str1,string str2);   //�ж�����ǰ��ĵ�ַ�ǲ������

int main()
{
    int n,m;    //n����������,m������Ҫ���Ե�����
    cin>>n>>m;
    URL model[n];   //��������ڽṹ������
    string tempAdd,tempVa;
    for(int i=0;i<n;i++)    //����Щֵ���ڽṹ������
    {
        cin>>tempAdd>>tempVa;
        model[i].address=tempAdd;   //�����ֵ���ٽṹ������
        model[i].Value=tempVa;
    }
    string tempsum;
    vector<string> Totalsum;    //�����������ս������ֱ�����
    for(int i=0;i<m;i++)
    {
        cin>>tempsum;
        Totalsum.push_back(FindSum(model,tempsum,n)); //����Щֵ���뵽һ���µ�ϵͳ����
    }
    for(int i=0;i<m;i++)
    {
        cout<<Totalsum[i]<<endl;
    }
    return 0;
}

string FindSum(URL *L,string str,int len)  //�����ֵ��URLӳ����ҳ���
{
    int judge=0;
    string sumstr="";   //�մ���ʼ
    if(!judgeHeFa(str))    //�ȼ�鷵�ص��Ƿ�Ϸ�,������Ϸ�ֱ�ӷ���404
    {   
        sumstr="404";   
        return sumstr;
    }
    for(int i=0;i<len;i++)  //���������ַ�����ȫһ��ʱ
    {
        if(str==L[i].address) //���������ַ��ȫһ����ֱ�����ԭ���÷���ֵ
        {
            judge=1;
            sumstr=L[i].Value;
            break;
        }
        int x=judgeXiangdeng(L[i].address,str); //�ж�ǰ���ȡֵ�ǲ���һ��

        if(x==-1)   //��һ��ֱ�ӵ���һ��.һ��������ȥ��
        {
            continue;
        }

        else
        {
            if(L[i].address[x+1]!='<')  //������ǰ��������϶��Ѿ���һ����,ֱ�ӷ���
            {
                continue;   
            }

            if(L[i].address[x+2]=='p')  //��path��Ҳ��ȡ����
            {
                judge=1;
                string temp1=str.substr(x+1);   //��������ַ�����ȡ����
                if(judgeHeFa(temp1))
                {
                    sumstr=L[i].Value;
                    sumstr+=" ";
                    sumstr+=temp1;
                    break;
                }
            }

            else    //��<int><str>���͵�Ҳ��ȡ����
            {
                string linshi1=L[i].address.substr(x+1);
                string linshi2=str.substr(x+1);
                if(judgeisPipei(linshi1,linshi2))
                {
                    judge=1;
                    sumstr=L[i].Value;
                    sumstr+=" ";
                    int js=count(linshi1.begin(),linshi1.end(),'/');
                    int x1=0,x2=0;  //x1��x2������������ַ�����Χ
                    for(int k=0;k<js;k++)
                    {
                        x1=linshi2.find('/',x2+1);
                        if(k==0)
                        {
                            for(int h=x2;h<x1;h++)
                            {
                                if(linshi2[h]=='0'&&h==x2)
                                {
                                    continue;
                                }                               
                                sumstr+=linshi2[h];                                                             
                            }
                        }
                        else
                        {
                            for(int h=x2+1;h<x1;h++)
                            {
                                if(linshi2[h]=='0'&&h==x2+1)
                                {
                                    continue;
                                }                        
                                sumstr+=linshi2[h];                                                             
                            }
                        }        
                        if(k!=js-1)
                        {
                            sumstr+=" ";
                        }                                    
                        x2=x1;
                    }
                    break;
                }
                else
                {
                    continue;
                }
            }
        }
    }
    if(judge==0)    //û����������ֱ�ӷ���404
    {
        sumstr="404";
    }
    return sumstr;

}

bool judgeHeFa(string str) //�����������Ƿ�Ϸ�
{
    int length=str.length();  
    int count=0;  
    for(int i=0;i<length;i++)
    {
        if((str[i]>=45&&str[i]<=57)||(str[i]>=65&&str[i]<=90)||str[i]==95||(str[i]>=97&&str[i]<=122))
        {
            count++;
        }
        else
        {
            return false;
        }
    }
    return true;
}

int judgeXiangdeng(string str1,string str2)   //�ж�����ǰ��ĵ�ַ�ǲ������,���ֵ��-1�����
{
    int sum=-1;
    int js=0;
    for(int i=0;i<str2.length();i++)
    {
        if(str1[i]==str2[i]&&str1[i]=='/')  //�ж��ʼ�ĵ�ַ�ǲ���һ����
        {
            js++;
            if(js==2)
            {
                sum=i;
                return sum;
            }
        }
        if(str1[i]!=str2[i])    //���߲���ͬ
        {
            break;
        }
    }
    return sum;
}

bool judgeisPipei(string str1,string str2) //�ж��ǲ�������ƥ��
{
    int js1=count(str1.begin(),str1.end(),'/'); //�м���js1�����м����ж�Ҫ��
    int js2=count(str2.begin(),str2.end(),'/');
    //cout<<js1<<" "<<js2<<endl;
    if(js1!=js2)    //���������е�/���бȽ��������һ��������������,���������һ�����������
    {
        return false;
    }
    if(!judgeHeFa(str2))    //������Ϸ�����Ȼ���ش���
    {
        return false;
    }
    int x1=0,x2=0;  //x���������ַ�����Χ��
    int y1=0;   //y����������Χ
    for(int i=0;i<js1;i++)  //����/�����õ�ѭ��������
    {
        x1=str2.find('/',x2+1);
        if(i!=0)
        {
            y1=str1.find('/',y1+1);
        }       
        if(i==0)
        {
            if(str1[1]=='i')    //������ӳ����int��
            {
                for(int j=0;j<x1;j++)
                {
                    if(str2[j]<48||str2[j]>57)  //�����㴿����Ҫ��
                    {
                        return false;
                    }
                    //cout<<"1"<<endl;
                }
            }
            x2=x1;
        }
        else
        {
            if(str1[y1+2]=='i')
            {
                for(int j=x2+1;j<x1;j++)
                {
                    if(str2[j]<48||str2[j]>57)  //�����㴿����Ҫ��
                    {
                        return false;
                    }
                }
            }
            x2=x1;
        }
    }
    return true;    //ȫ��û�������򷵻�true
}
