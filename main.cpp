#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;



/* The `Storage` class in C++ contains data structures for storing account information, bank debt, and
essential bank details, along with methods for banking operations such as deposit, withdraw,
transfer, and account management. */
class Storage
{
    //one use temporary holding username and password
    protected:
    struct acc_info
    {
        string username;
        string password;
        double balance;
    }acc;

    struct bankDebt
    {
        string name = "Bank";
        string password = "1234";
        double amount = 10000000.0;
    }bdebt;
    
    //file
    protected:
        fstream bankfile;
        fstream file;

    public:
    //constructor overload
    Storage()
    {
        cout << "Using Vault System." << endl;
        Bankdeposit(bdebt.name,bdebt.amount);
        createBankFile("VAULT",bdebt.name,bdebt.amount,bdebt.amount);
    }

    //update file by amount of money
    bool Bankdeposit(string,double);
    //update file by amount of money
    bool Bankwithdraw(string,double);
    //transfer service using deposit and withdraw
    bool Transfer();
    //seperate bank file
    void createBankFile(string,string,double,double);
    //loop register/login page
    bool accountCheck(string,string);
    //return either true or false based on username password
    bool verifyPassword(string,string);
    //registering an account process 
    bool registerAccount(string,string);
    bool BankTransfer(string,double);
    bool OwnerTransfer(string,double);
    //void RegisterValidation();

    // check if username existed
    bool accountExists(string);

    //public method for getting name and password and balance for validation
    string getName();
    string getPass();
    double getAmount();

    ~Storage(){cout << "End Vault System." << endl;}
};

//giveaway
/**
 * The function `Bankdeposit` in C++ reads account information from a file, updates the balance for a
 * specified receiver, and writes the changes back to the file after a successful transfer.
 * 
 * @param reciever The `reciever` parameter in the `Bankdeposit` function represents the username of
 * the account to which the specified `amount` is being deposited.
 * @param amount The `amount` parameter in the `Bankdeposit` function represents the amount of money
 * that is being deposited into a bank account. The function checks if the amount is greater than or
 * equal to zero before proceeding with the deposit transaction. If the amount is valid, it updates the
 * balance of the account specified
 * 
 * @return The function `Storage::Bankdeposit` returns a boolean value - `true` if the deposit was
 * successful, and `false` if the amount is less than 0 or if the withdrawal during the deposit process
 * fails.
 */
bool Storage::Bankdeposit(string reciever,double amount)
{
    if (amount < 0)
    {
        return false;
    }
    else
    {
    string username, password;
    double balance;
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

/**
 * The function `Bankwithdraw` in C++ reads account information from a file, processes a withdrawal
 * transaction, and updates the account balance accordingly.
 * 
 * @param Sender The `Sender` parameter in the `Bankwithdraw` function represents the username of the
 * account from which the withdrawal is being made.
 * @param amount The `amount` parameter in the `Bankwithdraw` function represents the amount of money
 * that the user wants to withdraw from their bank account.
 * 
 * @return The function `Bankwithdraw` returns a boolean value. If the withdrawal is successful, it
 * returns `true`. If the withdrawal fails due to insufficient funds or other reasons, it returns
 * `false`.
 */
bool Storage::Bankwithdraw(string Sender,double amount)
{
    //this->acc.username
    if (amount < 0)
    {
        return false;
    }
    else
    {
    string username, password;
    double balance;
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
                balance = balance  - amount;
                cout << "Transfer successful." << Sender << " new balance: " << balance << endl;
                this->acc.balance = balance;
                this->bdebt.amount += amount;
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

/**
 * The function `createBankFile` creates a bank file with user information and writes it to a text
 * file.
 * 
 * @param uname1 The `uname1` parameter in the `createBankFile` function is a string that represents
 * the username of the sender in a banking transaction.
 * @param uname2 The parameter `uname2` in the `createBankFile` function is a string variable that
 * represents the username of the second user involved in the bank transaction.
 * @param size The `size` parameter in the `createBankFile` function likely represents the size of the
 * transaction or some other relevant data related to the bank file being created. It seems to be an
 * integer value that is being passed to the function.
 * @param total The `total` parameter in the `createBankFile` function likely represents the total
 * amount of money involved in a bank transaction between two users. This could be the total balance in
 * the transaction, the total amount being transferred, or some other total value related to the
 * transaction.
 */
void Storage::createBankFile(string uname1,string uname2,double size,double total)
{
    string usender,ureciever;
    double balance,amount;
    string fileName = "BankFile.txt";
    cout << "Bankfile Created" << endl;
    //read file temporary
    file.open(fileName,ios::out|ios::app);
    file << uname1 << " " << uname2 << " " <<  size << " " << total << endl;
    file.close();


}
/**
 * The Transfer function in C++ prompts the user to enter a receiver name and amount to transfer money,
 * checks if the receiver account exists, and then performs the transfer if successful.
 * 
 * @return The `Transfer` function returns a boolean value. It returns `true` if the money transfer is
 * successful and `false` if the transfer fails or if the receiver account does not exist.
 */
bool Storage::Transfer()
{
    string reciever;
    double amount;
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
/**
 * The function `OwnerTransfer` transfers a specified amount of money to a receiver's account while
 * updating the account balances in a file.
 * 
 * @param reciever The `reciever` parameter in the `OwnerTransfer` function represents the username of
 * the account to which the transfer of `amount` is being made.
 * @param amount The `amount` parameter in the `OwnerTransfer` function represents the amount of money
 * that is being transferred to the `reciever` account.
 * 
 * @return The function `Storage::OwnerTransfer` returns a boolean value - `true` if the transfer is
 * successful, and `false` if the transfer fails due to a negative amount or if the `Bankwithdraw`
 * function returns false.
 */
bool Storage::OwnerTransfer(string reciever,double amount)
{
    if (amount < 0)
    {
        return false;
    }
    else
    {
    string username, password;
    double balance;
    string fileName = "accounts.txt";

    //iterator for reading balance at username
    if(Bankwithdraw(bdebt.name,amount) == false){return false;}
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
/**
 * The function `BankTransfer` transfers a specified amount of money from one account to another if the
 * receiver account exists.
 * 
 * @param receivername The `receivername` parameter in the `BankTransfer` function represents the name
 * of the account holder to whom the bank transfer is being made.
 * @param amount The `amount` parameter in the `BankTransfer` function represents the amount of money
 * that is being transferred from one account to another.
 * 
 * @return The `BankTransfer` function returns a boolean value (`true` or `false`) based on the success
 * of the bank transfer operation.
 */
bool Storage::BankTransfer(string receivername,double amount)
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
double Storage::getAmount()
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
/**
 * The function `verifyPassword` in C++ reads from a file to check if a given username and password
 * match any stored credentials.
 * 
 * @param username The `username` parameter is a string that represents the username input provided by
 * a user trying to log in.
 * @param password The `verifyPassword` function in the provided code snippet reads from a file named
 * "accounts.txt" to check if a given `username` and `password` match any entries in the file. If a
 * matching entry is found, it sets the `acc` object's `username` and `password
 * 
 * @return The `verifyPassword` function returns a boolean value - `true` if the provided `username`
 * and `password` match an entry in the "accounts.txt" file, and `false` otherwise.
 */
bool Storage::verifyPassword(string username, string password)
        {
            file.open("accounts.txt", ios::in);

            string file_username;
            string file_password;
            double amount;
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
/**
 * The function `accountCheck` in C++ checks if the username and password are valid and returns true if
 * they are, otherwise it outputs an error message and returns false.
 * 
 * @param uname The `uname` parameter is a string representing the username input provided by the user
 * for account verification.
 * @param upass The `upass` parameter in the `accountCheck` function represents the password input
 * provided by the user for a specific username (`uname`). This password is then verified using the
 * `verifyPassword` function to determine if it matches the stored password for the given username.
 * 
 * @return The `accountCheck` function returns a boolean value. If the `verifyPassword` function
 * returns true for the given username and password, then `true` is returned. Otherwise, if the
 * password verification fails, it outputs an error message and returns `false`.
 */
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
/**
 * The function `registerAccount` registers a new account with a username, password, and initial
 * balance of 0 in a file and returns true upon successful registration.
 * 
 * @param username The `username` parameter is a string that represents the username of the account
 * being registered.
 * @param pass The `pass` parameter in the `registerAccount` function represents the password
 * associated with the `username` for registering an account.
 * 
 * @return The `registerAccount` function is returning a boolean value `true`.
 */
bool Storage::registerAccount(string username, string pass)
        {
            file.open("accounts.txt",ios::out|ios::app);

            file << username << " " << pass << " " << 0 << endl;
            file.close();

            cout << "Account registered successfully!" << endl;
            
            return true;
        }

//return true/false based on account existed or not (use for register loop) and use for returning
/**
 * The function `accountExists` checks if a given username exists in a file named "accounts.txt" along
 * with corresponding password and amount.
 * 
 * @param username The `username` parameter is a string that represents the username of the account
 * that we are checking for existence in the `accounts.txt` file.
 * 
 * @return This function returns a boolean value indicating whether an account with the specified
 * username exists in the "accounts.txt" file. If the username is found in the file, the function
 * returns true. Otherwise, it returns false.
 */
bool Storage::accountExists(string username)
    {
        file.open("accounts.txt", ios::in);

        string file_username;
        string password;
        double amount;
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

class Debt:virtual public Storage

{
    public:
    bool checkMoneyUser(double);
    bool checkMoneyBank();
    //choice display 
    void customerChoice();
    //choice selection
    void debtChoice();
    double checkloan();
    //method for loan money
    void loanMoney();
    //method for repay money
    void repayMoney();
};

/**
 * The function `checkloan` reads the balance amount associated with a specific username from a file
 * named "Debt.txt".
 * 
 * @return The `checkloan` function is returning the amount of debt associated with the current user's
 * account. If the username in the file matches the username of the current account, then the function
 * returns the amount of debt for that user. If no match is found, the function does not return
 * anything explicitly (which is not ideal practice).
 */
double Debt::checkloan()
    {
    string fileName = "Debt.txt";
    //need personal balance checking
    file.open(fileName, ios::in);
    //iterator for reading balance at username
    string file_username;
    double amount;
    while (file >> file_username >> amount)
    {
        if (file_username == acc.username)
        {
            file.close();
            return amount;
        }
    }
    return 0;
    }
/**
 * The function `checkMoneyUser` reads user balances from a file and checks if the user has enough
 * balance to cover a given debt.
 * 
 * @param debt The `debt` parameter in the `checkMoneyUser` function represents the amount of money
 * that the user wants to borrow or use. The function reads user account information from a file and
 * checks if the user's balance is sufficient to cover the debt. If the user's balance is greater than
 * or
 * 
 * @return The function `checkMoneyUser` returns a boolean value - `true` if the user's balance is
 * greater than or equal to the debt amount, and `false` otherwise.
 */
bool Debt::checkMoneyUser(double debt)
{
        string fileName = "accounts.txt";
        //need personal balance checking
        file.open(fileName, ios::in);
        //iterator for reading balance at username
        string file_username;
        string file_password;
        double amount;
        while (file >> file_username >> file_password >> amount)
        {
            if (file_username == acc.username && file_password == acc.password)
                {
                    acc.balance = amount;
                }
            }

        file.close();
        if(acc.balance > 0 && acc.balance >= debt)
        {
            return true;
        }
        else
        {
        return false;
    }
}
/**
 * The function `checkMoneyBank` reads account balances from a file and checks if the user's balance is
 * greater than zero, returning true if so, and applying fees and returning false if the balance is
 * zero.
 * 
 * @return This function returns a boolean value. If the amount in the `bdebt` object is greater than
 * 0, it returns true. Otherwise, it prints a message indicating that the bank has run out of money,
 * includes a fee in the transaction, and returns false.
 */
bool Debt::checkMoneyBank()
{
        string fileName = "accounts.txt";
        //need personal balance checking
        file.open(fileName, ios::in);
        //iterator for reading balance at username
        string file_username;
        string file_password;
        double amount;
        while (file >> file_username >> file_password >> amount)
        {
            if (file_username == bdebt.name && file_password == bdebt.password)
                {
                    bdebt.amount = amount;
                    file.close();
                }
            }

        if(bdebt.amount > 0)
        {
            return true;
        }
        else
        {

        cout << "Bank run out of money" << endl;
        return false;
    }
}

//display choice and called selection part
/**
 * The function `customerChoice` displays a menu of options for the user to choose from and then calls
 * the `debtChoice` function.
 */
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
/**
 * The function `debtChoice` allows the user to select options related to managing debt, such as taking
 * a loan or repaying money.
 */
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

/**
 * The function `loanMoney` processes a loan request by updating the debt amount for a specific user
 * and handling the transfer of funds from a bank account if sufficient balance is available.
 */
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
                
                
                bdebt.amount = bdebt.amount-debt;
                if(checkMoneyBank())
                {
                    
                    BankTransfer(acc.username,debt);
                    cout << "Loan request processed. Thank you!" << endl;
                    found = true;
                    bdebt.amount+=debt;
                }
                else
                {
                    bdebt.amount+=debt;
                    cout << "Couldnt let user loan." << endl;
                    found=false;
                }
                outfile << acc.username << " " << debt << "\n";
            }
            
             else {
                outfile << line << endl;
            }
        }
    }
    infile.close();

    // If the user does not exist in the debt file, add a new entry
    if (!found) {
        outfile << acc.username << " " << 0 << endl;;
        cout << "Loan request failed." << endl;
    }

    outfile.close();
    remove(filename.c_str());
    rename("Debt_copy.txt", filename.c_str());

    customerChoice();
}

/**
 * The function `repayMoney` allows a user to repay a specified amount of debt, updating the debt
 * records accordingly and handling various scenarios such as insufficient funds.
 */
void Debt::repayMoney() {
    double amount;
    cout << "Total " << checkloan() << endl;
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
            if (username == acc.username) {
                
                outfile << username << " " << (debt-amount <= 0?0:debt-amount) << endl;
                cout << "Repayment of " << amount << " successful." << endl;

                if(checkMoneyUser(amount))
                {
                    Bankdeposit(bdebt.name,amount);
                    createBankFile(acc.username,bdebt.name,amount,acc.balance);
                }
                else
                {
                    cout << "You not have enough money to pay debt.";
                    cout << "Want to pay debt in minimum(include further fees)?" << endl;
                    repayMoney();

                    customerChoice();
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
    // Init Bank
    void Init()
    {
        accountValidation();
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
/**
 * The function `selectChoice` in a C++ Bank class allows the user to choose various banking operations
 * like withdraw, deposit, check balance, transfer, change account, or delete account based on the
 * selected number.
 */
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
/**
 * The function Bank::viewChoice displays a menu of banking options for the user to choose from.
 */
void Bank::viewChoice()
        {
            const char* selective_choice[] = {"1.Withdraw","2.Deposit","3.Balance","4.Loan","5.Transfer","6.ChangeAccount","7.Exit"};
            cout<<"=================="<<endl;
            cout <<"Username: "<< getName() << endl;
            cout<<"=================="<<endl;
            for (int i=0;i<sizeof(selective_choice) / sizeof(selective_choice[0]);i++)
            {
                cout <<selective_choice[i] << endl;
            }
            cout<<"=================="<<endl;
            selectChoice();
        }

//display Balance
/**
 * The `checkBalance` function reads account information from a file and displays the current balance
 * for a specific user.
 */
void Bank::checkBalance()
        {
            string fileName = "accounts.txt";
            //need personal balance checking
            file.open(fileName, ios::in);
            //iterator for reading balance at username
            string file_username;
            string file_password;
            double amount;

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
/**
 * The function `accountCreate` in C++ prompts the user to enter a username and password, checks if the
 * account already exists, and either prompts for a new username or registers the account and logs in.
 */
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
/**
 * The function `changeAccount` in the Bank class calls the `accountValidation` function.
 */
void Bank::changeAccount()
{
    accountValidation();
}
//auto login
/**
 * The function `autoLogin` in C++ checks the account credentials and either displays the main menu or
 * prompts for account validation.
 * 
 * @param uname The `uname` parameter in the `autoLogin` function is a string that represents the
 * username entered by the user for logging into their bank account.
 * @param upass The parameter `upass` in the `autoLogin` function is a string that represents the
 * password entered by the user for logging into their bank account.
 */
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
/**
 * The function `accountValidation` in C++ prompts the user to either register or login, then calls the
 * appropriate function based on the user's choice.
 */
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
/**
 * The function `deposit` in the Bank class allows a user to deposit a specified amount into their
 * account and updates the balance accordingly in a file.
 */
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
    double balance;
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
    
    

/**
 * The function `withdraw` in C++ allows a user to withdraw a specified amount from their bank account
 * and updates the balance accordingly in a file.
 */
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
    double balance;

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

/**
 * The main function creates a Bank object and calls the accountValidation method on it.
 * 
 * @return The `main` function is returning an integer value of 0.
 */
int main()
{
    //make Bank object
    Bank bank;
    //called registeration
    bank.Init();
    return 0;
}