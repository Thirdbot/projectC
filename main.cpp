#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class Debt
{
    public:
    void customer_Choice()
    {
        const char* selective_choice[] = {"1.Loan money", "2.Repay money", "3.Exit"};
        for (int i = 0; i < sizeof(selective_choice) / sizeof(selective_choice[0]); i++)
        {
            cout << selective_choice[i] << endl;
        }
        selectChoice();
    }

    void selectChoice()
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
            delete this;
            break;
        default:
            customer_Choice();
            break;
        }
    }

    void loanMoney()
    {
        double amount;
        cout << "Enter amount to loan: ";
        cin >> amount;
        // Process loan request
        cout << "Loan request processed. Thank you!" << endl;
        customer_Choice();
    }

    void repayMoney()
    {
        double amount;
        cout << "Enter amount to repay: ";
        cin >> amount;
        // Process repayment
        cout << "Repayment processed. Thank you!" << endl;
        customer_Choice();
    }
};
class Bank:public Debt
{
    
    private:
       virtual void accountValidation(){};
        
        //dont care
        bool registerAccount(char*username,char*pass){
            //check
            // if no account
            //write files by Bank class
            //step 1
            //if account
            //return true 
        };
    public:
        void mainMenu()
        {
            viewChoice();
        }; 
        void callAccount(){
            accountValidation();
        }
        //do not care
        //always get account
        bool getAccount(char*username,char*password){
            //return true if there account or created one
            return registerAccount(username,password);
        }

        void viewChoice()
        {
            const char* selective_choice[] = {"1.Withdraw","2.Deposit","3.Balance","4.Loan","5.Exit"};
            for (int i=0;i<size(selective_choice);i++)
            {
                cout <<selective_choice[i] << endl;
            }
            selectChoice();
        }
        void checkBalance()
        {
            //check balance
            //view choice
            viewChoice();
        }
        void selectChoice()
        {
            int number_selected;
            cout << "select choices by number: ";
            cin >> number_selected;
            switch (number_selected)
            {
                case 1:
                    /* code */
                    break;
                case 2:
                    /* code */
                    break;
                case 3:
                    checkBalance();
                    break;
                case 4:
                {
                    customer_Choice();
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
        ~Bank()
            {
                cout << "Exit successfully,Thank you for services" <<endl;
            };

};

class Customer:public Bank
{

    protected:
    fstream file;

    bool registerAccount(string username, string pass)
    {
        file.open("accounts.txt", ios::app);

        file << username << " " << pass << " " << 0 << endl;

        file.close();

        cout << "Account registered successfully!" << endl;
        return true;
    }

    bool accountExists(string username)
    {
        file.open("accounts.txt", ios::app);

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

    bool verifyPassword(string username, string password)
    {
        file.open("accounts.txt", ios::in);

        string file_username;
        string file_password;
        int amount;
        while (file >> file_username >> file_password >> amount)
        {
            if (file_username == username && file_password == password)
            {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }
    public:
    

    virtual void accountValidation()
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
    bool accountCreate()
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

    bool accountCheck(string uname, string upass)
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

};



int main(){
    Bank *bank = new Customer;
    bank->callAccount();
    bank = new Bank;
    bank->mainMenu();
    return 0;
}
