/*Md Nuhel Nawaz Chowdhury
ID: 109455162
Milestone 2
Dec 04, 2017 */
#pragma once
#ifndef SICT_ERRORMESSAGE_H
#define SICT_ERRORMESSAGE_H
#include<iostream>

namespace sict
{
	class ErrorMessage
	{
	private:
		char* message_;
	public:
		ErrorMessage();
		ErrorMessage(const char* errorMessage);
		ErrorMessage(const ErrorMessage& em) = delete;
		ErrorMessage& operator=(const ErrorMessage& em) = delete;
		ErrorMessage& operator=(const char* errorMessage);
		virtual ~ErrorMessage();
		void clear();
		bool isClear()const;
		void message(const char* value);
		const char* message() const;
		std::ostream& write(std::ostream& ostr) const;
	};
	std::ostream& operator<<(std::ostream& ostr, const ErrorMessage& em);
}
#endif

