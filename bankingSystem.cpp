#include<iostream>
#include<map>
using namespace std;

class Account{
	private:
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
};

ostream & operator<<(ostream &os, Account &acc){
	os<<"Account number: "<<acc.getNumber()<<endl;
	os<<"First Name: "<<acc.getFirstName()<<endl;
	os<<"Last Name: "<<acc.getLastName()<<endl;
	os<<"Balance: "<<acc.getBalance()<<endl<<endl;
	return os;
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
		void openAccount(string fname, string lname, float balance);
		void closeAccount(long number);
		void displayAllAccounts();
		Account deposit(long accountNumber, float amount);
		Account withdraw(long accountNumber, float amount);
		Account BalanceEnquiry(long accountNumber);
};

void Bank::openAccount(string fname, string lname, float balance){
	Account acc(fname,lname,balance);
	cout<<"Number: "<<acc.getNumber()<<endl;
	accounts.insert(pair<long,Account>(acc.getNumber(),acc));
	cout<<"Created Account Number: "<<acc.getNumber()<<endl<<"Account Created Successfully. "<<endl<<endl;
}

void Bank::closeAccount(long number){
	map<long, Account>::iterator itr;
	itr=accounts.find(number);
	cout<<"Deleted Account: "<<itr->first<<endl;
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
	
int choice(){
	int c;
	cout<<"1. Create Account"<<endl;
	cout<<"2. Close Account"<<endl;
	cout<<"3. Deposit"<<endl;
	cout<<"4. Withdraw"<<endl;
	cout<<"5. Balance Enquiry"<<endl;
	cout<<"6. Show All Accounts"<<endl;
	cout<<"7. Exit"<<endl;
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
			B.openAccount(fname,lname,balance);
			c=choice();
			break;
		case 2:
			cout<<"Enter Account Number: ";
			cin>>number;
			B.closeAccount(number);
			c=choice();
			break;
		case 3:
			cout<<"Enter Account Number: ";
			cin>>number;
			cout<<"Enter Deposit Amount: ";
			cin>>amount;
			acc=B.deposit(number, amount);
			cout<<acc;
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
			cout<<"Amount withdraw in account Successfully!"<<"\n\n";
			c=choice();
			break;
		case 5:
			cout<<"Enter Account Number: ";
			cin>>number;
			acc=B.BalanceEnquiry(number);
//			cout<<"Account Balance: "<<acc.getBalance()<<endl<<endl;
			cout<<acc;
			c=choice();
			break;
		case 6:
			B.displayAllAccounts();
			c=choice();
			break;
		case 7:
			cout<<"Exit"<<endl;
			exit(0);
		default:
			cout<<"Invalid Choice. Try Again! \n"<<endl;
			c=choice();
	}
}
	
	return 0;
}
