// ViewReservation.h
// ViewReservation class definition.
#ifndef VIEW_CANCEL_RESERVATION_H
#define VIEW_CANCEL_RESERVATION_H

#include "ReservationDatabase.h" // ReservationDatabase class definition
#include "AvailableRoomsDatabase.h" // AvailableRoomsDatabase class definition

class ViewReservation
{
public:
   ViewReservation( ReservationDatabase &, AvailableRoomsDatabase & );
   void execute();
private:
//   bool userAuthenticated; // whether user is authenticated
//   string currentIDNumber; // current user's ID number
   ReservationDatabase &reservationDatabase;
   AvailableRoomsDatabase &availableRoomsDatabase;
//   void authenticateUser();
//   bool legalID( string ); // whether an ID number is legal
}; // end class ViewReservation

#endif // VIEW_CANCEL_RESERVATION_H