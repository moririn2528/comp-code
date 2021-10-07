#include<iostream>
#include<cstdio>
#include<stdlib.h>
#include<cstring>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>
#include<map>
#include<queue>
#include<deque>
#include<iomanip>
#include<tuple>
#include<cassert>
#include<set>
#include<complex>
#include<numeric>
#include<functional>
#include<unordered_map>
#include<unordered_set>
#include<fstream>
//#include<filesystem>
using namespace std;
typedef long long int LL;
typedef pair<int,int> P;
typedef pair<LL,LL> LP;
const int INF=1<<30;
const LL MAX=1e9+7;

void array_show(int *array,int array_n,char middle=' '){
    for(int i=0;i<array_n;i++)printf("%d%c",array[i],(i!=array_n-1?middle:'\n'));
}
void array_show(LL *array,int array_n,char middle=' '){
    for(int i=0;i<array_n;i++)printf("%lld%c",array[i],(i!=array_n-1?middle:'\n'));
}
void array_show(vector<int> &vec_s,int vec_n=-1,char middle=' '){
    if(vec_n==-1)vec_n=vec_s.size();
    for(int i=0;i<vec_n;i++)printf("%d%c",vec_s[i],(i!=vec_n-1?middle:'\n'));
}
void array_show(vector<LL> &vec_s,int vec_n=-1,char middle=' '){
    if(vec_n==-1)vec_n=vec_s.size();
    for(int i=0;i<vec_n;i++)printf("%lld%c",vec_s[i],(i!=vec_n-1?middle:'\n'));
}
template<typename T> ostream& operator<<(ostream& os,const vector<T>& v1){
    int n=v1.size();
    for(int i=0;i<n;i++){
        if(i)os<<" ";
        os<<v1[i];
    }
    return os;
}
template<typename T1,typename T2> ostream& operator<<(ostream& os,const pair<T1,T2>& p){
    os<<p.first<<" "<<p.second;
    return os;
}
template<typename T> istream& operator>>(istream& is,vector<T>& v1){
    int n=v1.size();
    for(int i=0;i<n;i++)is>>v1[i];
    return is;
}

int system(string sa){
    return system(sa.c_str());
}

int compile(string source_file,string output_file){
    string sa="g++ -std=c++17 -DMORIRIN -D_GLIBCXX_DEBUG -O2 -Wall -Wextra "+source_file+" -o "+output_file;
    return system(sa);
}


string solve(){
    int n;
    int i;
    int a;
    int cnt;
    bool check_same=false;
    const string message_file="message.txt";
    string source_file="";
    string sa,sb;
    ifstream ifs("files\\\\before_source_file.txt");
    ofstream ofs;
    string bef_source_file="";
    if(ifs>>sa)bef_source_file=sa;
    while(source_file==""){
        cout<<"input source file name"<<endl;
        cin>>sa;
        if(sa.size()==1 && bef_source_file!=""){
            sa=bef_source_file;
        }
        cout<<"source file: "<<sa<<" OK?(y/n)"<<endl;
        cin>>sb;
        if(!sb.empty() && (sb[0]=='y' || sb[0]=='Y'))source_file=sa;
    }
    ifs.close();
    ofs.open("files\\\\before_source_file.txt");
    ofs<<source_file<<endl;
    ofs.close();
    cout<<"compare with greedy and check same output?"<<endl;
    cin>>sb;
    if(!sb.empty() && (sb[0]=='y' || sb[0]=='Y'))check_same=true;

    if(system("del /q in\\\\*"))return "del in file";
    if(system("del /q out\\\\*"))return "del out file";
    if(system("del "+message_file))return "del message file(message.txt)";
    if(compile("..\\\\code\\\\"+source_file,"a.exe"))return "compile error: a.exe";
    if(compile("generator.cpp","generator.exe"))return "compile error: generator.exe";
    if(check_same){
        if(compile("greedy.cpp","greedy.exe"))return "compile error: greedy.exe";
    }else{
        if(compile("checker.cpp","checker.exe"))return "compile error: checker.exe";
    }

    system("cls");
    cout<<"repeat times"<<endl;
    cin>>n;
    assert(n>0);
    for(i=0;i<n;i++){
        system("cls");
        cout<<"generate "<<i<<"/"<<n<<endl;
        if(system("generator.exe > in\\\\"+to_string(i)+".txt"))return "generate "+to_string(i)+".txt";
    }
    for(i=0;i<n;i++){
        system("cls");
        cout<<"execute "<<i<<"/"<<n<<endl;
        if(system("a.exe < in\\\\"+to_string(i)+".txt > out\\\\"+to_string(i)+".txt"))return "execute "+to_string(i)+".txt";
    }
    cnt=0;
    for(i=0;i<n;i++){
        system("cls");
        cout<<"check "<<i<<"/"<<n<<endl;
        if(check_same){
            if(system("greedy.exe < in\\\\"+to_string(i)+".txt > files\\\\greedy_out.txt"))return "greedy "+to_string(i)+".txt";
            if(system("fc files\\\\greedy_out.txt out\\\\"+to_string(i)+".txt > files\\\\temp1.txt"))return "fc greedy_out.txt and out-"+to_string(i)+".txt";
            if(system("type files\\\\temp1.txt | find /v /c \"\" > files\\\\judge.txt"))return "check column num";
            ifs.open("files\\\\judge.txt");
            assert(ifs.is_open());
            ifs>>a;
            ifs.close();
            if(a<=3)sa="AC";
            else sa="WA";
        }else{
            if(system("checker.exe "+to_string(i)+" > files\\\\checker_out.txt"))return "checker "+to_string(i)+".txt";
            ifs.open("files\\\\judge.txt");
            assert(ifs.is_open());
            ifs>>sa;
            ifs.close();
        }
        if(sa=="AC")continue;
        cnt++;
        system("echo "+to_string(i)+": >> "+message_file);
        system("echo input >> "+message_file);
        system("type in\\\\"+to_string(i)+".txt >> "+message_file);
        system("echo output >> "+message_file);
        system("type out\\\\"+to_string(i)+".txt >> "+message_file);
        if(check_same){
                system("echo greedy >> "+message_file);
                system("type files\\\\greedy_out.txt >> "+message_file);
        }else{
            int fsize=0;//filesystem::file_size("files\\\\checker_out.txt");
            if(fsize>2){
                system("echo message >> "+message_file);
                system("type files\\\\checker_out.txt >> "+message_file);
            }
        }
        system("echo;>> "+message_file);
    }
    system("cls");
    cout<<"finished"<<endl;
    cout<<"WA: "<<cnt<<"/"<<n<<endl;
    cout<<"press ENTER to exit application"<<endl;
    cin.ignore();
    return "";
}

int main(){
    string sa=solve();
    if(sa.empty())return 0;
    cout<<"Error: "<<sa<<endl;
}