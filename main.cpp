#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <ctime>
#include <chrono>
#include <iomanip>
using namespace std;


class card{
    private:
        fstream f1;
        long long cardNo;
        string pin;
        string line;
    public:
        void setCardNo(long long cardNo){
            this->cardNo = cardNo;
        }
        bool setPin(){
            cin>>pin;
            while(pin.length()!=4){
                cout<<"PIN length can only be of 4 digits.. Enter again: "<<endl;
                cin>>pin;
            }
            ofstream f1("Cards.txt",ios::app);
            f1<<cardNo<<" "<<pin<<endl;
            f1.close();
            cout<<"Your pin registered successfully"<<endl;
            return true;
        }
        bool checkPin(){
            string a,b,c,d;
            cout<<"Enter your card no: ";
            cin>>a;
            cout<<"Enter your pin: ";
            cin>>b;
            f1.open("Cards.txt");
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>c>>d;
                if(c == a && b == d){
                    f1.close();
                    return true;
                }
            }
            f1.close();
            return false;
        }
        long long getCardNo(){
            return cardNo;
        }
};
class transaction{
    private:
        fstream f1,f2;
        string line;
        int transactionId;
        double amount;
        string fromAccId;
        string toAccId;
        string timeStamp;
        string dateStamp;
    public:
        void generateTransactionId(string loc){
            int n = 1;
            f1.open(loc);
            while(getline(f1,line)){
                n+=1;
            }
            f1.close();
            transactionId = n;
        }
        void postTransaction_U(){
            generateTransactionId("Transactions.txt");
            f1.open("Transactions.txt",ios::app);
            f1<<transactionId<<" "<<fromAccId<<" "<<toAccId<<" "<<amount<<" "<<getDate()<<" "<<getTime()<<endl;
            f1.close();
        }
        void postTransaction_C(){
            generateTransactionId("companiesTransactions.txt");
            f1.open("companiesTransactions.txt",ios::app);
            f1<<transactionId<<" "<<fromAccId<<" "<<toAccId<<" "<<amount<<" "<<getDate()<<" "<<getTime()<<endl;
            f1.close();
        }
        void deposit(int id,double amount,string loc){
            // update balance in users.txt
            int a;
            double balance;
            string b,c,d,e,f;
            f1.open(loc);
            f2.open("New.txt",ios::app);
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>a>>b>>c>>d>>e>>f>>balance;
                if(a == id){
                    f2<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<" "<<f<<" "<<balance+amount<<endl;
                }
                else if(a!=id){
                    f2<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<" "<<f<<" "<<balance<<endl;
                }
            }
            f1.close();
            f2.close();
            remove(loc.c_str());
            rename("New.txt",loc.c_str());
            cout<<"Amount deposited successfully!"<<endl;
            // add to transaction history.. make a separate function
            this->amount = amount;
            if(loc == "Users.txt"){
                fromAccId = "Deposit";
                toAccId = to_string(id);
                postTransaction_U();
            }
            else if(loc == "companies.txt"){
                fromAccId = to_string(id);
                toAccId = "Deposit";
                postTransaction_C();
            }
        }
        
        void withdraw(int id,double amount,string loc){
            // update balance in users.txt
            int a;
            double balance;
            string b,c,d,e,f;
            f1.open(loc);
            f2.open("New.txt",ios::app);
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>a>>b>>c>>d>>e>>f>>balance;
                if(a == id){
                    f2<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<" "<<f<<" "<<balance-amount<<endl;
                }
                else if(a!=id){
                    f2<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<" "<<f<<" "<<balance<<endl;
                }
            }
            f1.close();
            f2.close();
            remove(loc.c_str());
            rename("New.txt",loc.c_str());
            cout<<"Amount withdrawn successfully!"<<endl;
            // add to transaction history.. make a separate function
            this->amount = amount;
            if(loc == "Users.txt"){
                fromAccId = to_string(id);
                toAccId = "Withdraw";
                postTransaction_U();
            }
            else if(loc == "companies.txt"){
                fromAccId = to_string(id);
                toAccId = "Withdraw";
                postTransaction_C();
            }
        }
        void sendAmount(int fan,int tan,double amount){
            int a;
            double balance;
            string b,c,d,e,f;
            f1.open("Users.txt");
            f2.open("New.txt",ios::app);
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>a>>b>>c>>d>>e>>f>>balance;
                if(a == fan){
                    f2<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<" "<<f<<" "<<balance-amount<<endl;
                }
                else if(a == tan){
                    f2<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<" "<<f<<" "<<balance+amount<<endl;

                }
                else if(a!=fan && a!=tan){
                    f2<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<" "<<f<<" "<<balance<<endl;
                }
            }
            f1.close();
            f2.close();
            remove("Users.txt");
            rename("New.txt","Users.txt");
            cout<<"Amount transferred successfully!"<<endl;
            // add to transaction history.. make a separate function
            fromAccId = to_string(fan);
            toAccId = to_string(tan);
            this->amount = amount;
            postTransaction_U();
        }
        void sendAmount_C(int fan,int tan,double amount){
            int a;
            double balance;
            string b,c,d,e,f;
            f1.open("companies.txt");
            f2.open("New.txt",ios::app);
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>a>>b>>c>>d>>e>>f>>balance;
                if(a == fan){
                    f2<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<" "<<f<<" "<<balance-amount<<endl;
                }
                else{
                    f2<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<" "<<f<<" "<<balance<<endl;
                }
            }
            f1.close();
            f2.close();
            remove("companies.txt");
            rename("New.txt","companies.txt");
            // add to transaction history.. make a separate function
            fromAccId = to_string(fan);
            toAccId = to_string(tan);
            this->amount = amount;
            postTransaction_C();
            sendAmount(fan,tan,amount);
        }
        void viewTransactions(int accountNo,string loc){
            f1.open(loc);
            f1.seekg(0,ios::beg);
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>transactionId>>fromAccId>>toAccId>>amount>>dateStamp>>timeStamp;
                if((to_string(accountNo)) == fromAccId || (to_string(accountNo)) == toAccId){
                    cout<<"---------------------------------------"<<endl;
                    cout<<"Transaction id: "<<transactionId<<endl;
                    cout<<"---------------------------------------"<<endl;
                    cout<<"From Account Number: "<<fromAccId<<endl;
                    cout<<"To Account Number: "<<toAccId<<endl;
                    cout<<"Transaction Amount: "<<amount<<endl;
                    cout<<"Transaction date: "<<dateStamp<<endl;
                    cout<<"Transaction time: "<<timeStamp<<endl;
                }
            }
            f1.close();
        }
        string getTime(){
            auto now = chrono::system_clock::now();
            time_t nowTime_t = chrono::system_clock::to_time_t(now);
            tm* localTime = localtime(&nowTime_t);
            stringstream ss;
            ss<<put_time(localTime,"%H:%M");
            string timeString = ss.str();
            return timeString;
        }
        string getDate(){
            auto now = chrono::system_clock::now();
            time_t nowTime_t = chrono::system_clock::to_time_t(now);
            tm* localTime = localtime(&nowTime_t);
            stringstream ss;
            ss<<localTime->tm_mday<<"/"<<(localTime->tm_mon+1)<<"/"<<(localTime->tm_year+1900);
            string dateString = ss.str();
            return dateString;
        }
};
class dailyLimit{
    protected:
        int accNo;
        string accType;
        double limit;
        string line;
        fstream f1,f2;
        double amount;
    public:
        void setAccountDailyLimit(int accNo,string accType){
            if(accType == "bronze"){
                amount = 100000;
            }
            else if(accType == "gold"){
                amount = 500000;
            }
            else if(accType == "business"){
                amount = 20000000;
            }
            ofstream f3("dailyLimits.txt",ios::app);
            f3<<accNo<<" "<<accType<<" "<<amount<<endl;
            f3.close();
        }
        string getCurrentDate(){
            auto now = chrono::system_clock::now();
            time_t nowTime_t = chrono::system_clock::to_time_t(now);
            tm* localTime = localtime(&nowTime_t);
            stringstream ss;
            ss<<localTime->tm_mday<<"/"<<(localTime->tm_mon+1)<<"/"<<(localTime->tm_year+1900);
            string dateString = ss.str();
            return dateString;
        }
        string fileTime(){
            f1.open("dailyLimits.txt");
            getline(f1,line);
            f1.close();
            return line;
        }
        
        void setLimit(){
            string filedate = fileTime();
            string crrDate = getCurrentDate();
            int day1,day2,pos;
            for(int i=0;i<filedate.length();i++){
                if(filedate[i]=='/'){
                    pos = i;
                    break;
                }
            }
            day1 = stoi(filedate.substr(0,pos));
            for(int i=0;i<crrDate.length();i++){
                if(filedate[i]=='/'){
                    pos = i;
                    break;
                }
            }
            day2 = stoi(crrDate.substr(0,pos));
            if(day1<day2){
                string a,b,c;
                f1.open("dailyLimits.txt");
                f2.open("new.txt",ios::app);
                f2<<crrDate<<endl;
                int counter = 0;
                while(getline(f1,line)){
                    if(counter != 0){
                        stringstream ss(line);
                        ss>>a>>b;
                        f2<<a<<" "<<b<<" "<<0<<endl;
                    }
                    counter++;
                }
                f1.close();
                f2.close();
                remove("dailyLimits.txt");
                rename("new.txt","dailyLimits.txt");
            }
        }
        bool checkLimit(int accNo,double amount){
            f1.open("dailyLimits.txt");
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>this->accNo>>accType>>limit;
                if(this->accNo==accNo){
                    if(accType == "bronze"){
                        if(amount+limit<=100000){
                            f1.close();
                            return true;
                        }
                        else{
                            f1.close();
                            cout<<"Daily limit exceeds this amount"<<endl;
                            return false;
                        }
                    }
                    else if(accType == "gold"){
                        if(amount+limit<=500000){
                            f1.close();
                            return true;
                        }
                        else{
                            f1.close();
                            cout<<"Daily limit exceeds this amount"<<endl;
                            return false;
                        }
                    }
                    else if(accType == "business"){
                        if(amount+limit<=20000000){ 
                            f1.close();
                            return true;
                        }
                        else{
                            f1.close();
                            cout<<"Daily limit exceeds this amount"<<endl;
                            return false;
                        }
                    }
                }
            }
            f1.close();
        }
        void updateDailyLimit(int accNo,double amount){
            int counter = 1;
            fstream f4,f5;
            f4.open("dailyLimits.txt");
            f5.open("new.txt",ios::app);
            while(getline(f4,line)){
                if(counter == 1){
                    f5<<line<<endl;
                }
                else if(counter !=1){
                    stringstream ss(line);
                    ss>>this->accNo>>accType>>limit;
                    // cout<<this->accNo<<" "<<accType<<" "<<limit<<endl;
                    if(this->accNo==accNo){
                        f5<<this->accNo<<" "<<accType<<" "<<limit+amount<<endl;
                    }
                    else{
                        f5<<this->accNo<<" "<<accType<<" "<<limit<<endl;
                    }
                }
                counter +=1;
            }
            f4.close();
            f5.close();
            remove("dailyLimits.txt");
            rename("new.txt","dailyLimits.txt");
        }
};
class user{
    protected:
        int choice;
        string line;
        string loginId;
        string password;
        fstream f1;
};
class companyClientAccount:public user{
    private:
        int companyNumber = -1;
        string companyName;
        string companyAddress;
        string taxNumber;
        double balance;
        transaction *tr;
        dailyLimit *dl;
    public:
        bool login(){
            cout<<"Enter login id: ";
            cin>>loginId;
            cout<<"Enter password: ";
            cin>>password;
            if(verify()){
                cout<<"Logged in successfully"<<endl;
                return true;
            }
            else{
                cout<<"Login unsuccessful"<<endl;
                return false;
            }
        }
        bool verify(){
            string a,b;
            f1.open("companies.txt");
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>companyNumber>>companyName>>companyAddress>>taxNumber>>a>>b>>balance;
                if(a==loginId && b==password){
                    f1.close();
                    return true;
                }
            }
            f1.close();
            return false;
        }
        void requestLoan(){
            double amount;
            cout<<"Enter the amount of the loan: ";
            cin>>amount;
            f1.open("loanReqs.txt",ios::app);
            f1<<companyNumber<<" "<<amount<<endl;
            f1.close();
            cout<<"The loan of "<<amount<<" has been requested"<<endl;
        }
        void menu(){
            do{ 
                cout<<"------------------------------"<<endl;
                cout<<"1. Assign access to user"<<endl;
                cout<<"2. Request loan"<<endl;
                cout<<"3. Logout"<<endl;
                cout<<"------------------------------"<<endl;
                cin>>choice;
                if(choice == 1){
                    assignAccess();
                }
                else if(choice == 2){
                    requestLoan();
                }
                else if(choice == 3){
                    cout<<"Logging out"<<endl;
                }
                else{
                    cout<<"Wrong input"<<endl;
                }
            }while(choice != 3);
        }
        void showBalance(){
            int a;
            f1.open("companies.txt");
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>a>>companyName>>companyAddress>>taxNumber>>loginId>>password>>balance;
                if(a==companyNumber){
                    cout<<"Current Balance = "<<balance;
                    f1.close();
                    return;
                }
            }
            f1.close();
        }
        void deposit(){
            double depositAmount;
            cout<<"Enter the amount you want to deposit: ";
            cin>>depositAmount;
            balance += depositAmount;
            tr = new transaction();
            tr->deposit(companyNumber,depositAmount,"companies.txt");
            delete tr;
        }
        void withdraw(){
            double withdrawAmount;
            cout<<"Enter the amount you want to withdraw: ";
            cin>>withdrawAmount;
            int a;
            f1.open("companies.txt");
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>a>>companyName>>companyAddress>>taxNumber>>loginId>>password>>balance;
                if(a==companyNumber){
                    f1.close();
                    break;
                }
            }
            if(withdrawAmount>balance){
                cout<<"Not enough balance"<<endl;
                cout<<"Current balance = "<<balance<<endl;
            }
            else{
                dl = new dailyLimit();
                if(dl->checkLimit(companyNumber,withdrawAmount)){
                    dl->updateDailyLimit(companyNumber,withdrawAmount);
                    balance-=withdrawAmount;
                    tr = new transaction();
                    tr->withdraw(companyNumber,withdrawAmount,"companies.txt");
                    delete tr;
                }
                delete dl;
                
            }
        }
        bool checkAccountExists(int toAccNo){
            int a;
            f1.open("Users.txt");
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>a;
                if(a==toAccNo){
                    f1.close();
                    return true;
                }
            }
            f1.close();
            return false;
        }
        void transferFunds(){
            double sendAmount;
            int toAccNo,a;
            cout<<"Please enter the account no for tranfer: "<<endl;
            cin>>toAccNo;
            if(checkAccountExists(toAccNo)){
                cout<<"Enter the amount to transfer: ";
                cin>>sendAmount;
                // storing balance:
                f1.open("companies.txt");
                while(getline(f1,line)){
                    stringstream ss(line);
                    ss>>a>>companyName>>companyAddress>>taxNumber>>loginId>>password>>balance;
                    if(a==companyNumber){
                        f1.close();
                        break;
                    }
                }
                if(sendAmount>balance){
                    cout<<"Not enough balance"<<endl;
                    cout<<"Current balance = "<<balance<<endl;
                }
                else{
                    balance-=sendAmount;
                    tr = new transaction();
                    tr->sendAmount_C(companyNumber,toAccNo,sendAmount);
                    delete tr; 
                }
            }
            else{
                cout<<"The account no "<<toAccNo<<" does not exists."<<endl;
            }
            
        }
        void viewTransactions(){
            tr = new transaction();
            tr->viewTransactions(companyNumber,"companiesTransactions.txt");
            delete tr;
        }
        void menuAsEmployee(int accNo){
                companyNumber = accNo;
            do{
                cout<<"------------------------------"<<endl;
                cout<<"1. View Account Balance"<<endl;
                cout<<"2. Deposit Money"<<endl;
                cout<<"3. Withdraw Money"<<endl;
                cout<<"4. Transfer funds"<<endl;
                cout<<"5. View Transactions"<<endl;
                cout<<"6. Logout"<<endl;
                cout<<"------------------------------"<<endl;
                cin>>choice;
                if(choice == 1){
                    showBalance();
                }
                else if(choice == 2){
                    deposit();
                }
                else if(choice == 3){
                    withdraw();
                }
                else if(choice == 4){
                    transferFunds();
                }
                else if(choice == 5){
                    viewTransactions();
                }
                else if(choice ==6){
                    cout<<"Logging out"<<endl;
                }
                else{
                    cout<<"Wrong input"<<endl;
                }
            }while(choice != 6);
        }
        void setLimit(){
            f1.open("dailyLimits.txt",ios::app);
            f1<<companyNumber<<" "<<"business"<<" "<<"0"<<endl;
            f1.close();
        }
        void makeAccount(){
            cout<<"Enter your company's name: ";
            cin>>companyName;
            cout<<"Enter your company's Address: ";
            cin>>companyAddress;
            cout<<"Enter your company's tax number: ";
            cin>>taxNumber;
            cout<<"Choose your account's id: ";
            cin>>loginId;
            cout<<"Choose your account's password: ";
            cin>>password;
            registerAccount();
        }
        void generateCompanyNumber(){
            f1.open("companies.txt");
            while(getline(f1,line)){
                companyNumber-=1;
            }
            f1.close();
        }
        void registerAccount(){
            generateCompanyNumber();
            f1.open("companies.txt",ios::app);
            f1<<companyNumber<<" "<<companyName<<" "<<companyAddress<<" "<<taxNumber<<" "<<loginId<<" "<<password<<" "<<0<<endl;
            f1.close();
            setLimit();
            cout<<"Account registered successfully"<<endl;
        }
        void assignAccess(){
            // ask the account no check it exits or not then enter
            int accNo,a;
            cout<<"Enter the employee's account number for permission: ";
            cin>>accNo;
            // check whether account exists or not
            f1.open("Users.txt");
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>a;
                if(a==accNo){
                    f1.close();
                    f1.open("companiesEmployees.txt",ios::app);
                    f1<<accNo<<" "<<companyNumber<<endl;
                    f1.close();
                    cout<<"Account no "<<accNo<<" assigned access successfully"<<endl;
                    return;
                }
            }
            cout<<"Account no "<<accNo<<" not exists"<<endl;
        }
};
class userClient : public user{
    protected:
        int accountNo;
        string name;
        string address;
        string phoneNo;
        string cnic;
        string accountType;
        double balance;
        card *crd;
        transaction *tr;
        dailyLimit *dl;
    public:
        void makeAccount(){
            setName();setAddress();setPhone();setCnic();setLoginId();setPassword();setAccountType();
            request();
            cout<<"Account aaplication has been submitted. Wait till it is approved to start using it."<<endl;
        }
        void setName(){cout<<"Enter your name: ";cin>>name;}
        void setAddress(){cout<<"Enter your address: ";cin>>address;}
        void setPhone(){cout<<"Enter your phone number: ";cin>>phoneNo;}
        void setCnic(){cout<<"Enter your cnic number: ";cin>>cnic;}
        void setLoginId(){cout<<"Set your login Id: ";cin>>loginId;}
        void setPassword(){cout<<"Set your password: ";cin>>password;}
        void setAccountType(){
            cout<<"1. Bronze Account"<<endl;
            cout<<"2. Gold Account"<<endl;
            cin>>choice;
            while(choice != 1 && choice !=2){
                cout<<"Wrong choice.. Enter again: "<<endl;
                cout<<"1. Bronze Account"<<endl;
                cout<<"2. Gold Account"<<endl;
                cin>>choice;
            }
            if(choice == 1){
                accountType = "bronze";
            }
            else if(choice == 2){
                accountType = "gold";
            }
        }
        void request(){
            f1.open("AccReqs.txt",ios::app);
            f1<<name<<" "<<address<<" "<<phoneNo<<" "<<cnic<<" "<<accountType<<" "<<loginId<<" "<<password<<" "<<"Pending"<<endl;
            f1.close();
        }
        bool login(){
            cout<<"Enter id: ";
            cin>>loginId;
            cout<<"Enter password: ";
            cin>>password;
            if(verify()){
                cout<<"Logged in successfully"<<endl;
                return true;
            }
            else{
                if(verifyApplications()){
                }
                else{
                    cout<<"Login unsuccessful"<<endl;
                }
                return false;
            }
        }
        bool verify(){
            string a,b;
            long long c;
            f1.open("Users.txt");
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>accountNo>>a>>b>>c>>accountType>>address>>balance; // also making account ready to use
                if(a==loginId && b==password){
                    crd = new card();
                    crd->setCardNo(c);
                    f1.close();
                    return true;
                }             
            }
            f1.close();
            return false;
        }
        bool verifyApplications(){
            string a,b,c;
            f1.open("AccReqs.txt");
            f1.seekg(0,ios::beg);
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>name>>address>>phoneNo>>cnic>>accountType>>a>>b>>c;
                if(a==loginId && b==password){
                    cout<<"Account application Status: "<<c<<endl;
                    f1.close();
                    return true;
                }             
            }
            f1.close();
            return false;
        }
        void checkNotifications(){
            int a;
            string b,c;
            f1.open("Notifications.txt");
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>a>>b>>c;
                if(a == accountNo){
                    cout<<"Notification type: "<<c<<endl;
                    if(c == "ChoosePin"){
                        cout<<"Here is your newly issued card no: "<<b<<endl;
                        cout<<"Please choose a PIN (4-digits) for your card to activate it:"<<endl;
                        if(crd->setPin()){
                            // delete notification();
                        }
                    }
                }
            }
            f1.close();
        }
        void deposit(){
            double depositAmount;
            cout<<"Enter the amount you want to deposit: ";
            cin>>depositAmount;
            balance += depositAmount;
            tr = new transaction();
            tr->deposit(accountNo,depositAmount,"Users.txt");
            delete tr;
        }
        void withdraw(){
            double withdrawAmount;
            cout<<"Enter the amount you want to withdraw: ";
            cin>>withdrawAmount;
            if(withdrawAmount>balance){
                cout<<"Not enough balance"<<endl;
                cout<<"Current balance = "<<balance<<endl;
            }
            else{
                if(crd->checkPin()){
                    dl = new dailyLimit();
                    if(dl->checkLimit(accountNo,withdrawAmount)){
                        dl->updateDailyLimit(accountNo,withdrawAmount);
                        balance-=withdrawAmount;
                        tr = new transaction();
                        tr->withdraw(accountNo,withdrawAmount,"Users.txt");
                        delete tr;
                    }
                    delete dl;
                }
                else{
                    cout<<"Wrong input"<<endl;
                }
            }
        }
        bool checkAccountExists(int toAccNo){
            int a;
            f1.open("Users.txt");
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>a;
                if(a==toAccNo){
                    f1.close();
                    return true;
                }
            }
            f1.close();
            return false;
        }
        void transferAmount(){
            double sendAmount;
            int toAccNo;
            cout<<"Please enter the account no for tranfer: "<<endl;
            cin>>toAccNo;
            if(checkAccountExists(toAccNo)){
                cout<<"Enter the amount to transfer: ";
                cin>>sendAmount;
                if(sendAmount>balance){
                    cout<<"Not enough balance"<<endl;
                    cout<<"Current balance = "<<balance<<endl;
                }
                else{
                    if(crd->checkPin()){
                        balance-=sendAmount;
                        tr = new transaction();
                        tr->sendAmount(accountNo,toAccNo,sendAmount);
                        delete tr; 
                    }
                }
            }
            else{
                cout<<"Account no "<<toAccNo<<" not exists."<<endl;
            }
            
        }
        void viewTransactionHistory(){
            tr = new transaction();
            tr->viewTransactions(accountNo,"Transactions.txt");
            delete tr;
        }
        void accessCompanyAccount(){
            int companyAccNo,a,b;
            cout<<"Enter your company's account no: "<<endl;
            cin>>companyAccNo;
            f1.open("companiesEmployees.txt");
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>a>>b;
                if(a==accountNo && b==companyAccNo){
                    cout<<"Logged in successfully"<<endl;
                    companyClientAccount cca1;
                    cca1.menuAsEmployee(companyAccNo);
                    break;
                }
            }
            f1.close();
        }
        void menu(){
            do{
                cout<<"------------------------------"<<endl;
                cout<<"1. Deposit Balance"<<endl;
                cout<<"2. Withdraw balance"<<endl;
                cout<<"3. Transfer Money"<<endl;
                cout<<"4. Check Notifications"<<endl;
                cout<<"5. View Account Balance"<<endl; //check newly
                cout<<"6. View Transaction History"<<endl;
                cout<<"7. Access Your Company's Accout"<<endl;
                cout<<"8. Logout"<<endl;
                cout<<"------------------------------"<<endl;
                cout<<"Check your notifications if you have newly opened your account"<<endl;
                cin>>choice;
                if(choice == 1){
                    deposit();
                }
                else if(choice == 2){
                    withdraw();
                }
                else if(choice == 3){
                    transferAmount();
                }
                else if(choice == 4){
                    checkNotifications();
                }
                else if(choice == 5){
                    cout<<"Current Balance = "<<balance<<endl;
                }
                else if(choice == 6){
                    viewTransactionHistory();
                }
                else if(choice == 7){
                    accessCompanyAccount();
                }
                else if(choice == 8){
                    cout<<"Logging out"<<endl;
                }
                else{
                    cout<<"Wrong output"<<endl;
                }
            }while(choice!=8);
        }
        ~userClient(){
            delete crd;
        }

};
class employee: public user{
    private:
        transaction *tr;
        dailyLimit *dl;
    public:
        bool login(){
            cout<<"Enter id: ";
            cin>>loginId;
            cout<<"Enter password: ";
            cin>>password;
            if(verify()){
                cout<<"Logged in successfully"<<endl;
                return true;
            }
            else{
                cout<<"Wrong credentials"<<endl;
                return false;
            }
        }
        bool verify(){
            f1.open("admin.txt");
            f1.seekg (0,ios::beg);
            string i,p;
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>i>>p;
                if(i == loginId && p==password){
                    f1.close();
                    return true;
                }
            }
            f1.close();
            return false;
        }
        void viewClientAccounts(){
            string a,b,c,d,e,f,g;
            f1.open("Users.txt");
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>a>>b>>c>>d>>e>>f>>g;
                cout<<"----------------------"<<endl;
                cout<<"Account no "<<a<<endl;
                cout<<"----------------------"<<endl;
                cout<<"Login id: "<<b<<endl;
                cout<<"Account type: "<<e<<endl;
                cout<<"Address: "<<f<<endl;
                cout<<"Current Balance = "<<g<<endl;
            }
            f1.close();

        }
        void viewCompanyAccounts(){
            string a,b,c,d,e,f,g;
            f1.open("companies.txt");
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>a>>b>>c>>d>>e>>f>>g;
                cout<<"----------------------"<<endl;
                cout<<"Account no "<<a<<endl;
                cout<<"----------------------"<<endl;
                cout<<"Company Name: "<<b<<endl;
                cout<<"Company Address: "<<c<<endl;
                cout<<"Company's Tax Number: "<<d<<endl;
                cout<<"Current Balance = "<<g<<endl;
            }
            f1.close();
        }
        void viewUserTranHistory(){
            int accNo;
            string a,b,c,d,e,f;
            cout<<"Enter account number for transaction history: ";
            cin>>accNo;
            tr = new transaction();
            tr->viewTransactions(accNo,"Transactions.txt");
            delete tr;
        }
        void viewCompanyTranHistory(){
            int accNo;
            string a,b,c,d,e,f;
            cout<<"Enter account number for transaction history: ";
            cin>>accNo;
            tr = new transaction();
            tr->viewTransactions(accNo,"companiesTransactions.txt");
            delete tr;
        }
        void checkLoanRequests(){
            string cNo,a;
            f1.open("loanReqs.txt");
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>cNo>>a;
                cout<<"Loan Request: "<<endl;
                cout<<"Company Number: "<<cNo<<endl;
                cout<<"Amount requested: "<<a<<endl;
            }
            f1.close();
        }
        void removeRequest(int cNo){
            int a,b;
            f1.open("loanReqs.txt");
            ofstream f2("New.txt");
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>a>>b;
                if(a!=cNo){
                    f2<<a<<" "<<b<<endl;
                }
            }
            f1.close();
            f2.close();
            remove("loanReqs.txt");
            rename("New.txt","loanReqs.txt");
        }
        void acceptLoanRequest(){
            double amount;
            int cNo,a;
            string c;
            cout<<"Enter the company number: "<<endl;
            cin>>cNo;
            f1.open("loanReqs.txt");
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>a>>amount;
                if(a==cNo){
                    cout<<"Request for "<<amount<<".Accept? (y/Y): ";
                    cin>>c;
                    break;
                }
            }
            f1.close();
            if(c == "y" || c== "Y"){
                tr = new transaction();
                tr->deposit(cNo,amount,"companies.txt");
                delete tr;
                removeRequest(cNo);
            }
        }
        void menu(){
            do{
                cout<<"------------------------------"<<endl;
                cout<<"1. View clients accounts"<<endl;
                cout<<"2. Approve/reject account applications"<<endl;
                cout<<"3. Approve/reject loan requests"<<endl;
                cout<<"4. View transaction history"<<endl;
                cout<<"5. Freeze/close account"<<endl;
                cout<<"6. logout"<<endl;
                cout<<"------------------------------"<<endl;
                cin>>choice;
                if (choice == 1){
                    cout<<"1. View user client accounts."<<endl;
                    cout<<"2. View company client accounts"<<endl;
                    cin>>choice;
                    if(choice == 1){
                        viewClientAccounts();
                    }
                    else if(choice == 2){
                        viewCompanyAccounts();
                    }
                }
                else if(choice == 2){
                    cout<<"1. View account applications"<<endl;
                    cout<<"2. Approve account application"<<endl;
                    cout<<"3. Reject account application"<<endl;
                    cin>>choice;
                    if(choice == 1){
                        ViewAccountApplications();
                    }
                    else if(choice == 2){
                        approveRequest();
                    }
                    else if(choice == 3){
                        rejectApplication();
                    }
                }
                else if(choice == 3){
                    cout<<"1. Check loan requests"<<endl;
                    cout<<"2. Accept loan request"<<endl;
                    cout<<"3. Reject loan requests"<<endl;
                    cin>>choice;
                    if(choice == 1){
                        checkLoanRequests();
                    }
                    else if(choice == 2){
                        acceptLoanRequest();
                    }
                    else if(choice==3){
                        int accNo;
                        cout<<"Enter account no to reject loan request: ";
                        cin>>accNo;
                        removeRequest(accNo);
                        cout<<"If there was a request, then it is rejected successfully"<<endl;
                    }
                }
                else if(choice == 4){
                    cout<<"1. View user client transaction history."<<endl;
                    cout<<"2. View company client transaction history"<<endl;
                    cin>>choice;
                    if(choice == 1){
                        viewUserTranHistory();
                    }
                    else if(choice == 2){
                        viewCompanyTranHistory();
                    }
                }
                else if(choice == 6){
                    cout<<"Logging out"<<endl;
                }
                else{
                    cout<<"Logging out"<<endl;
                }
            }while(choice !=6);
        }
        void ViewAccountApplications(){
            f1.open("AccReqs.txt");
            f1.seekg(0,ios::beg);
            string a,b,c,d,e;
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>a>>b>>c>>d>>e;
                cout<<"Account application: "<<endl;
                cout<<"Name: "<<a<<endl;
                cout<<"Address: "<<b<<endl;
                cout<<"Phone no: "<<c<<endl;
                cout<<"Cnic no: "<<d<<endl;
                cout<<"Account type = "<<e<<endl;
            }
            f1.close();
        }
        int generateAccountNo(){
            int n = 1;
            string line2;
            ifstream f4; //making new variable as f1 is already in use which is causing error
            f4.open("Users.txt");
            f4.seekg(0,ios::beg);
            while(getline(f4,line2)){
                n+=1;
            }
            cout<<n<<endl;
            f4.close();
            return n;
        }
        long long generateCreditCardNumber(){
            mt19937_64 rng(time(nullptr)); 
            uniform_int_distribution<long long> dist(1000000000000000, 9999999999999999); 
            return dist(rng);
        }
        void setLimit(int an,string e){
            ofstream f11;
            f11.open("dailyLimits.txt",ios::app);
            f11<<an<<" "<<e<<" "<<0<<endl;
            f11.close();
        }
        void approveRequest(){
            string cnic,a,b,c,d,e,f,g,h;
            cout<<"Enter the cnic of person submitted the application: ";
            cin>>cnic;
            f1.open("AccReqs.txt");
            f1.seekg(0,ios::beg);
            ofstream f2("new.txt",ios::app);
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>a>>b>>c>>d>>e>>f>>g>>h;
                if(d!=cnic){
                    f2<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<" "<<f<<" "<<g<<" "<<h<<endl;
                }
                else if(d==cnic){
                    int an = generateAccountNo();
                    long long cn = generateCreditCardNumber();
                    ofstream f3("Users.txt",ios::app);
                    f3<<an<<" "<<f<<" "<<g<<" "<<cn<<" "<<e<<" "<<b<<" "<<0<<endl;
                    f3.close();
                    setLimit(an,e);
                    sendPinNotification(an,cn);
                    cout<<"Account application approved successfully!"<<endl;
                }
            }
            f1.close();
            f2.close();
            remove("AccReqs.txt");
            rename("new.txt","AccReqs.txt");
        }
        void sendPinNotification(int a,long long b){
            ofstream f9;
            f9.open("Notifications.txt",ios::app);
            f9<<a<<" "<<b<<" "<<"ChoosePin"<<endl;
            f9.close();
        }
        void rejectApplication(){
            string cnic,line,a,b,c,d,e,f,g,h;
            cout<<"Enter the cnic of person submitted the application: ";
            cin>>cnic;
            f1.open("AccReqs.txt");
            f1.seekg(0,ios::beg);
            ofstream f2("new.txt",ios::app);
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>a>>b>>c>>d>>e>>f>>g;
                if(d!=cnic){
                    f2<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<" "<<f<<" "<<g<<" "<<h<<endl;
                }
                else if(d==cnic){
                    f2<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<" "<<f<<" "<<g<<" "<<"Rejected"<<endl;
                }
            }
            f1.close();
            f2.close();
            remove("AccReqs.txt");
            rename("new.txt","AccReqs.txt");
            cout<<"Account application rejected successfully!"<<endl;
        }

};

class ceo:public user{
    private:
        companyClientAccount *cca;
    public:
        bool login(){
            cout<<"Enter your login id: ";
            cin>>loginId;
            cout<<"Enter your password: ";
            cin>>password;
            if(authenticate()){
                cout<<"Login successful"<<endl;
                return true;
            }
            return false;
        }
        bool authenticate(){
            string a,b;
            f1.open("CEO.txt");
            while(getline(f1,line)){
                stringstream ss(line);
                ss>>a>>b;
                if(a==loginId && b==password){
                    return true;
                }
            }
            f1.close();
            return false;
        }
        void openCompanyClientAccount(){
            cca = new companyClientAccount();
            cca->makeAccount();
            delete cca;
        }
        void menu(){
            do{
                cout<<"------------------------------"<<endl;
                cout<<"1. Make Company client account"<<endl;
                cout<<"2. Check anyone's account"<<endl;
                cout<<"3. Steal everyone's money"<<endl;
                cout<<"4. Logout"<<endl;
                cout<<"------------------------------"<<endl;
                cin>>choice;
                if(choice == 1){
                    openCompanyClientAccount();
                }
                else if(choice == 3){
                    cout<<"This is haram bro....."<<endl;
                }
                else if(choice ==4){
                    cout<<"Logging out"<<endl;
                }
                else{
                    cout<<"Wrong input"<<endl;
                }
            }while(choice !=4 );
        }
};
int main(){
    // system("Color 0A");
    dailyLimit dl;
    dl.setLimit();
    int choice;
    do{
        cout<<"------------------------------"<<endl;
        cout<<"Enter 1 to login as user. "<<endl;
        cout<<"Enter 2 to login as admin. "<<endl;
        cout<<"Enter 3 to login as company client"<<endl;
        cout<<"Enter 4 to make account."<<endl;
        cout<<"Enter 5 to exit."<<endl;
        cout<<"------------------------------"<<endl;
        cin>>choice;
        if(choice == 1){
            userClient uc;
            if(uc.login()){
                uc.menu();
            }
        }
        else if(choice == 2){
            employee e;
            if(e.login()){
                e.menu();
            }
        }
        else if(choice == 3){
            companyClientAccount cca;
            if(cca.login()){
                cca.menu();
            }
        }
        else if(choice == 4){
            userClient uc;
            uc.makeAccount();
        }
        else if(choice == 34592){
            system("Color DE");
            ceo ccc;
            if(ccc.login()){
                ccc.menu();
            }
        }
        else if(choice == 5){
            cout<<"Exiting"<<endl;
        }
        else{
            cout<<"Wrong input"<<endl;
        }
    }while(choice != 5);
}