#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<sstream>
#include<chrono>
#include<thread>
#include<ctime>
#include<vector>
#include <unistd.h>
#include<conio.h>
#include <stdlib.h>
using namespace std;
using std::cout;
using std::cin;

vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}
pair<string, bool> searchIDInFile(const string& filename, const string& id) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Failed to open the file: " << filename << endl;
        return make_pair("", false);
    }
    
    string line;
    while (getline(file, line)) {
        vector<string> tokens = split(line, ',');
        if (!tokens.empty() && tokens[0] == id) {
            file.close();
            return make_pair(line, true);
        }
    }
    
    file.close();
    return make_pair("", false);
}
bool isFileEmpty(const string& filename) {
    ifstream file(filename);
    bool val_to_ret = file.peek() == ifstream::traits_type::eof();
    file.close();
    return val_to_ret;
}

string enterPassword(){
    /*Source: "https://stackoverflow.com/questions/41652182/how-to-display-asterisk-for-input-password-in-c-using-clion"*/
    START:
    char* pass = new char[32];//to store password.
    int i = 0;
    char a;//a Temp char
    for(i=0;i<32;)//infinite loop
    {
        a=getch();//stores char typed in a
        pass[i]=a;//stores a in pass
        ++i;
        cout<<"*";
        if(a=='\b'&&i>=1)//if user typed backspace
            //i should be greater than 1.
        {
            cout<<"\b \b";//rub the character behind the cursor.
            --i;
        }
        if(a=='\r')//if enter is pressed
        {
            pass[i]='\0';//null means end of string.
            break;//break the loop
        }
    }
    pass[i-1]='\0';
    // cout<<"\nYou entered: "<<pass;
    // string password = string(pass);
    // cout<<endl<<"Length is "<<password.length()<<" , "<<strlen(pass)<<endl;
    //here we can even check for minimum digits needed
    return string(pass);
}
bool checkComma(string s){
    for(int i=0;i<s.length();i++){
        if(s[i]==','){
            return true;
        }
    }
    return false;
}

string curr_date(){
    auto now = std::chrono::system_clock::now();

    // Convert the system time to a time_t object
    time_t time = std::chrono::system_clock::to_time_t(now);

    // Convert the time_t object to a local time
    tm* local_time = std::localtime(&time);

    // Extract the year, month, and day from the local time
    int year = local_time->tm_year + 1900;  // Years since 1900
    int month = local_time->tm_mon + 1;      // Months are zero-based
    int day = local_time->tm_mday;

    return to_string(day) + "." + to_string(month) + "." + to_string(year);
}
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
bool isDateValid(string date){
    vector<string> tiles = split(date, '.');
    int day = stoi(tiles[0]);
    int month = stoi(tiles[1]);
    int year = stoi(tiles[2]);
    if (year < 1 || month < 1 || month > 12 || day < 1)
        return false;

    // Number of days in each month
    int daysInMonth[] = {31, 28 + isLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (day > daysInMonth[month - 1])
        return false;

    return true;
}
bool compare_dates(string date1, string date2){
    /*Returns true if first date is later else false*/
    vector<string> tokens1 = split(date1, '.');
    vector<string> tokens2 = split(date2, '.');
    if(stoi(tokens1[2])>stoi(tokens2[2])){
        return true;
    }
    else if(stoi(tokens1[2])<stoi(tokens2[2])){
        return false;
    }
    else{
        if(stoi(tokens1[1])>stoi(tokens2[1])){
            return true;
        }
        else if(stoi(tokens1[1])<stoi(tokens2[1])){
            return false;
        }
        else{
            if(stoi(tokens1[0])>stoi(tokens2[0])){
                return true;
            }
            else if(stoi(tokens1[0])<stoi(tokens2[0])){
                return false;
            }
            else{
                return true;
            }
        }
    }
}
int countLeapYears(string date) { 
    vector<string> tokens = split(date, '.');
    int years = stoi(tokens[2]); 
    int month = stoi(tokens[1]);
    if (month <= 2) 
        years--; 
  
    // An year is a leap year if it  
    // is a multiple of 4, 
    // multiple of 400 and not a  
     // multiple of 100. 
    return years / 4  
           - years / 100 
           + years / 400; 
} 
int dayDiff(string date1, string date2){
    int monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    vector<string> tokens1 = split(date1, '.');
    vector<string> tokens2 = split(date2, '.');
    long int n1 = stoi(tokens1[2]) * 365 + stoi(tokens1[0]);
    for (int i = 0; i < stoi(tokens1[1]) - 1; i++) 
        n1 += monthDays[i];
    n1 += countLeapYears(date1);
    long int n2 = stoi(tokens2[2]) * 365 + stoi(tokens2[0]);
    for (int i = 0; i < stoi(tokens2[1]) - 1; i++) 
        n2 += monthDays[i];
    n2 += countLeapYears(date2);
    
    return (n2 - n1);
}

int average_general(string filename){
    ifstream file(filename);
    string line;
    int total_score=0,total_users=0;
    while (getline(file, line)) {
        vector<string> tokens = split(line, ',');
        total_score += stoi(tokens[4]);
        total_users++;
    }
    file.close();
    return total_score/total_users;
}


class Car {
    public:
    Car(string uid, string model, string condition,int cost){
        this->model = model;
        this->uid = uid;
        this->condition = condition;
        this->cost = cost;
}
    string model;
    string uid;
    string condition;
    int cost;
    bool isRented;
    string due_date="";
    string rented_by="";
    bool rentRequest(string date, string person_id, int role);
};

bool Car::rentRequest(string date, string person_id, int role){
    int days = dayDiff(curr_date(),date);
    int price = (this->cost)*(days);
    price = price - (price*0.15*role);
    cout<<"Total cost for renting the car for "<<days<<" days is : "<<price<<endl;
    cout<<"Do you want to continue? (y/n) : ";
    string c;
    cin>>c;
    if(c=="n"){
        return false;
    }
    else if(c=="y"){
        system("cls");
        cout<<"Confirming with Bank"<<endl;
        cout<<"Processing payment..."<<endl;
        sleep(2);
        this->isRented = true;
        this->due_date = date;
        this->rented_by = person_id;
        ifstream file("all_cars.csv");
        string line;
        ofstream temp("temporary.csv");

        while(getline(file, line)){
            vector<string> tokens = split(line, ',');
            if(tokens[0] == this->uid){
                temp<<tokens[0]<<","<<tokens[1]<<","<<tokens[2]<<",1,"<<this->due_date<<","<<this->rented_by<<","<<tokens[6]<<endl;
            }
            else{
                temp<<line<<endl;
            }
        }
        cout<<"Car rented successfully"<<endl;
        temp.close();
        file.close();
        remove("all_cars.csv");
        rename("temporary.csv", "all_cars.csv");
        return true;
    }
    else{
        cout<<"Invalid input"<<endl;
        return false;
    }
}

class People {
    public:
    string id;
    string name;
    string password;
    int fine_due;
    int personal_score;
    int rented_cars;
    virtual void update_info(string data){
        return;
    };
    virtual int number_of_allowed_cars(){
        return 0;
    };
    virtual int tell_role(){
        return -1;
    };
    void change_password();
    void rent_car();
    bool showCars();
    bool showRentedCars();
    void return_car();
    void pay_fine();
    void display_menu_detailed();
    virtual int average_score(){
        return 0;
    };
};
class Customer : public People {
    public:
    Customer(string id, string name,int fine_due, int personal_score,int rented_cars){
        this->id = id;
        this->name = name;
        this->fine_due = fine_due;
        this->personal_score = personal_score;
        this->rented_cars = rented_cars;
        this->display_menu_detailed();
    }
    void update_info(string data);
    int number_of_allowed_cars();
    int average_score();
    int tell_role(){
        return 0;
    };
};
class Employee : public People {
    public:
    Employee(string id, string name,int fine_due, int personal_score,int rented_cars){
        this->id = id;
        this->name = name;
        this->fine_due = fine_due;
        this->personal_score = personal_score;
        this->rented_cars = rented_cars;
        this->display_menu_detailed();
    }
    void update_info(string data);
    int number_of_allowed_cars();
    int average_score();
    int tell_role(){
        return 1;
    };
};
class Manager : public People{
    public:
    string id;
    string name;
    string password;
    Manager(string id, string name){
        this->id = id;
        this->name = name;
        this->display_menu_manager();
    }
    void modifyPeople(string role);
    void display_menu_manager();
    void modifyCars();
    void show_all_cars();
};

void Manager::display_menu_manager(){
    system("cls");
    cout<<"Welcome "<<this->name<<"!"<<endl;
    while(true){
        string c;
        cout<<"Press 1 to modify customer details"<<endl;
        cout<<"Press 2 to modify employee details"<<endl;
        cout<<"Press 3 to see all cars details"<<endl;
        cout<<"Press 4 modify car details"<<endl;
        cout<<"Press 5 to logout"<<endl;
        cin>>c;
        if(c=="1"){
            this->modifyPeople("customer");
        }
        else if(c=="2"){
            this->modifyPeople("employee");
        }
        else if(c=="3"){
            this->show_all_cars();
        }
        else if(c=="4"){
            this->modifyCars();
        }
        else if(c=="5"){
            cout<<"Thank you for using our service\n";
            break;
        }
        else{
            cout<<"Invalid input"<<endl;
        }
    }
}
void Manager::show_all_cars(){
    system("cls");
    while(true){
        string c;
        cout<<"Press 1 to see all cars"<<endl;
        cout<<"Press 2 to see rented cars"<<endl;
        cout<<"Press 3 to see unrented cars"<<endl;
        cout<<"Press 4 to exit"<<endl;
        cin>>c;
        if(c=="1"){
            if(isFileEmpty("all_cars.csv")){
                cout<<"No cars are present in the shop"<<endl;
                continue;
            }
            ifstream file("all_cars.csv");
            string line;
            system("cls");
            while(getline(file, line)){
                vector<string> tokens = split(line, ',');
                cout<<"UID : "<<tokens[0]<<endl;
                cout<<"Model : "<<tokens[1]<<endl;
                cout<<"Condition : "<<tokens[2]<<endl;
                cout<<"Cost per Day: "<<tokens[6]<<endl;
                cout<<"---------------------------------------------------------------------\n";
            }
            file.close();
        }
        else if(c=="2"){
            ifstream file("all_cars.csv");
            string line;
            system("cls");
            bool are_cars = true;
            while(getline(file, line)){
                vector<string> tokens = split(line, ',');
                if(tokens[3] == "1"){
                    are_cars = false;
                    cout<<"UID : "<<tokens[0]<<endl;
                    cout<<"Model : "<<tokens[1]<<endl;
                    cout<<"Condition : "<<tokens[2]<<endl;
                    cout<<"Cost per Day: "<<tokens[6]<<endl;
                    cout<<"Rented by : "<<tokens[5]<<endl;
                    cout<<"Due Date: "<<tokens[4]<<endl;
                    cout<<"---------------------------------------------------------------------\n";
                }
            }
            if(are_cars){
                cout<<"No cars are rented"<<endl;
            }
            file.close();
        }
        else if(c=="3"){
            this->showCars();
        }
        else if(c=="4"){
            break;
        }
        else{
            cout<<"Invalid input"<<endl;
        }
    }
}
void Manager::modifyPeople(string role){
    while(true){
        string c;
        system("cls");
        cout<<"Press 1 to add a new "<<role<<endl;
        cout<<"Press 2 to remove a "<<role<<endl;
        cout<<"Press 3 to update infomation of a "<<role<<endl;
        cout<<"Press 4 to exit"<<endl;
        cin>>c;
        string filename = role + "s.csv";
        string line;
        if(c=="1"){
            system("cls");
            cout<<"Enter ID of the new "<<role<<" : ";
            string id;
            cin>>id;
            cout<<"Enter name of the new "<<role<<" : ";
            string name;
            cin>>name;
            while(true){
                cout<<"Maximum length of password is 31"<<endl;
                cout<<"Enter password of the new "<<role<<" : ";
                string password=enterPassword();
                if(checkComma(password)){
                    cout<<",'s are not allowed"<<endl;
                    continue;
                }
                else{
                    break;
                }
            }
            int score = average_general(filename);
            ofstream file(filename, ios::app);
            file<<id<<","<<name<<","<<password<<",0,"<<score<<",0"<<endl;
            file.close();
        }
        else if(c=="2"){
            system("cls");
            cout<<"Enter ID of the "<<role<<" to be removed : ";
            string id;
            cin>>id;
            pair<string, bool> result = searchIDInFile(filename, id);
            if(!result.second){
                cout<<"Invalid ID"<<endl;
                continue;
            }
            else{
                ifstream file(filename);
                ofstream temp("temp.csv");
                while(getline(file, line)){
                    vector<string> tokens = split(line, ',');
                    if(tokens[0] != id){
                        temp<<line<<endl;
                    }
                }
                file.close();
                temp.close();
                remove(filename.c_str());
                rename("temp.csv", filename.c_str());
            }
        }
        else if(c=="3"){
            system("cls");
            cout<<"Enter ID of the "<<role<<" to be updated : ";
            string id;
            cin>>id;
            pair<string, bool> result = searchIDInFile(filename, id);
            if(!result.second){
                cout<<"Invalid ID"<<endl;
                continue;
            }
            else{
                ifstream file(filename);
                ofstream temp("temp.csv");
                while(getline(file, line)){
                    vector<string> tokens = split(line, ',');
                    if(tokens[0] == id){
                        char update;
                        cout<<"Enter 1 to update name"<<endl;
                        cout<<"Enter 2 to update password"<<endl;
                        cout<<"Enter 3 to update score"<<endl;
                        cin>>update;
                        if(update=='1'){
                            cout<<"Enter new name : ";
                            string name;
                            cin>>name;
                            temp<<tokens[0]<<","<<name<<","<<tokens[2]<<","<<tokens[3]<<","<<tokens[4]<<","<<tokens[5]<<endl;
                        }
                        else if(update=='2'){
                            cout<<"Enter new password : ";
                            string password;
                            cin>>password;
                            temp<<tokens[0]<<","<<tokens[1]<<","<<password<<","<<tokens[3]<<","<<tokens[4]<<","<<tokens[5]<<endl;
                        }
                        else if(update=='3'){
                            string score;
                            while(true){
                                cout<<"Enter new score : ";
                                cin>>score;
                                try{
                                    int check_int = stoi(score);
                                    break;
                                }
                                catch(...){
                                    cout<<"Enter Integer value"<<endl;
                                    continue;
                                }
                            }
                            
                            temp<<tokens[0]<<","<<tokens[1]<<","<<tokens[2]<<","<<tokens[3]<<","<<score<<","<<tokens[5]<<endl;
                        }
                        else{
                            cout<<"Invalid input, no value was updated"<<endl;
                            temp<<line<<endl;
                        }
                    }
                    else{
                        temp<<line<<endl;
                    }
                }
                file.close();
                temp.close();
                remove(filename.c_str());
                rename("temp.csv", filename.c_str());
            }
        }
        else if(c=="4"){
            break;
        }
        else{
            cout<<"Invalid input"<<endl;
            continue;
        }
    }
}
void Manager::modifyCars(){
    while(true){
        string c;
        system("cls");
        cout<<"Press 1 to add a new car"<<endl;
        cout<<"Press 2 to remove a car"<<endl;
        cout<<"Press 3 to update infomation of a car"<<endl;
        cout<<"Press 4 to exit"<<endl;
        cin>>c;
        string filename = "all_cars.csv";
        string line;
        if(c=="1"){
            cout<<"Enter UID of the new car : ";
            string uid;
            cin>>uid;
            cout<<"Enter model of the new car : ";
            string model;
            cin>>model;
            cout<<"Enter condition of the new car : ";
            string condition;
            cin>>condition;
            string cost;
            while(true){
                cout<<"Enter cost per day of the new car : ";
                cin>>cost;
                try{
                    int check_int = stoi(cost);
                    break;
                }
                catch(...){
                    cout<<"Enter Integer value"<<endl;
                    continue;
                }
            }
            ofstream file(filename, ios::app);
            file<<uid<<","<<model<<","<<condition<<",0,,,"<<cost<<endl;
            file.close();
        }
        else if(c=="2"){
            cout<<"Enter UID of the car to be removed : ";
            string uid;
            cin>>uid;
            pair<string, bool> result = searchIDInFile(filename, uid);
            if(!result.second){
                cout<<"Invalid UID"<<endl;
                continue;
            }
            ifstream file(filename);
            ofstream temp("temp.csv");
            while(getline(file, line)){
                vector<string> tokens = split(line, ',');
                if(tokens[0] != uid){
                    temp<<line<<endl;
                }
            }
            file.close();
            temp.close();
            remove(filename.c_str());
            rename("temp.csv", filename.c_str());
        }
        else if(c=="3"){
            cout<<"Enter UID of the car to be updated : ";
            string uid;
            cin>>uid;
            pair<string, bool> result = searchIDInFile(filename, uid);
            if(!result.second){
                cout<<"Invalid UID"<<endl;
                continue;
            }
            ifstream file(filename);
            ofstream temp("temp.csv");
            while(getline(file, line)){
                vector<string> tokens = split(line, ',');
                if(tokens[0] == uid){
                    cout<<"Enter new model : ";
                    string model;
                    cin>>model;
                    cout<<"Enter new condition : ";
                    string condition;
                    cin>>condition;
                    string cost;
                    while(true){
                        cout<<"Enter new cost per day : ";
                        cin>>cost;
                        try{
                            int check_int = stoi(cost);
                            break;
                        }
                        catch(...){
                            cout<<"Enter Integer value"<<endl;
                            continue;
                        }
                    }
                    temp<<tokens[0]<<","<<model<<","<<condition<<","<<tokens[3]<<","<<tokens[4]<<","<<tokens[5]<<","<<cost<<endl;
                }
                else{
                    temp<<line<<endl;
                }
            }
            file.close();
            temp.close();
            remove(filename.c_str());
            rename("temp.csv", filename.c_str());
        }
        else if(c=="4"){
            break;
        }
        else{
            cout<<"Invalid input"<<endl;
        }
    }
}


void People::display_menu_detailed(){
    system("cls");
    cout<<"Welcome "<<this->name<<"!"<<endl;
    while(true){
        string c;
        cout<<"Press 0 to see list of all cars"<<endl;
        cout<<"Press 1 to rent a car"<<endl;
        cout<<"Press 2 to see list of rented cars"<<endl;
        cout<<"Press 3 to return a car"<<endl;
        cout<<"Press 4 to pay fine"<<endl;
        cout<<"Press 5 to change password"<<endl;
        cout<<"Press 6 to logout"<<endl;
        cin>>c;
        if(c=="0"){
            this->showCars();
        }
        else if(c=="1"){
            if(this->showCars())
                this->rent_car();
        }
        else if(c=="2"){
            this->showRentedCars();
        }
        else if(c=="3"){
            if(this->showRentedCars())
                this->return_car();
        }
        else if(c=="4"){
            this->pay_fine();
        }
        else if(c=="5"){
            this->change_password();
        }
        else if(c=="6"){
            cout<<"Thank you for using our service\n";
            break;
        }
        else{
            cout<<"Invalid input\n";
            continue;
        }
    }
}
bool People::showCars(){
    /*Shows all unrented cars*/
    ifstream file("all_cars.csv");
    string line;
    system("cls");
    bool are_cars = true;
    while(getline(file, line)){
        vector<string> tokens = split(line, ',');
        if(tokens[3] == "0"){
            are_cars = false;
            cout<<"UID : "<<tokens[0]<<endl;
            cout<<"Model : "<<tokens[1]<<endl;
            cout<<"Condition : "<<tokens[2]<<endl;
            cout<<"Cost per Day: "<<tokens[6]<<endl;
            cout<<"---------------------------------------------------------------------\n";
        }
    }
    file.close();
    if(are_cars){
        cout<<"No cars are available to rent"<<endl;
        return false;
    }
    return true;
}
void People::pay_fine(){
    if(this->fine_due<=0){
        system("cls");
        cout<<"You do not have any fine"<<endl;
        return;
    }
    else{
        while(true){
            system("cls");
            cout<<"Your fine is : "<<this->fine_due<<endl;
            string amount_str;
            int amount;
            while(true){
                cout<<"Enter the amount you want to pay : ";
                cin>>amount_str;
                try{
                    amount = stoi(amount_str);
                    break;
                }
                catch(...){
                    cout<<"Invalid input"<<endl;
                    continue;
                }
            }
            if(amount>this->fine_due){
                cout<<"You are paying more than your fine. Please enter a valid amount"<<endl;
                continue;
            }
            else{
                this->fine_due -= amount;
                cout<<"Fine paid successfully"<<endl<<"Your remaining fine is : "<<this->fine_due<<endl;
                this->update_info("fine");
                break;
            }
        }
    }
}
void People::change_password(){
    while(true){
        system("cls");
        cout<<"Maximum length of password is 31"<<endl;
        cout<<",'s are not allowed"<<endl;
        cout<<"Enter your new password : ";
        string new_password = enterPassword();
        if(checkComma(new_password)){
            cout<<",'s are not allowed"<<endl;
            continue;
        }
        cout<<"Confirm new password : ";
        string confirm_password = enterPassword();
        if(new_password != confirm_password){
            cout<<"Passwords do not match. Please try again"<<endl;
            continue;
        }
        else{
            this->password = new_password;
            this->update_info("password");
            system("cls");
            cout<<"Password changed successfully"<<endl;
            break;
        }
    }
}
bool People::showRentedCars(){
    ifstream file("all_cars.csv");
    string line;
    system("cls");
    bool are_cars = true;
    while(getline(file, line)){
        vector<string> tokens = split(line, ',');
        if(tokens[3] == "1" && tokens[5] == this->id){
            are_cars = false;
            cout<<"UID : "<<tokens[0]<<endl;
            cout<<"Model : "<<tokens[1]<<endl;
            cout<<"Due Date: "<<tokens[4]<<endl;
            if(compare_dates(curr_date(),tokens[4])){
                cout<<"!!Car is late return is as quickly as possible!!"<<endl;
            }
            cout<<"---------------------------------------------------------------------\n";
        }
    }
    file.close();
    if(are_cars){
        cout<<"You have not rented any cars"<<endl;
        return false;
    }
    return true;
}
void People::rent_car(){
    int rented = this->rented_cars;
    if(rented>=this->number_of_allowed_cars()){
        system("cls");
        cout<<"You have already rented the maximum number of cars allowed"<<endl;
        return;
    }
    while(true){
        string uid;
        cout<<"Enter 1 to go back to main menu"<<endl;
        cout<<"Enter the UID of the car you want to rent : ";
        cin>>uid;
        if(uid == "1"){
            return;
        }
        ifstream file("all_cars.csv");
        string line;
        bool found = false;
        while(getline(file, line)){
            vector<string> tokens = split(line, ',');
            if(tokens[0] == uid){
                found = true;
                if(tokens[3] == "1"){
                    cout<<"Car is already rented"<<endl;
                    break;
                }
                else{
                    cout<<"Enter date till required (dd.mm.yyyy): ";
                    string date;
                    cin>>date;
                    if(!isDateValid(date)){
                        cout<<"Invalid date format"<<endl;
                        break;
                    }
                    else if(compare_dates(curr_date(),date)){
                        cout<<"Enter date that is later than today"<<endl;
                        break;
                    }
                    else{
                        Car car(tokens[0],tokens[1],tokens[2],stoi(tokens[6]));
                        file.close();
                        if(car.rentRequest(date,this->id,this->tell_role())){
                            this->rented_cars++;
                            this->update_info("rented_cars");
                        }
                        return;
                    }
                }
            }
        }
        if(!found){
            cout<<"Invalid UID"<<endl;
            continue;
        }
    }
}
void People::return_car(){
    while(true){
        cout<<"Enter -1 to go back to main menu"<<endl;
        cout<<"Enter UID of the car you want to return : ";
        string uid;
        cin>>uid;
        if(uid == "-1"){
            return;
        }
        ifstream file("all_cars.csv");
        string line;
        bool found = false;
        bool returned = false;
        while(getline(file, line)){
            vector<string> tokens = split(line, ',');
            if(tokens[0] == uid){
                found = true;
                if(tokens[3] == "0"){
                    cout<<"Car is not rented"<<endl;
                    break;
                }
                else if(tokens[5] != this->id){
                    cout<<"You are not the one who rented this car"<<endl;
                    break;
                }
                else{
                    string date=curr_date();
                    int days = dayDiff(tokens[4],date);
                    if(days>0){
                        system("cls");
                        cout<<"Car is late. Fine of "<<days*100 <<" will be charged"<<endl;
                        this->personal_score -= 10*days;
                        this->fine_due += days*100;
                        this->update_info("fine");
                        this->update_info("score");
                    }
                    else{
                        system("cls");
                        cout<<"Car returned on time"<<endl;
                        this->personal_score += 10;
                        this->update_info("score");
                    }
                    this->rented_cars--;
                    this->update_info("rented_cars");
                    returned = true;
                    break;
                }
            }
        }
        file.close();
        if(returned){
            ifstream file("all_cars.csv");
            ofstream file1("temp.csv");
            while(getline(file, line)){
                vector<string> tokens = split(line, ',');
                // cout<<line<<endl;
                if(tokens[0] == uid){
                    file1<<tokens[0]<<","<<tokens[1]<<","<<tokens[2]<<",0,,,"<<tokens[6]<<endl;
                }
                else{
                    file1<<line<<endl;
                }
            }
            file1.close();
            file.close();
            remove("all_cars.csv");
            rename("temp.csv", "all_cars.csv");
            cout<<"Car returned successfully"<<endl;
            return;
        }
        else{
            file.close();
        }
    }
}


void Customer::update_info(string data){
    ifstream file("customers.csv");
    ofstream temp("temp.csv");
    string line;
    while(getline(file, line)){
        vector<string> tokens = split(line, ',');
        if(tokens[0] == this->id){
            if(data == "password"){
                tokens[2] = this->password;
            }
            else if(data == "fine"){
                tokens[3] = to_string(this->fine_due);
            }
            else if(data == "score"){
                tokens[4] = to_string(this->personal_score);
            }
            else if(data == "rented_cars"){
                tokens[5] = to_string(this->rented_cars);
            }
            else{
                cout<<"Invalid data to update"<<endl;
            }
        }
        temp<<tokens[0]<<","<<tokens[1]<<","<<tokens[2]<<","<<tokens[3]<<","<<tokens[4]<<','<<tokens[5]<<endl;
    }
    file.close();
    temp.close();
    remove("customers.csv");
    rename("temp.csv", "customers.csv");
}
int Customer::number_of_allowed_cars(){
    int score = this->personal_score;
    //Max allowed cars are 5
    if(score>=250){
        return 5;
    }
    else if(score<250 && score>=200){
        return 4;
    }
    else if(score<200 && score>=150){
        return 3;
    }
    else if(score<150 && score>=100){
        return 2;
    }
    else if(score<100 && score>=0){
        return 1;
    }
    else{
        return 0;
    }
}
int Customer::average_score(){
    return average_general("customers.csv");
}


void Employee::update_info(string data){
    ifstream file("employees.csv");
    ofstream temp("temp.csv");
    string line;
    while(getline(file, line)){
        vector<string> tokens = split(line, ',');
        if(tokens[0] == this->id){
            if(data == "password"){
                tokens[2] = this->password;
            }
            else if(data == "fine"){
                tokens[3] = to_string(this->fine_due);
            }
            else if(data == "score"){
                tokens[4] = to_string(this->personal_score);
            }
            else if(data == "rented_cars"){
                tokens[5] = to_string(this->rented_cars);
            }
            else{
                cout<<"Invalid data to update"<<endl;
            }
        }
        temp<<tokens[0]<<","<<tokens[1]<<","<<tokens[2]<<","<<tokens[3]<<","<<tokens[4]<<','<<tokens[5]<<endl;
    }
    file.close();
    temp.close();
    remove("employees.csv");
    rename("temp.csv", "employees.csv");
}
int Employee::number_of_allowed_cars(){
    int score = this->personal_score;
    //Max allowed cars are 7
    if(score>=300){
        return 7;
    }
    else if(score<300 && score>=250){
        return 6;
    }
    else if(score<250 && score>=200){
        return 5;
    }
    else if(score<200 && score>=150){
        return 4;
    }
    else if(score<150 && score>=100){
        return 3;
    }
    else if(score<100 && score>=50){
        return 2;
    }
    else if(score<50 && score>=0){
        return 1;
    }
    else{
        return 0;
    }
}
int Employee::average_score(){
    return average_general("employees.csv");
}


void login(){
    while(true){
        string id, password;
        string role;
        system("cls");
        cout<<"Enter 0 to go back to main menu"<<endl;
        cout<< "Login as Employee/Customer/Manager?(e/c/m)  ";
        cin>>role;

        string filename;
        if(role=="c"){
            filename = "customers.csv";
        }
        else if(role=="e"){
            filename = "employees.csv";
        }
        else if(role=="m"){
            filename = "managers.csv";
        }
        else if(role=="0"){
            return;
        }
        else{
            cout<<"Invalid user type"<<endl;
            continue;
        }
        cout << "Enter your id: ";
        cin >> id;
        cout<<endl;
        pair<string, bool> result = searchIDInFile(filename, id);
        if (result.second) {
            cout << "ID is valid" << endl;
        } 
        else {
            cout << "Invalid ID" << endl;
            continue;
        }
        cout << "Enter your password (max length is 31): ";
        /*Testing Code*/
        password=enterPassword();
        /*Testing End*/
        cout<<endl;
        vector<string> tokens = split(result.first, ',');
        if (tokens[2] == password) {
            if(role=="c"){
                Customer customer(id, tokens[1],stoi(tokens[3]),stoi(tokens[4]),stoi(tokens[5]));
            }
            else if(role=="e"){
                Employee employee(id, tokens[1],stoi(tokens[3]),stoi(tokens[4]),stoi(tokens[5]));
            }
            else if(role=="m"){
                Manager manager(id, tokens[1]);
            }
            else{
                cout<<"Invalid user type"<<endl;
            }
        }
        else{
            cout << "Invalid password" << endl;
            continue;
        }
    }
}
void register_user(){
    while(true){
        string id, name, password;
        cout << "Whats your name: ";
        cin>>name;
        cout<<endl;
        bool unique_id = false;
        cout << "Enter your id: ";
        cin >> id;
        pair<string, bool> result = searchIDInFile("customers.csv", id);
        if (result.second) {
            cout << "ID already exists" << endl;
            continue;
        } 
        cout<<"ID is available"<<endl;
        while(true){
            cout<<"Maximum length of password is 31"<<endl;
            cout << "Enter your password: ";
            password=enterPassword();
            if(checkComma(password)){
                cout<<endl<<",'s are not allowed"<<endl;
                continue;
            }
            else{
                break;
            }
        }
        ofstream file("customers.csv", ios::app);

        //get avg score
        int avg_score=average_general("customers.csv");

        file << id << "," << name << "," << password << ",0,"<<to_string(avg_score)<<",0"<< endl;
        file.close();
        system("cls");
        cout << "Registered successfully" << endl;
        break;
    }
}
void display_menu(){
    system("cls");
    while(true){
        string c;
        cout<<"---------------------------------------------------------------------\n";
        cout<<"Welcome to the Car Rental Service of Nawab Motors!\n\n";
        cout<<"Press 1 to log in"<<endl;
        cout<<"Press 2 to register"<<endl;
        cout<<"Press 3 to exit"<<endl;
        cout<<"---------------------------------------------------------------------\n";
        cin>>c;
        if(c=="1"){
            login();
        }
        else if(c=="2"){
            register_user();
        }
        else if(c=="3"){
            cout<<"Thank you for using our service\n";
            break;
        }
        else{
            cout<<"Invalid input\n";
        }
    }
}


int main(){
    display_menu();
    system("cls");
    return 0;
}