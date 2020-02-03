#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "NonPerishable.h"

using namespace std;
namespace sict

{


	void NonPerishable::name(const char *n) {


		if (n == nullptr) {
			delete[] m_product_name;

		}
		else {
			m_product_name = new char[strlen(n) + 1];
			strncpy(m_product_name, n, (strlen(n) + 1));
			m_product_name[strlen(n) + 1] = '\0';
		}
	}

	const char *NonPerishable::name() const
	{
		if (m_product_name == nullptr)
			return nullptr;
		else return m_product_name;
	}



	void NonPerishable::message(const char *error)
	{
		err.message(error);

	}

	const char* NonPerishable::sku()const {
		return m_sku;
	}


	const char* NonPerishable::unit()const {
		return m_unit;
	}
	bool NonPerishable::isClear()const {
		if (err.isClear())

			return true;
		else
			return false;
	}
	NonPerishable::NonPerishable(char type)
	{

		m_food_type = type;
		m_sku[0] = '\0';
		m_product_name = nullptr;
		m_unit[0] = '\0';
		m_on_hand = 0;
		qty_needed = 0;
		m_price = 0;
		isTaxable = true;
	}


	NonPerishable::NonPerishable(const char* sku_, const char* Prod_name_, const char* unit_, int onHand_ , bool IsTaxable_, double price_, int qnt_needed_)
	{
		//Safe empty state.

		m_food_type = '\0';
		m_sku[0] = '\0';
		m_product_name = nullptr;
		m_price = 0.0;
		m_unit[0] = '\0';
		m_on_hand = 0;
		qty_needed = 0;
		

		strncpy(m_sku, sku_, +1);
		m_product_name = new char[strlen(Prod_name_) + 1];
		strncpy(m_product_name, Prod_name_, max_name_length);
		strncpy(m_unit, unit_, Unit_length + 1);
		m_on_hand = onHand_;
		isTaxable = IsTaxable_;
		m_price = price_;
		qty_needed = qnt_needed_;
		
	}

	NonPerishable::NonPerishable(const NonPerishable& other)
	{
		m_product_name = nullptr;
		*this = other;

	}
	NonPerishable & NonPerishable::operator=(const NonPerishable & other)
	{

		if (this != &other) {
			sku(other.m_sku);
			name(other.m_product_name);
			strcpy(m_unit, other.m_unit);
			m_on_hand = other.m_on_hand;
			qty_needed = other.qty_needed;
			isTaxable = other.isTaxable;
			m_price = other.m_price;

			return *this;

		}
		else
			m_sku[0] = '\0';
		m_product_name = nullptr;
		m_unit[0] = '\0';
		m_on_hand = 0;
		qty_needed = 0;
		isTaxable = false;

		return *this;
	}


	NonPerishable::~NonPerishable()
	{
		err.clear();
	}



	fstream & NonPerishable::store(fstream& file, bool newLine) const
	{

		file << m_food_type << ','
		<< m_sku << ','
		<< m_product_name << ',' 
		<< m_price << ',' 
		<< isTaxable << ','
		<< m_on_hand<< ',' 
		<< m_unit << ',' 
		<< qty_needed;
		if (newLine) {
			file << endl;
		}
		return file;
	}

	fstream& NonPerishable::load(fstream& file)
	{
		char temp_sku[max_sku_length + 1];
		char temp_name[max_name_length + 1];
		char temp_unit[Unit_length + 1];
		double temp_price;
		int temp_qty, temp_qtyN, temp_tax;

		if (file.is_open()) {
			file.getline(temp_sku, max_sku_length, ',');
			sku(temp_sku);
			file.getline(temp_name, max_name_length + 1, ',');

			name(temp_name);

			file >> temp_price;
			file.ignore();
			m_price = temp_price;

			file >> temp_tax;
			file.ignore();
			isTaxable = temp_tax;

			file >> temp_qty;
			file.ignore();
			m_on_hand = temp_qty;


			file.getline(temp_unit, Unit_length + 1, ',');
			unit(temp_unit);

			file >> temp_qtyN;
			file.ignore();
			qty_needed = temp_qtyN;
		}
		return file;
	}

	std::ostream &NonPerishable::write(std::ostream & os, bool linear) const
	{

		if (!(err.isClear())) {
			os << err.message();
		}
		else if (linear) {
			os << left << setw(max_sku_length) << setfill(' ') << sku() << "|"
				<< left << setw(20) << setfill(' ') << name() << "|";

			os << right << fixed << setfill(' ') << setw(7) << setprecision(2) << cost() << "|";


			os << right << setw(4) << setfill(' ') << fixed << quantity() << "|"
				<< left << setw(10) << setfill(' ') << unit() << "|"
				<< right << setw(4) << setfill(' ') << fixed << qtyNeeded() << "|";
		}
		else {
			os << "Sku: " << m_sku << endl;
			os << "Name: " << m_product_name << endl;
			os << "Price: " << m_price << endl;
			os << "Price after tax: ";
			if (taxed()) {
				os << cost() << endl;
			}
			else {
				os << "N/A" << endl;
			}
			os << "Quantity On Hand: " << quantity() << ' ' << m_unit << endl;
			os << "Quantity Needed: " << qtyNeeded();
		}
		return os;
	}

	std::istream& NonPerishable::read(std::istream& is) {
		
		char tempSku[max_sku_length + 1];
		char tempName[max_name_length + 1];
		char tempUnit[Unit_length + 1];

		char taxChar;
		double tempPrice;
		int tempCurrentQty;
		int tempQtyNeeded;

		if (!is.fail()) {
			err.clear();
			cout << " Sku: ";
			is >> tempSku;
			cin.ignore();
			sku(tempSku);

			cout << " Name: ";
			is.getline(tempName, max_name_length + 1);
			name(tempName);

			cout << " Unit: ";
			is.getline(tempUnit, Unit_length - 1);
			unit(tempUnit);

			cout << " Taxed? (y/n): ";
			is >> taxChar;
			if (is.fail() || !(taxChar == 'Y' || taxChar == 'y' || taxChar == 'N' || taxChar == 'n')) {
				err.message("Only (Y)es or (N)o are acceptable");
				is.setstate(std::ios::failbit);
				return is;
			}
			else {
				if (taxChar == 'Y' || taxChar == 'y')
				{
					setTaxable(true);
				}
				else
				{
					setTaxable(false);
				}

			}
			cout << " Price: ";
			if (err.isClear()) {
				is >> tempPrice;
				if (is.fail()) {

					err.message("Invalid Price Entry");
					is.setstate(ios::failbit);
					return is;
				}
				else {
					m_price = tempPrice;
				}
			}
			if (err.isClear()) {
				cout << "Quantity On hand: ";
				is >> tempCurrentQty;
				if (is.fail()) {

					err.message("Invalid Quantity Entry");
					is.setstate(ios::failbit);
					return is;
				}
				else
				{
					m_on_hand = tempCurrentQty;
				}
			}
			if (err.isClear()) {
				cout << "Quantity Needed: ";
				is >> tempQtyNeeded;
				if (is.fail()) {

					err.message("Invalid Quantity Needed Entry");
					is.setstate(ios::failbit);
					return is;

				}
				else {
					qty_needed = tempQtyNeeded;
				}
				return is;
			}
		}
		return is;
	}

	bool NonPerishable::operator==(const char* Sku) const
	{
		if (strcmp(m_sku, Sku) == 0)
			return true;
		else
			return false;
	}

	bool NonPerishable::taxed() const {
		return isTaxable;
	}

	double NonPerishable::total_cost() const {


		double totalcost = 0.0;

		totalcost = m_on_hand * cost();


		return totalcost;

	}

	double NonPerishable::cost() const {


		double cost = m_price;
		if (isTaxable)
			return cost *= (1 + Tax_rate);
		else
			return cost;
	}

	bool NonPerishable::isEmpty() const {
		if (m_product_name == nullptr)
			return true;
		else
			return false;
	}

	int NonPerishable::quantity() const {

		return  m_on_hand;
	}

	int NonPerishable::qtyNeeded() const {
		return qty_needed;
	}

	bool NonPerishable::operator>(const char* item) const {
		int a = strcmp(m_sku, item);
		if (a > 0)
			return true;
		else
			return false;
	}

	int NonPerishable::operator+=(int add) {
		if (add > 0)
		{
			m_on_hand += add;
			return m_on_hand;
		}
		else
			return m_on_hand;
	}

	bool NonPerishable::operator>(const Product& name) const
	{
		int a = strcmp(m_sku, name.name());
		if (a > 0)
			return true;
		else
			return false;
	}

	std::ostream& operator<<(std::ostream&os, const Product& I)
	{

		return I.write(os, true);

	}

	std::istream& operator >> (std::istream& i, Product& p) {

		return p.read(i);

	}

	double operator+=(double& l, const Product& item) {

		return l += item.total_cost();


	}
	Product * CreateProduct()
	{
		Product* p = nullptr;
		p = new NonPerishable();
		return p;
	}

	//bool operator

	

	void NonPerishable::setTaxable(bool T) {

		isTaxable = T;
	}

	void NonPerishable::sku(const char* sku) {
		strncpy(m_sku, sku, max_sku_length + 1);
	}

	void NonPerishable::unit(const char * unit)
	{
		strncpy(m_unit, unit, Unit_length + 1);
	}


	void NonPerishable::quantity(int b)
	{
		m_on_hand = b;
	}

}
