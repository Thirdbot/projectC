#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;



class Storage
{
    //one use temporary holding username and password
    protected:
    struct acc_info
    {
        string username;
        string password;
        int balance;
    }acc;
    struct bankDebt
    {
        string name = "Bank";
        string password = "1234";
        int amount;
    }bdebt;
    struct bankessential
    {
        int fee=0;
    }bs;
    

    //file
    protected:
        fstream bankfile;
        fstream file;

    public:
    //update file by amount of money
    bool Bankdeposit(string,int);
    //update file by amount of money
    bool Bankwithdraw(string,int);
    //transfer service using deposit and withdraw
    bool Transfer();
    //seperate bank file
    void createBankFile(string,string,int,int);
    //loop register/login page
    bool accountCheck(string,string);
    //return either true or false based on username password
    bool verifyPassword(string,string);
    //registering an account process 
    bool registerAccount(string,string);
    bool BankTransfer(string,int);
    bool OwnerTransfer(string,int);
    //void RegisterValidation();

    // check if username existed
    bool accountExists(string);

    //public method for getting name and password and balance for validation
    string getName();
    string getPass();
    int getAmount();
};

//giveaway
bool Storage::Bankdeposit(string reciever,int amount)
{
    if (amount < 0)
    {
        return false;
    }
    else
    {
    string username, password;
    int balance;
    string fileName = "accounts.txt";

    //iterator for reading balance at username
    if(Bankwithdraw(this->acc.username,amount) == false){return false;}
    ifstream depo(fileName);
    ofstream outfile("account_copy.txt");

    while (depo >> username >> password >> balance )
        {
            if (username == reciever)
            {
                balance = balance+amount;
                
            }
            outfile << username << " " << password << " " << balance << endl;
        }
    cout << "Transfer successful. money transfered : " << amount << endl;
    depo.close();
    outfile.close();
    remove(fileName.c_str());
    string origFile = "accounts.txt";
    remove(origFile.c_str());
    rename("account_copy.txt","accounts.txt");
    return true;
    
    }
}

bool Storage::Bankwithdraw(string Sender,int amount)
{
    //this->acc.username
    if (amount < 0)
    {
        return false;
    }
    else
    {
    string username, password;
    int balance;
    string fileName = "accounts.txt";
    //read file temporary
    ifstream wit(fileName);
    ofstream outfile("account_copy.txt");
    bool failed = false;
    //iterator for reading balance at username
    while (wit >> username >> password >> balance)
    {
        if (username == Sender)
        {
            if(balance >= amount)
            {
                balance = balance - amount-bs.fee;
                cout << "Transfer successful." << Sender << " new balance: " << balance << endl;
                this->acc.balance = balance;
            }
            else
            {
                cout << "You may not have enough money to Transfer." << endl;
                failed = true;
            }

        }

        outfile << username << " " << password << " " << balance << endl;
    }
    wit.close();
    outfile.close();
    remove(fileName.c_str());

    //string deponame = "depoacc.txt";
    rename("account_copy.txt",fileName.c_str());

    if(!failed)
    {
        return true;
    }
    else{return false;};
    
    }
}

void Storage::createBankFile(string uname1,string uname2,int size,int total)
{
    string usender,ureciever;
    int balance,amount;
    string fileName = "BankFile.txt";
    cout << "Bankfile Created" << endl;
    //read file temporary
    file.open(fileName,ios::out|ios::app);
    file << uname1 << " " << uname2 << " " <<  size << " " << total << endl;
    file.close();


}
bool Storage::Transfer()
{
    string reciever;
    int amount;
    cout << "Transfer Money" << endl;
    cout << "Enter reciever name: ";
    cin >> reciever;
    if (accountExists(reciever))
    {
        cout << "From:" << acc.username << " To " << reciever << endl;
        cout << "Enter Amount of money: ";
        cin >> amount;
        if(Bankdeposit(reciever,amount))
        {
            createBankFile(acc.username,reciever,amount,acc.balance);
            return true;
        }
        else
        {
            return false;
        } 
    }
    else
    {
        return false;
    }
   
}
bool Storage::OwnerTransfer(string reciever,int amount)
{
    if (amount < 0)
    {
        return false;
    }
    else
    {
    string username, password;
    int balance;
    string fileName = "accounts.txt";

    //iterator for reading balance at username
    if(Bankwithdraw(this->bdebt.name,amount) == false){return false;}
    ifstream depo(fileName);
    ofstream outfile("account_copy.txt");

    while (depo >> username >> password >> balance )
        {
            if (username == reciever)
            {
                balance = balance+amount;
                
            }
            outfile << username << " " << password << " " << balance << endl;
        }
    cout << "Transfer successful. money transfered : " << amount << endl;
    depo.close();
    outfile.close();
    remove(fileName.c_str());
    string origFile = "accounts.txt";
    remove(origFile.c_str());
    rename("account_copy.txt","accounts.txt");
    return true;
    
    }
}
bool Storage::BankTransfer(string receivername,int amount)
{
    if (accountExists(receivername))
    {
        cout << "From:" << bdebt.name << " To " << receivername << endl;
        if(OwnerTransfer(receivername,amount))
        {
            createBankFile(bdebt.name,receivername,amount,acc.balance);
            return true;
        }
        else
        {
            return false;
        } 
    }
    else
    {
        return false;
    }
   
}
//return protected structure contains balance
int Storage::getAmount()
{
    return acc.balance;
};
//return protected structure contains username
string Storage::getName()
{
    return acc.username;
};
//return protected structure contains pass
string Storage::getPass()
{
    return acc.password;
};

//return true if username and password is registered (for login parts)
bool Storage::verifyPassword(string username, string password)
        {
            file.open("accounts.txt", ios::in);

            string file_username;
            string file_password;
            int amount;
            while (file >> file_username >> file_password >> amount)
            {
                if (file_username == username && file_password == password)
                {
                    acc.username = file_username;
                    acc.password = file_password;
                    file.close();
                    return true;
                }
            }

            file.close();
            return false;
        }

//a method that return true if verifyPassword also return true and return false if not (use for login loop)
bool Storage::accountCheck(string uname, string upass)
        {
            if (verifyPassword(uname, upass))
            {
                return true;
            }
            else
            {
                cout << "Invalid username or password. Please try again." << endl;
                return false;
            }
        }

//registering part
bool Storage::registerAccount(string username, string pass)
        {
            file.open("accounts.txt",ios::out|ios::app);

            file << username << " " << pass << " " << 0 << endl;
            file.close();

            cout << "Account registered successfully!" << endl;
            
            return true;
        }

//return true/false based on account existed or not (use for register loop) and use for returning
bool Storage::accountExists(string username)
    {
        file.open("accounts.txt", ios::in);

        string file_username;
        string password;
        int amount;
        while (file >> file_username >> password >> amount)
        {
            if (file_username == username)
            {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }
/*void Storage::RegisterValidation()
{
    string username;
    string password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (accountExists(username))
    {
        cout << "Account with this username already exists. Please choose another username." << endl;
    }

    bool success = registerAccount(username, password);
    
}*/
class Debt:virtual public Storage

{
    protected:
    

    public:
    bool checkMoneyUser();
    bool checkMoneyBank();
    //choice display 
    void customerChoice();
    //choice selection
    void debtChoice();
    //method for loan money
    void loanMoney();
    //method for repay money
    void repayMoney();
};
bool Debt::checkMoneyUser()
{
        string fileName = "accounts.txt";
        //need personal balance checking
        file.open(fileName, ios::in);
        //iterator for reading balance at username
        string file_username;
        string file_password;
        int amount;
        while (file >> file_username >> file_password >> amount)
        {
            if (file_username == acc.username && file_password == acc.password)
                {
                    acc.balance = amount;
                }
            }

        file.close();
        if(acc.balance > 0)
        {
            return true;
        }
        else
        {
        return false;
    }
}
bool Debt::checkMoneyBank()
{
        string fileName = "accounts.txt";
        //need personal balance checking
        file.open(fileName, ios::in);
        //iterator for reading balance at username
        string file_username;
        string file_password;
        int amount;
        while (file >> file_username >> file_password >> amount)
        {
            if (file_username == bdebt.name && file_password == bdebt.password)
                {
                    bdebt.amount = amount;
                }
            }

        file.close();
        if(bdebt.amount > 0)
        {
            return true;
        }
        else
        {
        cout << "Bank run out of money" << endl;
        cout << "Start include fees in transaction"<<endl;
        bs.fee = 10;
        cout << "Fees:"<<bs.fee<<endl;
        return false;
    }
}

//display choice and called selection part
void Debt::customerChoice()
    {
        const char* selective_choice[] = {"1.Loan money", "2.Repay money", "3.Exit"};
        for (int i = 0; i < sizeof(selective_choice) / sizeof(selective_choice[0]); i++)
        {
            cout << selective_choice[i] << endl;
        }
        cout<<"=================="<<endl;
        debtChoice();

    }
//selection part
void Debt::debtChoice()
    {
        int number_selected;
        cout << "Select choices by number: ";
        cin >> number_selected;
        cout<<"=================="<<endl;
        switch (number_selected)
        {
        case 1:
            loanMoney();
            break;
        case 2:
            repayMoney();
            break;
        case 3:
            break;
        default:
            customerChoice();
            break;
        }
    
    }
void Debt::loanMoney() {
    double amount;
    cout << "Enter amount to loan: ";
    cin >> amount;

    string line; // Declare the line variable here
    string filename = "Debt.txt";
    ifstream infile(filename);
    ofstream outfile("Debt_copy.txt");
    bool found = false;

    while (getline(infile, line)) {
        string username;
        double debt;
        istringstream iss(line);

        if (iss >> username >> debt) {
            if (username == acc.username) {
                debt += amount; // Add new loan amount to existing debt
                outfile << username << " " << debt << endl;
                cout << "Loan request processed. Thank you!" << endl;
                bdebt.amount -= debt;
                if(checkMoneyBank())
                {
                    BankTransfer(acc.username,debt);
                }
                else
                {
                    debtChoice();
                }
                    
                found = true;
            } else {
                outfile << line << endl;
            }
        }
    }
    infile.close();

    // If the user does not exist in the debt file, add a new entry
    if (!found) {
        outfile << acc.username << " " << amount << endl;
        cout << "Loan request processed. Thank you!" << endl;
    }

    outfile.close();
    remove(filename.c_str());
    rename("Debt_copy.txt", filename.c_str());

    customerChoice();
}

void Debt::repayMoney() {
    double amount;
    cout << "Enter amount to repay: ";
    cin >> amount;
    string line;
    string filename = "Debt.txt";
    ifstream infile(filename);
    ofstream outfile("Debt_copy.txt");
    bool found = false;

    while (getline(infile, line)) {
        string username;
        double debt;
        istringstream iss(line);
        if (iss >> username >> debt) {
            if (username == acc.username && debt >= amount) {
                debt -= amount;
                outfile << username << " " << debt << endl;
                cout << "Repayment of " << amount << " successful." << endl;
                if(checkMoneyUser())
                {
                    BankTransfer(bdebt.name,amount);
                }
                else
                {
                    cout << "You not have enough money to pay debt.";
                    debtChoice();
                }
                found = true;
            } else {
                outfile << line << endl;
            }
        }
    }
    infile.close();
    outfile.close();
    remove(filename.c_str());
    rename("Debt_copy.txt", filename.c_str());

    if (!found) {
        cout << "Error: User does not have enough debt to repay or user not found." << endl;
    }

    customerChoice();
}


class Bank:virtual public Storage,public Debt
{
    public:
    //constructor for welcomeing
    Bank()
    {
        cout << "Welcome to Bank."<<endl;
    }
    //create account and use accountExist method
    void accountCreate();
    //choice selection for register or login (use for register login loop)
    void accountValidation();
    //account changing
    void changeAccount();
    //autologin
    void autoLogin(string,string);
    //update file by amount of money
    void deposit();
    //update file by amount of money
    void withdraw();
    //view file output a  Balance
    void checkBalance();
    //choice display
    void viewChoice();
    //choice selection
    void selectChoice();
    //destructor after method selectChoice done
     ~Bank()
            {
                cout << "Exit successfully,Thank you for services" <<endl;
            };
};

//select choice
void Bank::selectChoice()
        {
            int number_selected;
            cout << "select choices by number: ";
            cin >> number_selected;
            cout<<"=================="<<endl;
            switch (number_selected)
            {
                case 1:
                {
                    withdraw();
                    viewChoice();
                    break;
                }
                    
                case 2:
                {
                    deposit();
                    viewChoice();
                    break;
                }
                    
                case 3:
                {
                    checkBalance();
                    break;
                }
                    
                case 4:
                {
                    customerChoice();
                    viewChoice();
                    break;
                }
                case 5:
                {
                    Transfer();
                    viewChoice();
    
                }
                case 6:
                {
                    changeAccount();
                }
                case 7:
                {
                    delete this;
                    break;
                }
                default:
                    viewChoice();
                    break;
            }
        
        }
//choice display and called selectChoice
void Bank::viewChoice()
        {
            const char* selective_choice[] = {"1.Withdraw","2.Deposit","3.Balance","4.Loan","5.Transfer","6.ChangeAccount","7.Exit"};
            cout<<"=================="<<endl;
            cout <<"Username: "<< getName() << endl;
            cout<<"=================="<<endl;
            for (int i=0;i<size(selective_choice);i++)
            {
                cout <<selective_choice[i] << endl;
            }
            cout<<"=================="<<endl;
            selectChoice();
        }

//display Balance
void Bank::checkBalance()
        {
            string fileName = "accounts.txt";
            //need personal balance checking
            file.open(fileName, ios::in);
            //iterator for reading balance at username
            string file_username;
            string file_password;
            int amount;

            while (file >> file_username >> file_password >> amount)
            {
                if (file_username == this->acc.username && file_password == this->acc.password)
                {
                    cout << "Current Balance:" << amount<<endl;
                    
                }
            }
            file.close();
            
            viewChoice();
        }

//create account if username is not existed
void Bank::accountCreate()
        {
            string username;
            string password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            if (accountExists(username))
            {
                cout << "Account with this username already exists. Please choose another username." << endl;
                accountValidation();
                
            }
            if(registerAccount(username,password))
            {
                autoLogin(username,password);
            }
        }
void Bank::changeAccount()
{
    accountValidation();
}
//auto login
void Bank::autoLogin(string uname,string upass)
{
    if (accountCheck(uname,upass))
    {
        viewChoice();
    }
    else
    {
        accountValidation();
    }
}
//method for select a register or login options
void Bank::accountValidation()
    {
            int rol;
            cout << "register or login" << endl;
            cout << "type 1 for register.\ntype 2 for login." << endl;
            cout << "Type:";
            cin >> rol;
            switch (rol)
            {
            case 1:
                accountCreate();
                break;
            case 2:
                char username[20];
                char userpass[20];
                cout << "Username: ";
                cin >> username;
                cout << "Password:";
                cin >> userpass;


                if (accountCheck(username,userpass))
                {
                    viewChoice();
                }
                accountValidation();

            default:
            {
                break;
            }
            
            }
        }

//write file deposit
void Bank::deposit() 
{

    double amount;
    cout << "Enter Amount to deposit: ";
    cin >> amount;
    if (amount < 0)
    {
    deposit();
    }
    else
    {
    string username, password;
    int balance;
    string fileName = "accounts.txt";
    //read file temporary
    ifstream file(fileName);
    ofstream outfile("account_copy.txt");
    //iterator for reading balance at username
    while (file >> username >> password >> balance)
    {
        if (username == this->acc.username)
        {
        balance += amount;
        cout << "Deposit successful. New balance: " << balance << endl;
        this->acc.balance = balance;
        } 
        outfile << username << " " << password << " " << balance << endl;
    }

    file.close();
    outfile.close();
    remove(fileName.c_str());
    rename("account_copy.txt",fileName.c_str());
    
    }
}
    
    

//write file withdraw
void Bank::withdraw() {
    double amount;
    cout << "Enter Amount to withdraw: ";
    cin >> amount;
    if (amount < 0)
    {
    withdraw();
    }
    else
    {
    string fileName = "accounts.txt";
    string username, password;
    int balance;

    //read file temporary
    ifstream file(fileName);
    ofstream outfile("account_copy.txt");

    //iterator for reading balance at username
    while (file >> username >> password >> balance)
    {  
    if (username == this->acc.username)
    {
        if (amount > balance) 
        {
        cout << "Insufficient funds!" << endl;
        } 
        else 
        {
        balance -= amount;
        cout << "Withdrawal successful. New balance: " << balance << endl;
        this->acc.balance = balance;
        }
    }
    outfile << username << " " << password << " " << balance << endl;
    }
    file.close();
    outfile.close();
    remove(fileName.c_str());
    rename("account_copy.txt",fileName.c_str());
  
    }
    
}

int main()
{
    //make Bank object
    Bank bank;
    //called registeration
    bank.accountValidation();
    return 0;
}