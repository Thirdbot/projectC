class Customer : public Bank
{
private:
    struct account
    {
        string user_name;
        string user_pass;
        int amount;
    } acc;

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
        cout << "Welcome to the banking system!" << endl;
        cout << "1. Register\n2. Login" << endl;
        cout << "Enter your choice: ";
        cin >> rol;
        switch (rol)
        {
        case 1:
            accountCreate();
            accountValidation();
            break;
        case 2:
            {
                string username;
                string userpass;
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> userpass;
                if (accountCheck(username, userpass))
                {
                    cout << "Login successful!" << endl;
                    viewChoice();
                }
                else
                {
                    cout << "Invalid username or password. Please try again." << endl;
                    accountValidation();
                }
                break;
            }
        default:
            cout << "Invalid choice. Please try again." << endl;
            accountValidation();
            break;
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

    virtual void viewChoice()
    {
        cout << "Select an option:" << endl;
        cout << "1. Deposit\n2. Withdraw\n3. Loan\n4. Payback\n5. Exit" << endl;
        selectChoice();
    }

    virtual void selectChoice()
    {
        int number_selected;
        cout << "Enter your choice: ";
        cin >> number_selected;
        switch (number_selected)
        {
        case 1:
            //cout << "You selected Deposit." << endl;
            break;
        case 2:
            //cout << "You selected Withdraw." << endl;
            break;
        case 3:
            //cout << "You selected Loan." << endl;
            break;
        case 4:
            //cout << "You selected Payback." << endl;
            break;
        case 5:
            //cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid selection. Please try again." << endl;
            viewChoice();
            break;
        }
    }
};

