#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>
using namespace std;

double MAX_BAL=100000000;//MAX BALANCE 10 cr

string date_curr(void){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [100];
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer,100,"%D",timeinfo);
    string a(buffer);
    return a;
}
string date_global=date_curr();
long long int random_gen(){
    return rand()%999999999+1;
}




//ACCOUNTS CLASS
class Account{
    public:
        char type;
        long long int account_no;
        void deposit(double);
        void withdraw(double);
        void transfer(double,long long int account_1,long long int account_2);
        
    protected:
       
        double account_bal;
        string open_date;
        vector <pair<string, double> > account_st;
};

//SAVINGS ACCOUNT
class Savings_Acc: public Account{
    public:
        Savings_Acc(long long int open_bal);
        float get_interest_rate(void);
        void set_interest_rate(void);

    private:
        float interest_rate;//IN PERCENTAGE
};
//constructor
Savings_Acc::Savings_Acc(long long int open_bal){
    account_no=random_gen();
    type='S';
    account_bal=open_bal;
    open_date=date_global;
}


//CURRENT ACCOUNT
class Current_Acc: public Account{
    public:
        Current_Acc();
        float get_interest_rate(void);
    
    private:
        float interest_rate=0;

};
//constructor
Current_Acc::Current_Acc(){
    account_no=random_gen();
    type='C';
    open_date=date_global;
}




//BANK HOLDER CLASS
class Bank_Holder{
    private:
        string name;
        string username;
        string password;
        vector <Account> accounts;
        vector <Savings_Acc> accounts_s;
        vector <Current_Acc> accounts_c;
    public:    
        Bank_Holder(string n,string u, string p);
        void get_Accounts(void);//DONE
        void changepasswd(string s1,string s2);
        void createAccount(char c,long long int amt);
        bool checkAccess(string u,string p);//DONE
};
//CONSTRUCTOR of Bank_Account_Holder
Bank_Holder::Bank_Holder(string n,string u, string p){
    name=n;
    username=u;
    password=p;
}

//FUNCTION DEFINITIONS:
bool Bank_Holder::checkAccess(string u,string p){
    if((username==u)&&(password==p)){
        return true;
    }
    else{
        return false;
    }
}
void Bank_Holder::get_Accounts(){
    for(int i=0;i<accounts_s.size();i++){
            cout<<"SAVINGS ACCOUNT:";
            cout<<accounts_s[i].account_no<<endl;
    }
    for(int i=0;i<accounts_c.size();i++){
            cout<<"CURRENT ACCOUNT:";
            cout<<accounts_c[i].account_no<<endl;
    }      
}   
void Bank_Holder::createAccount(char c,long long int amt){
    if(c=='S'||c=='s'){
        Savings_Acc acc_created(amt);
        accounts_s.push_back(acc_created);
    }
    else if(c=='C'||c=='c'){
        Current_Acc acc_created;
        accounts_c.push_back(acc_created);
    }
    else{
        cout<<"Please enter valid input";
    }
}
void Bank_Holder::changepasswd(string s1,string s2){
    if(s2==s1){
        password=s1;
        cout<<"NEW PASSWORD SET SUCCESSFULLY";
    }
    else{
        cout<<"Passwords don't match";
    }

}

int main(){
    vector <Bank_Holder> Bank_Holder_list;
    vector <string> username_list;
    string user_bm_rl,user_bm_rl_pw;
    char a;
    cout<<"Hello, Bank Manager"<<endl;
    cout<<"Please create your login_id by using new username and password"<<endl;
    cout<<"Please enter your bank username:";
    cin>>user_bm_rl;

    cout<<"Please enter your bank password:";
    cin>>user_bm_rl_pw;

    cout<<"To Start the baking session please press E:";
    while(a!='E'){
        cin>>a;
    }

    while(1){
        cout<<"          #      Welcome to Banking Services!!      #"<<endl<<endl;
        cout<<"Do you want to LOGIN or SIGNUP(1/2):";
        char b;
        cin>>b;
        //SIGN UP WITH UNIQUE USERNAMES
        if(b=='2'){
            cout<<"                               SIGN UP "<<endl;
            cout<<"Please Enter your name:";
            string name;
            cin>>name;
            while(1){
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
                    Bank_Holder Usr(name,user_username,pass);
                    Bank_Holder_list.push_back(Usr);
                    cout<<"You have successfully registered,\nPlease LOGIN to view your account\'s status."<<endl;
                    break;
                }
            }
        }
        if(b=='1'){
            cout<<"                               LOGIN"<<endl;
            string login_usr,login_pw;
            cout<<"Enter your USERNAME:";
            cin>>login_usr;
            cout<<"Enter your PASSWORD:";
            cin>>login_pw;
            pair <string,string> a;
            for(int i=0;i<Bank_Holder_list.size();i++){
                if(Bank_Holder_list[i].checkAccess(login_usr,login_pw)){
                    int choice=50;
                    cout<<"SUCCESSFULLY LOGGED IN"<<endl;
                    while(choice!=0){    
                        cout<<"WHICH OPERATION DO YOU WANT TO PERFORM:\n1.Show all your accounts.\n2.Change password\n3.Create a new Account.\n";
                        cout<<"Please choose any operation (1/2/3/0-TO EXIT)";
                        cin>>choice;
                    
                        if(choice==1){
                           
                            Bank_Holder_list[i].get_Accounts();
                        }
                        else if(choice==2){
                            string s1,s2;
                            cout<<"Please enter NEW PASSWORD:";
                            cin>>s1;
                            cout<<"Please re-enter NEW PASSWORD:";
                            cin>>s2;
                            Bank_Holder_list[i].changepasswd(s1,s2);
                        }
                        else if(choice==3){
                            cout<<"Choose your type:\n1.SAVINGS(S)\n2.CURRENT(C)"<<endl;
                            char c;
                            cin>>c;
                            if(c=='S'||c=='s'){
                                cout<<"ENTER OPENING BALANCE AND DEPOSIT IT:"<<endl;
                                long long int amt;
                                while(1){
                                    cin>>amt;
                                    if(amt<=0){
                                        cout<<"Please enter non zero balance";
                                    }
                                    else{
                                        break;
                                    }
                                }
                                Bank_Holder_list[i].createAccount(c,amt);
                            }
                            else if(c=='c'||c=='C'){
                                Bank_Holder_list[i].createAccount(c,0);
                            }
                        }
                    }
                    break;
                }
                else{
                    cout<<"WRONG USERNAME OR PASSWORD"<<endl;
                    break;
                }
            }
            
            
        }
    
    
    
    }

    return 0;
}
