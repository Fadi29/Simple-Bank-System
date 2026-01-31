#include <iostream>
#include <iomanip>
#include <vector>
#include <cctype>
#include "StringLib.h"
using namespace std;

enum enOperationsOptions{ ShowClientList = 1, AddNewClient = 2, DeleteClient = 3, UpdateClient = 4, FindClient = 5, Transactions = 6, Exit = 7};

enum enTransactionsOpentions {Deposit = 1, Withdraw = 2, TotalBalances = 3, MainMenu = 4};

enum SeperatorType{ thick = 1, Thin = 0};

const string FileOfClientData = "ClientData.txt";

bool YesOrNo(string Message)
{
    string YOrN = "";
    cout << Message;
    getline(cin >> ws, YOrN);
    if (StringLib::LowerAllLetters(YOrN) == "yes")
        return true;
    return false;
}

void PressAnyKeySentence()
{
    cout << "\n\nPress any Key to go back to Main Menu...";
    system("pause>0");
}



void LineSeperator(short Length, SeperatorType Type = SeperatorType::thick)
{
    if (Type == SeperatorType::thick)
        for (short i = 0; i <= Length; i++)
            cout << '=';
    else
        for (short i = 0; i <= Length; i++)
            cout << '-';
}
int ReadInt(string Message)
{
    int Num;
    cout << Message;
    cin >> Num;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid Input, Enter a number? ";
        cin >> Num;
    }
    return Num;
}
double ReadDouble(string Message)
{
    double Num;
    cout << Message;
    cin >> Num;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid Input, Enter a number? ";
        cin >> Num;
    }
    return Num;
}

string ReadAccountNumber()
{
    string AccountNumber;
    cout << "Please enter Account Number? ";
    getline(cin >> ws, AccountNumber);
    return AccountNumber;
}

void PrintClientRecord(const stClient &Client)
{
    cout << "The following are the client details:\n";
    LineSeperator(40);
    cout << '\n';
    cout << "\nAccout Number : " << Client.AccountNumber;
    cout << "\nPin Code      : " << Client.PinCode;
    cout << "\nName          : " << Client.Name;
    cout << "\nPhone         : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << '\n';
    LineSeperator(40);
}


bool IsAccountNumberExistInVector(const vector <stClient>& vClientsData, string AccountNumber)
{
    for (int i = 0; i < vClientsData.size(); i++)
    {
        if (AccountNumber == vClientsData[i].AccountNumber)
            return true;
    }
    return false;
}

stClient ReadNewClient(stClient &Client)
{

    cout << "Enter PinCode? ";
    getline(cin>>ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    Client.AccountBalance = ReadDouble("Enter Account Balance? ");

    return Client;
}


void UpdateClientInfoFromVector(vector <stClient>& ClientsData, const string& AccountNumber)
{
    for (stClient& C : ClientsData)
        if (C.AccountNumber == AccountNumber)
            ReadNewClient(C);
}


bool UpdateClientInfo(vector <stClient>& vClientData, string AccountNumber)
{
    bool IsUpdated = false;
    char YOrN;
    stClient ClientInfo;
    if (StringLib::FindClientByAccountNumber(AccountNumber, ClientInfo, vClientData))
    {
        PrintClientRecord(ClientInfo);
        cout << "\n\nAre you sure you want update this Client? y/n ? ";
        cin >> YOrN;
        if (tolower(YOrN) == 'y')
        {
            UpdateClientInfoFromVector(vClientData, AccountNumber);            
            cout << "\n\nClient Updated Succesfully.";
            IsUpdated = true;
        }
        else
            cout << "\n\nClient NOT Updated.";
    }
    else
    {
        cout << "\n\nClient with Account Number (" << AccountNumber << ") Not Found!";
    }
    return IsUpdated;
}


void HeaderOfSubScreens(string title)
{
    LineSeperator(40, SeperatorType::Thin);
    cout << '\n';
    cout << setw(8) << "" << title;
    cout << '\n';
    LineSeperator(40, SeperatorType::Thin);
}

void AddNewClientToVector(vector <stClient>& vClientsData)
{
    stClient Client;
    Client.AccountNumber = ReadAccountNumber();
    while (IsAccountNumberExistInVector(vClientsData, Client.AccountNumber))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }
    vClientsData.push_back(ReadNewClient(Client));
}


void FindClientInfo(const vector <stClient>& vClientsData, string AccountNumber)
{
    stClient ClientInfo;
    if (StringLib::FindClientByAccountNumber(AccountNumber, ClientInfo, vClientsData))
    {  
        cout << '\n';
        PrintClientRecord(ClientInfo);
    }
    else
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
}


void MainMenuScreen() // ^
{
    LineSeperator(40);
    cout << '\n';
    cout << setw(12) << "" << "Main Menu Screeen";
    cout << '\n';
    LineSeperator(40);
    
    cout << "\n\t [1] Show Client List.\n";
    cout << "\t [2] Add New Client.\n";
    cout << "\t [3] Delete Client.\n";
    cout << "\t [4] Update Client Info.\n";
    cout << "\t [5] Find Client.\n";
    cout << "\t [6] Transactions.\n";
    cout << "\t [7] Exit.\n";
    LineSeperator(40);
}

void TransactionsMenuScreen()
{
    LineSeperator(40);
    cout << '\n';
    cout << setw(8) << "" << "Transactions Menu Screeen";
    cout << '\n';
    LineSeperator(40);
    cout << "\n\t[1] Deposite.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menu.\n";
    LineSeperator(40);
}

void ClientsListScreen(const vector <stClient> &vClientsData) // ^
{
    StringLib::TableOfClientData(vClientsData);  
    PressAnyKeySentence();  
}



void AddNewClientScreen(vector <stClient>& vClientsData) // ^
{
    HeaderOfSubScreens("Add New Clients Screen");
    cout << '\n';
    char YOrN = 'y';
    cout << "\nAdding New Client: \n\n";
    do
    {
        AddNewClientToVector(vClientsData);
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> YOrN;
    } while (tolower(YOrN) == 'y');
    PressAnyKeySentence();
}

void DeleteClientInfoFromVector(vector <stClient>& vClientsData) // ^
{
    HeaderOfSubScreens("Delete Client Screen");
    cout << "\n\n";
    string AccountNumber = ReadAccountNumber();
    cout << '\n';
    StringLib::DeleteClientByAccountNumber(AccountNumber ,vClientsData);
    PressAnyKeySentence();
}

void UpdateClientInfoScreen(vector <stClient>& vClientsData) // ^ 
{
    HeaderOfSubScreens("Update Client Info Screen");
    cout << '\n';
    string AccountNumber = ReadAccountNumber();
    cout << '\n';
    UpdateClientInfo(vClientsData, AccountNumber);
    PressAnyKeySentence();
}

void FindClientScreen(const vector <stClient>& vClientsData) // ^
{
    HeaderOfSubScreens("Find Client Screen");
    cout << "\n\n";
    FindClientInfo(vClientsData, ReadAccountNumber());
    PressAnyKeySentence();
}


void SaveClientInfoInVector(vector <stClient>& vClientsData,const stClient& ClientInfo, const string& AccountNumber)
{
    if (vClientsData.empty())
        return;
    for (int i = 0; i < vClientsData.size(); i++)   
        if (vClientsData[i].AccountNumber == AccountNumber)
        {
            vClientsData[i] = ClientInfo;
            return;
        }             
}

void PrintClientRecord(stClient& ClientInfo)
{
    cout << "The following are the client details:\n";
    LineSeperator(40, SeperatorType::Thin);
    StringLib::PrintClientCard(ClientInfo);
    cout << '\n';
    LineSeperator(40, SeperatorType::Thin);

}

bool DepositMoneyUsingVector(stClient &ClientInfo)
{
    int Num;
    bool Deposit = true;
    PrintClientRecord(ClientInfo);
    cout << "\n\n";
    Num = ReadDouble("Please enter deposite amount? ");
    cout << "\n\n";   
    if (YesOrNo("Are you sure you want to perform this transactions? [Yes,No] ?"))
    {
        ClientInfo.AccountBalance = ClientInfo.AccountBalance + Num;
        cout << "\n\n";
        cout << "Done successfully, new balance " << ClientInfo.AccountBalance << endl;
        PressAnyKeySentence();
        return Deposit;
    }
    Deposit = false;
    return Deposit;
}


void DepositScreen(vector <stClient>& vClientsData)
{
    HeaderOfSubScreens(" Deposit Screen");
    cout << "\n\n";
    stClient ClientInfo;
    string AccountNumber = ReadAccountNumber();
    while (!StringLib::FindClientByAccountNumber(AccountNumber, ClientInfo, vClientsData))
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!" << endl;
        
        if (YesOrNo("Do you want to continue? [Yes,No] ?\n"))
            AccountNumber = ReadAccountNumber();
        else
            return;        
    }
    cout << '\n';
    if (DepositMoneyUsingVector(ClientInfo))
    {
        SaveClientInfoInVector(vClientsData, ClientInfo, AccountNumber);
    }
    return;
}


bool WithdrawMoneyUsingVector(stClient& ClientInfo)
{
    int Num;
    bool Withdraw = true;
    PrintClientRecord(ClientInfo);
    cout << "\n\n";
    Num = ReadDouble("Please enter Withdraw amount? ");
    
    while (Num > ClientInfo.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << ClientInfo.AccountBalance << endl;
        Num = ReadDouble("Please enter anther amount? ");
    }
    cout << "\n\n";
    if (YesOrNo("Are you sure you want to perform this transactions? [Yes,No] ?"))
    {
        ClientInfo.AccountBalance = ClientInfo.AccountBalance - Num;
        cout << "\n\n";
        cout << "Done successfully, new balance " << ClientInfo.AccountBalance << endl;
        PressAnyKeySentence();
        return Withdraw;
    }
    Withdraw = false;
    return Withdraw;
}

void WithdrawScreen(vector <stClient>& vClientsData)
{
    HeaderOfSubScreens("Withdraw Screen");
    cout << "\n\n";
    stClient ClientInfo;
    string AccountNumber = ReadAccountNumber();
    while (!StringLib::FindClientByAccountNumber(AccountNumber, ClientInfo, vClientsData))
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!" << endl;
        if (YesOrNo("Do you want to continue? [Yes,No] ?\n"))
            AccountNumber = ReadAccountNumber();
        else
            return;
    }
    cout << '\n';
    if (WithdrawMoneyUsingVector(ClientInfo))
    {
        SaveClientInfoInVector(vClientsData, ClientInfo, AccountNumber);
    }
    return;
}

void HeaderOfTotalBalancesTable(const int &NumberOfClients)
{
    cout << '\n';
    cout << setw(40) << ""
        << "Client List (" << NumberOfClients
        << ") Client(s).\n";
    StringLib::HeaderFrame(110);
    cout << "\n\n";
    cout << "| " << left << setw(20) << "Account Number";
    cout << "| " << left << setw(45) << "Client Name";
    cout << "| " << left << setw(35) << "Balance";
    cout << "\n";
    StringLib::HeaderFrame(110);
}

void RowOfTotalBalancesTable(const stClient& ClientInfo)
{
    cout << "| " << left << setw(20) << ClientInfo.AccountNumber;
    cout << "| " << left << setw(45) << ClientInfo.Name;
    cout << "| " << left << setw(35) << ClientInfo.AccountBalance;
}
void TotalBalancesScreen(const vector <stClient>& vClientsData)
{
    double TotalBalances = 0;
    HeaderOfTotalBalancesTable(vClientsData.size());
    cout << '\n';
    if (vClientsData.size() == 0)
    {
        cout "There is no Client Data right now!" << endl;
    }
    else
    {
        for (int i = 0; i < vClientsData.size(); i++)
        {
            TotalBalances = TotalBalances + vClientsData[i].AccountBalance;
            RowOfTotalBalancesTable(vClientsData[i]);
            cout << endl;
        }
        cout << '\n';
        StringLib::HeaderFrame(110);
        cout << '\n';
        cout << setw(40) << "" << "Total Balances = " << TotalBalances;
    }
    PressAnyKeySentence();
}

void ControlPanelOfTransactions(vector <stClient> &vClientsData)
{
    short TransactionsNum = 4;
    enTransactionsOpentions OperationOfTrans;
    do
    {
        TransactionsMenuScreen();
        TransactionsNum = ReadInt("\nChoose what do you want to do? [1 to 4]? ");
        OperationOfTrans = enTransactionsOpentions(TransactionsNum);
        system("cls");       
        switch (OperationOfTrans)
        {
        case enTransactionsOpentions::Deposit:
            DepositScreen(vClientsData);
            break;
        case enTransactionsOpentions::Withdraw:
            WithdrawScreen(vClientsData);
            break;
        case enTransactionsOpentions::TotalBalances:
            TotalBalancesScreen(vClientsData);
            break;
        }
        StringLib::SaveClientsDataToFile(FileOfClientData, vClientsData);
        system("cls");
    } while (OperationOfTrans != enTransactionsOpentions::MainMenu);
    
}

void MainControlPanel()
{
    short OptionNum = 7;
    enOperationsOptions Operation;
    vector <stClient> vClientsData = StringLib::LoadClientsDataFromFile(FileOfClientData);
    do
    {
        MainMenuScreen();
        OptionNum = ReadInt("\nChoose what do you want to do? [1 to 7]? ");
        Operation = enOperationsOptions(OptionNum);
        system("cls");
        switch (Operation)
        {
        case enOperationsOptions::Exit:
            break;
        case enOperationsOptions::ShowClientList:
            ClientsListScreen(vClientsData); 
            break;
        case enOperationsOptions::AddNewClient:
            AddNewClientScreen(vClientsData);
            break;
        case enOperationsOptions::DeleteClient:
            DeleteClientInfoFromVector(vClientsData);
            break;
        case enOperationsOptions::UpdateClient:
            UpdateClientInfoScreen(vClientsData);
            break;
        case enOperationsOptions::FindClient:
            FindClientScreen(vClientsData);
            break;
        case enOperationsOptions::Transactions:
            ControlPanelOfTransactions(vClientsData);
            break;          
        } 
        StringLib::SaveClientsDataToFile(FileOfClientData, vClientsData);
        system("cls");
    } while (Operation != enOperationsOptions::Exit);
    HeaderOfSubScreens("Program Ends :-)");
}

int main()
{
    MainControlPanel();
}
