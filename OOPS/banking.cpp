#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>
#include<memory>
using namespace std;

double MAX_BAL=1000000000;//MAX BALANCE 10 cr

//GLOBAL LIST FOR BRANCH MANAGER
vector <pair<string, long long int> > NAME_ACC;


//TIME VARIATION
string date_curr(void){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [100];
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer,100,"%F",timeinfo);
    string a(buffer);
    return a;
}
string date_global_s=date_curr();
string date_global=date_curr();
string date_change(int m, int d, int y){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [100];
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    timeinfo->tm_mday=d;
    timeinfo->tm_mon=m-1;
    timeinfo->tm_year=y-1900;
    strftime (buffer,100,"%F",timeinfo);
    string a(buffer);
    return a;
}
pair<int,int> month(string s1){
    string sub=s1.substr(5,2);
    int mon=stoi(sub);
    int y=stoi(s1.substr(0,4));
    pair<int,int> a;
    a.first=mon;
    a.second=y;
    return a;
}
int diff(pair<int,int> p1, pair<int,int> p2){
    int m1=p1.first;
    int m2=p2.first;
    int y1=p1.second;
    int y2=p2.second;
    if (y2!=y1)
    {   
        if(m2>m1){
            return m2-m1+(y2-y1)*12;
        }
        else if(m2==m1){
            return (y2-y1)*12;
        }
        else{
            return (12+m1-m2)+(y2-y1-1)*12;
        }
    }
    else {
        return m2-m1;
    }
    
}





//RANDOM ACCOUNT NUMBER GEN
long long int random_gen(){
    return rand()%900000000+100000000;
}




//ACCOUNTS CLASS
class Account{
    public:
        string name;
        char type;
        long long int account_no;
        void deposit(double amt);
        void withdraw(double amt);
        void transfer(double amt,long long int account_1,long long int account_2,char c1,char c2);
        void show_statement(void);
        string open_date;
        
    protected:
       
        double account_bal;
        
        vector <pair<pair<string,double>,pair<string, double> > > account_st;
};
//FUNCTIONS OF ACCOUNT CLASS
void Account::deposit(double amt){
    if(account_bal+amt<=MAX_BAL){
        account_bal=account_bal+amt;
        pair<string,double> stt;
        stt.first=date_global;
        stt.second=account_bal;

        pair<string,double> stt_chg;
        stt_chg.first="DEPOSITED Rs";
        stt_chg.second=amt;

        pair<pair<string,double>,pair<string,double> > PAIR;

        PAIR.first=stt;
        PAIR.second=stt_chg;


        account_st.push_back(PAIR);
    }
    else{
        cout<<"MAX BALANCE EXCEDDED"<<endl;
        cout<<"TRANSACTION CANCELLED!"<<"\n\n";
    }
}
void Account::withdraw(double amt){
    if(account_bal-amt>0){
        account_bal=account_bal-amt;
        pair<string,double> stt;
        stt.first=date_global;
        stt.second=account_bal;
    
        pair<string,double> stt_chg;
        stt_chg.first="WITHDRAWN Rs";
        stt_chg.second=amt;

        pair<pair<string,double>,pair<string,double> > PAIR;
        PAIR.first=stt;
        PAIR.second=stt_chg;

        account_st.push_back(PAIR);
    }
    else{
        cout<<"INSUFFICIENT FUNDS"<<endl;
    }
}

void Account::show_statement(void){
    cout<<"\n";
    cout<<"----------------------STATEMENT-----------------------"<<"\n\n";
    for(int i=account_st.size()-1;i>=0;i--){
        cout<<i+1<<". "<<account_st[i].first.first<<" "<<account_st[i].second.first<<account_st[i].second.second<<" FINAL BAL:"<<account_st[i].first.second<<endl;
    }
    cout<<"\n\n";
}



//SAVINGS ACCOUNT
class Savings_Acc: public Account{
    public:
        Savings_Acc(long long int open_bal,string name);
        double getinterestrate(void);
        void setinterestrate(void);
        void interest(int month);

    private:
        double interest_rate;//IN PERCENTAGE
};
//constructor of SAVINGS
Savings_Acc::Savings_Acc(long long int open_bal,string name){
    setinterestrate();
    pair<string,double> stt;
    stt.first=date_global;
    stt.second=open_bal;
    pair<string,double> stt_chg;
    stt_chg.first="DEPOSITED Rs";
    stt_chg.second=open_bal;
    
    pair<pair<string,double>,pair<string,double> > PAIR;
    PAIR.first=stt;
    PAIR.second=stt_chg;
    
    account_st.push_back(PAIR);
    account_no=random_gen();
    pair<string,long long int> Data;
    Data.first=name;
    Data.second=account_no;
    NAME_ACC.push_back(Data);
    type='S';
    account_bal=open_bal;
    open_date=date_global;
}

double interest1(double interestr,int month){
    double interestrr=1;
    while(month>0){
        interestrr=interestrr*((double)1+interestr/100);
        month--;
    }
    return interestrr;
}
void Savings_Acc::setinterestrate(void){
    if(account_bal<100000){
        interest_rate=3.0;
    }
    else if(account_bal<500000){
        interest_rate=4.0;
    }
    else if(account_bal<1000000){
        interest_rate=7.0;
    }
    else if(account_bal<MAX_BAL){
        interest_rate= 6.0;
    }
}

double Savings_Acc::getinterestrate(void){
    return interest_rate;
}


//CURRENT ACCOUNT
class Current_Acc: public Account{
    public:
        Current_Acc(long long int open_bal,string name);
        float get_interest_rate(void);
    
    private:
        double interest_rate;

};
//constructor of CURRENT
Current_Acc::Current_Acc(long long int open_bal,string name){
    pair<string,double> stt;
    stt.first=date_global;
    stt.second=open_bal;

    pair<string,double> stt_chg;
    stt_chg.first="DEPOSITED Rs";
    stt_chg.second=open_bal;

    pair<pair<string,double>,pair<string,double> > PAIR;

    PAIR.first=stt;
    PAIR.second=stt_chg;
    account_st.push_back(PAIR);
    account_no=random_gen();
    pair<string,long long int> Data;
    Data.first=name;
    Data.second=account_no;
    NAME_ACC.push_back(Data);
    account_bal=open_bal;
    type='C';
    open_date=date_global;
}


//GLOBAL LIST FOR BRANCH MANAGER
vector<shared_ptr<Savings_Acc> > accounts_s_g;
vector<shared_ptr<Current_Acc> > accounts_c_g;

void Savings_Acc::interest(int month){
        for(int i=0;i<accounts_s_g.size();i++){
            if(accounts_s_g[i]->account_no==account_no){
                cout<<"Interest Added";
                accounts_s_g[i]->deposit(account_bal*(interest1(getinterestrate(),month))-account_bal);
                date_global_s=date_global;
            }
        }    
}

//BANK HOLDER CLASS
class Bank_Holder{
    private:
        string username;
        string password;
        vector <Account> accounts;
        vector <Savings_Acc> accounts_s;
        vector <Current_Acc> accounts_c;
    public:    
        string name;
        Bank_Holder(string n,string u, string p);
        void get_Accounts(void);//DONE
        void changepasswd(string s1,string s2);
        void createAccount(char c,long long int amt,string name1);
        void accessAccount(char c,long long int account_no);
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
    cout<<endl<<endl;      
}   
void Bank_Holder::createAccount(char c,long long int amt,string name1){
    if(c=='S'||c=='s'){
        shared_ptr<Savings_Acc> acc_created = make_shared<Savings_Acc>(amt, name1);
        accounts_s.push_back(*acc_created); // Add the object to the vector
        accounts_s_g.push_back(acc_created);
    }
    else if(c=='C'||c=='c'){
        shared_ptr<Current_Acc> acc_created = make_shared<Current_Acc>(amt, name1);
        accounts_c.push_back(*acc_created); // Add the object to the vector
        accounts_c_g.push_back(acc_created);
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
void Bank_Holder::accessAccount(char c,long long int account_no1){
    if(c=='S'||c=='s'){
        for(int i=0;i<accounts_s_g.size();i++){
            if(accounts_s_g[i]->account_no==account_no1){
                cout<<"\n\n";
                cout<<"-------ACCESSING ACCOUNT WITH ACCOUNT NO:"<<account_no1<<"-------"<<endl<<endl;
                pair<int, int> PAIR1,PAIR2;
                PAIR1=month(date_global_s);
                PAIR2=month(date_global);
                int diffmont=diff(PAIR1,PAIR2);
                if(date_global_s!=date_global){
                    accounts_s_g[i]->interest(diffmont);
                }
                while(1){
                cout<<"You can perform the following functions:\n1.DEPOSIT MONEY\n2.WITHDRAW MONEY\n3.TRANSFER MONEY\n4.VIEW STATEMENT\n5.CLOSE ACCOUNT\n";
                cout<<"Please choose your operation(1/2/3/4/5/0->to exit):";
                char num;
                cin>>num;
                if(num=='1'){
                    cout<<"Enter the money to deposit:";
                    double amt_usr;
                    cin>>amt_usr;
                    accounts_s_g[i]->deposit(amt_usr);
                }
                else if(num=='2'){
                    cout<<"Enter the money to withdraw:";
                    double amt_usr;
                    cin>>amt_usr;
                    accounts_s_g[i]->withdraw(amt_usr);
                }
                else if(num=='3'){
                    long long int num2;
                    cout<<"Please Enter the user's ACCOUNT NUMBER in which money has to be transffered:";
                    cin>>num2;
                    char f;
                    cout<<"Please ENTER user's ACCOUNT type(S/C):";
                    cin>>f;
                    long long int amt;
                    cout<<"Please ENTER amount:";
                    cin>>amt;
                    accounts_s_g[i]->transfer(amt,accounts_s[i].account_no,num2,'s',f);
                }
                else if(num=='4'){
                    cout<<"SHOWING YOUR STATEMENT:\n";
                    if(date_global_s!=date_global){
                        accounts_s_g[i]->interest(diff(month(date_global_s),month(date_global)));
                    }
                    accounts_s_g[i]->show_statement();

                }
                else if(num=='5'){
                    cout<<"CLOSING YOUR ACCOUNT!!\n";
                    for(int j=0;j<accounts_s.size();j++){
                        if(accounts_s[j].account_no==account_no1){
                            accounts_s.erase(accounts_s.begin()+j);
                        }

                    }
                    accounts_s_g.erase(accounts_s_g.begin()+i);
                    break;

                }
                else if(num=='0'){
                    break;
                }
            }
            


            }
        }
    }
    else if(c=='C'||c=='c'){
         for(int i=0;i<accounts_c_g.size();i++){
            if(accounts_c_g[i]->account_no==account_no1){
                cout<<"ACCESSING ACCOUNT WITH ACCOUNT NO:"<<account_no1<<endl<<endl;
                while(1){
                    cout<<"You can perform the following functions:\n1.DEPOSIT MONEY\n2.WITHDRAW MONEY\n3.TRANSFER MONEY\n4.VIEW STATEMENT\n5.CLOSE ACCOUNT\n";
                    cout<<"Please choose your operation(1/2/3/4/5/0->to exit):";
                    char num;
                    cin>>num;
                    if(num=='1'){
                        cout<<"Enter the money to deposit:";
                        double amt_usr;
                        cin>>amt_usr;
                        accounts_c_g[i]->deposit(amt_usr);
                    }
                    else if(num=='2'){
                        cout<<"Enter the money to withdraw:";
                        double amt_usr;
                        cin>>amt_usr;
                        accounts_c_g[i]->withdraw(amt_usr);
                    }
                    else if(num=='3'){
                        accounts_c_g[i]->transfer(0,0,0,'c','s');
                    }
                    else if(num=='4'){
                        cout<<"SHOWING YOUR STATEMENT:\n";
                        accounts_c_g[i]->show_statement();

                    }
                    else if(num=='5'){
                        cout<<"CLOSING YOUR ACCOUNT!!\n";
                        for(int j=0;j<accounts_c.size();j++){
                            if(accounts_c[j].account_no==account_no1){
                                accounts_c.erase(accounts_c.begin()+j);
                            }

                        }

                        accounts_c_g.erase(accounts_c_g.begin()+i);
                    }
                    else if(num=='0'){
                        break;
                    }

                }
            }
        }

    }
}




class BranchManager{
    private:
        string username;
        string password;
    public:
        bool check(string s1,string s2);
        BranchManager(string s1,string s2);
        void fastforward(string &s,string m,string d,string y);
        void getStatement(long long int account_num,char c);
        void getAccountHolders();
};

BranchManager::BranchManager(string s1,string s2){
    username=s1;
    password=s2;
}

bool BranchManager::check(string s1,string s2){
    if((username==s1)&&(password==s2)){
        return true;
    }
    else{
        return false;
    }

}

void BranchManager::fastforward(string &s,string m,string d,string y){
    string cpy=s;
    s=date_change(stoi(m),stoi(d),stoi(y));
}

void BranchManager::getAccountHolders(){
    if(NAME_ACC.size()==0){
        cout<<"NO ACCOUNTS!!"<<endl;
    }
    for(int i=0;i<NAME_ACC.size();i++){
        cout<<NAME_ACC[i].first<<": "<<NAME_ACC[i].second<<endl;
    }
}

void BranchManager::getStatement(long long int acc_num,char c){
    if(c=='s'||c=='S'){
        if(accounts_s_g.size()==0){
            cout<<"NO SAVING ACCOUNT CREATED!!\n";
        }
        for(int i=0;i<accounts_s_g.size();i++){
            
            if(accounts_s_g[i]->account_no==acc_num){
                // cout<<"enter";
                accounts_s_g[i]->interest(diff(month(date_global_s),month(date_global)));
                accounts_s_g[i]->show_statement();
            }
        }
    }
    else if(c=='c'||c=='C'){
        if(accounts_c_g.size()==0){
            cout<<"NO CURRENT ACCOUNT CREATED!!\n";
        }
        for(int i=0;i<accounts_c_g.size();i++){
            if(accounts_c_g[i]->account_no==acc_num){
                accounts_c_g[i]->show_statement();
            }
        }


    }
    
}


//TIME
void Account::transfer(double amt,long long int account_1,long long int account_2,char type1,char type2){
    if(type1=='s'||type1=='S'){
        for(int i=0;i<accounts_s_g.size();i++){
            if(accounts_s_g[i]->account_no==account_1){
                if(type2=='s'||type2=='S'){
                    for(int j=0;j<accounts_s_g.size();j++){
                        if(accounts_s_g[j]->account_no==account_2){
                            accounts_s_g[i]->withdraw(amt);
                            accounts_s_g[j]->deposit(amt);
                        }
                    }
                }
                else if(type2=='c'||type2=='C'){
                    for(int j=0;j<accounts_c_g.size();j++){
                        if(accounts_c_g[j]->account_no==account_2){
                            accounts_s_g[i]->withdraw(amt);
                            accounts_c_g[j]->deposit(amt);
                            
                        }
                    }
                }
                else{
                    cout<<"INVALID INPUT";
                }
            
            }

        }
    }
    else if(type1=='c'||type1=='C'){
        for(int i=0;i<accounts_c_g.size();i++){
            if(accounts_c_g[i]->account_no==account_1){
                if(type2=='s'||type2=='S'){
                    for(int j=0;j<accounts_s_g.size();j++){
                        if(accounts_s_g[j]->account_no==account_2){
                            accounts_c_g[i]->withdraw(amt);
                            accounts_s_g[j]->deposit(amt);
                            break;
                        }
                    }
                }
                else if(type2=='c'||type2=='C'){
                    for(int j=0;j<accounts_c_g.size();j++){
                        if(accounts_c_g[j]->account_no==account_2){
                            accounts_c_g[i]->withdraw(amt);
                            accounts_c_g[j]->deposit(amt);
                            break;
                        }
                    }
                }
                else{
                    cout<<"INVALID INPUT\n\n";
                }
            }


        }
    }
    else{
        cout<<"INVALID INPUT";
        cout<<"\n\n";
    }

}


int main(){
    vector <Bank_Holder> Bank_Holder_list;
    vector <string> username_list;
    string user_bm_rl,user_bm_rl_pw;
    char a;
    cout<<"Hello, Bank Manager"<<endl;
    cout<<"Create your login_id by using new username and password"<<endl;
    cout<<"Create your branch manager username:";
    cin>>user_bm_rl;

    cout<<"Create your branch manager password:";
    cin>>user_bm_rl_pw;

    BranchManager New(user_bm_rl,user_bm_rl_pw);

    cout<<"To Start the baking session please press E:";
    while(a!='E'){
        cin>>a;
    }
    cout<<"\n\n";
    date_global_s=date_curr();
    string cpy=date_global_s;
    

    while(1){
        cout<<"\n\n";
        cout<<"                         ########  Welcome to Banking Services!!  #######"<<endl<<endl;
        cout<<"Do you want to LOGIN or SIGNUP(1->LOGIN/2->SIGNUP/M->MANAGER LOGIN/0->ABORT SESSION):";
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
        
        //LOGIN 
        if(b=='1'){
            cout<<"                               LOGIN"<<endl;
            string login_usr,login_pw;
            cout<<"Enter your USERNAME:";
            cin>>login_usr;
            cout<<"Enter your PASSWORD:";
            cin>>login_pw;
            pair <string,string> a;
            bool checkk=true;
            for(int i=0;i<Bank_Holder_list.size();i++){
                if(Bank_Holder_list[i].checkAccess(login_usr,login_pw)){
                    checkk=false;
                    
                    cout<<"---------------------------SUCCESSFULLY LOGGED IN---------------------------"<<endl;
                    while(1){ 
                        cout<<"\n\n";  
                        cout<<"WHICH OPERATION DO YOU WANT TO PERFORM:\n1.Show all your accounts.\n2.Change password\n3.Create a new Account.\n4.Access Account by Account num.\n";
                        cout<<"Please choose any operation (1/2/3/4/0-TO EXIT)";
                        int choice;
                        cin>>choice;

                        //LIST ALL ACCOUNTS
                        if(choice==1){
                            Bank_Holder_list[i].get_Accounts();
                        }
                        //CHANGE PASSWORD
                        else if(choice==2){
                            string s1,s2;
                            cout<<"Please enter NEW PASSWORD:";
                            cin>>s1;
                            cout<<"Please re-enter NEW PASSWORD:";
                            cin>>s2;
                            Bank_Holder_list[i].changepasswd(s1,s2);
                        }
                        //CREATE NEW ACCOUNT
                        else if(choice==3){
                            cout<<"TYPES OF ACCOUNTS:\n1.SAVINGS(S)\n2.CURRENT(C)"<<endl;
                            cout<<"Choose type(S/C):";
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
                                Bank_Holder_list[i].createAccount(c,amt,Bank_Holder_list[i].name);
                            }
                            else if(c=='c'||c=='C'){
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
                                Bank_Holder_list[i].createAccount(c,amt,Bank_Holder_list[i].name);
                                
                            }
                        }
                        //ACCESS A SPECIFIC ACCOUNT
                        else if(choice==4){
                            char u;
                            cout<<"Please Enter your account type(S/C):";
                            cin>>u;
                            long long int account_num;
                            cout<<"Please type your account number:";
                            cin>>account_num;
                            
                            
                            Bank_Holder_list[i].accessAccount(u,account_num);

                        }
                        else if(choice==0){
                            break;
                        }
                        else{
                            cout<<"ENTER VALID INPUT";
                            continue;
                        }
                    
                    }

                    break;
                }
                
            }
            if(checkk==true){
                    cout<<"WRONG USERNAME OR PASSWORD"<<endl;
                    continue;
            }
            
            
        }


        //BRANCH MANAGER LOGIN
        if(b=='M'){
            string user_br;
            string user_br_pw;
            cout<<"BRANCH MANAGER LOGIN"<<endl;
            cout<<"PLEASE ENTER USERNAME:";
            cin>>user_br;
            cout<<"PLEASE ENTER PASSWORD:";
            cin>>user_br_pw;
            if(New.check(user_br,user_br_pw)){
                cout<<endl<<endl;
                int num=3;
                cout<<"-----------WELCOME BRANCH MANANGER----------"<<endl;
                cout<<"\n\n";
                while(1){
                    cout<<"\n\n";
                    cout<<"Choose your desired function:"<<endl;
                    cout<<"1.List Info of all accounts active\n2.Skip Time\n3.Statement of Account\n";
                    cout<<"Please enter(1/2/3/0->to exit):";
                    cin>>num;
                    if(num==1){
                        New.getAccountHolders();
                    }
                    else if(num==2){
                        string m,d,y;
                        cout<<"Enter the final date you want as:\n";
                        cout<<"1.MM:";
                        cin>>m;
                        cout<<"2.DD:";
                        cin>>d;
                        cout<<"3.YYYY:";
                        cin>>y;
                        New.fastforward(date_global,m,d,y);
                    }
                    else if(num==3){
                        int acc_num;
                        cout<<"Please enter account num:";
                        cin>>acc_num;
                        cout<<"Please enter account type(S/C):";
                        char c;
                        cin>>c;
                        New.getStatement(acc_num,c);
                    }
                    else if(num==0){
                        cout<<"EXITING"<<endl;
                        break;
                    }
                }
            }
            else{
                cout<<"WRONG USERNAME OR PASSWORD";
            }

        }
        
        //ABORT
        if(b=='0'){
            break;
        }
    
    }

    return 0;
}
