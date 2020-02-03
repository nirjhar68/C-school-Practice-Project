#include <iostream>
#include <iomanip>
#include <fstream>
#include "Date.h"
#include "NonPerishable.h"
#include "Perishable.h"

	namespace sict {

	Perishable::Perishable() :NonPerishable('P')
	{
		err.clear();
	}

	std::fstream& Perishable::store(std::fstream& file, bool newLine) const
	{

		NonPerishable::store(file, false);
		file << ",";
		m_expiry_date.write(file);
		if (newLine)
		{
			file << std::endl;
		}
		return file;
	}


	std::fstream & Perishable::load(std::fstream & file)
	{
		NonPerishable::load(file);
		m_expiry_date.read(file);
		file.ignore();

		return file;
	}


	std::ostream & sict::Perishable::write(std::ostream & os, bool linear) const
	{
		NonPerishable::write(os, linear);
		if (isClear() && !isEmpty()) {
			if (linear == true) {
				m_expiry_date.write(os);
			}
			else {
				os << "\nExpiry date: ";
				m_expiry_date.write(os);
			}
		}
		return os;
	}


	std::istream &Perishable::read(std::istream & is)
	{

		is.clear();
		NonPerishable::read(is);

		if (err.isClear()) {
			std::cout << "Expiry date (YYYY/MM/DD): ";
			m_expiry_date.read(is);
		}

		if (m_expiry_date.errCode() == CIN_FAILED) {
			err.clear();
			err.message("Invalid Date Entry");
		}
		if (m_expiry_date.errCode() == YEAR_ERROR) {
			err.message("Invalid Year in Date Entry");
		}
		if (m_expiry_date.errCode() == MON_ERROR) {
			err.clear();
			err.message("Invalid Month in Date Entry");
		}
		if (m_expiry_date.errCode() == DAY_ERROR) {
			err.clear();
			err.message("Invalid Day in Date Entry");
		}
		if (m_expiry_date.errCode()) {
			is.setstate(std::ios::failbit);
		}
		if (m_expiry_date.errCode() != CIN_FAILED && m_expiry_date.errCode() != YEAR_ERROR && m_expiry_date.errCode() != MON_ERROR && m_expiry_date.errCode() != DAY_ERROR) {
			err.clear();  //clear if there is no errorcode.
		}

		return is;
	}


	//Expiry
	const Date& Perishable:: expiry() const
	{
		return m_expiry_date;
	}

	//Helper Function

	Product* createPerishable()
	{
		Product* product = new Perishable();
		return product;
	}
}
