#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <array>
#include "Patient.h"
#include "Date.h"

using namespace std;

Patient::Patient(char *f, char *l, Date birthday, int primary_doctorID) {
	setFirstName(f);
	setLastName(l);
	setPrimaryDoctorID(primary_doctorID);
	setBirthDate(birthday);
	currentCountOfProcedures = 0;
	setID();

}

//~Patient() {}

//check if length of name string is < 32.
// if not, shorten to 32 letters.

void Patient::setID() {

	char newID[32];
	strcpy_s(newID, getLastName());
	strcat_s(newID, getFirstName());

	string yearstring = to_string(birthdate.getYear());
	strcat_s(newID, yearstring.c_str());


	strncpy_s(ID, newID, 32);


}
//check if length of name string is < 
// 15, if not, shorten to 14 letters.
void Patient::setFirstName(const char * fName) {

	if (strlen(fName) > 15) {
		strncpy_s(firstName, fName, 14);
		firstName[14] = '\0';
	}
	else
		strcpy_s(firstName, fName);

}

//check if length of name string is < 
// 15, if not, shorten to 14 letters.
void Patient::setLastName(const char * lName) {
	if (strlen(lName) > 15) {
		strncpy_s(lastName, lName, 14);
		lastName[14] = '\0';
	}
	else
		strcpy_s(lastName, lName);
}

// void setBirthDate(int m, int d, int y);
void Patient::setBirthDate(Date bbday) {
	birthdate = bbday;

}

void Patient::setPrimaryDoctorID(int primary_doctorID) {
	primaryDoctorID = primary_doctorID;
}

const char * Patient::getID() {

	return ID;
}


const char * Patient::getFirstName() {
	return firstName;
}

const char * Patient::getLastName() {
	return lastName;
}

Date Patient::getBirthDate() {
	return birthdate;
}


int Patient::getPrimaryDoctorID() {
	return primaryDoctorID;
}
//tries to add a new entry to record array, return, true if added, false if cannot be added
bool Patient::enterProcedure(Date procedureDate, int procedureID, int procedureProviderID) {
	if (currentCountOfProcedures == 100) {
		cout << "Update failed." << endl;
		return false;
	}
	else {
		record[currentCountOfProcedures].dateOfProcedure = procedureDate;
		record[currentCountOfProcedures].procedureID = procedureID;
		record[currentCountOfProcedures].procedureProviderID = procedureProviderID;
		currentCountOfProcedures++;
		return true;
	}
}

void Patient::printAllProcedures() {
		
		if (currentCountOfProcedures == 0) {
			cout << "No records to print." << endl;
		}
		else {
			for (int i = 0; i < currentCountOfProcedures; i++) {
				cout << "Record " << i + 1 << ": " << endl;
				cout << "Date: " << record[i].dateOfProcedure.getMonth() << "/" << record[i].dateOfProcedure.getDay() << "/"
					<< record[i].dateOfProcedure.getYear() << endl;
				cout << "Procedure ID: " << record[i].procedureID << endl;
				cout << "Provider ID: " << record[i].procedureProviderID << "\n" << endl;
			}
	}
}






