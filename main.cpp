#include <iostream>
using namespace std;
class Bank
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
        void Called()
        {
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
                    /* code */
                    break;
                case 4:
                {
                    break;
                }
                case 5:
                {
                    break;
                }
                default:
                    viewChoice();
                    break;
            }

            Bank* bank_exit = new Bank;
            bank_exit->~Bank();
        }
        ~Bank()
            {
                cout << "Exit successfully,Thank you for services" <<endl;
            };

};

class Customer:public Bank
{
    private:
    //not using i guessed
        struct account
        {
            char user_name[20];
            char user_pass[20];
        }acc;
    
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
        //check username not in file
        //check password two times
        int n = 0;
        while (n<=1)
        {
            //check password
        }
        

        //create account in file
        return true;
    }
    bool accountCheck(char* uname , char* upass)
    {
        //check account from file
        //check password from file
        return true;
    }

};

class Debt : public Customer
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
        viewChoice();
    }

    void repayMoney()
    {
        double amount;
        cout << "Enter amount to repay: ";
        cin >> amount;
        // Process repayment
        cout << "Repayment processed. Thank you!" << endl;
        viewChoice();
    }
};

int main(){
    Bank* bank = new Customer;
    bank->Called();
    return 0;
}
