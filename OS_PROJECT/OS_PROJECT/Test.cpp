#include<bits/stdc++.h>
#include "CPU_SCHEDULING.h"
#include "CPU_SCHEDULING.cpp"
using namespace std;

int main()
{
    cout<<"************** CPU_SCHEDULING_PROJECT **************"<<endl;
    cout<<"\n";

    int ch=1;
    while(ch)
    {
        cout<<"\n-Please select a Scheduling Policy"<<endl;
        cout<<endl;

        cout<<"1.) FIRST COME FIRST SERVE"<<endl;
        cout<<"2.) SHORTEST JOB FIRST "<<endl;
        cout<<"3.) SHORTEST REMAINING TIME FIRST"<<endl;
        cout<<"4.) PRIORITY BASED NON PRE-EMPTIVE "<<endl;
        cout<<"5.) PRIORITY BASED PRE-EMPTIVE "<<endl;
        cout<<"6.) ROUND ROBIN "<<endl;
        cout<<"7.) LONGEST JOB FIRST "<<endl;
        cout<<"8.) LONGEST REMAINING TIME FIRST "<<endl;
        cout<<"9.) HIGHEST RESPONSE RATIO NEXT"<<endl;
        cout<<"10.) MULTI LEVEL FEEDBACK QUEUE SCHEDULING "<<endl;
        cout<<"11.) MULTI LEVEL QUEUE SCHEDULING "<<endl;

        int n;
        cout<<endl;
        cout<<"Enter a Choice : ";
        cin>>n;

        switch (n)
        {
            case 1:FCFS();
                break;
            case 2:SJF();
                break;
            case 3:SRTF();
                break;
            case 4:PRIORITY_NP();
                break;
            case 5:PRIORITY_P();
                break;
            case 6:RoundRobin();
                break;
            case 7:LJF();
                break;
            case 8:LRTF();
                break;
            case 9:HRRN();
                break;
            case 10:MFQS();
                break;
            case 11:MQS();
                break;
            default:cout<<"\nEnter A Valid Input."<<endl;
        }
        cout<<"\nDo You Want To Continue (0 to Exit) : ";
        cin>>ch;
    }
}
