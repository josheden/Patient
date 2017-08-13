#ifndef PATIENT_H
#define PATIENT_H
#include <iostream>
#include <string>
#include "Date.h"

using namespace std;

const Date DEFAULT_DATE;

//struct works as class but has no member functions and everything is public
struct procedure
{
	Date dateOfProcedure;
	int procedureID;
	int procedureProviderID;
};


class Patient {
private:
	char ID[33];
	char firstName[15];
	char lastName[15];
	Date  birthdate;
	int primaryDoctorID;
	procedure record[100];
	int currentCountOfProcedures;  // keeps track of how many procedures have 								//been recorded.  if it reaches 500, no new procedures can 							//be entered.

public:
	//Put in default values just as in Date class
	//Use the set functions so input values are checked 
	Patient(char *first = "", char *last = "", Date = DEFAULT_DATE, int id = 0000);
//	Patient() : ID{}, firstName{}, lastName{}, birthdate(0, 0, 0), primaryDoctorID(0) {};

	//~Patient();

	//check if length of name string is < 32.
	// if not, shorten to 32 letters.
	void setID();
	//check if length of name string is < 
	// 15, if not, shorten to 14 letters.
	void setFirstName(const char *);

	//check if length of name string is < 
	// 15, if not, shorten to 14 letters.
	void setLastName(const char *);

	//void setBirthDate(Date);
	void setBirthDate(Date);

	void setPrimaryDoctorID(int);

	const char * getID();

	const char * getFirstName();

	const char * getLastName();

	Date getBirthDate();

	int getPrimaryDoctorID();

	bool Patient::enterProcedure(Date procedureDate, int procedureID,
		int procedureProviderID);//tries to add a new entry to record array, returns 	 //true if added, false if cannot be added
	void Patient::printAllProcedures();
};
#endif 
