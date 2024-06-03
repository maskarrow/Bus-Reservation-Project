#include <conio.h>
#include <cstdio>
#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;

static int busCount = 0;

class Bus {
    char busNumber[5], driverName[10], arrivalTime[5], departureTime[5], startPoint[10], endPoint[10], seats[8][4][10];

public:
    void installBus();
    void reserveSeat();
    void initializeSeats();
    void showBusDetails();
    void listAvailableBuses();
    void displaySeatPositions(int i);
} buses[10];

void printLine(char ch) {
    for (int i = 80; i > 0; i--)
        cout << ch;
}

void Bus::installBus() {
    cout << "Enter bus number: ";
    cin >> buses[busCount].busNumber;

    cout << "\nEnter driver's name: ";
    cin >> buses[busCount].driverName;

    cout << "\nArrival time: ";
    cin >> buses[busCount].arrivalTime;

    cout << "\nDeparture time: ";
    cin >> buses[busCount].departureTime;

    cout << "\nFrom: ";
    cin >> buses[busCount].startPoint;

    cout << "\nTo: ";
    cin >> buses[busCount].endPoint;

    buses[busCount].initializeSeats();
    busCount++;
}

void Bus::reserveSeat() {
    int seatNumber;
    char busNo[5];

top:
    cout << "Enter bus number: ";
    cin >> busNo;

    int n;
    for (n = 0; n <= busCount; n++) {
        if (strcmp(buses[n].busNumber, busNo) == 0)
            break;
    }

    if (n > busCount) {
        cout << "Enter correct bus number.\n";
        goto top;
    }

    while (n <= busCount) {
        cout << "\nEnter seat number: ";
        cin >> seatNumber;

        if (seatNumber > 32) {
            cout << "\nThere are only 32 seats available in this bus.";
        } else {
            if (strcmp(buses[n].seats[seatNumber / 4][(seatNumber % 4) - 1], "Empty") == 0) {
                cout << "Enter passenger's name: ";
                cin >> buses[n].seats[seatNumber / 4][(seatNumber % 4) - 1];
                break;
            } else {
                cout << "The seat number is already reserved.\n";
            }
        }
    }
}

void Bus::initializeSeats() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            strcpy(buses[busCount].seats[i][j], "Empty");
        }
    }
}

void Bus::showBusDetails() {
    int n;
    char busNo[5];

    cout << "Enter bus number: ";
    cin >> busNo;

    for (n = 0; n <= busCount; n++) {
        if (strcmp(buses[n].busNumber, busNo) == 0)
            break;
    }

    if (n > busCount) {
        cout << "Enter correct bus number.\n";
        return;
    }

    while (n <= busCount) {
        printLine('*');
        cout << "Bus number: \t" << buses[n].busNumber
             << "\nDriver: \t" << buses[n].driverName << "\t\tArrival time: \t"
             << buses[n].arrivalTime << "\tDeparture time: " << buses[n].departureTime
             << "\nFrom: \t\t" << buses[n].startPoint << "\t\tTo: \t\t" << buses[n].endPoint << "\n";
        printLine('*');
        buses[0].displaySeatPositions(n);

        int seatCounter = 1;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 4; j++) {
                seatCounter++;
                if (strcmp(buses[n].seats[i][j], "Empty") != 0)
                    cout << "\nThe seat number " << (seatCounter - 1) << " is reserved for " << buses[n].seats[i][j] << ".";
            }
        }
        break;
    }
}

void Bus::displaySeatPositions(int busIndex) {
    int seatNumber = 0, emptySeatCount = 0;

    for (int i = 0; i < 8; i++) {
        cout << "\n";
        for (int j = 0; j < 4; j++) {
            seatNumber++;
            if (strcmp(buses[busIndex].seats[i][j], "Empty") == 0) {
                cout.width(5);
                cout.fill(' ');
                cout << seatNumber << ".";
                cout.width(10);
                cout.fill(' ');
                cout << buses[busIndex].seats[i][j];
                emptySeatCount++;
            } else {
                cout.width(5);
                cout.fill(' ');
                cout << seatNumber << ".";
                cout.width(10);
                cout.fill(' ');
                cout << buses[busIndex].seats[i][j];
            }
        }
    }

    cout << "\n\nThere are " << emptySeatCount << " seats empty in Bus Number: " << buses[busIndex].busNumber;
}

void Bus::listAvailableBuses() {
    for (int n = 0; n < busCount; n++) {
        printLine('*');
        cout << "Bus number: \t" << buses[n].busNumber
             << "\nDriver: \t" << buses[n].driverName
             << "\t\tArrival time: \t" << buses[n].arrivalTime << "\tDeparture time: \t"
             << buses[n].departureTime << "\nFrom: \t\t" << buses[n].startPoint << "\t\tTo: \t\t"
             << buses[n].endPoint << "\n";
        printLine('*');
        printLine('_');
    }
}

int main() {
    system("cls");
    int choice;

    while (1) {
        cout << "\n\n\n\n\n";
        cout << "\t\t\t1. Install Bus\n\t\t\t"
             << "2. Reserve Seat\n\t\t\t"
             << "3. Show Bus Details\n\t\t\t"
             << "4. List Available Buses\n\t\t\t"
             << "5. Exit";
        cout << "\n\t\t\tEnter your choice:-> ";
        cin >> choice;

        switch (choice) {
        case 1:
            buses[busCount].installBus();
            break;
        case 2:
            buses[busCount].reserveSeat();
            break;
        case 3:
            buses[0].showBusDetails();
            break;
        case 4:
            buses[0].listAvailableBuses();
            break;
        case 5:
            exit(0);
        }
    }

    return 0;
}
