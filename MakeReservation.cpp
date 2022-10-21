// MakeReservation.cpp
// Member-function definitions for class MakeReservation.
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
#include "MakeReservation.h" // MakeReservation class definition

// extern bool legalID( const string &id );
extern void computeCurrentDate(Date &currentDate);
extern bool leapYear(unsigned int year);

// MakeReservation constructor initializes base-class data members
MakeReservation::MakeReservation(ReservationDatabase &theReservationDatabase,
	AvailableRoomsDatabase &theAvailableRoomsDatabase)
	: reservationDatabase(theReservationDatabase),
	availableRoomsDatabase(theAvailableRoomsDatabase)
{
} // end MakeReservation constructor

  // performs transaction
void MakeReservation::execute()
{
	Date currnet, available[6];
	Date in, out;//
	Reservation NewData;
	unsigned int YMcode = -1, first = -1, last = -1;
	computeCurrentDate(currnet);
	computeAvailableMonths(currnet, available);
	inputCheckInDates(in, currnet, available, YMcode, first, last);
	inputCheckOutDates(out, in, available, YMcode, first, last);//inDate,outDate

	availableRoomsDatabase.displayAvailableRooms(in, out);
	cout << "\nSelect Room Type¡G\n"
		<< "1. Superior Room\n"
		<< "2. Deluxe Room\n"
		<< "3. Deluxe Twin Room\n"
		<< "4. Superior Suite\n"
		<< "5. Deluxe Suite\n";
	int choice = -1, number = -1;//
	while (choice < 1 || choice>5)
	{
		cout << "?";
		cin >> choice;
	}
	cout << endl;
	int canUseNumber = availableRoomsDatabase.findMinNumRooms(choice, in, out);
	while (number <= 0 || number>canUseNumber)
	{
		if (canUseNumber == 0)
			return;
		cout << "Number of rooms(" << canUseNumber << " rooms available):";
		cin >> number;
	}
	cout << endl;
	string name, id, mobile;
	cout << "\nID Number¡G";
	cin >> id;
	cout << "\nName¡G";
	cin >> name;
	cout << "\nMobile Phone¡G";
	cin >> mobile;
	NewData.setReservation(choice, number, in, out, id, name, mobile);

	string roomName[6] = { "","Superior Room","Deluxe Room","Deluxe Twin Room","Superior Suite","Deluxe Suite" };
	unsigned int roomRate[6] = { 0,5390,6270,6270,6820,8470 };
	cout << "\n\n" << setw(8) << "Name" << setw(8) << "Fare" << setw(10) << "Mobile" << setw(14) << "Room type"
		<< setw(18) << "Number of rooms" << setw(16) << "Check in date" << setw(17) << "Check out date" << endl;
	NewData.displayReservation();
	availableRoomsDatabase.decreaseAvailableRooms(choice, number, in, out);
	reservationDatabase.pushBack(NewData);

	cout << "\nReservation successfully!\n\n";
}

void MakeReservation::computeAvailableMonths(Date currentDate, Date availableMonths[])
{
	int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	int Y = currentDate.getYear(), M = currentDate.getMonth() + 1;
	availableMonths[0] = currentDate;
	for (int i = 1; i < 6; i++, M++)
	{
		if (M > 12)
		{
			M -= 12;
			Y++;
		}
		availableMonths[i].setYear(Y);
		availableMonths[i].setMonth(M);
		availableMonths[i].setDay(1);
	}
}

void MakeReservation::inputCheckInDates(Date &checkInDate, Date currentDate, Date availableMonths[],
	unsigned int &checkInYMCode, unsigned int &firstDay, unsigned int &lastDay)
{
	int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

	cout << "\nPlease Input Check In Date\n\nMonth¡G\n";
	for (int i = 0; i < 6; i++)
		cout << i + 1 << ". " << availableMonths[i].getYear() << "-" << availableMonths[i].getMonth() << endl;
	while (checkInYMCode < 0 || checkInYMCode>6)
	{
		cout << "?";
		cin >> checkInYMCode;
	}
	checkInYMCode--;
	checkInDate.setYear(availableMonths[checkInYMCode].getYear());
	checkInDate.setMonth(availableMonths[checkInYMCode].getMonth());
	while (firstDay<availableMonths[checkInYMCode].getDay() || firstDay>days[availableMonths[checkInYMCode].getMonth()])
	{
		cout << endl << "Day (" << availableMonths[checkInYMCode].getDay()
			<< " ~ " << days[availableMonths[checkInYMCode].getMonth()] << "): ";
		cin >> firstDay;
		if (days[availableMonths[5].getMonth()] == firstDay&&checkInYMCode == 5)
			firstDay = -1;
	}
	checkInDate.setDay(firstDay);
}

void MakeReservation::inputCheckOutDates(Date &checkOutDate, Date checkInDate, Date availableMonths[],
	unsigned int checkInYMCode, unsigned int firstDay, unsigned int lastDay)
{
	int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

	cout << "\nPlease Input Check Out Date\n\nMonth¡G\n";
	int low = 0;
	for (int i = 0; i < 6; i++)
	{
		if (days[availableMonths[checkInYMCode].getMonth()] == firstDay
			&&availableMonths[i].getMonth() == checkInDate.getMonth())
		{
			low++;
			continue;
		}
		else if (checkInDate.getMonth()>availableMonths[i].getMonth())
		{
			low++;
			continue;
		}
		cout << i + 1 << ". " << availableMonths[i].getYear() << "-" << availableMonths[i].getMonth() << endl;
	}
	int outYMcode = -1;
	while (outYMcode < 0 || outYMcode>6)
	{
		cout << "?";
		cin >> outYMcode;
		if (outYMcode <= low)
			outYMcode = -1;
	}
	outYMcode--;
	checkOutDate.setYear(availableMonths[outYMcode].getYear());
	checkOutDate.setMonth(availableMonths[outYMcode].getMonth());
	while (lastDay<availableMonths[outYMcode].getDay() || lastDay>days[availableMonths[outYMcode].getMonth()])
	{
		if (availableMonths[outYMcode].getMonth() == checkInDate.getMonth())
		{
			cout << endl << "Day (" << checkInDate.getDay() + 1
				<< " ~ " << days[availableMonths[outYMcode].getMonth()] << "): ";
			cin >> lastDay;
			if (lastDay <= checkInDate.getDay())
				lastDay = -1;
		}
		else
		{
			cout << endl << "Day (" << availableMonths[outYMcode].getDay()
				<< " ~ " << days[availableMonths[outYMcode].getMonth()] << "): ";
			cin >> lastDay;
		}
	}
	checkOutDate.setDay(lastDay);
}