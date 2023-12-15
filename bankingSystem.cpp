#include<iostream>
#include<map>
#include<fstream>
using namespace std;

#define MIN_BALANCE 500

class insufficientFunds{
};
class accountNotFound{
};
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
		static long getLastNextAccountNumber(){ return nextAccountNumber;}
		static void setLastNextAccountNumber(long nextAccNumber){ nextAccountNumber = nextAccNumber;}
		friend ostream & operator<<(ostream &os, Account &acc);
		friend ofstream & operator<<(ofstream &ofs, Account &acc);
		friend ifstream & operator>>(ifstream &ifs, Account &acc);
};

ostream & operator<<(ostream &os, Account &acc){
	os<<"Account number: "<<acc.number<<endl;
	os<<"First Name: "<<acc.firstName<<endl;
	os<<"Last Name: "<<acc.lastName<<endl;
	os<<"Balance: "<<acc.balance<<endl<<endl;
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
	if(balance-amount<0)
		throw insufficientFunds();
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
		void transferMoney(long accountNumber1, long accountNumber2,float amount);
		~Bank();
};

Bank::Bank(){
	Account account;
	ifstream ifs("accounts.data");
	
	if(!ifs){
		cout<<"File can't open!!"<<endl;
		return;
	}
	ifs>>account;
	if(!account.getNumber()){
		cout<<"\tNo Accounts"<<endl<<endl;
		return ;
	}
	accounts.insert(pair<long,Account>(account.getNumber(),account));
	while(!ifs.eof()){
		ifs>>account;
		accounts.insert(pair<long,Account>(account.getNumber(),account));
	}
	Account::setLastNextAccountNumber(account.getNumber()); 
	ifs.close();
}


Account Bank::openAccount(string fname, string lname, float balance){
	Account acc(fname,lname,balance);
	accounts.insert(pair<long,Account>(acc.getNumber(),acc));
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
	if(accounts.end()==itr || itr->first!=accountNumber){
		throw accountNotFound();
	}
	itr->second.deposit(amount);
	return itr->second;
}

Account Bank::withdraw(long accountNumber, float amount){
	map<long, Account>::iterator itr;
	itr=accounts.find(accountNumber);
	if(accounts.end()==itr || itr->first!=accountNumber){
		throw accountNotFound();
	}
	itr->second.withdraw(amount);
	return itr->second;
}

void Bank::transferMoney(long accountNumber1, long accountNumber2,float amount){
	map<long, Account>::iterator itr;
	itr=accounts.find(accountNumber1);
	if(accounts.end()==itr || itr->first!=accountNumber1){
		throw accountNotFound();
	}
	itr->second.withdraw(amount);
	
	map<long, Account>::iterator itr1;
	itr1=accounts.find(accountNumber2);
	if(accounts.end()==itr1 || itr1->first!=accountNumber2){
		throw accountNotFound();
	}
	itr1->second.deposit(amount);

}

void Bank::displayAllAccounts(){
	map<long, Account>::iterator itr;
	if(accounts.size()==0){
		cout<<"\tNo Accounts"<<endl<<endl;
		return;
	}
	for(itr=accounts.begin();itr!=accounts.end();itr++){
//		cout<<"Account: "<<itr->first<<endl;
		cout<<itr->second;
	}
}

Account Bank::BalanceEnquiry(long accountNumber){
	map<long, Account>::iterator itr;
	itr=accounts.find(accountNumber);
	if(itr->first!=accountNumber){
		throw accountNotFound();
	}
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
	cout<<"\t To save all Transaction. Please Exit\n";
	cout<<"Select one below option"<<endl;
	cout<<"\t1. Create Account"<<endl;
	cout<<"\t2. Balance Enquiry"<<endl;
	cout<<"\t3. Deposit"<<endl;
	cout<<"\t4. Withdraw"<<endl;
	cout<<"\t5. Transfer Money"<<endl;
	cout<<"\t6. Close Account"<<endl;
	cout<<"\t7. Show All Account"<<endl;
	cout<<"\t8. Exit"<<endl;
	cout<<"Enter your Choice: ";
	cin>>c;
	cout<<endl;
	if(c>0 && c<=8){
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
	long number,number2;
	Bank B;
	Account acc,acc2;
		int c=choice();
while(1)
{
	switch(c){
		case 1:
			try{
			cout<<"Enter First Name: ";
			cin>>fname;
			cout<<"Enter Last Name: ";
			cin>>lname;
			cout<<"Enter Balance: ";
			cin>>balance;
			if(balance<MIN_BALANCE)
				throw insufficientFunds();
			cout<<endl;
			acc=B.openAccount(fname,lname,balance);
			cout<<acc;
			cout<<"Account created Successfully!"<<endl<<endl;
			}
			catch(insufficientFunds e){
				cout<<"Minimum Balance must be "<<MIN_BALANCE<<endl<<endl;
			}
			c=choice();
			break;
		case 2:
			try{
			cout<<"Enter Account Number: ";
			cin>>number;
			cout<<endl;
			acc=B.BalanceEnquiry(number);
//			cout<<"Account Balance: "<<acc.getBalance()<<endl<<endl;
			cout<<acc;
			}
			catch(accountNotFound e){
				cout<<"Account Not Found\n\n";
			}
			c=choice();
			break;
		case 3:
			try{
			cout<<"Enter Account Number: ";
			cin>>number;
			cout<<"Enter Deposit Amount: ";
			cin>>amount;
			acc=B.deposit(number, amount);
			cout<<acc;
			cout<<endl;
			cout<<"Amount deposit in account Successfully!"<<"\n\n";
			}
			catch(accountNotFound e){
				cout<<"Account Not Found\n\n";
			}
			c=choice();
			break;
		case 4:
			try{
			cout<<"Enter Account Number: ";
			cin>>number;
			cout<<"Enter Withdraw Amount: ";
			cin>>amount;
			acc=B.withdraw(number, amount);
			cout<<acc;
			cout<<endl;
			cout<<"Amount withdraw in account Successfully!"<<"\n\n";
			}
			catch(insufficientFunds e){
			cout<<"Insufficient Funds"<<endl<<endl;
			}
			catch(accountNotFound e){
			cout<<"Account Not Found\n\n";
			}
			c=choice();
			break;
		case 5:
			try{
			cout<<"Transfer Money"<<endl;;
			cout<<"Enter From (Debit) Account Number: ";
			cin>>number;
			cout<<"Enter To (Credit) Account Number: ";
			cin>>number2;
			cout<<"Enter Amount: ";
			cin>>amount;
			B.transferMoney(number,number2,amount);
			cout<<"Transaction completed Successfully!"<<endl<<endl;
			}
			catch(insufficientFunds e){
			cout<<"Insufficient Funds"<<endl<<endl;
			}
			catch(accountNotFound e){
				cout<<"Account Not Found\n\n";
			}
			c=choice();
			break;
		case 6:
			cout<<"Enter Account Number: ";
			cin>>number;
			B.closeAccount(number);
			cout<<endl;
			cout<<"Account deleted Successfully!"<<endl<<endl;
			c=choice();
			break;
		case 7:
			B.displayAllAccounts();
			c=choice();
			break;
		case 8:
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
