#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>
#include "Patient.h"
#include "Date.h"

using namespace std;

int main() {

	char choice;
	char tryagain;
	int doctorID;
	char first_Name[16];
	char last_Name[16];
	Patient all_patients[20];
	Patient checkin_today[10];
	Patient all_record[20];
	Patient print_patient;
	int check_count = 0;
	//int all_patients_count = 0;
	int record_count = 0;
	int procedure_count = 0;
	bool quit = false;

	int all_patients_count = 0;

	ifstream inFile("CurrentPatients.dat", ios::in | ios::binary);
	if (inFile.is_open()) {

		
			inFile.read((char*)&all_patients_count, sizeof(Patient));
			if (!inFile.eof()) {
				for (int i = 0; i < all_patients_count; i++) {
				inFile.read((char*)&all_patients[i], sizeof(Patient));
			}
			
		}
		inFile.close();
	}
	else cout << "File not open." << endl;

	int month, day, year;
	cout << "whats todays date";//make a date object called today
	cin >> day;
	cin >> month;
	cin >> year;
	Date todays_date(day, month, year);

	//Patient patient;
	

	while (!quit) {
		cout << "\n\nN: New patient information." << endl;
		cout << "R: Returning patient information" << endl;
		cout << "O: Check out patient(s)." << endl;
		cout << "I: Print patient past information." << endl;
		cout << "P: Display all patients information who are checked in." << endl;
		cout << "Q: Write to binary file and quit." << endl << endl;
		cout << "Enter choice: ";
		cin >> choice;


		switch (choice) {
		case 'N': {

			cout << "\n\nPlease enter patients first name: ";
			cin >> first_Name;
			cout << "\nPlease enter patients last name: ";
			cin >> last_Name;
			cout << "\nPlease enter patients birthday, month, and year: ";
			cin >> day;
			cin >> month;
			cin >> year;
			cout << "enter doctorID: ";
			cin >> doctorID;
			Date bd(day, month, year);
			Patient patient(first_Name, last_Name, bd, doctorID);

			cout << patient.getID();
			checkin_today[check_count] = patient;
			check_count++;

			all_patients[all_patients_count] = patient;
			all_patients_count++;
			break;
		}

		case 'R': {
			string patient_ID;
			cout << "Enter ID: ";
			cin >> patient_ID;
			bool found = false;
			int i = 0;
			while (!found && i < all_patients_count) {
				if (all_patients[i].getID() == patient_ID) {
					found = true;
					cout << "Patient ID has been found!" << endl;
				}
				else i++;
			}
			if (found) {
				checkin_today[check_count] = all_patients[i];
				check_count++;
			}
			else
				cout << "ID has not been found." << endl;
			break;

		}
		case 'O': {
			string patient_ID;
			string ID_retry;
			int patient_location;
			cout << "Enter patient ID:";
			cin >> patient_ID;
			bool found = false;

			//Date proc_date(month, day, year);
			int procedureID;
			cout << "Enter procedure ID: ";
			cin >> procedureID;
			int providerID;
			cout << "Enter provider ID: ";
			cin >> providerID;

			int i = 0;
			while (!found && i < check_count) {
				if (checkin_today[i].getID() == patient_ID) {
					found = true;
					cout << "Patient ID found in checked in today." << endl;
				}
				else
					i++;
			}



			if (found) {
				bool all_found = false;
				int j = 0;
				checkin_today[i].enterProcedure(todays_date, procedureID, providerID);
				while (!all_found && j < all_patients_count) {
					if (all_patients[j].getID() == patient_ID) {
						all_found = true;
						all_patients[j] = checkin_today[i];
					}
					else j++;
				}
				if (check_count > 1) {
					for (int k = i; k < check_count; k++) {
						checkin_today[k] = checkin_today[k + 1];
					}				
				}
				check_count--;
			}
			
			
			if (!found) {
				cout << "ID not found." << endl;
			}

			break;
		}
		case 'I': {
			cout << "Enter patients ID: ";
			string patient_ID;
			cin >> patient_ID;
			int i = 0;

			bool found = false;
			while (!found && i < all_patients_count) {
				if (all_patients[i].getID() == patient_ID) {
					found = true;
					cout << "Print patient record........" << endl;
					cout << "Birthdate: " << all_patients[i].getBirthDate() << "\nFirst name: " << all_patients[i].getFirstName()
						<< "\nLast name: " << all_patients[i].getLastName() << "\nID number :" << all_patients[i].getID()
						<< "\n Procedures: ";
					all_patients[i].printAllProcedures();

				}
				else
					i++;
			}
			break;
		}
				  //currently checked in print
		case 'P': {
			cout << "All patient count " << all_patients_count << endl;
			cout << "Checked in count " << check_count << endl;

			if (all_patients_count == 0) {
				cout << "No records to be displayed." << endl;
			}
			else {
				for (int i = 0; i < all_patients_count; i++) {
					cout << "\n\nPatient ID: " << all_patients[i].getID() << "\n" //check in
						<< "First name: " << all_patients[i].getFirstName() << "\n"
						<< "Last name: " << all_patients[i].getLastName() << "\n"
						<< "Primary Doctor ID: " << all_patients[i].getPrimaryDoctorID() << endl;
				}
			}
			break;
		}

		case 'Q': {
			if (check_count == 0) {
				ofstream outFile("CurrentPatients.dat", ios::out, ios::binary);
				outFile.write((char*)&all_patients_count, sizeof(Patient));
				for (int i = 0; i < all_patients_count; i++) 
					outFile.write(reinterpret_cast<char*>(&all_patients[i]), sizeof(Patient));

				outFile.close();
				cout << "Current checked in list is currently empty. " << endl;
				quit = true;
			}
			else 
				cout << "Error, people still checked in." << endl;
				
			break;	
		}
		}
	}

	system("PAUSE");
	return 0;

} 
