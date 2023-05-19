#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <regex>
#include <stdio.h>
#include<conio.h>

class Patient;
class Doctor;


using namespace std;

class Date
{
	int day;
	int month;
	int year;
public:
	Date();
	Date(int, int, int);
};

class Time
{
	int hours;
	int minutes;
public:
	Time();
	Time(int, int);
};

class Payment
{
protected:
	bool paidStatus = false;
	int paidAmount;
public:
};

class BankTranfer:  public Payment
{
public:
	virtual void pay(int) {}
	int getPaidAmount();

};

class eTransaction:  public Payment
{
public:
	virtual void pay(int){}
	int getPaidAmount();

};

class Jazzcash: public eTransaction
{
public:
	virtual void pay(int);

};

class EasyPaisa: public eTransaction
{
public:
	virtual void pay(int);

};

class PayPak: public BankTranfer
{
public:
	virtual void pay(int);

};
class UnionPay : public BankTranfer
{
public:
	virtual void pay(int);

};


class Appointment
{
//	Date date;
	//Time time;
	bool appointmentMode;//false - online, true - inperson
	int status; // (0-pending, 1- accepted, 2-rejected)
	Payment payment;

public:
	void bookAppointment(Patient&);
	void saveAppointment(Doctor&, Patient&, Appointment&);
	void displayAppointment();

};

class User
{
protected:
	char username[50], password[50];
public:
	User();
	User(string, string);
	void login(int,bool&);
	//void editProfile();
	bool userChecker(string,int);
	bool checkpassword(string&);
	//~User();
	const char* getUser()
	{
		return username;
	}
	const char* getPass()
	{
		return password;
	}



};

class Child : public User
{
protected:
	char CNIC[50], firstName[50], lastName[50];
	int balance;
public:
	Child();
	Child(string, string);
	Child(string, string, string, string, string,int);
	int& getBalance();
	const char* getFirst()
	{
		return firstName;
	}
	const char* getLast()
	{
		return lastName;
	}
	const char* getCNIC()
	{
		return CNIC;
	}
};
//

class AvailibilityHours
{
	int startingTime;
	int finishingTime;
public:
	AvailibilityHours();
	AvailibilityHours(int, int);
	int getStartingTime()
	{
		return startingTime;
	}
	int getFinishingTime()
	{
		return finishingTime;
	}
	int difference()
	{
		return finishingTime - startingTime;
	}
};

class Doctor : public Child
{
protected:
	//Appointment* appointment;
	char specialty[50], email[50], hospital[50], city[50];
	AvailibilityHours availabilityHours;
	int ratings, yearsOfExp, videoCharges, inpersonCharges, slots;
	//availability hours
	//keep updating the size function SIZEEEEEE
public:
	Doctor();
	Doctor(string,string);
	Doctor(string, string, string,string, string, string, string, string, string, AvailibilityHours, int,int, int,int);
	void registration();
	void menu(bool&);
	bool operator==(Doctor&);
	void displayData();
	char* getSpecialty();
	char* getHospital();
	char* getCity();
	int getVidCharges();
	int getInPersonCharges();
	void setAppointmentStatus(int);
	bool emailCheck(const std::string&);
	void setAvailability(AvailibilityHours&);

};



class Patient : public Child
{
protected:
	char phone[50];
	char gender;// M for Male, F forfemale
	Appointment appointment;
public:
	Patient();
	Patient(string, string);
	Patient(string,string,string,string,string,string, char,int);
	void registration();
	void menu(bool&);
	bool operator==(Patient&);
	void displayData();
	void setPass(string&);
	void viewProfile();
	void searchDoctor();


};

class Admin :  public User
{
protected:
	Appointment* appointment;
public:
	Admin();
	Admin(string, string);
	void registration();
	void menu(bool&);
	bool operator==(Admin&);
	void setStatus(int);
	/*void display()
	{
		cout << "User: " << getUser() << endl;
		cout << "pass: " << getPass() << endl;
	}*/

};


class Browse
{

public:
	void menu(bool&);
	void searchDoctor();
};

class Oladoc
{
	Admin* admin;
	Patient* patient;
	Doctor* doctor;
	Browse* browse;
public:
	Oladoc();
	Admin*& getAdmin();
	Patient*& getPatient();
	Doctor*& getDoctor();
	Browse*& getBrowse();
	//~Oladoc();

};