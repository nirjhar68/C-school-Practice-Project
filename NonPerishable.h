
#ifndef SICT_NONPERISHABLE_H
#define SICT_NONPERISHABLE_H

#include "Product.h"
#include "ErrorMessage.h"

namespace sict
{
	const int max_sku_length = 7;
	const int Unit_length = 10;
	const int max_name_length = 75;
	const double Tax_rate = 0.13;
	
	class NonPerishable : public Product
	{
	private:
		char m_food_type;// A character indicates the type of product – for use in the file record

		char m_sku[max_sku_length];// A character array that holds the product’s sku. The maximum number of characters excluding the null byte is max_sku_length. 
		
		char* m_product_name;//A pointer to a character array in dynamic memory that holds the name of the product.

		char m_unit[Unit_length];// A character array that holds the unit for the product. The maximum number of characters excluding the null byte is max_unit_length.

		int m_on_hand;// An integer that holds the current quantity on hand of the product.

		int qty_needed;

		double m_price;// A double that holds the price of the product before taxes.
		
		bool isTaxable;// A bool that is true if the product is taxable.
		
		const char* sku() const;

		const char* unit()const;

		char m_pro_type;
		
		// An ErrorMessage object that holds the error state of the current object.
		
		void setEmpty(char);

	protected:

		

		void name(const char*);/*receives the address of a C-style null terminated string that holds
							   the name of the product and stores the name in dynamically allocated memory.*/
		
		const char*name() const;/*;- returns the address of the C-style string that holds the name of the product.
								If the product has no name, this query returns nullptr.*/

		double cost() const; /*returns the price of the product plus any tax that applies to the product.*/

		void message(const char*); /*receives the address of a C-style string holding an
								   error message and stores that message in the ErrorMessage object.*/

		bool isClear() const; /*returns true if the ErrorMessage object is clear; false otherwise.*/

		bool isEmpty() const;

		void sku(const char* sku_);

		void unit(const char* unit_);

		ErrorMessage err;
	
	public: 
		
		NonPerishable(char type = 'N');//This constractor reveices optionally a character that describe the type of the product.
		
		~NonPerishable();

		NonPerishable(const char* sku_, const char* Prod_name_, const char* unit_, int onHand_= 0, bool IsTaxable_ = true, double price_ = 0.0, int qnt_needed_= 0);// Seven argument Constructor.

		NonPerishable(const NonPerishable&);// Receives an unmodifiable reference to current object. Copy constructor.

		NonPerishable& operator = (const NonPerishable&);// Copy assign operator.

		std::fstream& store(std::fstream& file, bool newLine = true) const;

		std::fstream& load(std::fstream&file);

		std::ostream& write(std::ostream& os, bool linear) const;

		std::istream& read(std::istream&is);

		bool operator == (const char*) const;

		bool taxed() const;

		double total_cost() const;

		void quantity(int);
	
		//bool isEmpty() const;

		int qtyNeeded() const;

		int quantity() const;

		bool operator > (const char*) const;

		int operator += (int);

		bool operator > (const Product& ) const;

		void setTaxable(bool T);


	};

	//Helper Functions...

	std::ostream& operator<<(std::ostream&, const Product&);

	std::istream& operator>>(std::istream&, Product&);

	double operator += (double&, const Product&);

	Product* CreateProduct();

}
#endif
