// AvailableRoomsDatabase.cpp
// Member-function definitions for class AvailableRoomsDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "AvailableRoomsDatabase.h" // AvailableRoomsDatabase class definition

extern void computeCurrentDate(Date &currentDate);
extern bool leapYear(unsigned int year);

void AvailableRoomsDatabase::loadAvailableRooms()
{
	ifstream inAvailable("Available Rooms.dat", ios::in | ios::binary);
	AvailableRooms buffer;
	if (!inAvailable)
		cout << "Availble error!!(first open no data)\n";
	else
		while (inAvailable.read((char*)&buffer, sizeof(buffer)))
			availableRooms.push_back(buffer);
	if (availableRooms.size() == 0)
		initilizeAvailableRooms();
	adjustAvailableRooms();
	inAvailable.close();
}

void AvailableRoomsDatabase::initilizeAvailableRooms()
{
	Date current;
	computeCurrentDate(current);
	int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	int M = current.getMonth();
	int Y = current.getYear();
	for (int i = current.getDay(); i <= days[M]; i++)
	{
		AvailableRooms buffer;
		buffer.setDate(Y, M, i);
		buffer.initilizeAvailableRooms();
		availableRooms.push_back(buffer);
	}
	M++;
	for (int i = 0; i < 5; i++, M++)
	{
		if (M > 12)
		{
			M -= 12;
			Y++;
		}
		for (int i = 0; i <= days[M]; i++)
		{
			AvailableRooms buffer;
			buffer.setDate(Y, M, i);
			buffer.initilizeAvailableRooms();
			availableRooms.push_back(buffer);
		}
	}
}

void AvailableRoomsDatabase::adjustAvailableRooms()
{
	Date current;
	computeCurrentDate(current);
	int i = 0;
	int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

	while (availableRooms[i].getDate() < current)
		i++;

	Date Last = availableRooms[availableRooms.size() - 1].getDate();
	int D = Last.getDay();
	int M = Last.getMonth();
	int Y = Last.getYear();
	for (int j = 0; j < i; j++, D++)
	{
		if (D > days[M])
		{
			D -= days[M];
			M++;
			if (M > 12)
			{
				M -= 12;
				Y++;
			}
		}
		AvailableRooms buffer;
		buffer.initilizeAvailableRooms();
		buffer.setDate(Y, M, D);
		availableRooms.push_back(buffer);
	}
}

void AvailableRoomsDatabase::displayAvailableRooms(const Date &checkInDate, const Date &checkOutDate)
{
	cout << setw(11) << "Date " << setw(14) << "Superior Room" << setw(18) << "Deluxe Room" << setw(19)
		<< "Deluxe Twin Room" << setw(17) << "Superior Suite" << setw(15) << "Deluxe Suite" << endl;
	vector< AvailableRooms >::iterator in, out;
	findIterators(checkInDate, checkOutDate, in, out);
	for (; in != out; in++)
		cout << in->getDate().getYear() << "-" << setw(2) << in->getDate().getMonth()
		<< "-" << setw(2) << in->getDate().getDay()
		<< setw(14) << in->getAvailableRooms()[1] << setw(18) << in->getAvailableRooms()[2]
		<< setw(19) << in->getAvailableRooms()[3] << setw(17) << in->getAvailableRooms()[4]
		<< setw(15) << in->getAvailableRooms()[5] << endl;
}

unsigned int AvailableRoomsDatabase::findMinNumRooms(unsigned int roomType,
	const Date &checkInDate, const Date &checkOutDate)
{
	vector< AvailableRooms >::iterator in, out;
	findIterators(checkInDate, checkOutDate, in, out);
	unsigned int output = 10;
	for (; in != out; in++)
		if (in->getAvailableRooms()[roomType] < output)
			output = in->getAvailableRooms()[roomType];
	return output;
}

void AvailableRoomsDatabase::decreaseAvailableRooms(unsigned int roomType, unsigned int numRooms,
	const Date &checkInDate, const Date &checkOutDate)
{
	vector< AvailableRooms >::iterator in, out;
	findIterators(checkInDate, checkOutDate, in, out);
	for (; in != out; in++)
		in->decreaseAvailableRooms(roomType, numRooms);
}

void AvailableRoomsDatabase::saveAvailableRooms()
{
	ofstream outRooms("Available Rooms.dat", ios::out | ios::binary);
	for (int i = 0; i < availableRooms.size(); i++)
		outRooms.write((char*)&availableRooms[i], sizeof(AvailableRooms));
	outRooms.close();
}

void AvailableRoomsDatabase::findIterators(const Date &checkInDate, const Date &checkOutDate,
	vector< AvailableRooms >::iterator &checkInIterator,
	vector< AvailableRooms >::iterator &checkOutIterator)
{
	vector< AvailableRooms >::iterator it = availableRooms.begin();
	for (; it != availableRooms.end(); it++)
		if (it->getDate() == checkInDate)
		{
			checkInIterator = it;
			break;
		}
	for (; it != availableRooms.end(); it++)
		if (it->getDate() == checkOutDate)
		{
			checkOutIterator = it;
			break;
		}
}