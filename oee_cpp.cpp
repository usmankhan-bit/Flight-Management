#include <bits/stdc++.h>
#include <fstream>

using namespace std;

int id=1;
int ttid=1;

class passenger
{
    public:
        int flypoints;
        int flightnum;
        string passName;
        string seatnum;

        passenger(int ff,int fnum,string name,string seat):flypoints(ff),flightnum(fnum),passName(name),seatnum(seat){}

        void display()
        {
            cout<<"name: "<<passName<<" Seat num : "<<seatnum<<" Flight num: "<<flightnum<<endl;
            cout<<"Fly points: "<<flypoints<<endl;
        }

};

class seat
{
    public:
        passenger *p;
        bool setAvail;
        string seatno;

        seat(string sno)
        {
            seatno=sno;
            setAvail=true;
        }

        void setPassenger(passenger *x)
        {
            p=x;
        }

        void display()
        {
            cout<<seatno<<endl;
        }


};

class luggage
{
    public:
        int kg;
        int lid;
        bool avail;

        luggage(int kkg):kg(kkg){lid=id++; avail=true;}

        void displayL()
        {
            cout<<"Luggage id: "<<lid<<"Weight: "<<kg<<endl;
        }
};

class ticket
{
    public:
        int tid;
        passenger *p;
        string seatno;

        ticket(passenger *x,string ss)
        {
            tid=ttid++;
            p=x;
            seatno=ss;
        }

};


class airplane
{
    public:
        int flightType;
        string airlineName;
        long flightNumber;
        int flyerPoint;
        string departure,arrival,depTime,arrivalTime;
        int capacity;
        int price;
        vector <seat> allSeats;
        vector <luggage> lugArr;

        void configureFlight()
        {
            cout<<"Enter the flight type"<<endl<<"1. For Passenger flight\n2. For Cargo flight"<<endl;
            cin>>flightType;

            cout<<"Enter the Airline Name"<<endl;
            cin>>airlineName;
            
            cout<<"Enter the flight Number"<<endl;
            cin>>flightNumber;
            while(!cin)
            {
                cin.clear();
                cin.ignore();
                cout<<"invalid flight number"<<endl;
                cout<<"Enter the flight number"<<endl;
                cin>>flightNumber;
            }

            cout<<"Enter the flyer points for this flight"<<endl;
            cin>>flyerPoint;

            cout<<"Enter the departure and arrival cities"<<endl;
            cin>>departure>>arrival;

            cout<<"Enter the departure time and arrival time"<<endl;
            cin>>depTime>>arrivalTime;

            cout<<"Enter the price\n";
            cin>>price;
            while(!cin)
            {
                cin.clear();
                cin.ignore();
                cout<<"invalid price"<<endl;
                cout<<"Enter the correct price"<<endl;
                cin>>price;
            }

            if(flightType==1)
            {
                cout<<"Enter the total number of seats"<<endl;
                cin>>capacity;
            }
            else if(flightType==2)
            {
                cout<<"Enter the max capacity(in kgs) for luggage"<<endl;
                cin>>capacity;
            }
            cout<<"Flight created"<<endl;
        }

        virtual void addPassengers(){}

        virtual void deletePassengers(){}

        virtual void addLuggage(){}

        virtual void removeLuggage(){}

        virtual void setSeats(){};

        virtual void displayPassengers(){}

        virtual void configure(){}

        virtual void displayLuggage(){}
};

class pflight:public airplane
{
    public:
        int rows,cols;
        int seatsOcc;

        
        void setSeats()
        {
            seatsOcc=0;
            if(airlineName=="AirIndia")
            {
                rows=8;
                cols=5;
            }
            else if(airlineName=="SpiceJet")
            {
                rows=5;
                cols=7;
            }
            else
            {
                rows=10;
                cols=7;
            }
            string colnames="ABCDEFG";
            for(int i=0;i<rows;i++)
            {
                for(int j=0;j<cols;j++)
                {
                    allSeats.push_back(seat(to_string(i+1)+colnames[j]));
                }
            }
            
        }

        void addPassengers()
        {
            string name;
            int num;
            int fp;
            
            vector<seat>::iterator it;
            for(it=allSeats.begin();it!=allSeats.end();it++)
            {
                if(it->setAvail==true)
                {
                    cout<<"Enter the passenger name"<<endl;
                    cin>>name;
                    cout<<"Enter the flight number"<<endl;
                    cin>>num;
                    cout<<"Enter the flight points"<<endl;
                    cin>>fp;
                    
                    it->setPassenger(new passenger(fp,num,name,it->seatno));
                    it->setAvail=false;
                    it->p->flypoints+=flyerPoint;
                    cout<<"Passenger added"<<endl;
                    cout<<"Note your seat no is "<<it->seatno<<endl;
                    break;
                }
            }
                
            
            
            
        }

        void deletePassengers()
        {
            string nname,ssname;
            cout<<"Enter the passenger name"<<endl;
            cin>>nname;
            cout<<"Enter the seat number"<<endl;
            cin>>ssname;

            vector<seat>::iterator it;
            for(it=allSeats.begin();it!=allSeats.end();it++)
            {
                if(it->seatno==ssname)
                {
                    it->setAvail=true;
                    it->p->flypoints-=flyerPoint;
                    delete it->p;
                    cout<<"Passenger deleted"<<endl;
                    break;
                    
                }
            }
            
        }

        void displayPassengers()
        {
            vector<seat>::iterator it;
            cout<<"seat no."<<"\t"<<"name"<<endl;
            for(it=allSeats.begin();it!=allSeats.end();it++)
            {
                if(it->setAvail==false)
                {
                    cout<<it->seatno<<"\t\t"<<it->p->passName<<endl;
                }
            }
        }



};

class cflight:public airplane
{
    public:
        int tempkg;
        cflight()
        {
            tempkg=0;
        }

        void configure()
        {
            for(int i=0;i<50;i++)
                lugArr.push_back(luggage(0));
            
        }
        void addLuggage()
        {
            int temp;
            cout<<"Enter the weight of your luggage\n";
            cin>>temp;
            temp+=tempkg;
            vector<luggage>::iterator it;
            if(tempkg<capacity)
            {
                for(it=lugArr.begin();it!=lugArr.end();it++)
                {
                    if(it->avail==true)
                    {
                        it->kg=temp;
                        it->avail=false;
                        cout<<"Luggage added\n";
                        cout<<"Please note your luggage id: "<<it->lid<<endl;
                        break;
                    }
                }
            }
            else{
                cout<<"Cargo plane full\n";
            }
        }

        void removeLuggage()
        {
            int iid;
            cout<<"Enter the luggage id\n";
            cin>>iid;
            vector<luggage>::iterator it;
            for(it=lugArr.begin();it!=lugArr.end();it++)
            {
                if(it->lid==iid&&it->avail==false)
                {
                    it->avail=true;
                    cout<<"Luggage deleted\n";
                    break;
                }
            }
        }

        void displayLuggage()
        {
            vector<luggage>::iterator it;
            cout<<"Luggageid\tweight\n";
            for(it=lugArr.begin();it!=lugArr.end();it++)
            {
                if(it->avail==false)
                {
                    cout<<it->lid<<"\t\t"<<it->kg<<endl;
                }
                
            }
        }

};


int main()
{
   /*
   airplane *a=new pflight();
   a->configureFlight();
   //a=new pflight();
   a->setSeats();
   a->addPassengers();
   a->displayPassengers();
   a->deletePassengers();
   a->displayPassengers();
   */
  /*
  airplane *a=new cflight();
  a->configureFlight();
  a->configure();
  a->addLuggage();
  a->displayLuggage();
  a->removeLuggage();
  a->displayLuggage();
  */

  list <airplane *> airarr;

  int val,flag,choice,fnotemp,flag2;
  int userflag,ufno,utemp,ulid;
  string utno;
  while(1)
  {
    try
    {
      string password="helloWorld";
      string passc;
      cout<<"Enter 1 for user and 2 for manager\n";
      cin>>val;
      if(val>2 || val <1)
        throw "Invalid Choice";
      if(val==2)
      {
          while(1)
          {
              cout<<"Enter password\n";
              cin>>passc;
              if(password!=passc)
              {
                cout<<"Incorrect password"<<endl;
              }
              else
              {
                  break;
              }
              
          }
          while(1)
          {
            list<airplane *>::iterator loop;
            int ccount;
            cout<<"Welcome to Flight Management System\n";
            cout<<"-------------------------------------\n";
            cout<<"1. Add Flights"<<endl;
            cout<<"2. Change Flight parameters"<<endl;
            cout<<"3. Delete Flight"<<endl;
            cout<<"4. Print all the flights"<<endl;
            cout<<"5. Get passengers List"<<endl;
            cout<<"6. Export flight details"<<endl;
            cout<<"7. Logout as manager"<<endl;
            cin>>flag;
            list<airplane *>::iterator search;
            
            if(flag==1)
            {
                cout<<"Enter\n1 for passenger flight\n2 for cargo flight\n";  
                cin>>choice;
                if(choice==1)
                {
                    airarr.push_back(new pflight());
                }
                else if(choice==2 )
                {
                    airarr.push_back(new cflight());
                }
                airarr.back()->configureFlight();
                if(choice==1)
                {
                    airarr.back()->setSeats();
                }
                else if(choice==2 )
                {
                    airarr.back()->configure();
                }             
            }
            else if(flag==2)
            {
                cout<<"Enter the flight number you want to change\n";
                cin>>fnotemp; 
                ccount=0;
                for(search=airarr.begin();search!=airarr.end();search++)
                {
                    ccount++;
                    if((*search)->flightNumber==fnotemp)
                    {
                        cout<<"Enter the field which you want to change\n";
                        cout<<"1. Destination city and Departure city"<<endl;
                        cout<<"2. Flight number"<<endl;
                        cout<<"3. Arrival time and Departure time"<<endl;
                        cout<<"4. Flyer points"<<endl;
                        cin>>flag2;
                        switch(flag2)
                        {
                            case 1: cin>>(*search)->arrival>>(*search)->departure;
                                    break;
                            case 2: cin>>(*search)->flightNumber;
                                    break;
                            case 3: cin>>(*search)->arrivalTime>>(*search)->depTime;
                                    break;
                            case 4: cin>>(*search)->flyerPoint;
                                    break;

                        }
                        break;
                    }
                    if(ccount==airarr.size())
                    {
                        cout<<"Flight number doesnt exists\n";
                    }
                }            
            }
            else if(flag==3)
            {
                ccount=0;
                cout<<"----------------------------"<<endl;
                cout<<"Enter the flight number you want to delete"<<endl;
                cin>>fnotemp;
                for(search=airarr.begin();search!=airarr.end();search++)
                {
                    ccount++;
                    if((*search)->flightNumber==fnotemp)
                    {
                        airarr.erase(search);
                        cout<<"Flight deleted\n";
                        break;
                    }
                    
                }
                if(ccount==airarr.size())
                    {
                        cout<<"Flight number doesnt exists\n";
                    }

            }
            else if(flag==4)
            {
                cout<<"****************************"<<endl;
                if(airarr.size()==0)
                    {
                        cout<<"No flights"<<endl;
                    }else{
                cout<<"The flights operations are"<<endl;
                cout<<"Flight number\tAirline \tDepcity \tArrcity \tDeptime \tArrtime \tprice \n";


                for(loop=airarr.begin();loop!=airarr.end();loop++)
                {
                    
                    cout<<(*loop)->flightNumber<<"\t\t"<<(*loop)->airlineName<<"\t\t"<<(*loop)->departure
                        <<"\t\t"<<(*loop)->arrival<<"\t\t"<<(*loop)->depTime<<"\t\t"<<(*loop)->arrivalTime<<"\t\t"<<(*loop)->price<<endl;
                }
                cout<<"*********************************"<<endl;}
                        
            }
            else if(flag==5)
            {
                ccount=0;
                cout<<"Enter the flight number\n"<<endl;
                cin>>fnotemp;
                //'list<airplane *>::iterator search;
                for(loop=airarr.begin();loop!=airarr.end();loop++)
                {
                    ccount++;
                    if((*loop)->flightNumber==fnotemp)
                    {
                        if((*loop)->flightType==1)
                        {
                            (*loop)->displayPassengers();
                            break;

                        }
                        else
                        {
                            (*loop)->displayLuggage();
                            break;
                        }
                    }
                }
                if(ccount==airarr.size())
                    {
                        cout<<"Flight number doesnt exists\n";
                    }
            
            }
            else if(flag==6)
            {
                ofstream file;
                file.open("flights.txt");
                file<<"Flight number\tAirline \tDepcity \tArrcity \tDeptime \tArrtime \tprice \n";
                for(loop=airarr.begin();loop!=airarr.end();loop++)
                {
                        file<<(*loop)->flightNumber<<"\t\t"<<(*loop)->airlineName<<"\t\t"<<(*loop)->departure
                        <<"\t\t"<<(*loop)->arrival<<"\t\t"<<(*loop)->depTime<<"\t\t"<<(*loop)->arrivalTime<<"\t\t"<<(*loop)->price<<endl;
                }
                cout<<"File written successfully"<<endl;
                file.close();
                    
            }
            else if(flag==7)
            {
                cout<<"You are logged out"<<endl;
                break;
            }

          }    
            
             
              
                      

        }
        else if(val==1)
        {
            list<airplane *>::iterator userit;
            int dcount;
            while(1)
            {   
              try
              {
                cout<<"---------------------------------"<<endl;
                cout<<"Welcome to Flight Booking System"<<endl;
                cout<<"Flight bookings made simple"<<endl;
                cout<<"1. Book Tickets"<<endl;
                cout<<"2. Cancel booking"<<endl;
                cout<<"3. Display Ticket details"<<endl;
                cout<<"4. Know your flyer points"<<endl;
                cout<<"---------------------------------"<<endl;
                cout<<"The flights operational are"<<endl;
                cout<<"Flight number \tAirline \tDepcity \tArrcity \tDeptime \tArrtime \tprice \n";
            
                for(userit=airarr.begin();userit!=airarr.end();userit++)
                {
                    cout<<(*userit)->flightNumber<<"\t\t"<<(*userit)->airlineName<<"\t\t"<<(*userit)->departure
                    <<"\t\t"<<(*userit)->arrival<<"\t\t"<<(*userit)->depTime<<"\t\t"<<(*userit)->arrivalTime<<"\t\t"<<(*userit)->price<<endl;
                }                
                cin>>userflag;
                if(userflag>4 || userflag<0)
                {
                    throw "Invalid Choice";
                }
                
                
                cout<<"Enter 1. for passenger flight and 2. for cargo flight"<<endl;
                cin>>utemp;
                cout<<"enter the flight number"<<endl;
                cin>>ufno;
                dcount=0;
                if(userflag==1)
                {
                    for(userit=airarr.begin();userit!=airarr.end();userit++)
                    {
                        dcount++;
                        if((*userit)->flightNumber==ufno)
                        {
                            if(utemp==1)
                            {
                                (*userit)->addPassengers();
                                break;
                            }
                            else
                            {
                                (*userit)->addLuggage();
                                break;
                            }
                        }
                    }
                    if(dcount==airarr.size())
                    {
                        cout<<"Flight doesnt exists"<<endl;
                    }

                }
                else if(userflag==2)
                {
                    dcount=0;
                    for(userit=airarr.begin();userit!=airarr.end();userit++)
                    {
                        dcount++;
                        if((*userit)->flightNumber==ufno)
                        {
                            if(utemp==1)
                            {
                                (*userit)->deletePassengers();
                                break;
                            }
                            else if(utemp==2)
                            {
                                (*userit)->removeLuggage();
                                break;
                            }
                        }
                    }
                    if(dcount==airarr.size())
                    {
                        cout<<"Flight doesnt exists"<<endl;
                    }

                }
                else if(userflag==3)
                {

                    for(userit=airarr.begin();userit!=airarr.end();userit++)
                    {
                        if((*userit)->flightNumber==ufno)
                        {
                            if(utemp==1)
                            {
                                cout<<"Enter seat number"<<endl;
                                cin>>utno;
                                vector<seat> ::iterator useat;
                                for(useat=(*userit)->allSeats.begin();useat!=(*userit)->allSeats.end();useat++)
                                {
                                    if(useat->seatno==utno)
                                    {
                                        useat->p->display();
                                        break;
                                    }
                                }
                                break;
                            }
                            else if (utemp==2)
                            {
                                cout<<"Enter luggage id"<<endl;
                                cin>>ulid;
                                vector<luggage> ::iterator uluggage;
                                for(uluggage=(*userit)->lugArr.begin();uluggage!=(*userit)->lugArr.end();uluggage++)
                                {
                                    if(uluggage->lid==ulid)
                                    {
                                        uluggage->displayL();
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
                else if(userflag==4)
                {
                    for(userit=airarr.begin();userit!=airarr.end();userit++)
                    {
                        if((*userit)->flightNumber==ufno)
                        {
                            if(utemp==1)
                            {
                                cout<<"Enter seat number"<<endl;
                                cin>>utno;
                                vector<seat> ::iterator useat;
                                for(useat=(*userit)->allSeats.begin();useat!=(*userit)->allSeats.end();useat++)
                                {
                                    if(useat->seatno==utno)
                                    {
                                        cout<<"Your fly points are: "<<useat->p->flypoints<<endl;
                                        break;
                                    }
                                }
                            }
                            break;
                            
                        }
                    }                   
                }
              }
                catch(const char * error)
                {
                    cout<<error<<endl;
                }
            } 
         
        
 


        }
    } 
    catch(const char * msg)
    {
        cout<<msg<<endl;
    }
 }
  



}
