#include <iostream>
#include <fstream>
#include <cstring>
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

    //file
    protected:
        fstream file;

    public:
    //loop register/login page
    bool accountCheck(string,string);
    //return either true or false based on username password
    bool verifyPassword(string,string);
    //registering an account process 
    bool registerAccount(string,string);
    //
    //void RegisterValidation();

    // check if username existed
    bool accountExists(string);

    //public method for getting name and password and balance for validation
    string getName();
    string getPass();
    int getAmount();
};
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

//registering part and return true
bool Storage::registerAccount(string username, string pass)
        {
            file.open("accounts.txt", ios::app);

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
    public:
    //choice display 
    void customerChoice();
    //choice selection
    void debtChoice();
    //method for loan money
    void loanMoney();
    //method for repay money
    void repayMoney();
};
//display choice and called selection part
void Debt::customerChoice()
    {
        const char* selective_choice[] = {"1.Loan money", "2.Repay money", "3.Exit"};
        for (int i = 0; i < sizeof(selective_choice) / sizeof(selective_choice[0]); i++)
        {
            cout << selective_choice[i] << endl;
        }
        debtChoice();

    }
//selection part
void Debt::debtChoice()
    {
        int number_selected;
        cout << "Select choices by number: ";
        cin >> number_selected;
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
//process loan
void Debt::loanMoney()
    {
        double amount;
        cout << "Enter amount to loan: ";
        cin >> amount;
        // Process loan request



        cout << "Loan request processed. Thank you!" << endl;
        customerChoice();
    }

//process repayment
void Debt::repayMoney()
    {
        double amount;
        cout << "Enter amount to repay: ";
        cin >> amount;
        // Process repayment

        cout << "Repayment processed. Thank you!" << endl;
        customerChoice();
    }


class Bank:virtual public Storage,public Debt
{
    public:
    //constructor for welcomeing
    Bank(){cout << "Welcome to Bank."<<endl;}
    //create account and use accountExist method
    void accountCreate();
    //choice selection for register or login (use for register login loop)
    void accountValidation();
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
            switch (number_selected)
            {
                case 1:
                    withdraw();
                    viewChoice();
                    break;
                case 2:
                    deposit();
                    viewChoice();
                    break;
                case 3:
                    checkBalance();
                    break;
                case 4:
                {
                    customerChoice();
                    viewChoice();
                    break;
                }
                case 5:
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
            const char* selective_choice[] = {"1.Withdraw","2.Deposit","3.Balance","4.Loan","5.Exit"};
            cout<<"=================="<<endl;
            cout <<"Username: "<< getName() << endl;
            cout<<"=================="<<endl;
            for (int i=0;i<size(selective_choice);i++)
            {
                cout <<selective_choice[i] << endl;
            }
            selectChoice();
        }

//display Balance
void Bank::checkBalance()
        {
            //need personal balance checking
            file.open("accounts.txt", ios::in);
            if ((file.is_open()) && (file >> this->acc.username >> this->acc.password >> this->acc.balance) )
            {
                cout << "Current Balance:" << this->acc.balance<<endl;
                file.close();
            }
            else{cout << "Error: Unable to read balance from file" << endl;}
            
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

            registerAccount(username, password);
            
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
void Bank::deposit() {
        double amount;
        cout << "Enter Amount to deposit: ";
        cin >> amount;
        file.open("accounts.txt", ios::in);
        string username, password;
        int balance;
        file >> username >> password >> balance;
        file.close();

        balance += amount;

        file.open("accounts.txt", ios::out);
        file << username << " " << password << " " << balance << endl;
        file.close();

    cout << "Deposit successful. New balance: " << balance << endl;
    }
//write file withdraw
void Bank::withdraw() {
    double amount;
    cout << "Enter Amount to withdraw: ";
    cin >> amount;
    file.open("accounts.txt", ios::in);
    string username, password;
    int balance;
    file >> username >> password >> balance;
    file.close();

    if (amount > balance) {
        cout << "Insufficient funds!" << endl;
    } else {
        balance -= amount;

        file.open("accounts.txt", ios::out);
        file << username << " " << password << " " << balance << endl;
        file.close();

        cout << "Withdrawal successful. New balance: " << balance << endl;
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