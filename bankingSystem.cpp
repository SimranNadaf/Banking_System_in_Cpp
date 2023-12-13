#include<iostream>
#include<map>
#include<fstream>
using namespace std;

class Account{
	public:
		float balance;
		string firstName;
		string lastName;
		long number;
		static long nextAccountNumber;
	public:
		Account(string fname, string lname, float balance){
			firstName=fname;
			lastName=lname;
			this->balance=balance;
//			nextAccountNumber++;
			number=++nextAccountNumber;
		}
		Account(){
			firstName="";
			lastName="";
			balance=0;
		}
		string getFirstName(){ return firstName;}
		string getLastName(){ return lastName;}
		long getNumber(){ return number;}
		float getBalance(){ return balance;}
		void setFirstName(string fname){ firstName=fname;}
		void setLastName(string lname){ lastName=lname;}
		void setBalance(float balance){ this->balance=balance;}
		void deposit(float amount);
		void withdraw(float amount);
		long getLastNextAccountNumber(){ return nextAccountNumber;}
		void setLastNextAccountNumber(long nextAccountNumber){ this->nextAccountNumber = nextAccountNumber;}		
};

ostream & operator<<(ostream &os, Account &acc){
	os<<"Account number: "<<acc.getNumber()<<endl;
	os<<"First Name: "<<acc.getFirstName()<<endl;
	os<<"Last Name: "<<acc.getLastName()<<endl;
	os<<"Balance: "<<acc.getBalance()<<endl<<endl;
	return os;
}

ofstream & operator<<(ofstream &ofs, Account &acc){
	ofs<<acc.number<<endl;
	ofs<<acc.firstName<<endl;
	ofs<<acc.lastName<<endl;
	ofs<<acc.balance<<endl;
	return ofs;
}

ifstream & operator>>(ifstream &ifs, Account &acc){
	ifs>>acc.number;
	ifs>>acc.firstName;
	ifs>>acc.lastName;
	ifs>>acc.balance;
	return ifs;
}


void Account::deposit(float amount){
	balance+=amount;
}

void Account::withdraw(float amount){
	balance-=amount;
}

class Bank{
	private:
		map<long,Account> accounts;
	public:
		Bank();
		Account openAccount(string fname, string lname, float balance);
		void closeAccount(long number);
		void displayAllAccounts();
		Account deposit(long accountNumber, float amount);
		Account withdraw(long accountNumber, float amount);
		Account BalanceEnquiry(long accountNumber);
		void save();
		~Bank();
};

Bank::Bank(){
	Account account;
	ifstream ifs("accounts.data");
	
	if(!ifs){
		cout<<"File can't open!!"<<endl;
		return;
	} 
	while(!ifs.eof()){
		ifs>>account;
		accounts.insert(pair<long,Account>(account.getNumber(),account));
	}
	long x=accounts.size();
	account.setLastNextAccountNumber(x); 
	ifs.close();
}


Account Bank::openAccount(string fname, string lname, float balance){
	ofstream outfile;
	Account acc(fname,lname,balance);
	accounts.insert(pair<long,Account>(acc.getNumber(),acc));
	outfile.open("Bank.data", ios::trunc);
 
 		map<long,Account>::iterator itr;
		 for(itr=accounts.begin();itr!=accounts.end();itr++)
 			{
		 outfile<<itr->second;
 		}
 		outfile.close();
	return acc;
}

void Bank::closeAccount(long number){
	map<long, Account>::iterator itr;
	itr=accounts.find(number);
	accounts.erase(number);
}

Account Bank::deposit(long accountNumber, float amount){
	map<long, Account>::iterator itr;
	itr=accounts.find(accountNumber);
	itr->second.deposit(amount);
	return itr->second;
}

Account Bank::withdraw(long accountNumber, float amount){
	map<long, Account>::iterator itr;
	itr=accounts.find(accountNumber);
	itr->second.withdraw(amount);
	return itr->second;
}

void Bank::displayAllAccounts(){
	map<long, Account>::iterator itr;
	for(itr=accounts.begin();itr!=accounts.end();itr++){
//		cout<<"Account: "<<itr->first<<endl;
		cout<<itr->second;
	}
}

Account Bank::BalanceEnquiry(long accountNumber){
	map<long, Account>::iterator itr;
	itr=accounts.find(accountNumber);
	return itr->second;
}
	
Bank::~Bank(){
	ofstream ofs;
	ofs.open("accounts.data",ios::trunc);
	map<long,Account>::iterator itr;
	for(itr=accounts.begin();itr!=accounts.end();itr++){
		ofs<<itr->second;
	}
	ofs.close();
}
	
int choice(){
	int c;
	cout<<"Select one below option"<<endl;
	cout<<"\t1. Create Account"<<endl;
	cout<<"\t2. Balance Enquiry"<<endl;
	cout<<"\t3. Deposit"<<endl;
	cout<<"\t4. Withdraw"<<endl;
	cout<<"\t5. Close Account"<<endl;
	cout<<"\t6. Show All Account"<<endl;
	cout<<"\t7. Exit"<<endl;
	cout<<"Enter your Choice: ";
	cin>>c;
	cout<<endl;
	if(c>0 && c<8){
		return c;
	}
	return -1;
}

long Account::nextAccountNumber=0;

int main(){
	
	cout<<"*********** Welcome To Bank **********\n\n";
	string fname,lname;
	float balance;
	float amount;
	long number;
	Bank B;
	Account acc;
		int c=choice();
while(1)
{
	switch(c){
		case 1:
			cout<<"Enter First Name: ";
			cin>>fname;
			cout<<"Enter Last Name: ";
			cin>>lname;
			cout<<"Enter Balance: ";
			cin>>balance;
			cout<<endl;
			acc=B.openAccount(fname,lname,balance);
			cout<<acc;
			cout<<"Account created Successfully!"<<endl<<endl;
			c=choice();
			break;
		case 2:
			cout<<"Enter Account Number: ";
			cin>>number;
			cout<<endl;
			acc=B.BalanceEnquiry(number);
//			cout<<"Account Balance: "<<acc.getBalance()<<endl<<endl;
			cout<<acc;
			c=choice();
			break;
		case 3:
			cout<<"Enter Account Number: ";
			cin>>number;
			cout<<"Enter Deposit Amount: ";
			cin>>amount;
			acc=B.deposit(number, amount);
			cout<<acc;
			cout<<endl;
			cout<<"Amount deposit in account Successfully!"<<"\n\n";
			c=choice();
			break;
		case 4:
			cout<<"Enter Account Number: ";
			cin>>number;
			cout<<"Enter Withdraw Amount: ";
			cin>>amount;
			acc=B.withdraw(number, amount);
			cout<<acc;
			cout<<endl;
			cout<<"Amount withdraw in account Successfully!"<<"\n\n";
			c=choice();
			break;
		case 5:
			cout<<"Enter Account Number: ";
			cin>>number;
			B.closeAccount(number);
			cout<<endl;
			cout<<"Account deleted Successfully!"<<endl<<endl;
			c=choice();
			break;
		case 6:
			B.displayAllAccounts();
			c=choice();
			break;
		case 7:
			cout<<"Exit"<<endl;
//			exit(0);
			return 0;
		default:
			cout<<"Invalid Choice. Try Again! \n"<<endl;
			c=choice();
	}
}
	
	return 0;
}
