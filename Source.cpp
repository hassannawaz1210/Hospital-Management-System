#include "Header.h"


//---------------------- Binary file handling functions ---------------------------//
//void Write(string file_name, int usertype)
//{
//	if (usertype == 0)
//	{
//		Admin obj(username, password);
//	}
//	fstream fout;
//	fout.open(file_name, fstream::app | fstream::out);
//	fout.write((char*)&obj, sizeof(Admin));
//	fout.seekg(0);
//	fout.close();
//}
//
//bool Read(User &obj, string file_name, int usertype)
//{
//	ifstream fin;
//	Admin temp;
//	fin.open(file_name);
//	if (fin.is_open())
//	{
//		
//	//	cout << "kekek";
//	////	bool condition = 0;
//	//while (fin.read((char*)&temp, sizeof(Admin)))
//	//	//return true;
//	////	temp.display();
//	//	{
//			if (temp == obj)
//			{
//				return true;
//			}
//	//	}
//	}
//	else cout << "No file found" << endl;
//	fin.seekg(0);
//	fin.close();
//	return false;
//}


//---------------------- end ----------------------//

//-------------------------- Data and time class -----------------------//
Date::Date()
{
	day = 0;
	month = 0;
	year = 0;
}

Date::Date(int d, int m, int y)
{
	day = d;
	month = m;
	year = y;
}

Time::Time()
{
	hours = 0;
	minutes = 0;
}

Time::Time(int h, int m)
{
	hours = h;
	minutes = m;
}
//--------------------------- end -------------------///



//---------------------- payment class functions ---------------------------//
void EasyPaisa::pay(int amount)
{
	cout << "You have successfully paid Rs." << amount << " for the appointment through EasyPaisa.\n";
	paidStatus = true;
}

void Jazzcash::pay(int amount)
{
	cout << "You have successfully paid Rs." << amount << " for the appointment through Jazzcash.\n";
	paidStatus = true;

}

void PayPak::pay(int amount)
{
	cout << "You have successfully paid Rs." << amount << " for the appointment through PayPak.\n";
	paidStatus = true;

}

void UnionPay::pay(int amount)
{
	cout << "You have successfully paid Rs." << amount << " for the appointment through Union pay.\n";
	paidStatus = true;

}

int BankTranfer::getPaidAmount()
{
	return paidAmount;
}

int eTransaction::getPaidAmount()
{
	return paidAmount;
}


//--------------------------- end -------------------///




//---------------------- Availability class functions ---------------------------//

AvailibilityHours::AvailibilityHours()
{
	startingTime = 0;
	finishingTime = 0;
}
AvailibilityHours::AvailibilityHours(int start, int finish)
{
	startingTime = start;
	finishingTime = finish;
}



//---------------------- Appointment class functions ---------------------------//
void Appointment::displayAppointment()
{
	cout << "Status: " << status << endl;
	cout << "Appointment mode: " << appointmentMode << endl;
}


void Appointment::bookAppointment(Patient &patient)
{
	string first, last;
	cout << "\nName of the doctor would you like to set up an appointment with:\n";
	bool repeat = true;
	Doctor temp;
	do
	{
		cout << "First Name: ";
		getline(cin, first);
		cout << "Last name: ";
		getline(cin, last);
		cout << endl;
		ifstream fin;
		fin.open("doctors.dat");
		if (fin.is_open())
		{
			while (fin.read((char*)&temp, sizeof(Doctor)))
			{

				if (!strcmp(temp.getFirst(), first.c_str()) && !strcmp(temp.getLast(), last.c_str()))
				{
					repeat = false;
					break;
				//	temp.displayData();
				}
			}
			system("CLS");
			if (repeat) cout << "No such doctor exist, please try again: \n";
		}
		fin.seekg(0);
		fin.close();
	} while (repeat);
	cout << "Appointment mode: \n";
	cout << "0. Online video consultation\n";
	cout << "1. In-person meeting\n";
	appointmentMode = _getch();
	status = 0;
	if (appointmentMode)
	{ 
		cout << "\nThe charges for In-person meeting are: " << temp.getInPersonCharges() << endl;
	}
	else cout << "\nThe charges for online cosultation are: " << temp.getVidCharges() << endl;
	//----- payment
	cout << "\nHow would you like to pay: \n";
	cout << "1. Bank transfer\n2. E-transaction\n";
	char input = _getch();
	int amount;

	if (input == '1')
	{
		BankTranfer* p = nullptr;
		cout << "\nChoose between the methods below: \n1. Paypak\n2. Union pay\n";
		input = _getch();
		if (input == '1')
		{
			p = new PayPak();
			cout << "\nEnter the amount you want to pay: ";
			cin >> amount;
			cin.ignore();
			if (amount > patient.getBalance())
				cout << "You dont have enough balance in your account.\n";
			else
			{
				system("CLS");
				p->pay(amount);
				cout << "\nThe appointment's status is now pending.\nPlease wait for the doctor to approve it.\n\n";
			}

		}
		else if (input == '2')
		{
			p = new UnionPay();
			cout << "\nEnter the amount you want to pay: ";
			cin >> amount;
			cin.ignore();
			if (amount > patient.getBalance())
				cout << "You dont have enough balance in your account.\n";
			else
			{
				system("CLS");
				p->pay(amount);
				cout << "\nThe appointment's status is now pending.\nPlease wait for the doctor to approve it.\n\n";
			}
		}
		patient.getBalance() -= p->getPaidAmount();
		temp.getBalance() += p->getPaidAmount();
	}
	else if (input == '2')
	{
		eTransaction* p = nullptr;
		cout << "\nChoose between the methods below: \n1. EasyPaisa\n2. Jazzcash\n";
		input = _getch();
		if (input == '1')
		{
			p = new EasyPaisa();
			cout << "\nEnter the amount you want to pay: ";
			cin >> amount;
			cin.ignore();
			if (amount > patient.getBalance())
				cout << "You dont have enough balance in your account.\n";
			else
			{
				system("CLS");
				p->pay(amount);
				cout << "\nThe appointment's status is now pending.\nPlease wait for the doctor to approve it.\n\n";
			}
		}
		else if (input == '2')
		{
			p = new Jazzcash();
			cout << "\nEnter the amount you want to pay: ";
			cin >> amount;
			cin.ignore();
			if (amount > patient.getBalance())
				cout << "You dont have enough balance in your account.\n";
			else
			{
				system("CLS");
				p->pay(amount);
				cout << "\nThe appointment's status is now pending.\nPlease wait for the doctor to approve it.\n\n";
			}
		}
		patient.getBalance() -= p->getPaidAmount();
		temp.getBalance() += p->getPaidAmount();
	}
	//this->displayAppointment();
	saveAppointment(temp, patient, *this);


}

void Appointment::saveAppointment(Doctor& doc, Patient& pat, Appointment& app )
{
	ofstream fout;
	fout.open("appointments.dat", ios::binary | ios::app);
	fout.write((char*)pat.getFirst(), 50);
	fout.write((char*)pat.getLast(), 50);
	fout.write((char*)pat.getCNIC(), 50);
	fout.write((char*)doc.getFirst(), 50);
	fout.write((char*)doc.getLast(), 50);
	fout.write((char*)&app, sizeof(Appointment));
	fout.close();
}

void readAppointment()
{
	cout << "-------- Appointment's details: ----------\n\n";
	ifstream fin;
	Appointment obj;
	fin.open("appointments.dat", ios::binary);
	char temp[50];
	fin.read((char*)&temp, 50);
	cout << "Patients's first name: " << temp << endl;
	fin.read((char*)&temp, 50);
	cout << "Patients's last name: " << temp << endl;
	fin.read((char*)&temp, 50);
	cout << "Patient's CNIC: " << temp << endl;
	fin.read((char*)&temp, 50);
	cout << "Doctors's first name: " << temp << endl;
	fin.read((char*)&temp, 50);
	cout << "Doctors's last name: " << temp << endl;
	fin.read((char*)&obj, sizeof(Appointment));
	obj.displayAppointment();
	fin.close();
	cout << "-------------------";
}

//---------------------- end ----------------------//



//---------------------- Patient class functions ---------------------------//
Patient::Patient(): Child("", "") {}

Patient::Patient(string user, string pass): Child(user,pass)
{}

Patient::Patient(string first, string last, string user, string pass , string cnic,string phone, char gen, int bal): Child(first, last, cnic, user, pass, bal)
{
	gender = gen;
	strcpy_s(this->phone, phone.c_str());
}

bool Patient::operator==(Patient& obj)
{
	if (!strcmp(username, obj.username) && !strcmp(password, obj.password)) return true;
	else return false;
}

void Patient::displayData()
{
	cout << "------ Patient " << firstName << " " << lastName << "'s Data: ------- \n";
	cout << "CNIC: " << CNIC << endl;
	cout << "Phone number: " << phone << endl;
	cout << "Gender: " << gender << endl;
	cout << "-------------------------\n";
}

void Patient::viewProfile()
{
	cout << "------ Your profile ------\n";
	cout << "First name: " << firstName << endl;
	cout << "Last name:" << lastName << endl;
	cout << "Username: " << username << endl;
	cout << "Phone number: " << phone << endl;
	cout << "Gender: " << gender << endl;
	cout << "CNIC: " << CNIC << endl;
	cout << "Balance: " << balance << endl;
	cout << "-------------------------\n";
}


void Patient::searchDoctor()
{
	cout << "Search doctor via:\n\n";
	cout << "1. Specialty\n2. Hospital\n3. City\n";
	char input; string specialty, hospital, city;
	input = _getch();
	if (input == '1')
	{
		cout << "Enter the doctor's specialty: \n";
		getline(cin, specialty);
	}
	else if (input == '2')
	{
		cout << "Enter the doctor's Hospital name: \n";
		getline(cin, hospital);
	}
	else if (input == '3')
	{
		cout << "Enter the doctor's city's name: \n";
		getline(cin, city);
	}
	ifstream fin;
	Doctor obj;
	fin.open("doctors.dat");
	bool flag = true;
	while (fin.read((char*)&obj, sizeof(Doctor)))
	{
		if (input == 1 && !(strcmp(obj.getSpecialty(), specialty.c_str())))
		{
			obj.displayData();
			flag = false;
		}
		else if (input == 2 && !(strcmp(obj.getHospital(), hospital.c_str())))
		{
			obj.displayData();
			flag = false;
		}
		else if (input == 3 && !(strcmp(obj.getCity(), city.c_str())))
		{
			obj.displayData();
			flag = false;
		}
	}
	system("CLS");
	if (flag) cout << "No such doctor found.\n";

}


void Patient::setPass(string& str)
{
	strcpy_s(password, str.c_str());
}


void Patient::menu(bool& logout)
{
	while (!logout)
	{
		cout << "\n ============= Patient's Menu ==============\n";
		cout << "1. Show available doctors.\n";
		cout << "2. Search for doctor\n";
		cout << "3. Book Appointment\n";
		cout << "4. Show my appointments\n";
		cout << "5. Reset password\n";
		cout << "6. View profile\n";
		cout << "7. Logout\n";
		cout << "=====================================\n\n";
		char input = _getch();
		switch (input)
		{
			case '1':
			{
				system("CLS");
				ifstream fin;
				Doctor obj;
				fin.open("doctors.dat", ios::binary);
				if (fin.is_open())
				{
					while (fin.read((char*)&obj, sizeof(Doctor)))
					{
						obj.displayData();
					}
					fin.close();
				}
				else
				{
					cout << "No Available doctors yet.\n";
					fin.close();
				}
				break;
			}
			
			case '2':
			{
				system("CLS");
				this->searchDoctor();
				break;
			}
			case '3':
			{
				system("CLS");
				appointment.bookAppointment(*this);
			//	readAppointment();
				break;
			}


			case '4':
			{
				system("CLS");
				ifstream fin;
				fin.open("appointments.dat", ios::binary);
				if (fin.is_open())
				{


					char temp[50], first[50], last[50];
					fin.seekg(0);
					bool flag = true;
					while (!fin.eof())
					{
						//fin.seekg(150, ios::cur);
						fin.read((char*)&first, 50);
						fin.read((char*)&last, 50);
						cout << first << last << endl;
						if (!strcmp(this->getFirst(), first) && !strcmp(this->getLast(), last))
						{
							flag = false;
							cout << "\n---------------- Appointment data --------------- \n";
							int a = fin.tellg();
							fin.seekg(a - 100, ios::beg);
							Appointment obj;
							fin.read((char*)&temp, 50);
							cout << "Patients's first name: " << temp << endl;
							fin.read((char*)&temp, 50);
							cout << "Patients's last name: " << temp << endl;
							fin.read((char*)&temp, 50);
							cout << "Patient's CNIC: " << temp << endl;
							fin.read((char*)&temp, 50);
							cout << "Doctors's first name: " << temp << endl;
							fin.read((char*)&temp, 50);
							cout << "Doctors's last name: " << temp << endl;
							fin.read((char*)&obj, sizeof(Appointment));
							obj.displayAppointment();
							cout << "--------------------------------- \n";
						}
						fin.get();
						if (fin.eof())
						{
							break;
						}
						else {
							int b = fin.tellg();
							fin.seekg(b - 1);
						}

					}

					if (flag) cout << "No appointments found.\n";
					fin.close();
				}
				else
				{
					cout << "You dont have any appointments yet.\n";
					fin.close();
				}
				break;
			}// case 4 end

			case '5':
			{
				system("CLS");
				fstream f;
				Patient temp;
				f.open("patients.dat", ios::binary | ios:: in | ios:: out);
				bool flag = true;
				while (f.read((char*)&temp, sizeof(Patient)))
				{
					if (!strcmp(temp.getUser(), this->getUser()))
					{
						string pass;
						cout << "Enter the new password: ";
						getline(cin, pass);
						temp.setPass(pass);
						int a = f.tellg();
						f.seekg(a - sizeof(Patient));
						f.write((char*)&temp, sizeof(Patient));
						flag = false;
						system("CLS");
						cout << "\nYour password has been succesfully changed.\n";
					}
				}
				f.close();
				if (flag) cout << "Your account was not found on the databases.\n";
				break;
			}// case 5 end
			case '6':
			{
				system("CLS");
				this->viewProfile();
				break;
			}// case 6 end
			case '7':
			{
				logout = 1;
				system("CLS");
				cout << "\nYou have successfully logged out.\n\n";
				break;
			}//case 1 end
		}//switch
	}//while
}




void Patient::registration()
{
	system("CLS");
	cout << "Fill in the following details to register:\n\n";
	string user, pass, string, temp, first, last , cnic, phone;
	char gen;
	cout << "Enter your first name: \n";
	getline(cin, first);
	cout << "Enter your last name: \n";
	getline(cin, last);

	bool repeat = false;
		do {
			if (repeat) cout << "\nThis username already exist, please try another username.\n\n";
			cout << "Username: ";
			getline(cin, user);
			repeat = true;
		} while (userChecker(user, 1) && repeat);
	cout << "Password: ";
	getline(cin, pass);
	while (checkpassword(pass) != 1)
	{
		cout << "The password should have atleast 8 characters and include uppercase, lowercase, and digits.\n";
		getline(cin, pass);
	}
	cout << "Re-enter your password: ";
	getline(cin, temp);
		while (temp != pass)
		{
			cout << "Your password do not match, please try again: \n";
			getline(cin, temp);
		}
		cout << "Enter your gender: (M/F): ";
		gen = _getch();
		cout << endl;
		cout << "Enter your phone number: ";
		getline(cin, phone);
	cout << "Enter your CNIC: ";
	getline(cin, cnic);
	while (cnic.length() != 13) {
		cout << "Your CNIC must be 13 digit long (without dashes)\n";
		getline(cin,cnic);
	}
		//check whether cnic is valid
	Patient obj(first, last, user, pass , cnic, phone, gen, 3500);
	balance = 3500;
	fstream fout;
	fout.open("patients.dat", fstream::app);
	fout.write((char*)&obj, sizeof(Patient));
	fout.seekg(0);
	fout.close();
	system("CLS");
	cout << "Successfully registered.\n";
}

//---------------------- end ----------------------//


// 
//---------------------- Doctor class functions ---------------------------//
Doctor::Doctor(): Child("","")
{
	strcpy_s(specialty, "");
	strcpy_s(email, "");
	strcpy_s(hospital, "");
	strcpy_s(city, "");
	ratings = 0;
	yearsOfExp = 0;
	videoCharges = 0;
	inpersonCharges = 0;
	ratings = 0;

}

Doctor::Doctor(string user, string pass): Child(user, pass)
{
	strcpy_s(specialty, "");
	strcpy_s(email, "");
	strcpy_s(hospital, "");
	strcpy_s(city, "");
	ratings = 0;
	yearsOfExp = 0;
	videoCharges = 0;
	inpersonCharges = 0;
	ratings = 0;
}

int Doctor::getVidCharges()
{
	return videoCharges;
}
int Doctor::getInPersonCharges()
{
	return inpersonCharges;
}

char* Doctor::getSpecialty()
{
	return specialty;
}
char* Doctor::getHospital()
{
	return hospital;
}
char* Doctor::getCity()
{
	return city;
}


bool Doctor::emailCheck(const std::string& email)
{
	const std::regex pattern
	("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	return std::regex_match(email, pattern);
}


void Doctor::setAvailability(AvailibilityHours& availability)
{
	availabilityHours = availability;
}

Doctor::Doctor(string first, string last, string user, string pass, string email_,string cnic, string specialty_, string city_, string hospital_, AvailibilityHours availability,
	int exp, int vid, int ip, int bal) : Child(first, last, cnic, user, pass, bal)
{
	strcpy_s(email, email_.c_str());
	strcpy_s(specialty, specialty_.c_str());
	strcpy_s(city, city_.c_str());
	strcpy_s(hospital, hospital_.c_str());
	availabilityHours = availability;
	slots = availabilityHours.difference();
	yearsOfExp = exp;
	videoCharges = vid;
	inpersonCharges = ip;
	ratings = 5;
}


bool Doctor::operator==(Doctor& obj)
{
	if (!strcmp(username, obj.username) && !strcmp(password, obj.password)) return true;
	else return false;
}

void Doctor::setAppointmentStatus(int )
{

}


void Doctor::displayData()
{
	cout << "\n------ Doctor " << firstName << " " << lastName << "'s Data: ------- \n";
	cout << "Email: " << email << endl;
	cout << "Availabiltiy:" << availabilityHours.getStartingTime() << " to " << availabilityHours.getFinishingTime() << endl;
	cout << "Specialty: " << specialty << endl;
	cout << "Hospital: " << hospital << endl;
	cout << "City: " << city << endl;
	cout << "Years of experience: " << yearsOfExp << endl;
	cout << "Video conference charges: " << videoCharges << endl;
	cout << "In person charges: " << inpersonCharges << endl;
	cout << "Ratings: " << ratings << endl;
	cout << "-----------------\n\n";
}


void Doctor::menu(bool& logout)
{
while (!logout)
{
	cout << "\n =========== Doctor's Menu ============\n";
	cout << "1. Show my Appointments\n";
	cout << "2. My Patients\n";
	cout << "3. Edit availability\n";
	cout << "4. Logout\n";
	cout << "=====================================\n\n";

	char input = _getch();

	switch (input)
	{
	case '1':
	{
		system("CLS");
		ifstream fin;
		fin.open("appointments.dat", ios::binary);
		if (!fin.is_open())
		{
			cout << "No appointments have been created yet.\n";
			fin.close();
		}
		else
		{
			char temp[50], first[50], last[50];
			fin.seekg(0);
			bool flag = true;
			while (!fin.eof())
			{
				fin.seekg(150, ios::cur);
				fin.read((char*)&first, 50);
				fin.read((char*)&last, 50);
				if (!strcmp(this->getFirst(), first) && !strcmp(this->getLast(), last))
				{
					flag = false;
					cout << "\n--------------- Appointment data --------------\n";
					int a = fin.tellg();
					fin.seekg(a - 250, ios::beg);
					Appointment obj;
					fin.read((char*)&temp, 50);
					cout << "Patients's first name: " << temp << endl;
					fin.read((char*)&temp, 50);
					cout << "Patients's last name: " << temp << endl;
					fin.read((char*)&temp, 50);
					cout << "Patient's CNIC: " << temp << endl;
					fin.read((char*)&temp, 50);
					cout << "Doctors's first name: " << temp << endl;
					fin.read((char*)&temp, 50);
					cout << "Doctors's last name: " << temp << endl;
					fin.read((char*)&obj, sizeof(Appointment));
					obj.displayAppointment();
					cout << "--------------------------------- \n";
				}
				fin.get();
				if (fin.eof())
				{
					break;
				}
				else {
					int b = fin.tellg();
					fin.seekg(b - 1);
				}
			}

			if (flag) cout << "No appointments found.\n";
			fin.close();
		}

		break;
	}// case 1 end

	case '2':
	{
		system("CLS");
		ifstream fin;
		fin.open("appointments.dat", ios::binary);
		if (!fin.is_open())
		{
			cout << "No patients have set up an appointment yet.\n";	
			fin.close();
		}
		else
		{
			char temp[50], first[50], last[50];
			fin.seekg(0);
			bool flag = true;
			while (!fin.eof())
			{
				fin.seekg(150, ios::cur);
				fin.read((char*)&first, 50);
				fin.read((char*)&last, 50);
				if (!strcmp(this->getFirst(), first) && !strcmp(this->getLast(), last))
				{
					flag = false;
					int a = fin.tellg();
					fin.seekg(a - 150, ios::beg);
					fin.read((char*)&temp, 50);
					ifstream fread;
					Patient obj;
					fread.open("patients.dat", ios::binary);
					while(!fread.eof()) {
													if (fread.read((char*)&obj, sizeof(Patient)))

													{
														if (!strcmp(obj.getCNIC(), temp))
														{
															obj.displayData();
														}
													}
													fread.get();
													if (fread.eof())
													{
														break;
													}
													else {
														int b = fread.tellg();
														fread.seekg(b - 1);
													}
					}
					fread.close();
							fin.get();
							if (fin.eof())
							{
								break;
							}
							else {
								int b = fin.tellg();
								fin.seekg(b - 1);
							}
				}

				if (flag) cout << "No appointments found.\n";
			}
			fin.close();
		}
			break;
	}//case 2 end

			case '3':
			{
				system("CLS");
				fstream f;
				Doctor temp;
				f.open("doctors.dat", ios::binary | ios::in | ios::out);
				bool flag = true;
				while (f.read((char*)&temp, sizeof(Doctor)))
				{
					if (!strcmp(temp.getUser(), this->getUser()))
					{
						int start, finish;
						cout << "Enter the new availability timings: \n";
						cout << "Starting time: ";
						cin >> start; cin.ignore();
						cout << "Finishing time: ";
						cin >> finish; cin.ignore();
						AvailibilityHours availability(start, finish);
						
						temp.setAvailability(availability);
						int a = f.tellg();
						f.seekg(a - sizeof(Doctor));
						f.write((char*)&temp, sizeof(Doctor));
						flag = false;
						system("CLS");
						cout << "\nYou have succesfully changed your availability timings.\n";
					}
				}
				f.close();
				if (flag) cout << "Your account was not found on the databases.\n";
				break;
			}

			case '4':
			{

				system("CLS");
				logout = 1;
				cout << "\nYou have successfully logged out.\n\n";
				break;
			}//case 2 end
		}//switch
	}//while
}


void Doctor::registration()
{
	system("CLS");
	cout << "Fill in the following details to register:\n\n";
	string user, pass, string, temp, first, last, email = "", cnic = "", hospital, city, specialty;
	int vidCharges, ipCharges, exp, start, finish;
	cout << "Enter you first name: ";
	getline(cin, first);
	cout << "Enter you last name: ";
	getline(cin, last);
	bool repeat = false;
	do {
		if (repeat) cout << "\nThis username already exist, please try another username.\n\n";
		cout << "Username: ";
		getline(cin, user);
		repeat = true;
	} while (userChecker(user, 2) && repeat);
	cout << "Password: ";
	getline(cin, pass);
	while (checkpassword(pass) != 1)
	{
		cout << "The password should have atleast 8 characters and include uppercase, lowercase, and digits.\n";
		getline(cin, pass);
	}
	cout << "Re-enter your password: ";
	getline(cin, temp);
	while (temp != pass)
	{
		cout << "Your password do not match, please try again: \n";
		getline(cin, temp);
	}
		cout << "Enter your email: ";
		getline(cin, email);
		while (emailCheck(email) != 1)
		{
			cout << "Your email was not correct, please try again: \n";
			getline(cin, email);
		}
		//Doctor obj(user, pass);
	

		cout << "Enter your CNIC: ";
		getline(cin, cnic);
		while (cnic.length() != 13) {
			cout << "Your CNIC must be 13 digit long (without dashes)\n";
			getline(cin, cnic);
		}
		//Doctor obj(user, pass);
		//checkkkkkkkkkkkkkkkkk
	
	cout << "Enter your specialty: ";
	getline(cin, specialty);
	cout << "Enter the name of the city you work at: ";
	getline(cin, city);
	cout << "Enter the name of the hospital you work at: ";
	getline(cin, hospital);


	cout << "\nEnter your availability hours: (24 hours scale) \n";
	cout << "Enter the starting time: ";
	cin >> start; cin.ignore();
	cout << "Enter the finishing time: ";
	cin >> finish; cin.ignore();
	AvailibilityHours availability(start,finish);


	cout << "Enter the number of years of experience you have: ";
	cin >> exp; cin.ignore();
	cout << "Enter the video conference charges: ";
	cin >> vidCharges; cin.ignore();
	cout << "Enter the in person charges: ";
	cin >> ipCharges; cin.ignore();
	Doctor obj(first, last, user, pass, email, cnic, specialty, city, hospital, availability, exp, vidCharges, ipCharges, 3500);
	fstream fout;
	fout.open("doctors.dat", fstream::app | fstream::out);
	fout.write((char*)&obj, sizeof(Doctor));
	fout.seekg(0);
	fout.close();
	system("CLS");
	cout << "Successfully registered.\n";
}


//---------------------- end ----------------------//




//---------------------- Admin class functions ---------------------------//
Admin::Admin() :User("test", "test") {}

Admin::Admin(string user, string pass) : User(user, pass)
{}


bool Admin::operator==(Admin& obj)
{
	if (!strcmp(username, obj.username) && !strcmp(password, obj.password)) return true;
	else return false;
}


void Admin::menu(bool& logout)
{
	
	while (!logout)
	{
		cout << "\n ============= Admin's Menu: =============\n";
		cout << "1. Show all appointments\n";
		cout << "2. Logout\n";
		cout << "=====================================\n\n";
		char input = _getch();
		switch (input)
		{

		case '1':
		{
			system("CLS");
			ifstream fin;
			fin.open("appointments.dat", ios::binary);
			char temp[50];
			fin.seekg(0);
			if (!fin.is_open())
			{
				cout << "No appointments have been created yet.\n";
				fin.close();
			}
			else
			while (!fin.eof())
			{
					cout << "\n------------------ \n";
					Appointment obj;
					fin.read((char*)&temp, 50);
					cout << "Patients's first name: " << temp << endl;
					fin.read((char*)&temp, 50);
					cout << "Patients's last name: " << temp << endl;
					fin.read((char*)&temp, 50);
					cout << "Patient's CNIC: " << temp << endl;
					fin.read((char*)&temp, 50);
					cout << "Doctors's first name: " << temp << endl;
					fin.read((char*)&temp, 50);
					cout << "Doctors's last name: " << temp << endl;
					fin.read((char*)&obj, sizeof(Appointment));
					obj.displayAppointment();
					cout << "------------------ \n";
				
				fin.get();
				if (fin.eof())
				{
					break;
				}
				else {
					int b = fin.tellg();
					fin.seekg(b - 1);
				}

			}
			fin.close();
			
			break;
		}// case 1 end
		case '2':
		{
			logout = 1;
			system("CLS");

			cout << "\nYou have successfully logged out.\n\n";
			break;
		}//case 1 end
		}//switch
	}//while
}


void Admin::registration()
{
	system("CLS");
	cout << "Fill in the following details to register:\n\n";
	string user, pass,temp;
	bool repeat = false;
	do {
		if (repeat) cout << "\nThis username already exist, please try another username.\n\n";
		cout << "Username: ";
		getline(cin, user);
		repeat = true;
	} while (userChecker(user,0) && repeat);
	cout << "Password: ";
	getline(cin, pass);
	while (checkpassword(pass) != 1)
	{
		cout << "The password should be atleast 8 characters long and include uppercase, lowercase, and digits.\n";
		getline(cin, pass);
	}
	cout << "Re-enter your password: ";
	getline(cin, temp);
	while (temp != pass)
	{
		cout << "Your password do not match, please try again: \n";
		getline(cin, temp);
	}
	Admin obj(user, pass);
	fstream fout;
	fout.open("admins.dat", fstream::app | fstream::out);
	fout.write((char*)&obj, sizeof(Admin));
	fout.seekg(0);
	fout.close();
	system("CLS");
	cout << "\nSuccessfully registered.\n";
}
//---------------------- end ----------------------//


//---------------------- Child class functions ---------------------------//
Child::Child()
{
	strcpy_s(firstName, "");
	strcpy_s(lastName, "");
	strcpy_s(CNIC, "");

}

Child::Child(string user, string pass): User(user,pass)
{}

Child::Child(string first, string last, string cnic, string user, string pass, int bal): User(user,pass)
{
	strcpy_s(firstName, first.c_str());
	strcpy_s(lastName, last.c_str());
	strcpy_s(CNIC, cnic.c_str());
	balance = bal;
}


int& Child::getBalance()
{
	return balance;
}




//---------------------- end ----------------------//


//---------------------- User class functions ---------------------------//

User::User()
{
	strcpy_s(username, "");
	strcpy_s(password, "");
	//point others to null
}

User::User(string user, string pass)
{
	strcpy_s(username, user.c_str());
	strcpy_s(password, pass.c_str());
}



bool User::checkpassword(string& password)
{
	int n = password.length();
	if (n < 8) return false;
	bool hasLower = false, hasUpper = false, hasDigit = false;

	for (int i = 0; i < n; i++) {
		if (islower(password[i]))
			hasLower = true;
		if (isupper(password[i]))
			hasUpper = true;
		if (isdigit(password[i]))
			hasDigit = true;
	}
	if (hasLower && hasUpper && hasDigit) return true;
	else return false;
}


bool User::userChecker(string user, int usertype)
{
	if (usertype == 0)
	{
		Admin temp;
		ifstream fin;
		fin.open("admins.dat");
		if (fin.is_open())
		{
			while (fin.read((char*)&temp, sizeof(Admin)))
			{

				if (!strcmp(temp.getUser(), user.c_str()))
				{
					return true;
				}
			}
		}
		fin.seekg(0);
		fin.close();
	}
	if (usertype == 1)
	{
		Patient temp;
		ifstream fin;
		fin.open("patients.dat");
		if (fin.is_open())
		{
			while (fin.read((char*)&temp, sizeof(Patient)))
			{

				if (!strcmp(temp.getUser(), user.c_str()))
				{
					return true;
				}
			}
		}
		fin.seekg(0);
		fin.close();
	}
	if (usertype == 2)
	{
		Doctor temp;
		ifstream fin;
		fin.open("doctors.dat");
		if (fin.is_open())
		{
			while (fin.read((char*)&temp, sizeof(Doctor)))
			{

				if (!strcmp(temp.getUser(), user.c_str()))
				{
					return true;
				}
			}
		}
		fin.seekg(0);
		fin.close();
	}
	return false;
}


void User::login(int type,bool &logout)
{
	cout << "Enter your credentials:\n\n";
	cout << "Username: ";
	string user, pass;
	getline(cin, user);
	cout << "Password: ";
	getline(cin, pass);
	cout << endl;
	if (type == 0)
	{
		Admin obj(user, pass),temp;
		ifstream fin;
		fin.open("admins.dat");
		if (fin.is_open())
		{
			while (fin.read((char*)&temp, sizeof(Admin)))
			{

				if (temp == obj)
				{
					system("CLS");
					cout << "You have successfully logged in as admin.\n";
					temp.menu(logout);
					return;
				}

			}
			system("CLS");
			cout << "No such user found.\n\n";
			cout << "1. Try again.\n2. Go back go Login page\n3. Go back to homepage\n\n";
			char condition = _getch();
			
			if (condition == '1')
				login(type, logout);
			else if (condition == '2')
			{
				return;
			}
			else if(condition == '3')
			{
				logout = 1;
				return;
			}

		}
		else cout << "No admin account has been created yet.\n";
		logout = 1;
		fin.seekg(0);
		fin.close();
	}

	else if (type == 1)
	{
		Patient obj(user, pass), temp;
		ifstream fin;
		fin.open("patients.dat");
		if (fin.is_open())
		{
			while (fin.read((char*)&temp, sizeof(Patient)))
			{
			//	temp.displayData();
				if (temp == obj)
				{
					system("CLS");
					cout << "You have successfully logged in as Patient.\n";
					temp.menu(logout);
					return;
				}

			}
			system("CLS");
			cout << "No such user found.\n\n";
			cout << "1. Try again.\n2. Go back go Login page\n3. Go back to homepage\n\n";
			char condition = _getch();

			if (condition == '1')
				login(type, logout);
			else if (condition == '2')
			{
				return;
			}
			else if (condition == '3')
			{
				logout = 1;
				return;
			}
		}
		else cout << "No patient account has been created yet.\n";
		logout = 1;
		fin.seekg(0);
		fin.close();
	}

	else if (type == 2)
	{
		Doctor obj(user, pass), temp;
		ifstream fin;
		fin.open("doctors.dat");
		if (fin.is_open())
		{
			while (fin.read((char*)&temp, sizeof(Doctor)))
			{
			//	temp.displayData();
				if (temp == obj)
				{
					system("CLS");
					cout << "You have successfully logged in as Doctor.\n";
					temp.menu(logout);
					return;
				}

			}
			system("CLS");
			cout << "No such user found.\n\n";
			cout << "1. Try again.\n2. Go back go Login page\n3. Go back to homepage\n\n";
			char condition = _getch();

			if (condition == '1')
				login(type, logout);
			else if (condition == '2')
			{
				return;
			}
			else if (condition == '3')
			{
				logout = 1;
				return;
			}
		}
		else cout << "No doctor account has been created yet.\n";
		logout = 1;
		fin.seekg(0);
		fin.close();
	}

	
}

//---------------------- end ----------------------//

//---------------------- Browse class functions ---------------------------//
void Browse::menu(bool& logout)
{
	cout << "\nAs an unregistered member, you can only access the following options:\n";
	cout << "1. Show available doctors\n";
	cout << "2. Search Doctor\n";
	cout << "3. Go back to home page.\n";
	char input = _getch();
	switch (input)
	{
		case '1':
			{
				system("CLS");
				ifstream fin;
				Doctor obj;
				fin.open("doctors.dat", ios::binary);
				if (fin.is_open())
				{
					while (fin.read((char*)&obj, sizeof(Doctor)))
					{
						obj.displayData();
					}
					fin.close();
				}
				else
				{
					cout << "No doctors have registered yet.\n";
					fin.close();
				}
				break;
			}
		case '2':
			{
				system("CLS");
				this->searchDoctor();
				break;
			}
		case '3':
			{
				system("CLS");
				logout = 1;
				break;
			}
	}
}


void Browse::searchDoctor()
{
	cout << "Search doctor via:\n\n";
	cout << "1. Specialty\n2. Hospital\n3. City\n";
	char input; string specialty, hospital, city;
	input = _getch();
	if (input == '1')
	{
		cout << "Enter the doctor's specialty: \n";
		getline(cin, specialty);
	}
	else if (input == '2')
	{
		cout << "Enter the doctor's Hospital name: \n";
		getline(cin, hospital);
	}
	else if (input == '3')
	{
		cout << "Enter the doctor's city's name: \n";
		getline(cin, city);
	}
	ifstream fin;
	Doctor obj;
	fin.open("doctors.dat");
	bool flag = true;
	while (fin.read((char*)&obj, sizeof(Doctor)))
	{
		if (input == 1 && !(strcmp(obj.getSpecialty(), specialty.c_str())))
		{
			obj.displayData();
			flag = false;
		}
		else if (input == 2 && !(strcmp(obj.getHospital(), hospital.c_str())))
		{
			obj.displayData();
			flag = false;
		}
		else if (input == 3 && !(strcmp(obj.getCity(), city.c_str())))
		{
			obj.displayData();
			flag = false;
		}
	}
	system("CLS");
	if (flag) cout << "No such doctor found.\n";

}

//---------------------- end ----------------------//



//---------------------- Oladoc class functions ---------------------------//
Oladoc::Oladoc()
{
	cout << " ----------- Welcome to Oladoc -----------\n\n";
}

Admin*& Oladoc::getAdmin()
{
	return admin;
}
Patient*& Oladoc::getPatient()
{
	return patient;
}
Doctor*& Oladoc::getDoctor()
{
	return doctor;
}
Browse*& Oladoc::getBrowse()
{
	return browse;
}
//---------------------- end ----------------------//


int main()
{
	Oladoc obj;
	//bool checkOladoc = true;
	while (1)
	{
		cout << "\n======= Home Page: =======\n";
		cout << "1. Login\n";
		cout << "2. Register\n";
		cout << "3. Browse\n";
		cout << "4. Exit\n";
		cout << "============================ \n";
		/*static int input;
		cin >> input;*/
		char ch = _getch();
		system("CLS");
		bool logout = 0;
		while (!logout)
		{

			switch (ch)
			{
			case '1':
			{
				cout << "\nPlease enter your user type:\n\n";
				cout << "0. Admin\n";
				cout << "1. Patient\n";
				cout << "2. Doctor\n";

				char type = _getch();
				system("CLS");
				User obj;
				obj.login(type-48,logout);
				

			break;
			}//case 1 end

			case '2':
			{
				cout << "\nPlease enter your user type:\n\n";
				cout << "0. Admin\n";
				cout << "1. Patient\n";
				cout << "2. Doctor\n";
				char type = _getch();

				if (type == '0')
				{
					obj.getAdmin() = new Admin;
					obj.getAdmin()->registration();
					obj.getAdmin()->menu(logout);

				}
				else if (type == '1')
				{
					obj.getPatient() = new Patient;
					obj.getPatient()->registration();
					obj.getPatient()->menu(logout);


				}
				else if (type == '2')
				{
					obj.getDoctor() = new Doctor;
					obj.getDoctor()->registration();
					obj.getDoctor()->menu(logout);
				}
				
			break;
			}//case2 end

			case '3':
				{
					obj.getBrowse() = new Browse;
					obj.getBrowse()->menu(logout);
					break;
				}
			case '4':
				{
					exit(0);
				}


			} //switch
		}//while
	}// main while

}// main