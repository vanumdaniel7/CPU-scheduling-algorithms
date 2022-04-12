#include <bits/stdc++.h>
#include "Cryptography.h"
#include "md5.h"
#include "md5.cpp"
#include <fstream>
using namespace std;
using example::encdec;

void encdec::encrypt()
{
    key=rand();

    cout<<endl;
    cout<<"Select Output Encryption Format\n";
    cout<<"1.) Key-based Encryption"<<endl;
    cout<<"2.) Md5 Encryption\n\n";
    cout<<"Enter Choice : ";
    cin>>k;
    file="Output.txt";
    if(k==2)
    {
        string w="";
        fstream fin(file,ios::in);
        while (fin >> noskipws >> c)
        {
            int temp =(c);
            w+=(char)temp;
        }
        fin.close();
        fstream fout("Encrypted_Output.txt",ios::out);
        remove("Output.txt");
        fout<<md5(w);
        fin.close();
        fout.close();
    }
    else if(k==1)
    {
        fstream fin(file,ios::in);
        while (fin >> noskipws >> c)
        {
            int temp = (c + key);
            s+=(char)temp;
        }
        fin.close();
        fstream fout("Encrypted_Output.txt",ios::out);
        remove("Output.txt");
        fout<<s;
        fin.close();
        fout.close();
	}
	else
    {
        cout<<"\nInvalid Input."<<endl;
    }
	std::cout<<"\nOutput File is produced in Encrypted Format.\n"<<endl;
}

void encdec::decrypt()
{
	int c;
	cout<<"Do you want to Decrypt the Output File (1/0) : ";
	cin>>c;
	if(k==2 && c==1)
    {
        cout<<endl;
        cout<<"Decryption is not possible as it is Md5 Encryption.\n"<<endl;
        return;
    }
    else if(c==1)
    {
        fstream fin("Encrypted_Output.txt",ios::in);
        string ans="";
        getline(fin,ans);
        for(int i=0;i<ans.size();i++)
        {
            int temp=ans[i]-key;
            ans[i]=(char)temp;
        }
        ofstream out("Decrypted_output.txt");
        out<<ans;
        fin.close();
        out.close();
        cout<<endl;
        cout<<"-Output Decrypted Succesfully.\n"<<endl;
	}
	return;
}
