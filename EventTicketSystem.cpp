#include <iostream>
#include <string>
using namespace std;

class Ticket {
public:
    int id;
    string name;
    string eventName;
    double price;
    bool valid;

    Ticket() {
        id = -1;
        valid = false;
    }

    Ticket(int i, string n, string e, double p) {
        id = i;
        name = n;
        eventName = e;
        price = p;
        valid = true;
    }

    void operator+=(double discount) {
        price -= (price * discount / 100);
    }

    void show() {
        cout << "\n----- TICKET -----";
        cout << "\nID    : " << id;
        cout << "\nName  : " << name;
        cout << "\nEvent : " << eventName;
        cout << "\nPrice : " << price;
        cout << "\n------------------\n";
    }
};

class Event {
protected:
    string name;
    int seats;
    int booked;
    double price;

public:
    Event(string n, int s, double p) {
        name = n;
        seats = s;
        price = p;
        booked = 0;
    }

    virtual void display() {
        cout << "\nEvent: " << name;
        cout << "\nSeats Left: " << (seats - booked);
        cout << "\nPrice: " << price << endl;
    }

    virtual Ticket book(string user, int id) {
        if (booked < seats) {
            booked++;
            return Ticket(id, user, name, price);
        }

        cout << "\nNo seats available!";
        return Ticket();
    }

    virtual ~Event() {}
};

class Concert : public Event {
public:
    Concert(string n, int s, double p) : Event(n, s, p) {}

    void display() override {
        cout << "\nCONCERT EVENT";
        Event::display();
    }

    Ticket book(string u, int id) override {
        Ticket t = Event::book(u, id);
        t += 10;
        return t;
    }
};

class Sports : public Event {
public:
    Sports(string n, int s, double p) : Event(n, s, p) {}

    void display() override {
        cout << "\nSPORTS EVENT";
        Event::display();
    }

    Ticket book(string u, int id) override {
        Ticket t = Event::book(u, id);
        t += 5;
        return t;
    }
};

class Theater : public Event {
public:
    Theater(string n, int s, double p) : Event(n, s, p) {}

    void display() override {
        cout << "\nTHEATER EVENT";
        Event::display();
    }

    Ticket book(string u, int id) override {
        Ticket t = Event::book(u, id);
        t += 15;
        return t;
    }
};

void addEvent(Event* events[], int& eventCount) {
    string name;
    int seats, type;
    double price;

    cout << "\nEnter event name: ";
    cin >> ws;
    getline(cin, name);

    cout << "Enter seats: ";
    cin >> seats;

    cout << "Enter price: ";
    cin >> price;

    cout << "\nSelect type:";
    cout << "\n1. Concert";
    cout << "\n2. Sports";
    cout << "\n3. Theater";
    cout << "\nChoice: ";
    cin >> type;

    if (type == 1)
        events[eventCount++] = new Concert(name, seats, price);
    else if (type == 2)
        events[eventCount++] = new Sports(name, seats, price);
    else if (type == 3)
        events[eventCount++] = new Theater(name, seats, price);
    else {
        cout << "\nInvalid event type!";
        return;
    }

    cout << "\nEvent Added!";
}

void showEvents(Event* events[], int eventCount) {
    if (eventCount == 0) {
        cout << "\nNo events available!";
        return;
    }

    for (int i = 0; i < eventCount; i++) {
        cout << "\n[" << i << "]";
        events[i]->display();
    }
}

void bookTicket(Event* events[], int eventCount,
                Ticket tickets[], int& ticketCount, int& ticketID) {

    if (eventCount == 0) {
        cout << "\nNo events to book!";
        return;
    }

    string user;
    int idx;

    cout << "\nEnter name: ";
    cin >> ws;
    getline(cin, user);

    showEvents(events, eventCount);

    cout << "\nSelect event index: ";
    cin >> idx;

    if (idx >= 0 && idx < eventCount) {
        Ticket t = events[idx]->book(user, ticketID++);

        if (t.id != -1) {
            tickets[ticketCount++] = t;
            cout << "\nTicket Booked!";
            t.show();
        }
    }
    else {
        cout << "\nInvalid selection!";
    }
}

void showTickets(Ticket tickets[], int ticketCount) {
    if (ticketCount == 0) {
        cout << "\nNo tickets booked!";
        return;
    }

    for (int i = 0; i < ticketCount; i++) {
        tickets[i].show();
    }
}

void menu(Event* events[], int& eventCount,
          Ticket tickets[], int& ticketCount, int& ticketID) {

    int choice;

    do {
        cout << "\n\n===== EVENT SYSTEM =====";
        cout << "\n1. Add Event";
        cout << "\n2. Show Events";
        cout << "\n3. Book Ticket";
        cout << "\n4. Show Tickets";
        cout << "\n5. Exit";
        cout << "\nEnter choice: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid input!";
            continue;
        }

        switch (choice) {
            case 1:
                addEvent(events, eventCount);
                break;

            case 2:
                showEvents(events, eventCount);
                break;

            case 3:
                bookTicket(events, eventCount,
                           tickets, ticketCount, ticketID);
                break;

            case 4:
                showTickets(tickets, ticketCount);
                break;

            case 5:
                cout << "\nExiting system...";
                break;

            default:
                cout << "\nInvalid choice!";
        }

    } while (choice != 5);
}

int main() {
    Event* events[50];
    Ticket tickets[100];

    int eventCount = 0;
    int ticketCount = 0;
    int ticketID = 100;

    menu(events, eventCount, tickets, ticketCount, ticketID);

    for (int i = 0; i < eventCount; i++) {
        delete events[i];
    }

    return 0;
}
