// ReservationDatabase.cpp
// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace::std;
#include "ReservationDatabase.h" // ReservationDatabase class definition

void ReservationDatabase::loadFromReservations()
{
	ifstream inReservation("Reservations.dat", ios::in | ios::binary);
	Reservation buffer;
	if (!inReservation)
		cout << "reservation error!!(first open no data)\n";
	else
		while (inReservation.read((char*)&buffer, sizeof(buffer)))
			pushBack(buffer);
	inReservation.close();
}

void ReservationDatabase::pushBack(Reservation newReservation)
{
	reservations.push_back(newReservation);
}

unsigned int ReservationDatabase::numReservations(string IDNumber)
{
	int output = 0;
	for (int i = 0; i < reservations.size(); i++)
		if (reservations[i].equalID(reservations[i].getIDNumber(), IDNumber))
			output++;
	return output;
}

void ReservationDatabase::displayReservations(string IDNumber)
{
	cout << "\n\n" << setw(8) << "Name" << setw(8) << "Fare" << setw(10) << "Mobile" << setw(14) << "Room type"
		<< setw(18) << "Number of rooms" << setw(16) << "Check in date" << setw(17) << "Check out date" << endl;
	for (int i = 0; i < reservations.size(); i++)
		if (reservations[i].equalID(reservations[i].getIDNumber(), IDNumber))
			reservations[i].displayReservation();

}

void ReservationDatabase::saveToReservationFile()
{
	ofstream outReservation("Reservations.dat", ios::out | ios::binary);
	for (int i = 0; i < reservations.size(); i++)
		outReservation.write((char*)&reservations[i], sizeof(Reservation));
	outReservation.close();
}