#include<iostream>
#include<fstream>
#include<time.h>
#include<queue> 
using namespace std;
//�˴������㷨ʱ�仨�ѱȽ�
void InsertSort(int *L);    //ֱ�Ӳ�������
void ShellSort(int *L); //ϣ������
void MaopaoSort(int *L);    //ð������
void Quicksort(int *L); //��������
int Partition(int p[],int low,int high);    //����һ�˿���
void Qsort(int p[],int low,int high);    //���ŵĵݹ�

void SelectSort(int *L);    //ѡ������

void THeapSort(int *L);  //������
void Heapadjust(int *p,int low,int high);   //�ѵ������㷨
void HeapSort(int *p,int high);  //���������㷨

void GuibingSort(int *L);   //�鲢�����㷨
void sortArr(int arr[],int low,int hight);    //��ֹ��� 
void mergeArr(int arr[],int low,int mid,int hight);  //�ϲ����������

void RadixSort(int *L); //��������

int main()
{
    fstream file;
    file.open("C:\\Codefield\\CODE_C\\CDesign\\KindsSort\\NumZxu.txt",ios::in);
    int arc[50001];
    int js=1;
    while(!file.eof())  //����Щ����ֱ�Ӷ�����������ȥ���
    {
        file>>arc[js];  //
        js++;
    }
    cout<<"ֱ�Ӳ����������õ�ʱ�䣺"<<endl;     //1
    clock_t start=clock();  //����ʼ��ʱ��
    InsertSort(arc);
    clock_t end=clock();    //���������ʱ��
    cout<<"����ʱ�䣺"<<(double)(end-start)/CLOCKS_PER_SEC*1000<<"ms"<<endl;
    cout<<endl; //CLOCKS_PER_SEC��ָ��һ����"�δ𼸴�",���Ժ�õ���������!!!

    cout<<"ϣ���������õ�ʱ�䣺"<<endl;     //2         
    start=clock();  //����ʼ��ʱ��
    ShellSort(arc);
    end=clock();    //���������ʱ��
    cout<<"����ʱ�䣺"<<(double)(end-start)/CLOCKS_PER_SEC*1000<<"ms"<<endl;
    cout<<endl; //CLOCKS_PER_SEC��ָ��һ����"�δ𼸴�",���Ժ�õ���������!!!

    cout<<"ð���������õ�ʱ�䣺"<<endl;     //3
    start=clock();  //����ʼ��ʱ��
    MaopaoSort(arc);
    end=clock();    //���������ʱ��
    cout<<"����ʱ�䣺"<<(double)(end-start)/CLOCKS_PER_SEC*1000<<"ms"<<endl;
    cout<<endl; //CLOCKS_PER_SEC��ָ��һ����"�δ𼸴�",���Ժ�õ���������!!!

    cout<<"�����������õ�ʱ�䣺"<<endl;     //4
    start=clock();  //����ʼ��ʱ��
    Quicksort(arc);
    end=clock();    //���������ʱ��
    cout<<"����ʱ�䣺"<<(double)(end-start)/CLOCKS_PER_SEC*1000<<"ms"<<endl;
    cout<<endl; //CLOCKS_PER_SEC��ָ��һ����"�δ𼸴�",���Ժ�õ���������!!!

    cout<<"ѡ���������õ�ʱ�䣺"<<endl;     //5
    start=clock();  //����ʼ��ʱ��
    SelectSort(arc);
    end=clock();    //���������ʱ��
    cout<<"����ʱ�䣺"<<(double)(end-start)/CLOCKS_PER_SEC*1000<<"ms"<<endl;
    cout<<endl; //CLOCKS_PER_SEC��ָ��һ����"�δ𼸴�",���Ժ�õ���������!!!

    cout<<"���������õ�ʱ�䣺"<<endl;       //6
    start=clock();  //����ʼ��ʱ��
    THeapSort(arc);
    end=clock();    //���������ʱ��
    cout<<"����ʱ�䣺"<<(double)(end-start)/CLOCKS_PER_SEC*1000<<"ms"<<endl;
    cout<<endl; //CLOCKS_PER_SEC��ָ��һ����"�δ𼸴�",���Ժ�õ���������!!!

    cout<<"�鲢�������õ�ʱ�䣺"<<endl;     //7
    start=clock();  //����ʼ��ʱ��
    GuibingSort(arc);
    end=clock();    //���������ʱ��
    cout<<"����ʱ�䣺"<<(double)(end-start)/CLOCKS_PER_SEC*1000<<"ms"<<endl;
    cout<<endl; //CLOCKS_PER_SEC��ָ��һ����"�δ𼸴�",���Ժ�õ���������!!!

    cout<<"�����������õ�ʱ�䣺"<<endl;     //8
    start=clock();  //����ʼ��ʱ��
    RadixSort(arc);
    end=clock();    //���������ʱ��
    cout<<"����ʱ�䣺"<<(double)(end-start)/CLOCKS_PER_SEC*1000<<"ms"<<endl;
    cout<<endl; //CLOCKS_PER_SEC��ָ��һ����"�δ𼸴�",���Ժ�õ���������!!!

    file.close();
    return 0;
} 

void InsertSort(int *L)    //ֱ�Ӳ�������
{
    int p[50001];  //��ֵ������������б���ԭ�����ݱ�����
    for(int i=1;i<=50000;i++)
    {
        p[i]=L[i];  
    }
    for(int i=2;i<=50000;i++)   //�ӵڶ�����ʼ������������
    {
        p[0]=p[i];  //0��Ϊ�ڱ�ȥ������ʱ����
        int j;
        for(j=i;j>1;j--)    //j�Ǽ�¼�������ֵ�÷�������
        {
            if(p[0]<p[j-1]) //��С����ǰ���ƶ�
            {
                p[j]=p[j-1];
            }
            else
            {
                break;
            }
        }
        p[j]=p[0];
    }
    fstream file;
    file.open("KindsSort\\Insert.txt",ios::out);
    for(int i=1;i<=50000;i++)
    {
        file<<p[i]<<endl;
    }
    file.close();
}

void ShellSort(int *L) //ϣ������
{
    int p[50001];  //��ֵ������������б���ԭ�����ݱ�����
    for(int i=1;i<=50000;i++)
    {
        p[i]=L[i];  
    }    
    int k;
    for(k=12501;k>=1;k=k-500)
    {       
        int i;
        for(i=1+k;i<=50000;i++)
        {
            if(p[i]<p[i-k]) //��֮ǰ��С����Ҫ���в�������
            {
                p[0]=p[i];
                int j;
                for(j=i;j>k;j=j-k)
                {
                    if(p[0]<p[j-k])
                    {
                        p[j]=p[j-k];
                    }
                    else 
                    {
                        break;
                    }
                }
                p[j]=p[0];  //��ʱ��jλ�þ���p[0]�÷��õ�λ��!!!
            }
        }
    }
    fstream file;
    file.open("KindsSort\\Shell.txt",ios::out);
    for(int i=1;i<=50000;i++)
    {
        file<<p[i]<<endl;
    }
    file.close();
}

void MaopaoSort(int *L)    //ð������
{
    int p[50001];  //��ֵ������������б���ԭ�����ݱ�����
    for(int i=1;i<=50000;i++)
    {
        p[i]=L[i];  
    }   
    for(int i=1;i<50000;i++)  //ð���������
    {
        int temp=0;
        for(int j=i+1;j<=50000;j++)
        {
            if(p[i]>p[j])
            {
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
    fstream file;
    file.open("KindsSort\\Maopao.txt",ios::out);
    for(int i=1;i<=50000;i++)
    {
        file<<p[i]<<endl;
    }
    file.close();
}

void SelectSort(int *L)    //ѡ������
{
    int p[50001];  //��ֵ������������б���ԭ�����ݱ�����
    for(int i=1;i<=50000;i++)
    {
        p[i]=L[i];  
    }  
    for(int i=1;i<=50000;i++)  //ѡ������ĺ���
    {
        int k=i;
        int temp=0;
        for(int j=i+1;j<=50000;j++)
        {
            if(p[k]>p[j]) 
            {
                k=j;    
            }
        }
        if(i!=k)
        {
            temp=p[i];
            p[i]=p[k];
            p[k]=temp;
        }
    }
    fstream file;
    file.open("KindsSort\\Select.txt",ios::out);
    for(int i=1;i<=50000;i++)
    {
        file<<p[i]<<endl;
    }
    file.close();
}

void Quicksort(int *L) //��������
{
    int p[50001];  //��ֵ������������б���ԭ�����ݱ�����
    for(int i=1;i<=50000;i++)
    {
        p[i]=L[i];  
    } 
    Qsort(p,1,50000);
    fstream file;
    file.open("KindsSort\\Qsort.txt",ios::out);
    for(int i=1;i<=50000;i++)
    {
        file<<p[i]<<endl;
    }
    file.close();
}
int Partition(int p[],int low,int high)    //����һ�˿���
{
    p[0]=p[low];    //0����Ϊ��ʱ��ŵ�
    while(low<high)
    {
        while(low<high&&p[high]>=p[0])
        {
            high--;
        }
        p[low]=p[high]; //������ؼ��������ֵ�����,low��ʱ�ǿ��Ա�ռ�õ�
        while(low<high&&p[low]<=p[0])
        {
            low++;
        }
        p[high]=p[low]; //high���ֵ֮ǰ�Ѿ�������,���Դ�ʱ�ǿ��Ա�ռ�õ�
    }
    p[low]=p[0];
    return low;
}
void Qsort(int p[],int low,int high)    //���ŵĵݹ�
{
    int linshi;   
    if(low<high)    //���������еݹ�����
    {
        linshi=Partition(p,low,high);  
        Qsort(p,low,linshi-1);
        Qsort(p,linshi+1,high);
    }
}

void THeapSort(int *L)  //������
{
    int p[50001];  //��ֵ������������б���ԭ�����ݱ�����
    for(int i=1;i<=50000;i++)
    {
        p[i]=L[i];  
    } 
    HeapSort(p,50000);
    fstream file;
    file.open("KindsSort\\HeapSort.txt",ios::out);
    for(int i=1;i<=50000;i++)
    {
        file<<p[i]<<endl;
    }
    file.close();

}
void Heapadjust(int *p,int low,int high)   //�ѵ������㷨
{
    p[0]=p[low];    //�������¿�ʼɸѡ
    int i=low;
    int j=2*i;
    while(j<=high)  //�����濪ʼ����ɸѡ
    {
        if(j+1<=high&&p[j+1]<p[j])  //ѡ����������и�С�Ĳ���
        {
            j++;
        }
        //ʼ���ǽ��ʼ�ĸ��ڵ�ȥ�Ƚ�Ϊ���ҵ�����ʵ�λ��
        if(p[0]<p[j])   //�Ѿ���С����
        {
            break;
        }
        else    //����С���Ѿͽ�С��ֵ��ֵ��������ڵ�,Ȼ�������������е���
        {
            p[i]=p[j];
            i=j;    //�����ֵ���С��ֵ���н�������
            j=i*2;  //���������濪ʼ�ж��Ƿ�����С����
        }
    }
    p[i]=p[0];
}
void HeapSort(int *p,int high)  //���������㷨
{
    for(int i=high/2;i>0;i--)  //������ѵ������濪ʼ�������Ͻ��жѵ���
    {
        Heapadjust(p,i,high);   //�Ѷ����������������,��βʼ����ĩβ
    }
    //�������ⲽֻ�ǹ�����һ��С����,���黹���Ǵ�С��������,����Ҫ�Ÿ���

    for(int i=high;i>1;i--) //����С���ѵ����ݴ�����ĩβ��С��������˴洢
    {
        p[0]=p[1];
        p[1]=p[i];  //���Ѷ������һ�������滻
        p[i]=p[0];  //���Զ��������һ������
        Heapadjust(p,1,i-1);
    }
}

void GuibingSort(int *L)   //�鲢�����㷨
{
    int p[50001];  //��ֵ������������б���ԭ�����ݱ�����
    for(int i=1;i<=50000;i++)
    {
        p[i]=L[i];  
    } 
    sortArr(p,1,50000);
    fstream file;
    file.open("KindsSort\\sorrArr.txt",ios::out);
    for(int i=1;i<=50000;i++)
    {
        file<<p[i]<<endl;
    }
    file.close();
}
void sortArr(int arr[],int low,int hight)    //��ֹ��� 
{
    if(low==hight)
    {
        arr[low]=arr[hight];
    }
	else
    {
		int mid=(hight+low)/2;
		sortArr(arr,low,mid);   //�Ȳ��ǰ�벿��
		sortArr(arr,mid+1,hight);   //�ٲ���벿��
		mergeArr(arr,low,mid,hight); //���ⲿ�ֵ�ֵ���г�Ϊ����������
	}
}
void mergeArr(int arr[],int low,int mid,int hight)  //�ϲ����������
{
    int*p=new int[hight-low+1]; //�ø���������кϲ�����,���ϲ������������ԭ�����м�ʱ����!!!
	int i=low;  //low��һ����0,��Ϊһ����ʼ��λ��
    int j=mid+1;    //�ڶ������鿪ʼ��λ��
    int k=0;    //���������0��ʼ����
	while (i <= mid && j <= hight) 
    {
		if (arr[i]<=arr[j])     //��ȡС��ֵ
        {
			p[k]=arr[i];
			i++;
		}
		else 
        {
			p[k]=arr[j];
			j++;
		}
		k++;    //һ���Ժ��������±�ҲҪ�����ƶ�һλ
	}
	while (i<=mid)    //ʣ�µĶ��Ǵ��ֱ�Ӹ�ֵ�������
    {
		p[k]=arr[i];
		i++;
		k++;
	}
	while (j<=hight) //ʣ�µĶ��Ǵ��ֱ�Ӹ�ֵ�������
    {
		p[k]=arr[j];
		j++;
		k++;
	}
	i=low;   
	for (int num=0;num<k;num++) //����ʱ�����źõ�˳����ԭ����֮�м�ʱ����!!! 
    {
		arr[i]=p[num];
		i++;
	}
	delete[] p;
}

void RadixSort(int *L) //��������
{
    int p[50001];  //��ֵ������������б���ԭ�����ݱ�����
    for(int i=1;i<=50000;i++)
    {
        p[i]=L[i];  
    } 
    queue<int> Duilie[10];  //����һ����������,����λ��ֵ������ͬ��С���±��Ӧ�Ķ�����!!!
    int radix=1;
    for(int k=1;k<=5;k++)   //���λ����λ,��ʼ���м�������
    {
        radix=radix*10;
        for(int i=1;i<=50000;i++)   //ÿ����������Ӧ�±�����Ӧ�Ķ���
        {
            int x;
            x=(p[i]%radix)/(radix/10);   //ȷ����ȡ���ض�λ�õ�ֵ
            Duilie[x].push(p[i]);   //�����ֵ���
        }

        for(int i=1,m=0;m<10;m++)   //һ������֮��˳������ռ�!!!
        {
            while(!Duilie[m].empty())   //���в�Ϊ�վͼ�����ֵ
            {
                p[i]=Duilie[m].front();
                Duilie[m].pop();
                i++;
            }
        }
    }
    fstream file;
    file.open("KindsSort\\Radixsort.txt",ios::out);
    for(int i=1;i<=50000;i++)
    {
        file<<p[i]<<endl;
    }
    file.close();
}
