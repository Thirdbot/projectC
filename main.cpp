#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;


//forwarding
class Bank;

class Storage
{
    private:
    struct acc_info
    {
        string username;
        string password;
    }acc;
    
    protected:
        fstream file;
    public:
    bool accountCheck(string,string);
    bool verifyPassword(string,string);
    bool registerAccount(string,string);
    bool StoreFile();
    bool accountExists(string);
    string getName();
    string getPass();
};

string Storage::getName()
{
    return acc.username;
};
string Storage::getPass()
{
    return acc.password;
};
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
bool Storage::registerAccount(string username, string pass)
        {
            file.open("accounts.txt", ios::app);

            file << username << " " << pass << " " << 0 << endl;

            file.close();

            cout << "Account registered successfully!" << endl;

            return true;
        }
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
bool Storage::StoreFile()
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
        return false;
    }

    bool success = registerAccount(username, password);
    return success;
}
class Debt:virtual public Storage
{
    public:
    void customerChoice();
    void selectChoice();
    ~Debt(){};
    void loanMoney();
    void repayMoney();
};
void Debt::customerChoice()
    {
        const char* selective_choice[] = {"1.Loan money", "2.Repay money", "3.Exit"};
        for (int i = 0; i < sizeof(selective_choice) / sizeof(selective_choice[0]); i++)
        {
            cout << selective_choice[i] << endl;
        }
        selectChoice();

    }
void Debt::selectChoice()
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

void Debt::loanMoney()
    {
        double amount;
        cout << "Enter amount to loan: ";
        cin >> amount;
        // Process loan request
        cout << "Loan request processed. Thank you!" << endl;
        customerChoice();
    }
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

    Bank(){cout << "Welcome to Bank."<<endl;}
    bool accountCreate();
    void accountValidation();
    void deposit();
    void withdraw();
    void checkBalance();
    void viewChoice();
    void selectChoice();
     ~Bank()
            {
                cout << "Exit successfully,Thank you for services" <<endl;
            };
};
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

void Bank::checkBalance()
        {
            //need personal balance checking
            file.open("accounts.txt", ios::in);
            int amount;
            file >> amount;
            cout << "Current Balance:" << amount<<endl;;
            //view choice
            file.close();
            viewChoice();
        }

bool Bank::accountCreate()
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
                return false;
            }

            bool success = registerAccount(username, password);
            return success;
        }
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
                accountValidation();
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
            default:
            {
                break;
            }
            
            }
        }
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
    Bank bank;
    bank.accountValidation();
    return 0;
}