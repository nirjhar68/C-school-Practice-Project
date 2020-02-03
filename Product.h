/*Md Nuhel Nawaz Chowdhury
ID:109455162
Milestone: 3
Dec 12, 2017*/

#ifndef  SICT_PRODUCT_H__
#define  SICT_PRODUCT_H__
#include <fstream>
#include <iostream>

namespace sict
{
	class Product
	{
	private:
	public:
		virtual std::fstream& store(std::fstream& file, bool newLine = true) const = 0;
		virtual std::fstream& load(std::fstream&file)= 0 ;
		virtual std::ostream& write(std::ostream&os, bool linear) const = 0;
		virtual std::istream& read(std::istream&is) = 0;
		virtual bool operator == (const char*) const = 0;
		virtual double total_cost() const = 0;
		virtual const char* name() const = 0;
		virtual void quantity(int) = 0;
		virtual int qtyNeeded() const = 0;
		virtual int quantity() const = 0;
		virtual int operator += (int)=0;
		virtual bool operator > (const Product& ) const = 0;


	};
	//Helper function
	std::ostream& operator<<(std::ostream&, const Product&);
	std::istream& operator>>(std::istream&, Product&);
	double operator += (double&, const Product&);
	Product* CreateProduct();
	Product* CreatePerishable();
}


#endif

