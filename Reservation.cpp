// Reservation.cpp
// Member-function definitions for class Reservation.
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;
#include "Reservation.h" // Reservation class definition

void Reservation::setReservation(unsigned int inputRoomType, unsigned int inputNumRooms,
	Date inputCheckInDate, Date inputCheckOutDate,
	string inputIDNumber, string inputName, string inputMobile)
{
	roomType = inputRoomType;
	numRooms = inputNumRooms;
	checkInDate = inputCheckInDate;
	checkOutDate = inputCheckOutDate;
	setIDNumber(inputIDNumber);
	setName(inputName);
	setMobile(inputMobile);
}

void Reservation::setIDNumber(string theIDNumber)
{
	strcpy_s(IDNumber, 12, theIDNumber.c_str());
}

void Reservation::setName(string theName)
{
	strcpy_s(name, 12, theName.c_str());
}

void Reservation::setMobile(string theMobile)
{
	strcpy_s(mobile, 12, theMobile.c_str());
}

string Reservation::getIDNumber()
{
	return IDNumber;
}

unsigned int Reservation::getRoomType()
{
	return roomType;
}

unsigned int Reservation::getNumRooms()
{
	return numRooms;
}

Date Reservation::getCheckInDate()
{
	return checkInDate;
}

Date Reservation::getCheckOutDate()
{
	return checkOutDate;
}

bool Reservation::equalID(string id1, string id2)
{
	if (id1.size() == id2.size())
		for (int i = 0; i < id1.size(); i++)
			if (id1[i] != id2[i])
				return false;
			else continue;
	else
		return false;
}

void Reservation::displayReservation()
{
	int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	int numDays = 0;
	if (checkInDate.getMonth() != checkOutDate.getMonth())//六個月不會重複的月
	{
		numDays += days[checkInDate.getMonth()] - checkInDate.getDay();
		for (int i = checkInDate.getMonth() + 1; i != checkOutDate.getMonth(); i++)
		{
			if (i > 12)
				i -= 12;
			numDays += days[i];
		}
		numDays += checkOutDate.getDay();
	}
	else
		numDays += checkOutDate.getDay() - checkInDate.getDay();

	string roomName[6] = { "","Superior Room","Deluxe Room","Deluxe Twin Room","Superior Suite","Deluxe Suite" };
	unsigned int roomRate[6] = { 0,5390,6270,6270,6820,8470 };
	cout << setw(8) << name << setw(8) << roomRate[roomType] * numRooms*numDays
		<< setw(10) << mobile << setw(14) << roomName[roomType]
		<< setw(18) << numRooms << setw(10) << checkInDate.getYear()
		<< "-" << setw(2) << checkInDate.getMonth() << "-" << setw(2) << checkInDate.getDay()
		<< setw(11) << checkOutDate.getYear()
		<< "-" << setw(2) << checkOutDate.getMonth()
		<< "-" << setw(2) << checkOutDate.getDay() << endl;
}