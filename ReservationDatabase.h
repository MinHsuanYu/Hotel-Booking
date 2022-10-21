// ReservationDatabase.h
// ReservationDatabase class definition. Represents reservation database.
#ifndef RESERVATION_DATABASE_H
#define RESERVATION_DATABASE_H

#include <vector>
#include "Reservation.h" // Reservation class definition

class ReservationDatabase
{
public:
   void loadFromReservations();
   unsigned int numReservations( string IDNumber );
   void displayReservations( string IDNumber );
//   unsigned int size();
   void pushBack( Reservation );
//   vector< Reservation >::iterator begin();
//   vector< Reservation >::iterator end();
//   void erase( vector< Reservation >::iterator );
   void saveToReservationFile();
private:
   vector< Reservation > reservations; // vector of the reservations
   // Reservation reservations[ 1000 ]; // array of the reservations
}; // end class ReservationDatabase

#endif // RESERVATION_DATABASE_H