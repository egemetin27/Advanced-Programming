#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Money
{
	string currency;
	double amount;
};


class Wallet
{
	public:
		Wallet();			// default copy constructor	
		Wallet(const Wallet&);	// deep copy constructor
		~Wallet();			// destructor
		const Wallet & operator+=(const Wallet & lhs);
		Wallet operator+ (const Money&) const;
		Wallet operator+ (const Wallet&) const;
		Wallet operator- (const Money &) const;
		const Wallet &operator= (const Wallet&);
		bool isExists(const Money &) const;			// checks whether money exists in the Wallet(array)
		Money *createClone() const;					// creates clone of the object(this) for deep copy constructor
		void addMoney(const Money &);				// adds money object to the wallet
		int getSize() const;						// gives the size for free functions
		Money *get_m_array() const;					// gives dynamic list for free functions
		bool operator >= (const Money&) const;
	private:
		Money *money_array;
		int size;
};

bool operator== (const Wallet &lhs, const Wallet &rhs);
bool operator<= (const Money&lhs, const Wallet &rhs);
ostream & operator<< (ostream &os, Wallet lhs);
