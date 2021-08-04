#include<iostream>
#include<cstring>
#include<string.h>
#include<string>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
#include<mysql.h>
#include<sstream>
#include <iomanip>
using namespace std;
class BusReservationSystem
{
	public:
	    BusReservationSystem(string,string,string,string);
	    ~BusReservationSystem();
	    MYSQL* db_conn;
	    bool Userlogin();
        void registration();
        void showListOfBuses();
        void bookTicket();
        void showticket();
};
BusReservationSystem::BusReservationSystem(string HOST,string USER,string PASSWORD,string DATABASE)
{
    db_conn = mysql_init(NULL);
    if(!db_conn)
    {
        cout<<"MySQL initialization failed! ";
    }
    db_conn = mysql_real_connect(db_conn, HOST.c_str(),USER.c_str(), PASSWORD.c_str(), DATABASE.c_str(), 0,NULL, 0);
    if(!db_conn)
    {
        cout<<"Connection Error! ";
    }
}
bool BusReservationSystem::Userlogin()
{
		string username,password="";
        char pass;
		cout<<"Enter Username : ";
        cin>>username;
        cout<<"Enter Password : ";

        pass = _getch();
        while(pass!='\r')
        {
            password.push_back(pass);
            cout<<"*";
            pass =_getch();
        }

        stringstream ss2;
        MYSQL_RES* rset;
        MYSQL_ROW rows;
        ss2<<"select username,password from user_details where username='"<<username<<"' and password='"<<password<<"'";
        int result = mysql_query(db_conn, ss2.str().c_str());
        rset = mysql_use_result(db_conn);
        if(rset)
        {
            while((rows = mysql_fetch_row(rset)))
            {
                if(rows[0]==username && password==rows[1])
                {
                        cout<<"\nLogin Successfully done\n";
                        return 1;

                }
            }

        }
        cout<<"\nInvalid User name or password\n";
                    return 0;
}
void BusReservationSystem::registration()
{
    char name[30], username[30], password[30], confirmPassword[30], email[30];
    long long int  mobileNo;
    cout<<"\nEnter Your Name : ";
    cin>>name;
    cout<<"\nEnter User Name : ";
    cin>>username;
    cout<<"\nEnter Password : ";
    cin>>password;
    confirm_password :
        cout<<"\nEnter confirm password : ";
        cin>>confirmPassword;
    if(strcmp(password,confirmPassword) != 0)
    {
        goto confirm_password;
    }
    cout<<"\nEnter email address : ";
    cin>>email;
    cout<<"\nEnter Mobile No : ";
    cin>>mobileNo;
    stringstream ss1;
    ss1  << "INSERT INTO user_details "
        << "values ( null ,'" <<name<< "','"
        <<username<<"','" <<password<< "','" <<email<< "'," <<mobileNo<< ")";
    int h=mysql_query(db_conn, ss1.str().c_str());
    if(h!=0)
    {
        cout<<"Failed";
    }
    else{cout<<"Item Added successfully.\n\n";}
}
void BusReservationSystem::bookTicket()
{
    int seats=0;
    stringstream ss3;
    MYSQL_RES* rset1;
    MYSQL_ROW rows1;
    int bus_no;
    int no_of_seats;
    char uname[20];
    cout<<"Enter bus no:";
    cin>>bus_no;
    ss3<<"select sum(num_of_seats) from ticket_details where bus_no="<<bus_no;
    int result1 = mysql_query(db_conn, ss3.str().c_str());
    rset1 = mysql_use_result(db_conn);
    if(rset1)
        {
            while((rows1 = mysql_fetch_row(rset1)))
            {
                    string s=rows1[0];
                    stringstream k(s);
                    k>>seats;
                        if(seats==30){
                            cout<<"All seats are booked";
                        }else{
                            cout<<"Enter name:";
                            cin>>uname;
                            cout<<"Enter number of seats:";
                            cin>>no_of_seats;
                            if(no_of_seats+seats<=30){

                                    db_conn = mysql_init(NULL);
    if(!db_conn)
    {
        cout<<"MySQL initialization failed! ";
    }
    db_conn = mysql_real_connect(db_conn, "localhost","root","","busreservationsystem", 0,NULL, 0);
    if(!db_conn)
    {
        cout<<"Connection Error! ";
    }

                                    stringstream ss4;
                                ss4 << "INSERT INTO ticket_details "
                                << "values ( null ," << bus_no << ",'"
                                <<uname<<"'," <<no_of_seats<<")";
                            //cout<<ss4.str();
    int h=mysql_query(db_conn, ss4.str().c_str());
    if(h!=0)
    {
        cout<<"Failed";
    }
    else{cout<<"Item Added successfully.";}


                            }else{
                                   cout<<"Please enter seats less than or equal to:"<<(30-seats);
                            }
                        }
            }

        }
}
void BusReservationSystem::showListOfBuses()
{
    MYSQL_RES* rset;
   	MYSQL_ROW rows;
	string sql = "SELECT bus_number,form,T_O,atime,dtime FROM bus_details";
    if(mysql_query(db_conn, sql.c_str()))
    {
        cout<<"Error printing";
        return;
  	}
   rset = mysql_use_result(db_conn);
   cout << left << setw(12) << setfill('-') << left << '+'
                << setw(21) << setfill('-') << left << '+'
                << setw(21) << setfill('-') << left << '+'
                << setw(21) << setfill('-') << left << '+'
                << setw(21) << setfill('-') << left << '+' <<right<<"+"<<endl;

   cout << setfill(' ') << '|' << left << setw(11) << "Bus Number"
        << setfill(' ') << '|' << setw(20) << "Form"
        << setfill(' ') << '|' << setw(20) << "To"
        <<  setfill(' ') << '|' << setw(20) << "Arrival Time"
        << setfill(' ') << '|' << setw(20) << "Departure Time"
        << setfill(' ') << '|' << right << setw(20)<< endl;

   cout << left << setw(12) << setfill('-') << left << '+'
                << setw(21) << setfill('-') << left << '+'
                << setw(21) << setfill('-') << left << '+'
                << setw(21) << setfill('-') << left << '+'
                << setw(21) << setfill('-') << left << '+' <<right<<"+"<<endl;

   if(rset)
    {
        while((rows = mysql_fetch_row(rset)))
        {
            cout<< setfill(' ') << '|' << left << setw(11) << rows[0]
                << setfill(' ') << '|' << setw(20) << rows[1]
                << setfill(' ') << '|' << setw(20) << rows[2]
                << setfill(' ') << '|' << setw(20) << rows[3]
                << setfill(' ') << '|' << setw(20) << rows[4]
                << setfill(' ') << '|' << endl;
        }
       cout << left << setw(12) << setfill('-') << left << '+'
                << setw(21) << setfill('-') << left << '+'
                << setw(21) << setfill('-') << left << '+'
                << setw(21) << setfill('-') << left << '+'
                << setw(21) << setfill('-') << left << '+' <<right<<"+"<<endl;
    }
    mysql_free_result(rset);
}
void BusReservationSystem::showticket()
{
MYSQL_RES* rset;
   	MYSQL_ROW rows;
	string sql = "SELECT bus_no,uname,num_of_seats FROM ticket_details";
    if(mysql_query(db_conn, sql.c_str())) {
    cout<<"Error printing";
      return;
  	}

   rset = mysql_use_result(db_conn);

   cout << left << setw(10) << setfill('-') << left << '+'
        << setw(21) << setfill('-') << left << '+'
        << setw(21)
        << setfill('-')
        << '+' <<right<<"+"<<endl;

   cout << setfill(' ') << '|' << left << setw(9)
        << "Bus No"
        << setfill(' ') << '|' << setw(20) << "Name"
        << setfill(' ') << '|' << setw(20) << "No Of Seats"
        << setfill(' ') << '|' << right << setw(20)<< endl;

   cout << left << setw(10) << setfill('-') << left
       << '+' << setw(21) << setfill('-') << left << '+'
       << setw(21)
       << setfill('-') << left << '+'
       << '+'<< endl;
   if(rset) {
      while((rows = mysql_fetch_row(rset))) {
         cout << setfill(' ') << '|' << left << setw(9) << rows[0]
              << setfill(' ') << '|' << setw(20) << rows[1]
              << setfill(' ') << '|' << setw(20) << rows[2]
              << setfill(' ') << '|' << endl;
      }
      cout << left << setw(10) << setfill('-') << left
       << '+' << setw(21) << setfill('-') << left << '+'
       << setw(21)
       << setfill('-') << left << '+'
       << '+'<< endl;
   }
   mysql_free_result(rset);
}

int main()
{
	BusReservationSystem* brs = new BusReservationSystem("localhost", "root","", "busreservationsystem");
	BusReservationSystem* brs1 = new BusReservationSystem("localhost", "root","", "busreservationsystem");
	int choice;
	while(1)
	{
		cout<<"1. Login\n";
		cout<<"2. Registration\n";
		cout<<"3. Exit\n";
		cout<<"Enter Choice : ";
		cin>>choice;
		switch(choice)
		{
			case 1:
			{
				if(brs->Userlogin())
				{
					int userChoice;
					while(1)
					{
						cout<<"\n1. Show List Of Buses\n";
						cout<<"2. Book Ticket\n";
						cout<<"3. Show Ticket\n";
						cout<<"4. Logout\n";
						cout<<"Enter Choice : ";
						cin>>userChoice;
						switch(userChoice)
						{
							case 1:
							{
                                brs1->showListOfBuses();
                                break;
							}
							case 2:
							{
							    brs1->bookTicket();
                                break;
							}
							case 3:
							{
							    brs1->showticket();
								break;
							}
							case 4:
							{
							    exit(0);
								break;
							}
						}
					}
				}
				break;
			}
			case 2:
			{
				brs->registration();
                break;
			}
			case 3:
			{
				exit(0);
			}
		}
	}
	return 0;
}
