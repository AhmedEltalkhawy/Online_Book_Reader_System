#include <iostream>
#include<vector>
#include <ctime>
#include <bits/stdc++.h>

#include "System.hpp"


using namespace std;

int ReadInt(int low , int high)
{
    int value ;
    cout<< "Enter your choice from <= " << low << " to " << high << " : "  ;
    cin >> value ;
    cout<<"\n" ;
    if(value >= low && value <= high)
    {
        return value ;
    }
    cout << "invalid option , try again :(" ;
    return ReadInt(low ,high) ;

}

int ShowReadMenu (const vector<string> &choices)
{
    cout<<" \n  \t\t Menu : \n\n" ;
    int i ;
    for(i=0 ; i < choices.size(); ++i)
    {
        cout << "Enter " << i+1 << " for " <<choices[i] << "\n\n" ;
    }
    return ReadInt(1 , choices.size()) ;
}

string GetCurrentTimeDate()
{	// src: https://stackoverflow.com/questions/17223096/outputting-date-and-time-in-c-using-stdchrono
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
	return ss.str();
}

int main()
{
    OnlineReaderSystem site ;
    site.Run() ;
    return 0;
}
