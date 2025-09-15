#include <iostream>
#include <vector>
#include <string>
using namespace std;

string getDistrictName(int opt) {
    switch (opt) {
        case 1: return "District 1";
        case 2: return "District 2";
        case 3: return "District 3";
        case 4: return "District 4";
        case 5: return "District 5";
        case 6: return "District 6";
        case 7: return "District 7";
        case 8: return "District 8";
        case 9: return "District 9";
        case 10: return "District 10";
        case 11: return "District 11";
        case 12: return "District 12";
        case 13: return "Go Vap District";
        case 14: return "Tan Binh District";
        case 15: return "Tan Phu District";
        case 16: return "Binh Thanh District";
        case 17: return "Phu Nhuan District";
        case 18: return "Binh Tan District";
        case 19: return "Thu Duc City";
        default: return "No supported";
    }
}

string getStationName(int type) {
    switch (type) 
    {
    case 1: return "Bus Station";
    case 2: return "Train Station";
    case 3: return "Metro Station";
    default: return "No supported";
    }
}

class Schedule {
    private: 
        bool isArrival; //1 == Arrival, 0 == Departure
        string time;
    public:
        Schedule(string time, bool isArrival) {
            this->time = time;
            this->isArrival = isArrival;
        }

        string getInfo() {
            return (isArrival ? "Arrival at " : "Departure at ") + time;
        }
};

class Station {
    private:
        string name;
        int location; //choose following to information at getDistrictName
        int type; //  1 = bus, 2 = train, 3 = metro
        vector<Schedule> listSchedules;
    public:
        Station(string name, int location, int type) {
            this->name = name;
            this->location = location;
            this->type = type;
        }

        //getter and setter
        string getName() {return name;}
        string getLocation() {return getDistrictName(location);}
        string getType() {return getStationName(type);}

        void setName(string name) {this->name = name;}
        void setLocation(int location) {this->location = location;}
        void setType(int type) {this->type = type;}

        void addSchedule(Schedule s) {
            listSchedules.push_back(s);
        }

        void displayInfo() {
            cout << "Schedules at " << name << " (" << getType() << ") in " << getDistrictName(location) << endl;
            for (Schedule &s : listSchedules) {
                cout << "- " << s.getInfo() << endl;
            }
        }
};

class Vehicle {
    private:
    protected:
        string route;
        int capacity;
        bool status;
        Station* station; //trỏ trực tiếp đến Station cụ thể ->>> tăng liên kết
    public: 
        Vehicle(string route, int capacity, bool status, Station* station = nullptr) {
            this->route = route;
            this->capacity = capacity;
            this->status = status;
            this->station = station;
        }

        //getter and setter
        string getRoute() {return route;}
        int getCapacity() {return capacity;}
        string getStatus() {return (status ? "on time" : "delayed");}
        Station* getStation() {return station;}

        void setRoute(string route) {this->route = route;}
        void setCapacity(int capacity) {this->capacity = capacity;}
        void setStatus(bool status) {this->status = status;}
        void setStation(Station* station) {this->station = station;}


        virtual double calculateTravelTime(double distance) {
            return distance/40.0; //mặc định
        }

        virtual void displayInfo() {
            cout << "- Route: " << route << ", Capacity: " << capacity << ", Status: " << (status ? "on time" : "delayed") << endl;
            if (station != nullptr) {
                cout << "- This route assigned to " << station->getName() << " station." << endl; //-> để truy cập thành phần của Station
            } else cout << "- Not assigned to any station." << endl;
        }
};

class ExpressBus : public Vehicle {
    private:
        double speed;
        int stops;
    public:
        ExpressBus(string route, int capacity, bool status, double speed, int stops, Station* station = nullptr) 
            : Vehicle(route, capacity, status, station) {
                this->speed = speed;
                this->stops = stops;
            }
    
        //getter and setter
        double getSpeed() {return speed;}
        int getStops() {return stops;}

        void setSpeed(double speed) {this->speed = speed;}
        void setStops(int stops) {this->stops = stops;}

        double calculateTravelTime(double distance) override { //unused thay cho tham số speed để đủ form tham số trong virtual mới override được
            return 0.8*distance/speed;
        }

        void displayInfo() override {
            cout << "- Route: " << route << ", Capacity: " << capacity << ", speed: " << speed << ", stops: " << stops << ", Status: " << (status ? "on time" : "delayed") << endl;
            if (station != nullptr) {
                cout << "- This route assigned to " << station->getName() << " station." << endl; //-> để truy cập thành phần của Station
            } else cout << "- Not assigned to any station." << endl;
        }
};

class Passenger {
    private:
        string name;
        string ID;
        vector<Vehicle*> bookedTickets;
    public:
        Passenger(string name, string ID) {
            this->name = name;
            this->ID = ID;
        }
    
        //getter and setter
        string getName() {return name;}
        string getID() {return ID;}

        void setName(string name) {this->name = name;}
        void setID(string ID) {this->ID = ID;}

        void bookVehicle(Vehicle* b) {
            bookedTickets.push_back(b);
        }

        void displayInfo() {
            cout << "Passenger: " << name <<  ", ID: " << ID << endl;
            cout << "Booked vehicles:" << endl;
            for (Vehicle* v : bookedTickets) {
                cout << "- Route: " << v->getRoute() << " (Status: " << v->getStatus() << ")" << endl;
            }
        }
};

int main() {

    cout << "Our system have some the information about the choosing on location from 1 to 19:" << endl;
    for (int i=1; i<=19; i+=4) {
        cout << i << ". " << getDistrictName(i) << "        " << i+1 << ". " << getDistrictName(i+1) << "        " 
            << i+2 << ". " << getDistrictName(i+2) << "        " << i+3 << ". " << getDistrictName(i+3) << endl;
    }

    cout << "And the option about the type of station:" << endl << "1. Bus Station           2. Train Station            3. Metro Station" << endl;

    // ====== Tạo dữ liệu mẫu ======
    Station s1("Central Bus Station", 1, 1);  // District 1, Bus
    Station s2("Main Train Station", 3, 2);   // District 3, Train

    s1.addSchedule(Schedule("08:00", true));   // Arrival
    s1.addSchedule(Schedule("08:30", false));  // Departure
    s2.addSchedule(Schedule("09:00", true));
    s2.addSchedule(Schedule("09:45", false));

    Vehicle* v1 = new Vehicle("Route A", 40, true, &s1); // On time, gán vào s1
    Vehicle* eb1 = new ExpressBus("Express 1", 30, true, 60.0, 5, &s2);

    Passenger p1("Alice", "P001");
    p1.bookVehicle(v1);
    p1.bookVehicle(eb1);

    // ====== Đưa dữ liệu vào vector ======
    vector<Station> stations;
    vector<Vehicle*> vehicles;
    vector<Passenger> passengers;

    stations.push_back(s1);
    stations.push_back(s2);

    vehicles.push_back(v1);
    vehicles.push_back(eb1);

    passengers.push_back(p1);

    int choice;
    do {
        cout << "Transportation System Menu" << endl;
        cout << "1. Add Station" << endl;
        cout << "2. Add Vehicle" << endl;
        cout << "3. Add Passenger\n";
        cout << "4. Book Ticket for Passenger\n";
        cout << "5. Show All Stations\n";
        cout << "6. Show All Vehicles\n";
        cout << "7. Show All Passengers\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            int location, type;
            cout << "Station name: ";
            cin.ignore(); getline(cin, name);
            cout << "Location: "; cin >> location;
            cout << "Station type: "; cin >> type;
            stations.push_back(Station(name, location, type));
        }
        else if (choice == 2) {
            string route;
            int capacity, type, stop;
            bool status;
            double speed;
            cout << "Route name: "; cin.ignore(); getline(cin, route);
            cout << "Capacit: "; cin >> capacity;
            cout << "Status (with 1 is on time and 0 is delayed): "; cin >> status;

            cout << "You have to select station:" << endl;
            for (int i=0; i<stations.size(); i++) {
                cout << i << "." << stations[i].getName() <<endl;
            }
            int select; cout << "Your selection: "; cin >> select;

            cout << "And select the type of vehicle: " << endl << "1. Normal or 2. Express Bus" << endl;
            cout << "Your selection: "; cin>>type;
            if (type == 1) {
                vehicles.push_back(new Vehicle(route, capacity, status, &stations[select]));
            } else {
                cout << "speed: "; cin >> speed;
                cout << "stops: "; cin >> stop;
                vehicles.push_back(new ExpressBus(route, capacity, status, speed, stop, &stations[select]));
            }
        }
        else if (choice == 3) {
            string name, ID;
            cout << "Passenger name: "; cin.ignore(); getline(cin, name);
            cout << "Passenger ID: "; getline(cin, ID);
            passengers.push_back(Passenger(name, ID));
        }
        else if (choice == 4) {
            string ID;
            cout << "Passenger ID: "; cin.ignore(); cin >> ID;
            cout << "Choose vehicle:\n";
            for (int i=0;i<vehicles.size();i++) 
                cout << i << ". " << vehicles[i]->getRoute() << endl;
            int vi; cin >> vi;

            for (Passenger &p : passengers) {
                if (p.getID()==ID) {
                    p.bookVehicle(vehicles[vi]);
                }
            }
        }
        else if (choice == 5) {
            for (Station &s : stations) s.displayInfo();
        }
        else if (choice == 6) {
            for (Vehicle* v : vehicles) v->displayInfo();
        }
        else if (choice == 7) {
            for (Passenger &p : passengers) p.displayInfo();
        }
    } while (choice != 8);

    // Giải phóng bộ nhớ động đã cấp phát cho vehicles
    for (Vehicle* v : vehicles) {
        delete v;
    }
    
    return 0;
}
