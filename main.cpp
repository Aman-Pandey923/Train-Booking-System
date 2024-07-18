# include <iostream>
# include <bits/stdc++.h>

using namespace std;

// Format of Date used in this whole program is YYYYMMDD.
int today_date = 20230519;

class Station {
    private: 
        float x, y;
    public:
        Station() {}
        Station(float a, float b) {
            x = a; y = b;
        }
        Station(const Station &obj) {
            this->x = obj.x;
            this->y = obj.y;
        }
        pair<float, float> get_Coord_() {
            return {x, y};
        }
};

class Ticket {
    private:
        Station Start_Station;
        Station Destination;
        int date; 
        float cost;
    public:
        Ticket(Station s, Station d, int da){
            Start_Station = s;
            Destination = d;
            date = da;
            auto a = Start_Station.get_Coord_();
            auto b = Destination.get_Coord_();
            cost = sqrt(pow(a.first-b.first, 2)+pow(a.second-b.second, 2))*25; // Rate = 25/km
        }
        void View_Ticket() {
            auto a = Start_Station.get_Coord_();
            auto b = Destination.get_Coord_();
            cout << "\nTICKET :-";
            cout << "\n\tStart : (" << a.first << ", " << a.second << ")";
            cout << "\n\tDestination : (" << b.first << ", " << b.second << ")";
            cout << "\n\tDate(YYYYMMDD) : " << date;
            cout << "\n\tCost: " << cost;
            cout << "\n\n";
        }
};


class User {
    protected:
        string Username;
        string Password;
        string Name;
        vector<Ticket> List_of_Tickets;
    public:
        User() {}
        User(string x, string y, string z) {
            Username = x;
            Password = y;
            Name = z;
        }
        string Get_Username() {
            return Username;
        }
        int Verify_Password(string password) {
            if (Password==password) return 1;
            return 0;
        }
        void View_Tickets(){
            for (Ticket tk : List_of_Tickets) {
                tk.View_Ticket();
            }
        }
};

class Seat {
    private:
        int coach_no=1, seat_no=1;
    public:
        int increase_no() {
            if (coach_no<3) {
                if (seat_no==4) {
                    coach_no++; 
                    seat_no=1; 
                    return 1;
                } else {
                    seat_no++; 
                    return 1;
                }
            } else return 0;
        }
};

class Passenger : public User {
    private: 
        string PassengerId; 
        Seat seat;
    public:
        Passenger(string x, string y, string z) {
            this->Username = x;
            this->Password = y;
            this->Name = z;
        }
        string Get_PassengerId() {
            return PassengerId;
        }
        void Book_Ticket();
};

class Travel {
    public:
        vector<Passenger> List_Passengers;
        Station Start_Station;
        Station Destination;
        int date; 
        Seat curr_seat;
    public:
        void View_Passenger_List() {
            cout << "\n\nList of Passengers are: \n";
            for (Passenger p : List_Passengers) {
                cout << "\t" << p.Get_Username();
            }
        }
        void View_Journey() {
            auto a = Start_Station.get_Coord_();
            auto b = Destination.get_Coord_();
            cout << "\n\nStart : (" << a.first << ", " << a.second << ")\n";
            cout << "\nDestination : (" << b.first << ", " << b.second << ")\n";
            cout << "\nDate(YYYYMMDD) : " << date << endl;
        }
};

vector<Travel> Tv;

void Passenger::Book_Ticket() {
        float stx, sty, dstx, dsty; int date;
        cout << "\nEnter Start Station (x, y) : ";
        cin >> stx >> sty; 
        cout << "Enter Destination Station (x, y) : ";
        cin >> dstx >> dsty;
        Station start = Station(stx, sty);
        Station dest_ = Station(dstx, dsty);
        cout << "Enter Date (YYYYMMDD) : ";
        cin >> date;

        if (date > today_date) {
            int check=0;
            for (Travel travel : Tv) {
                if (travel.Start_Station.get_Coord_()==start.get_Coord_() && travel.Destination.get_Coord_()==dest_.get_Coord_() && travel.date==date) {
                    check = 1;
                    Seat st = travel.curr_seat;
                    if (travel.curr_seat.increase_no()) {
                        seat = st;
                        travel.List_Passengers.push_back(*this);
                        Ticket tk = Ticket(start, dest_, date);
                        this->List_of_Tickets.push_back(tk);
                        cout << "\n\t\t Ticket booked Successfully !!! \n";
                    } else {
                        cout << "Seat not Available !!!";
                    }  
                }
            }
            if (!check) {
                Travel travel;
                travel.Start_Station = start;
                travel.Destination = dest_;
                travel.date = date;
                seat = travel.curr_seat; travel.curr_seat.increase_no();
                travel.List_Passengers.push_back(*this);
                Tv.push_back(travel);
                Ticket tk = Ticket(start, dest_, date);
                this->List_of_Tickets.push_back(tk);
                cout << "\n\t\t Ticket booked Successfully !!! ";
            }
        } else {
            cout << "\nInvalid Date !!\n";
        }
}


vector<Passenger> User_List;

class Ticket_Collector : public User {
    private:
        string EmployeeID;
    public:
        string Get_EmployeeID() {
            return EmployeeID;
        }
};

void User_Func(Passenger user) {
    int x;
    while (true) {
        cout << "\ni) Book Ticket (enter 1)\nii) View List of Tickets (enter 2)\niii) Exit (enter 3)\nEnter : ";
        cin >> x;
        if (x==1) {
            user.Book_Ticket();
        } else if (x==2) {
            user.View_Tickets();
        } else if (x==3) {
            break;
        } else {
            cout << "Please enter valid input !!";
        }
    }
}

int main() {

    int en_;
    cout << "\n\nPassenger LOGIN\n\n";

    while (true) {
        cout << "\nDo you wanna login (enter 1) or signup (enter 2) or exit (enter 3) ? ";
        cin >> en_; 
        if (en_==1) {
            string Username, password; int check=0;
            cout << "Enter Username : ";
            cin >> Username;
            cout << "Enter password : ";
            cin >> password;

            for (Passenger user : User_List) {
                if (Username==user.Get_Username() && user.Verify_Password(password)) {
                    cout << "\n\nAccess Granted !!\n";
                    User_Func(user);
                    check = 1; break;
                }
            }  
            if (!check) cout << "\nInvalid Username or Password !!\n";
        } else if (en_==2) {
            string username, password, name;
            cout << "Enter Username : "; cin >> username;
            cout << "Enter Password : "; cin >> password;
            cout << "Enter your Name : "; cin >> name;
            Passenger obj = Passenger(username, password, name);
            User_List.push_back(obj);
        } else if (en_==3) {
            break;
        } else {
            cout << "Please Enter Valid Input !!";
        }
    }

    return 0;
}