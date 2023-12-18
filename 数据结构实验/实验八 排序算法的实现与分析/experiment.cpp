#include<cstdio>
#include<cstdlib>
#include<vector>
#include<iostream>
using namespace std;

typedef  struct
{
    char  name[8];
    double  score;
} student;

//  冒泡排序算法
void InsertSort(vector<student>& a, int n)
{
    int i, j, flag;
    student temp;
    for (i = 0; i < n - 1; i++)
    {
        flag = 0;
        for (j = 0; j < n - i - 1; j++)
        {
            if (a[j].score < a[j + 1].score)
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                flag = 1;
            }
        }
        if (flag == 0)  break;
    }
}

//  插入排序算法
void CharuSort(vector<student>& a, int n)
{
    student temp;
    int j;
    for (int i = 1; i < n; i++)
    {
        if (a[i].score > a[i - 1].score)
        {
            temp = a[i];
            for (j = i - 1; j >= 0 && temp.score > a[j].score; j--)
            {
                a[j + 1] = a[j];
            }
            a[j + 1] = temp;
        }
    }
}

//  简单选择排序
void SelectionSort(vector<student> &a, int n)
{
    int i, j, k;
    student temp;
    for (i = 0; i < n; i++)
    {
        k = i;
        for (j = i; j < n; j++)
        {
            if (a[j].score > a[k].score)  k = j;
        }
        if (k != i)
        {
            temp = a[i];
            a[i] = a[k];
            a[k] = temp;
        }
    }
}

void myprint(vector<student> &a, int n)
{
    int t;
    printf("第%d名:   %s   %.2lf\n", 1, a[0].name, a[0].score);
    t = 1;
    for (int i = 1; i < n; i++)
    {
        if (a[i].score == a[i - 1].score)
        {
            printf("第%d名:   %s   %.2lf\n", t, a[i].name, a[i].score);
        }
        else
        {
            t = i + 1;
            printf("第%d名:   %s   %.2lf\n", t, a[i].name, a[i].score);
        }
    }
}

int main()
{
    int n, i, k;
    vector<student> a;
    student temp;
    cin >> temp.name >> temp.score;
    while (temp.name[0]!='0')
    {
        a.push_back(temp);
        cin >> temp.name >> temp.score;
    }
    n = a.size();
   
    k = 1;
    printf("排序结果输出如下:\n");
    switch (k)
    {
    case 1:
        InsertSort(a, n);
        break;
    case 2:
        SelectionSort(a, n);
        break;
    case 3:
        CharuSort(a, n);
        break;
    }
    myprint(a, n);
    
    return 0;
}

