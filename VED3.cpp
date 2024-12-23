#include<iostream>
using namespace std;

void ReverseString(string &str, int start, int end){
    if (start >= end){
        return;
    }
    swap (str[start], str[end]);
    ReverseString(str, start+1, end-1);
}
int main () {
    string str;
    cout<<"Enter a String: ";
    cin>>str;

    ReverseString(str, 0, str.length()-1);
    cout<<"Reverse String: "<<str<<endl;

    return 0;
}