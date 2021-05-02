#include "egemetin_Metin_Ege_hw5_wallet.h"

using namespace std;


/*-------------------------------Beginning of Member Functions----------------------------*/


Wallet::Wallet()	// default constructor
{
	money_array = NULL;
	size = 0;
}


Wallet::~Wallet()	// destructor
{
	delete [] money_array;
}


Wallet::Wallet(const Wallet &copy)	// deep copy constructor
{
	size = copy.size;
	money_array = copy.createClone();
}


Money *Wallet::createClone() const		// creates clone of a wallet for deep copy constructor
{
	if ( size == 0 ) return NULL;
	Money *temp = new Money[size];
	for ( int a = 0; a < size; a++ ) {
		Money money;
		money.amount = money_array[a].amount;
		money.currency = money_array[a].currency;
		temp[a] = money;
	}
	return temp;
}


bool Wallet::isExists(const Money &rhs) const			// checks whether the Money object exists in current Wallet object
{
	for ( int k = 0; k < size; k++ ) {
		if ( money_array[k].currency == rhs.currency ) return true;
	}
	return false;
}


void Wallet::addMoney(const Money &rhs)		// adds money object to the wallet
{
	for ( int a = 0; a < size; a++ ) {
		if ( money_array[a].currency == rhs.currency ) money_array[a].amount += rhs.amount;
	}
	if ( ! isExists(rhs) ) {
		Money *temp = new Money[size+1];
		if ( size != 0 ) 
		{
			for ( int a = 0; a < size; a++ ) {
				Money money;
				money.amount = money_array[a].amount;
				money.currency = money_array[a].currency;
				temp[a] = money;
			}
		}
		size++;
		temp[size-1] = rhs;		// assign money(rhs) to the last element of the array
		delete [] money_array;
		money_array = temp;
	}
}


const Wallet & Wallet::operator+=(const Wallet & rhs)
{
	for ( int a = 0; a < rhs.size; a++ ) {
		addMoney(rhs.money_array[a]);
	}
	return *this;
}


Wallet Wallet::operator+ (const Money & rhs) const
{
	Wallet result(*this);
	result.addMoney(rhs);
	return result;
}


const Wallet &Wallet::operator= (const Wallet & rhs)
{
	if ( ! (*this == rhs) ) {
		delete [] money_array;
		size = rhs.size;
		money_array = new Money[size];
		for ( int a = 0; a < size; a++ ) {
			money_array[a].amount = rhs.money_array[a].amount;
			money_array[a].currency = rhs.money_array[a].currency;
		}
		return *this;
	}
	else return *this;
}


Wallet Wallet::operator+ (const Wallet &rhs) const
{
	Wallet temp(*this);
	temp += rhs;
	return temp;
}


Wallet Wallet::operator- (const Money & rhs) const
{
	Wallet result(*this);
	for ( int a = 0; a < size; a++ ) {
		if ( result.money_array[a].currency == rhs.currency && result.money_array[a].amount - rhs.amount >= 0) {
			result.money_array[a].amount -= rhs.amount;
			if ( result.money_array[a].amount == 0 ) {
				Money *newArray = new Money[size-1];
				int y = 0;
				for ( int a = 0; a < size-1; a++ ) {		// remove the currency with 0 amount
					if ( result.money_array[y].amount == 0 ) y++;
					Money money;
					money.amount = result.money_array[y].amount;
					money.currency = result.money_array[y].currency;
					newArray[a] = money;
					y++;
				}
				delete [] result.money_array;
				result.size--;
				result.money_array = newArray;
			}
			return result;
		}
	}
	return result;
}


bool Wallet::operator>= (const Money&rhs) const
{
	if ( isExists(rhs) ) {
		for ( int a = 0; a < size; a++ ) {
			if ( money_array[a].currency == rhs.currency && money_array[a].amount >= rhs.amount ) return true;
		}
		return false;
	}
	else return false;
}


int Wallet::getSize() const				// gives the size for free functions
{
	int a = size;
	return a;
}


Money *Wallet::get_m_array() const		// gives dynamic list for free functions
{
	Money *temp = money_array;
	return temp;
}


/*------------------------------------End of Member Functions-----------------------------------------*/


/*------------------------------------Beginning of Free Functions-------------------------------------*/


bool operator<= (const Money&lhs, const Wallet &rhs)
{
	return rhs.operator>=(lhs);
}


ostream & operator<< (ostream &os, Wallet lhs) 
{
	int size = lhs.getSize();
	if ( size != 0 ) {
		Money *temparray = lhs.get_m_array();
		os << temparray[0].currency << " " << temparray[0].amount;
		for ( int a = 1; a < size; a++ ) {
			os << " - " << temparray[a].currency << " " <<  temparray[a].amount;
		}
	}
	return os;
}


bool operator== (const Wallet &lhs, const Wallet &rhs)
{
	int lhs_size = lhs.getSize(), rhs_size = rhs.getSize();
	if ( lhs_size != rhs_size ) return false;
	else {
		Money *lhs_array = lhs.get_m_array(), *rhs_array = rhs.get_m_array();
		bool check = true;
		for ( int a = 0; a < lhs_size; a++ ) {
			if (check == true) {
				check = false;
				for ( int b = 0; b < rhs_size; b++ ) {
					if ( lhs_array[a].currency == rhs_array[b].currency && lhs_array[a].amount == rhs_array[b].amount ) {
						check = true;
						b = rhs_size;
					}
				}
			}
		}
		return check;
	}
}
