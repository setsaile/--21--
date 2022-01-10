#include<iostream>
using namespace std;
#include<fstream> 
#include<stdlib.h>
#include<string.h>
#define N  58
#define MAX 10000
#define M 30
#define MAXSIZE 2000

struct Hfmnode  //���������Ĺ���
{//Ȩ�أ����׺�����ţ��洢���ַ� 
	int weight; 
	int parent,lchild,rchild;
	char c;     //���Ҷ�ӽڵ㴢����ַ�
};
//����������
struct Hfmcode 
{
	char* bit ; 
};

//�����ļ�,ͳ���ļ��и����ַ����ֵĴ���
void get_ch_count(int*&counts) 
{//counts:�洢�ַ����ֵĴ��� 
	counts=new int[N];//����ռ�
	if(!counts)
	{
		cout<<"����ʧ�ܣ�"<<endl;
		exit(0);
	} 
	for(int i=0;i<N;i++)//������ʼ�� 
	{
		counts[i]=0;
	}
	fstream file;
	char ch;
	file.open("Huffman\\source.txt",ios::in);
	if(!file)
	{
		cout<<"�ļ���ʧ�ܣ�"<<endl;
		exit(0);
	}
	while(!file.eof())//���ļ��ж����ݣ���������ֵĴ��� 
	{
		file.get(ch);//get()��ȡ�����Զ�ȡ�հ��ַ� 
		if(ch<='z'&&ch>='a')//[0,25]��[a,z] 
		{
			counts[ch-'a']++;
		}
		else if(ch<='Z'&&ch>='A')//[26,51]:[A,Z]
		{
			counts[ch-'A'+26]++;
		}
		else//ͳ�Ʊ�����  
		{
			switch(ch)//[52,57]֮�ڵ��ַ������Ķ���
			{
				case ' ':counts[52]++;break;
				case ',':counts[53]++;break;
				case '.':counts[54]++;break;
				case '\n':counts[55]++;break;
				case '(':counts[56]++;break;
				case ')':counts[57]++;break;	
			}
		} 
	}
	file.close();//�ر��ļ� 
} 

//ͨ������ķ�ʽ������������ 
void HufmanTree(Hfmnode*&h,int*counts)
{//h:���������ڵ����飬counts:ÿ��Ҷ�ӽڵ���ִ��� 
	h=new Hfmnode[N*2-1];//����2*N-1�����������ڵ�
	if(!h)
	{
		cout<<"�ռ�����ʧ�ܣ�"<<endl;
		exit(0); 
	} 
	for(int i=0;i<2*N-1;i++)//��ÿ���ڵ��ʼ�� 
	{
		h[i].weight=0;
		h[i].parent=-1;
		h[i].lchild=-1;
		h[i].rchild=-1;
		h[i].c='\0';
	}
	for(int i=0;i<N;i++)//��ʼ������������Ҷ�ӽڵ� 
	{//������Ÿ�ֵ
		if(i<26)   
			h[i].c = i + 'a';//[a,z]
		else if(i<52&&i>=26)
			h[i].c = i + 'A'-26;//[A,Z]
		else
		{
			switch(i)//�������Լ��հ��ַ� 
			{
				case 52:h[i].c=' ';break;
				case 53:h[i].c=',';break;
				case 54:h[i].c='.';break;
				case 55:h[i].c='\n';break;
				case 56:h[i].c='(';break;
				case 57:h[i].c=')';break;
			}
		}
		h[i].weight=counts[i];//ÿ��Ҷ�ӽڵ��Ȩ��ʵ���������ĵ��г��ֵĴ��� 
	}
	for(int i=0;i<N-1;i++)//��N-1����Ҷ�ӽڵ� 
	{
		int min1,min2,x1,x2; 
		x1=x2=-1;
		min1=min2=MAX;
		//min1,min2��ʾǰN+i���ڵ�Ȩ����С��������
		//x1,x2��ʾ��СȨ�������ڵ�ı�� 
		//min1<min2<others| h[x1].weight<h[x2].weight
		//��ȡN+i���ڵ���Ȩ����С�������ڵ� 
		for(int j=0;j<N+i;j++)
		{ 
			if(h[j].weight<min1 && h[j].parent==-1)
			{//parent=-1��û�г�Ϊ��֦��Ҷ�� 
				min2=min1;
				x2=x1;
				min1=h[j].weight;
				x1=j;
			}
			else if(h[j].weight<min2&&h[j].parent==-1)
			{
				
				min2=h[j].weight;
				x2=j;
			}
		}
		//����ÿ���ڵ���Ϣ, ������Ϣ�洢���ڵ�������
		//ȷ�����׺��ӹ�ϵ�����㸸�ڵ�Ȩ�� 
		h[x1].parent=N+i; 
		h[x2].parent=N+i; 
		h[N+i].lchild=x1;
		h[N+i].rchild=x2;
		h[N+i].weight=h[x1].weight+h[x2].weight;
	}
}
//���������룬����Ҷ�ӽڵ��λ��, ����·��0��1������䵽����������
void  HuffmandeCode(Hfmnode*h, int* counts, Hfmcode*& hcode)
{//h:���������ڵ����飬counts:ÿ��Ҷ�ӽڵ��Ȩ�� 
 //hcode:�����洢����������ṹ������ 
	int i,j,t,parent;
	char codestr[M]={'\0'};//�ݴ����鸳��ֵ 
	hcode=new Hfmcode[N];//����ռ� 
	if(!hcode)
	{
		cout<<"�ռ�����ʧ�ܣ�"<<endl;
		exit(0);
	}
	for(i=0;i<N;i++)//����Ҷ�ӽڵ� 
	{
		j=0;
		parent=h[i].parent;//��¼��ǰ�ڵ�ĸ���
		t=i; 
		while(1)//ǰһ��parent�Ѿ�Ϊ���ڵ� 
		{ 
			if(h[parent].lchild==t)//����·�����Ҵ��µ��ϴ洢0��1 
				codestr[j]='0';
			else
				codestr[j]='1';
			j++;
			t=parent;
			if(h[t].parent==-1)//�Ѿ�������ڵ� 
				break; 
			parent=h[parent].parent;
		}
		hcode[i].bit=new char[j+1];//����j+1���ռ�洢��i��Ҷ�ӽڵ���Ϣ 
		hcode[i].bit[j]='\0';//ĩβ��\0 
		//codestr��Ҷ�ӽڵ㵽���ڵ������˳���෴������洢
		for(int k=0;k<j;k++)  
		{
			hcode[i].bit[k]=codestr[j-k-1];
		}
	}
	fstream outfile;
	outfile.open("Huffman\\Huffman.txt", ios::out);
	if(!outfile)
	{
		cout<<"�ļ���ʧ�ܣ�"<<endl;
		exit(0);
	}
	for(i=0;i<N;i++)//�����ļ������ 
	{
		if(i==52)//�ո� 
		{
			cout<<"\\40";//�������Ļ 
			outfile<<"\\40:\t";//������ļ� 
		}
		else if(i==55)//���з� 
		{
			cout<<"\\n";
			outfile<<"\\n:\t";
		}
		else//�������� 
		{
			cout<<h[i].c;
			outfile<<h[i].c<<":\t";
		}
		cout<<"\t:"<<"����"<<counts[i]<<"��\t"<<"����Ϊ��"; 
		cout<<hcode[i].bit;//������� 
		outfile<<hcode[i].bit<<"     "<<counts[i]<<endl;
		cout<<endl;
	}
	outfile.close(); 
}
//���� 
void transcode(char*s,Hfmcode*hcode)//string->code 
{// s:�ַ�����hcode����� 
	int index;//���ñ������� 
	cout<<"\n"<<s<<" ��Ӧ�Ĺ���������Ϊ��"<<endl; 
	for(int i=0;i<strlen(s);i++)//����ÿһ���ַ�,�������� 
	{
		if(s[i]<='z'&&s[i]>='a')
			index=s[i]-'a';
		else if(s[i]<='Z'&&s[i]>='A')
			index=s[i]-'A'+26;
		else
		{
			switch(s[i])
			{
				case ' ':index=52;break;
				case ',':index=53;break;
				case '.':index=54;break;
				case '\n':index=55;break;
				case '(':index=56;break;
				case ')':index=57;break;
			}	
		} 
		cout<<hcode[index].bit;//����ַ�������������� 
	}
	cout<<endl;
}
//���ļ�ǰn�ν��б��� 
void traslate(Hfmcode*hcode)
{//hcode:����������� 
	fstream file,outfile,Datfile;
	char ch;
	cout<<"�����������£�"<<endl;
	outfile.open("Huffman\\code2.txt",ios::out);
	if(!outfile)
	{
		cout<<"�ļ���ʧ�ܣ�"<<endl;
		exit(0); 
	}
    Datfile.open("Huffman\\code.dat",ios::out);
    if(!Datfile)
    {
        cout<<"���ļ�ʧ�ܣ�"<<endl;
        exit(0);
    }
	file.open("Huffman\\source.txt",ios::in);
	if(!file)
	{
		cout<<"�ļ���ʧ�ܣ�"<<endl;
		exit(0); 
	}
	char cch[8];
	int index;//��Ӧ���������������� 
	while(!file.eof())
	{
		file.get(ch);//�����ȡ�ַ��������հ��ַ� ��Ȼ��������� 
        if(file.fail())
        {
            break;
        }
		if(ch<='z'&&ch>='a')
			index=ch-'a';
		else if(ch<='Z'&&ch>='A')
			index=ch-'A'+26;
		else
		{
			switch(ch)
			{
				case ' ':index=52;break;
				case ',':index=53;break;
				case '.':index=54;break;
				case '\n':index=55;break;
				case '(':index=56;break;
				case ')':index=57;break;
			}	
		} 
		Datfile.write((char*)hcode[index].bit,sizeof(hcode[index].bit));//�����������浽�������ļ�
		outfile<<hcode[index].bit;//д���ļ� 
		cout<<hcode[index].bit;//�������ʾ�� 
	}
	cout<<endl; 
	file.close();
	outfile.close(); 

}
//����������
void  HuffmanenCode(Hfmnode* h)//code->string 
{//h������������ 
	int child=N*2-2;//2*N-2�Ǹ��ڵ�����
    char ch;
	fstream file;
	file.open("Huffman\\code2.txt",ios::in);
	if(!file)
	{
		cout<<"�ļ���ʧ�ܣ�"<<endl;
		exit(0);
	}
	cout<<"�����������£�"<<endl;
	while(!file.eof())
	{
		file>>ch; //���ļ������ַ���ȡ0��1 ����ͷ������ֱ��Ҷ�ӽڵ� 
        if(file.fail())
        {
            break;
        }
		if(ch=='0')//0��1��
			child=h[child].lchild;
		else if(ch=='1')
			child=h[child].rchild;
		if(h[child].lchild==-1 && h[child].rchild==-1)//Ҷ�ӽڵ� 
		{
			cout<<h[child].c;//���ҵĶ�Ӧ��Ҷ�ӽڵ� 
			child=N*2-2;//���»ص����ڵ�
		}
		
	}
	file.close();
}
int main()
{
    cout<<"         Huffman������������չʾ"<<endl;
	int* counts;//�ַ����� 
	//char s[]="Data Structure";
	Hfmnode*h;//�������� 
	Hfmcode* hcode;//����������
	 
	get_ch_count(counts);//ͳ���ַ����� 
	HufmanTree(h,counts);//������������ 
	HuffmandeCode(h,counts,hcode);//���������� 
	
	traslate(hcode);//����ȫ�� 
	HuffmanenCode(h);//����ȫ��
	
	delete counts;//�ͷſռ� 
	delete hcode;
	delete h; 
	
	return 0;
}

