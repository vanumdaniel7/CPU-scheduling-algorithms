#include<bits/stdc++.h>
#include<fstream>
#include "CPU_SCHEDULING.h"
#include "PROCESS.h"
#include "Cryptography.h"
#include "Cryptography.cpp"

using namespace std;
using example::PROCESS;
using example::encdec;

bool File_Exist(string filename)
{
    fstream in(filename,ios::in);
    if(!in)
    {
        std::cout<<"\nThe File does not exist."<<endl;
        std::cout<<endl;
        return false;
    }
    std::cout<<endl;
    std::cout<<"\n-Reading Input from the File...\n\n";
    return true;
}

/*SORTING COMPARATORS*/

bool sortbyAT(PROCESS a,PROCESS b)
{
    return a.AT < b.AT;
}

bool sortbyBT(PROCESS a,PROCESS b)
{
    if(a.BT == b.BT)
        return a.AT < b.AT;

    return a.BT < b.BT;
}

bool sortbyPID(PROCESS a,PROCESS b)
{
    return a.PID < b.PID;
}
/* Input Function*/

void output_terminal(PROCESS p[],int n)
{
   cout<<"PID\t"<<"AT\t"<<"BT\t"<<"\n\n";
   for(int i=0;i<n;i++)
    {
        cout<<"P"<<p[i].PID<<"\t"<<p[i].AT<<"\t"<<p[i].BT<<"\t"<<endl;
    }
}
/* Output Function */

void Output(PROCESS p[],int n)
{
    double avg_TAT = 0,avg_WT = 0;

    for(int i=0;i<n;i++)
	{
        avg_TAT += p[i].TAT;
    	avg_WT += p[i].WT;
	}

    fstream cout("Output.txt",ios::out);

    cout<<"PID\t"<<"AT\t"<<"BT\t"<<"CT\t"<<"TAT\t"<<"WT\n\n";

    for(int i=0;i<n;i++)
    {
        cout<<"P"<<p[i].PID<<"\t"<<p[i].AT<<"\t"<<p[i].BT<<"\t"<<p[i].CT<<"\t"<<p[i].TAT<<"\t"<<p[i].WT<<endl;
    }
    cout<<endl;

	cout<<"Total Turn Around Time is "<<avg_TAT<<endl;
    cout<<"Average Turn Around Time is "<<avg_TAT/n<<endl;
    cout<<endl;

    cout<<"Total Waiting Time is "<<avg_WT<<endl;
    cout<<"Average Waiting Time is "<<avg_WT/n<<endl;
    cout<<endl;

    cout.close();
}

/* 1.) FIRST COME FIRST SERVE */

void FCFS()
{
    string file_name;
    std::cout<<"\nEnter the Input File Name with Extension : ";
    cin>>file_name;

    if(!File_Exist(file_name))
    {
        return;
    }

    fstream cin(file_name,ios::in);
    int n;
    cin>>n;

    PROCESS p[n];

    for(int i=0;i<n;i++)
    {
        p[i].PID = i+1;
        cin>>p[i].AT;
        cin>>p[i].BT;
    }

    cout<<"-Input read from File.\n\n";
    cin.close();
    output_terminal(p,n);
    cout<<"\nScheduling the Input data using FCFS Policy...\n";

    sort(p,p+n,sortbyAT);

    p[0].CT = p[0].AT+p[0].BT;

    for(int i=1;i<n;i++)
    {
        if(p[i-1].CT < p[i].AT)
        {
            p[i].CT = p[i].AT+p[i].BT;
        }
        else
        {
            p[i].CT = p[i-1].CT+p[i].BT;
        }
    }

    for(int i=0;i<n;i++)
	{
		p[i].TAT = p[i].CT-p[i].AT;
	}
	for(int i=0;i<n;i++)
	{
		p[i].WT = p[i].TAT-p[i].BT;
	}
	sort(p,p+n,sortbyPID);

    cout<<"\n--Scheduling Completed.\n\n";


    Output(p,n);

    encdec enc;
    enc.encrypt();
    enc.decrypt();
}

/* 2.) SHORTEST JOB FIRST */

void SJF()
{
    string file_name;
    std::cout<<"\nEnter the Input File Name with Extension : ";
    cin>>file_name;

    if(!File_Exist(file_name))
    {
        return;
    }

    fstream cin(file_name,ios::in);
    int n;
    cin>>n;

    PROCESS p[n];

    for(int i=0;i<n;i++)
    {
        p[i].PID = i+1;
        cin>>p[i].AT>>p[i].BT;
    }

    cout<<"-Input Read From File.\n\n";
    cin.close();
    output_terminal(p,n);
    cout<<"\nScheduling the Input data using SJF Policy...\n";

    sort(p,p+n,sortbyBT);

    int d;
    int mini = p[0].AT;

    for(int i=0;i<n;i++)
    {
        if(mini>p[i].AT)
        {
            mini=p[i].AT;
            d=i;
        }
    }

    int tt=mini;
    p[d].CT = tt+p[d].BT;
    tt = p[d].CT;

    for(int i=0;i<n;i++)
    {
        if(p[i].AT != mini)
        {
            p[i].CT = p[i].BT+tt;
            tt = p[i].CT;
        }
    }

    for(int i=0;i<n;i++)
    {
        p[i].TAT = p[i].CT-p[i].AT;
        p[i].WT = p[i].TAT - p[i].BT;
    }

	sort(p,p+n,sortbyPID);

    cout<<"\n--Scheduling Completed.\n\n";


    Output(p,n);

    encdec enc;
    enc.encrypt();
    enc.decrypt();
}

/* 3.) SHORTEST REMAINING TIME FIRST */

void SRTF()
{
    string file_name;
    std::cout<<"\nEnter the Input File Name with Extension : ";
    cin>>file_name;

    if(!File_Exist(file_name))
    {
        return;
    }

    fstream cin(file_name,ios::in);
    int n;
    cin>>n;

    PROCESS p[n];

    for(int i=0;i<n;i++)
    {
        p[i].PID = i+1;
        cin>>p[i].AT>>p[i].BT;
        p[i].RT = p[i].BT;
    }

    cout<<"-Input Read From File.\n\n";
    cin.close();
    output_terminal(p,n);
    cout<<"\nScheduling the Input data using SRTF Policy...\n";

    int current_time = 0;
    int completed = 0;
    int prev = 0;

    while(completed != n)
    {
        int idx = -1;
        int mn = 10000000;
        for(int i=0;i<n;i++)
        {
            if(p[i].AT <= current_time && p[i].check == 0)
            {
                if(p[i].RT < mn)
                {
                    mn = p[i].RT;
                    idx = i;
                }
                if(p[i].RT == mn)
                {
                    if(p[i].AT < p[idx].AT)
                    {
                        mn = p[i].RT;
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1)
        {
            p[idx].RT -= 1;
            current_time++;
            prev = current_time;

            if(p[idx].RT == 0)
            {
                p[idx].CT = current_time;
                p[idx].TAT = p[idx].CT - p[idx].AT;
                p[idx].WT = p[idx].TAT - p[idx].BT;

                p[idx].check = 1;
                completed++;
            }
        }
        else
        {
             current_time++;
        }

    }

    cout<<"\n--Scheduling Completed.\n\n";


    Output(p,n);

    encdec enc;
    enc.encrypt();
    enc.decrypt();
}

/* 4.) PRIORITY BASED NON PRE-EMPTIVE */

void PRIORITY_NP()
{
    string file_name;
    std::cout<<"\nEnter the Input File Name with Extension : ";
    cin>>file_name;

    if(!File_Exist(file_name))
    {
        return;
    }

    fstream cin(file_name,ios::in);
    int n;
    cin>>n;
    PROCESS p[n];
    for(int i=0;i<n;i++)
    {
        p[i].PID = i+1;
        cin>>p[i].AT>>p[i].BT;
        cin>>p[i].priority;
        p[i].RT = p[i].BT;
    }

    cout<<"-Input Read From File.\n\n";
    cin.close();
    cout<<"PID\t"<<"AT\t"<<"BT\t"<<"Priority no\n";
    for(int i=0;i<n;i++)
    {
        cout<<"P"<<p[i].PID<<'\t'<<p[i].AT<<'\t'<<p[i].BT<<'\t'<<p[i].priority<<'\n';
    }
    cout<<"\nScheduling the Input data using Priority_NP Policy...\n";

    sort(p,p+n,sortbyAT);

    int completed = 0,k = 0,prev = 0,f = 0,next = 0,nexts = 0;
    int pr = p[0].priority;

    while(completed != n)
    {
        p[k].ST = max(p[k].AT,p[prev].CT);
        p[k].CT = p[k].ST+p[k].BT;
        p[k].TAT = p[k].CT-p[k].AT;
        p[k].WT = p[k].TAT-p[k].BT;
        p[k].check = 1;
        completed++;
        prev = k;

        for(int i=0;i<n;i++)
        {
            if(p[i].AT <= p[i].CT && p[i].check == 0)
            {
                if(p[i].priority > pr)
                {
                    pr = p[i].priority;
                    next = i;
                }
                else if(p[i].priority == pr)
                {
                    if(p[k].AT > p[i].AT)
                    {
                        nexts = k;
                        next = i;
                        f = 1;
                    }
                }
            }
        }
        if(p[next].priority == pr && p[next].check == 1)
        {
            if(f == 1)
            {
                next = nexts;
                f = 0;
            }
            else
            {
                pr = 0;
                for(int i=0;i<n;i++)
                {
                    if(p[i].AT <= p[k].CT && p[i].check == 0)
                    {
                        if(p[i].priority > pr)
                        {
                            pr = p[i].priority;
                            next = i;
                        }
                    }
                }
            }
        }
        k = next;
    }

    cout<<"\n--Scheduling Completed.\n\n";

    Output(p,n);

    encdec enc;
    enc.encrypt();
    enc.decrypt();
}

/* 5.) PRIORITY BASED PRE-EMPTIVE */

void PRIORITY_P()
{
    string file_name;
    std::cout<<"\nEnter the Input File Name with Extension : ";
    cin>>file_name;

    if(!File_Exist(file_name))
    {
        return;
    }

    fstream cin(file_name,ios::in);
    int n;
    cin>>n;

    PROCESS p[n];
    for(int i=0;i<n;i++)
    {
        p[i].PID = i+1;
        cin>>p[i].AT>>p[i].BT;
        cin>>p[i].priority;
        p[i].RT = p[i].BT;
    }

    cout<<"-Input Read From File.\n\n";
    cin.close();
    cout<<"PID\t"<<"AT\t"<<"BT\t"<<"Priority no\n";
    for(int i=0;i<n;i++)
    {
        cout<<"P"<<p[i].PID<<'\t'<<p[i].AT<<'\t'<<p[i].BT<<'\t'<<p[i].priority<<'\n';
    }
    cout<<"\nScheduling the Input data using Priority_P Policy...\n";

    int current_time = 0,completed = 0,prev = 0;
    while(completed != n)
    {
        int index = -1;
        int maxi = -1;
        for(int i=0;i<n;i++)
        {
            if(p[i].AT <= current_time && p[i].check == 0)
            {
                if(p[i].priority > maxi)
                {
                    maxi = p[i].priority;
                    index = i;
                }
                if(p[i].priority == maxi)
                {
                    if(p[i].AT < p[index].AT)
                    {
                        maxi = p[i].priority;
                        index = i;
                    }
                }
            }
        }
        if(index != -1)
        {
            if(p[index].RT == p[index].BT)
            {
                p[index].ST = current_time;
            }

            p[index].RT -= 1;
            current_time++;
            prev=current_time;

            if(p[index].RT == 0)
            {
                p[index].CT =  current_time;
                p[index].TAT = p[index].CT-p[index].AT;
                p[index].WT = p[index].TAT-p[index].BT;
                p[index].check = 1;
                completed++;
            }
        }
        else
        {
            current_time++;
        }
    }

    cout<<"\n--Scheduling Completed.\n\n";

    Output(p,n);

    encdec enc;
    enc.encrypt();
    enc.decrypt();
}

/* 6.) ROUND ROBIN */

void RoundRobin()
{
    string file_name;
    std::cout<<"\nEnter the Input File Name with Extension : ";
    cin>>file_name;

    if(!File_Exist(file_name))
    {
        return;
    }

    fstream cin(file_name,ios::in);
    int n;
    cin>>n;

    int TQ;
    cin>>TQ;

    PROCESS p[n];

    for(int i=0;i<n;i++)
    {
        p[i].PID = i+1;
        cin>>p[i].AT>>p[i].BT;
        p[i].RT = p[i].BT;
    }

    cout<<"-Input Read From File.\n\n";
    cin.close();
    cout<<"Time quantum="<<TQ<<'\n';
    output_terminal(p,n);
    cout<<"\nScheduling the Input data using Round Robin Policy...\n";

    sort(p,p+n,sortbyAT);

    int cur_time=0;
    int completed=0;

    queue<int>que;

    que.push(0);
    p[0].check = 1;

    while(completed!=n)
    {
    	int index = que.front();
    	que.pop();

    	if(p[index].RT > TQ)
    	{
    		cur_time += TQ;
    		p[index].RT -= TQ;
    	}
    	else
    	{
    		cur_time += p[index].RT;
    		p[index].RT = 0;
    		completed++;
    		p[index].CT = cur_time;
    		p[index].TAT = p[index].CT-p[index].AT;
    		p[index].WT = p[index].TAT-p[index].BT;
    	}

    	for(int i=1;i<n;i++)
    	{
    		if(p[i].RT>0 && p[i].AT<=cur_time && p[i].check==0)
    		{
    			p[i].check = 1;
    			que.push(i);
    		}
    	}
    	if(p[index].RT>0)
    	que.push(index);

    	if(que.empty())
    	{
    		for(int i=1;i<n;i++)
    		{
    			if(p[i].RT>0)
    			{
    				que.push(i);
    				p[i].check = 1;
    				break;
    			}
    		}
    	}
    }
    sort(p,p+n,sortbyPID);

    cout<<"\n--Scheduling Completed.\n\n";


    Output(p,n);

    encdec enc;
    enc.encrypt();
    enc.decrypt();
}

/* 7.) LONGEST JOB FIRST */

void LJF()
{
    string file_name;
    std::cout<<"\nEnter the Input File Name with Extension : ";
    cin>>file_name;

    if(!File_Exist(file_name))
    {
        return;
    }

    fstream cin(file_name,ios::in);
    int n;
    cin>>n;

    PROCESS p[n];

    for(int i=0;i<n;i++)
    {
        p[i].PID = i+1;
        cin>>p[i].AT>>p[i].BT;
        p[i].RT = p[i].BT;
    }

    cout<<"-Input Read From File.\n\n";
    cin.close();
    output_terminal(p,n);
    cout<<"\nScheduling the Input data using LJF Policy...\n";

    int completed=0;
    int cur_time=0;

    while(completed!=n)
    {
    	int index=-1,maxi=-1;
    	for(int i=0;i<n;i++)
    	{
    		if(p[i].AT <= cur_time && p[i].check == 0)
    		{
    			if(p[i].BT > maxi)
    			{
    				maxi = p[i].BT;
    				index = i;
    			}
    		}
    	}

    	if(index==-1)
    	{
    		cur_time++;
    	}
    	else
    	{
    		cur_time += p[index].BT;
    		p[index].CT = cur_time;
    		p[index].check = 1;
    		p[index].TAT = p[index].CT-p[index].AT;
    		p[index].WT = p[index].TAT-p[index].BT;
    		completed++;
    	}
    }

    cout<<"\n--Scheduling Completed.\n\n";


    Output(p,n);

    encdec enc;
    enc.encrypt();
    enc.decrypt();
}

/* 8.) LONGEST REMAINING TIME FIRST */

void LRTF()
{
    string file_name;
    std::cout<<"\nEnter the Input File Name with Extension : ";
    cin>>file_name;

    if(!File_Exist(file_name))
    {
        return;
    }

    fstream cin(file_name,ios::in);
    int n;
    cin>>n;

    PROCESS p[n];

    for(int i=0;i<n;i++)
    {
        p[i].PID = i+1;
        cin>>p[i].AT>>p[i].BT;
        p[i].RT = p[i].BT;
    }

    cout<<"-Input Read From File.\n\n";
    cin.close();
    output_terminal(p,n);
    cout<<"\nScheduling the Input data using LRTF Policy...\n";

    int completed=0;
    int cur_time=0;

    while(completed!=n)
    {
    	int index=-1,maxi=-1;
    	for(int i=0;i<n;i++)
    	{
    		if(p[i].AT<=cur_time && p[i].check==0)
    		{
    			if(p[i].RT>maxi)
    			{
    				maxi=p[i].RT;
    				index=i;
    			}
    			else if(p[i].RT==maxi)
    			{
    				if(index!=-1)
    				{
    					if(p[i].AT<p[index].AT)
    					{
    						index=i;
    					}
    				}
    			}
    		}
    	}

    	if(index==-1)
    	{
    		cur_time++;
    	}
    	else
    	{
    		p[index].RT--;
    		cur_time++;
    		if(p[index].RT==0)
	    	{
	    		p[index].CT = cur_time;
	    		p[index].check = 1;
	    		p[index].TAT = p[index].CT-p[index].AT;
	    		p[index].WT = p[index].TAT-p[index].BT;
	    		completed++;
	    	}
    	}
    }

    cout<<"\n--Scheduling Completed.\n\n";


    Output(p,n);

    encdec enc;
    enc.encrypt();
    enc.decrypt();
}

/* 9.) HIGHEST RESPONSE RATIO NEXT */

void HRRN()
{
    string file_name;
    std::cout<<"\nEnter the Input File Name with Extension : ";
    cin>>file_name;

    if(!File_Exist(file_name))
    {
        return;
    }

    fstream cin(file_name,ios::in);
    int n;
    cin>>n;

    PROCESS p[n];

    int sum_BT = 0;

    for(int i=0;i<n;i++)
    {
        p[i].PID = i+1;
        cin>>p[i].AT>>p[i].BT;
        sum_BT += p[i].BT;
    }

    cout<<"-Input Read From File.\n\n";
    cin.close();
    output_terminal(p,n);
    cout<<"\nScheduling the Input data using HRRN Policy...\n";

    sort(p,p+n,sortbyAT);

	int time = p[0].AT;

	while(time < sum_BT)
	{
		float HRR = INT_MIN,temp;
		int index;

		for (int i = 0; i < n; i++)
		{

			if (p[i].AT <= time && p[i].check != 1)
			{

				temp = (p[i].BT+(time-p[i].AT))/p[i].BT;

				if (HRR < temp)
				{
					HRR = temp;
					index = i;
				}
			}
		}
		time += p[index].BT;

		p[index].CT = time;
		p[index].WT = time - p[index].AT - p[index].BT;
		p[index].TAT= time - p[index].AT;
		p[index].check = 1;

	}

	sort(p,p+n,sortbyPID);

	cout<<"\n--Scheduling Completed.\n\n";


	Output(p,n);

    encdec enc;
    enc.encrypt();
    enc.decrypt();
}

/* 10.) MULTI LEVEL FEEDBACK QUEUE SCHEDULING */

void MFQS()
{
    string file_name;
    std::cout<<"\nEnter the Input File Name with Extension : ";
    cin>>file_name;
    if(!File_Exist(file_name))
    {
        return;
    }

    fstream cin(file_name,ios::in);
    int n;
    cin>>n;

    int TQ1,TQ2;
	cin>>TQ1>>TQ2;

    queue<int>Q1,Q2,Q3;
    PROCESS p[n];

    for(int i=0;i<n;i++)
    {
        p[i].PID = i+1;
        cin>>p[i].AT>>p[i].BT;
        p[i].RT = p[i].BT;
        Q1.push(i);
    }


    cout<<"-Input Read From File.\n\n";
    cin.close();
    cout<<"Time quantum for queue 1 and queue 2 are="<<TQ1<<" "<<TQ2<<'\n';
    cout<<"PID\t"<<"AT\t"<<"BT\t"<<'\n';
    for(int i=0;i<n;i++)
    {
        cout<<"P"<<p[i].PID<<'\t'<<p[i].AT<<'\t'<<p[i].BT<<'\n';
    }
    cout<<"\nScheduling the Input data using MFQS Policy...\n";

	sort(p,p+n,sortbyAT);

	int time=0,flag=0;

	while(!Q1.empty())
	{
		int index = Q1.front();
    	Q1.pop();

    	if(p[index].RT <= TQ1)
    	{
    		time += p[index].RT;
    		p[index].RT = 0;
    		p[index].CT = time;
    		p[index].TAT = p[index].CT-p[index].AT;
    		p[index].WT = p[index].TAT-p[index].BT;
    	}
    	else
    	{
    		p[index].RT -= TQ1;
    		time += TQ1;
    		Q2.push(index);
    		flag = 2;
    	}
	}

	if(flag == 2)
	{
		while(!Q2.empty())
		{
			int index = Q2.front();
	    	Q2.pop();

	    	if(p[index].RT <= TQ2)
	    	{
	    		time += p[index].RT;
	    		p[index].RT = 0;
	    		p[index].CT = time;
	    		p[index].TAT = p[index].CT-p[index].AT;
	    		p[index].WT = p[index].TAT-p[index].BT;
	    	}
	    	else
	    	{
	    		p[index].RT -= TQ2;
	    		time += TQ2;
	    		Q3.push(index);
	    		flag = 3;
	    	}
		}
	}

	if(flag == 3)
	{
		while(!Q3.empty())
		{
			int index = Q3.front();
	    	Q3.pop();

	    	time += p[index].RT;
	    	p[index].RT = 0;
	    	p[index].CT = time;
	    	p[index].TAT = p[index].CT-p[index].AT;
	    	p[index].WT = p[index].TAT-p[index].BT;
		}
	}

	sort(p,p+n,sortbyPID);

	cout<<"\n--Scheduling Completed.\n\n";

	Output(p,n);

    encdec enc;
    enc.encrypt();
    enc.decrypt();
}

/* 11.) MULTI LEVEL QUEUE SCHEDULING */

void MQS()
{
    string file_name;
    std::cout<<"\nEnter the Input File Name with Extension : ";
    cin>>file_name;

    if(!File_Exist(file_name))
    {
        return;
    }

    fstream cin(file_name,ios::in);
    int n;
    cin>>n;

    int TQ;
    cin>>TQ;

    PROCESS p[n];

    int maxi=-1;

    for(int i=0;i<n;i++)
    {
        p[i].PID=i;
        cin>>p[i].AT>>p[i].BT;
        cin>>p[i].q;
        p[i].RT = p[i].BT;
        maxi=max(maxi,p[i].q);
    }

    cout<<"-Input Read From File.\n\n";
    cin.close();
    cout<<"Time quantum="<<TQ<<'\n';
    cout<<"PID\t"<<"AT\t"<<"BT\t"<<"Queue no\n";
    for(int i=0;i<n;i++)
    {
        cout<<"P"<<p[i].PID<<'\t'<<p[i].AT<<'\t'<<p[i].BT<<'\t'<<p[i].q<<'\n';
    }
    cout<<"\nScheduling the Input data using MQS Policy...\n";

    int completed = 0;

    queue<PROCESS>q[maxi+1];
    PROCESS x;

    int p_time = 0,k = 0;
    while(completed < n)
    {
        k = 1;
        while(k <= maxi && q[k].empty())
        {
            k++;
        }
        if(k == maxi+1)
        {
            int mini = 1e9;
            for(int i=0;i<n;i++)
            {
                if(p[i].check==0)
                {
                    mini = min(mini,p[i].AT);
                }
            }

            p_time = mini;

            for(int i=0;i<n;i++)
            {
                if(p[i].check == 0)
                {
                    if(p_time >= p[i].AT)
                    {
                        q[p[i].q].push(p[i]);
                        p[i].check = 1;
                    }
                }
            }
            continue;
        }

        x = q[k].front();
        int ifx = x.q;
        int z = -1;

        for(int i=0;i<n;i++)
        {
            if(p[i].check == 0)
            {
                if(p[i].q < ifx)
                {
                    if(p_time+TQ > p[i].AT)
                    {
                        z = 1;
                        break;
                    }
                }
            }
        }

        if(x.RT > TQ && z == -1)
        {
            p_time += TQ;
        }
        else if(z == 1)
        {
            p_time += 1;
            x.RT--;
            if(x.RT == 0)
            {
                q[x.q].pop();
            }
            else
            {
                q[x.q].pop();
                q[x.q].push(x);
            }
        }
        else
        {
            p_time += x.RT;
        }
        for(int i=0;i<n;i++)
        {
            if(p[i].check == 0)
            {
                if(p_time >= p[i].AT)
                {
                    q[p[i].q].push(p[i]);
                    p[i].check = 1;
                }
            }
        }
        if(z == 1)
        {
            continue;
        }
        if(x.RT <= TQ)
        {
            p[x.PID].CT = p_time;
            p[x.PID].TAT = p[x.PID].CT-p[x.PID].AT;
            p[x.PID].WT = p[x.PID].TAT-p[x.PID].BT;
            q[x.q].pop();
            completed++;
        }
        else
        {
            x.RT -= TQ;
            q[x.q].pop();
            q[x.q].push(x);
        }
    }

    cout<<"\n--Scheduling Completed.\n\n";

    Output(p,n);

    encdec enc;
    enc.encrypt();
    enc.decrypt();
}
