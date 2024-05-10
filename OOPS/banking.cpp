#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>
using namespace std;


string date_curr(void){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer,80,"%D",timeinfo);
    string a(buffer);
    return a;
}

string date_global=date_curr();

class Account{
    public:
        long long int account_no;
        void deposit(double);
        void withdraw(double);
        void transfer(double,long long int account_1,long long int account_2);
        
    private:
        double account_bal;
        string open_date;
        vector <pair<string, double> > account_st;
};

class Bank_Holder{
    private:
        string name;
        string username;
        string password;
        vector <Account> accounts;
    public:    
        void get_Accounts(void);
        void changepasswd(void);
        void createAccount(void);
        void set_data(string n,string u, string p);

};









int main(){
    vector <Bank_Holder> Bank_Holder_list;
    vector <string> username_list;
    string user_bm_rl,user_bm_rl_pw;
    char a;
    cout<<"Hello, Bank Manager"<<endl;
    cout<<"Please create your login_id by using new username and password"<<endl;
    cout<<"Please enter your username:";
    cin>>user_bm_rl;

    cout<<"Please enter your password:";
    cin>>user_bm_rl_pw;

    cout<<"To Start the baking session please press E:";
    while(a!='E'){
        cin>>a;
    }

    while(1){
        cout<<"Welcome to Banking Services!!"<<endl;
        cout<<"Do you want to LOGIN or SIGNUP(1/2):";
        char b;
        cin>>b;
        if(b=='2'){
            cout<<"               SIGN UP "<<endl;
            cout<<"Please Enter your name:";
            string name;
            cin>>name;
            int x=1;
            while(x){
                cout<<"Please enter a username:";
                string user_username;
                cin>>user_username;
                if(find(username_list.begin(),username_list.end(),user_username)!=username_list.end()){
                    cout<<"Username already in use."<<endl;
                    cout<<"Please enter new username."<<endl;
                    continue;
                }
                else{
                    username_list.push_back(user_username);
                    cout<<"Username set successfully!!"<<endl;
                    string pass;
                    string pass_chk;
                    while(1){
                        cout<<"Please Enter your password:";
                        cin>>pass;
                        cout<<"Renter your password:";
                        cin>>pass_chk;
                        if(pass==pass_chk){
                            cout<<"Password set successfully!!"<<endl;
                            break;
                        }
                        else{
                            cout<<"Passwords donot match, please renter them."<<endl;
                            continue;
                        }

                    }

                    //CREATING OBJECT OF USER AND STORING IT IN VECTOR
                    Bank_Holder Usr;
                    Usr.set_data(name,user_username,pass);
                    Bank_Holder_list.push_back(Usr);

                    
                    break;
                }
            }



        }

    }
    return 0;
}