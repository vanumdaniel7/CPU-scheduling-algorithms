#pragma once

#include<bits/stdc++.h>
using namespace std;

namespace example
{
	class PROCESS
	{
		public:
		    int AT,BT,PID,CT,WT,TAT,RT,check,priority,ST,q;
			PROCESS()
			{
			    AT = 0;
                BT = 0;
                CT = 0;
                WT = 0;
                TAT = 0;
                PID = 0;
                RT = 0;
                ST = 0;
                check = 0;
                priority = 0;
                q = 0;
			}
		    /*
                PID->Process ID
                AT->Arrival Time
                BT->Burst Time
                CT->Completion Time
                WT->Waiting Time
                RT->Remaining Burst Time
                TAT->Turn Around Time
                ST->Starting Time
            */
	};
}
