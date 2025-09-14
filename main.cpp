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
        default: return "Unknown";
    }
}

string getStationName(int type) {
    switch (type) 
    {
    case 1: return "Bus Station";
    case 2: return "Train Station";
    case 3: return "Metro Station";
    default: return "Unknown";
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
            cout << "Route: " << route << ", Capacity: " << capacity << ", Status: " << (status ? "on time" : "delayed") << endl;
            if (station != nullptr) {
                cout << "This route assigned to " << station->getName() << " station." << endl; //-> để truy cập thành phần của Station
            } else cout << " Not assigned to any station." << endl;
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
            cout << "Route: " << route << ", Capacity: " << capacity << ", speed: " << speed << ", stops: " << stops << ", Status: " << (status ? "on time" : "delayed") << endl;
            if (station != nullptr) {
                cout << "This route assigned to " << station->getName() << " station." << endl; //-> để truy cập thành phần của Station
            } else cout << " Not assigned to any station." << endl;
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
    // 1. Tạo các Station
    Station s1("Central Bus Station", 1, 1); // District 1, Bus
    Station s2("Main Train Station", 3, 2);  // District 3, Train

    // 2. Thêm Schedule cho Station
    s1.addSchedule(Schedule("08:00", true));   // Arrival
    s1.addSchedule(Schedule("08:30", false));  // Departure
    s2.addSchedule(Schedule("09:00", true));
    s2.addSchedule(Schedule("09:45", false));

    // 3. Tạo Vehicle và ExpressBus
    Vehicle v1("Route A", 40, true, &s1); // On time, gán vào s1
    ExpressBus eb1("Express 1", 30, true, 60.0, 5, &s1);

    // 4. Tạo Passenger và book Vehicle
    Passenger p1("Alice", "P001");
    p1.bookVehicle(&v1);
    p1.bookVehicle(&eb1);

    // ===== Hiển thị thông tin =====
    cout << "=== Station Info ===" << endl;
    s1.displayInfo();
    cout << endl;
    s2.displayInfo();
    cout << endl;

    cout << "=== Vehicle Info ===" << endl;
    v1.displayInfo();
    cout << endl;
    eb1.displayInfo();
    cout << endl;

    cout << "=== Passenger Info ===" << endl;
    p1.displayInfo();
    cout << endl;

    // 5. Test travel time
    double distance = 120; // km
    cout << "Travel time for v1 (distance " << distance << " km): " 
         << v1.calculateTravelTime(distance) << " h" << endl;
    cout << "Travel time for eb1 (distance " << distance << " km): " 
         << eb1.calculateTravelTime(distance) << " h" << endl;

    return 0;
}
