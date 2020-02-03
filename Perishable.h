/*Md Nuhel Nawaz Chowdhury
Milestone 5
ID: 109455162
SEC: AB
*/


#ifndef SICT_PERISHABLE_H
#define SICT_PERISHABLE_H
#include "NonPerishable.h"
#include "Date.h"

namespace sict {

	class Perishable : public NonPerishable {
	private:
		Date m_expiry_date;


	public:
		Perishable();/*this constructor passes the file record tag for
				  a perishable product (‘P’) to the base class constructor
				  and sets the current object to a safe empty state.*/

		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		const Date& expiry() const;

	};
	// Helper Function
	Product* CreatePerishable();
}

#endif
