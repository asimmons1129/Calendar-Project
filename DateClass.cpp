#include <iostream>
using namespace std;

class Date{
    private:
    int month, day, year;
    public:
    Date(){month=1; day=1; year=1753;}
    void setMonth(int m){month=m;}
    void setDay(int d){day=d;}
    void setYear(int y){year=y;}
    int getMonth(){return month;}
    int getDay(){return day;}
    int getYear(){return year;}
    void printDate(){
        if(month<10 && day<10){
            cout<<"\nDate(mm=dd=yyyy): 0"<<month<<"-0"<<day<<"-"<<year<<"\n\n";
        }
        else if(month<10 && day>10){
            cout<<"\nDate(mm=dd=yyyy): 0"<<month<<"-"<<day<<"-"<<year<<"\n\n";
        }
        else if(month>10 && day<10){
            cout<<"\nDate(mm=dd=yyyy): "<<month<<"-0"<<day<<"-"<<year<<"\n\n";
        }else{
            cout<<"\nDate(mm=dd=yyyy): "<<month<<"-"<<day<<"-"<<year<<"\n\n";
        }
    }
    void printMonthName(){
        string d;
        const char*m[12]={"January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"};
        d=getDayName(day,month,year);
        cout<<d<<","<<m[month-1]<<" "<<day<<","<<year<<"\n\n";
    }
    string getDayName(int d,int m, int y){
        int a=0;
        int months[12]={31,28,31,30,31,30,31,31,30,31,30,31};
        string week[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        if((y%400==0)||((y%4==0)&&(y%100!=0))){
            months[1]=29;
        }
        a=(d+=m<3?y--:y-2,23*m/9+d+4+y/4-y/100+y/400)%7;
        return week[a];
    }
    Date operator-(Date d2);
    Date operator++();
    Date operator--();
    bool leapYear(){
        if((year%400==0)||((year%4==0) && (year%100!=0))){
            return true;
        }else{
            return false;
        }
    }
    void dayIntoYear(){
        int currentDay=day+((month<3)?(int)((306*month-301)/10):(int)((306*month-913)/10)+((year%4==0 && (year%100!=0||year%400==0))?60:59));
        cout<<currentDay<<" days have passed this year.\n\n";
    }
    void daysRemaining(){
        int currentDay=day+((month<3)?(int)((306*month-301)/10):(int)((306*month-913)/10)+((year%4==0 && (year%100!=0||year%400==0))?60:59));
        int daysLeft;
        if(year%400==0||((year%4==0) &&(year%100!=0))){
            daysLeft=366-currentDay;
        }else{
            daysLeft=365-currentDay;
        }
        cout<<"There are "<<daysLeft<<" days remaining this year.\n\n";
    }
    int getTotalDays(){
        int totalDays;
        if(month==1||month==2){
            month+=12;
            year-=1;
        }
        totalDays=365*year+year/4-year/100+year/400+day+(153*month+8)/5;
        return totalDays;
    }
    Date futureDate(int n){
        for(int i=0;i<n;i++){
            operator++();
        }
        return *this;
    }
    Date pastDate(int n){
        for(int i=0;i<n;i++){
            operator--();
        }
        return *this;
    }
    int dayNumber(){
        static int t[]={0,3,2,5,0,3,5,1,5,6,2,4};
        year-=month<3;
        return (year+year/4-year/100+year/400+t[month-1]+day)%7;
    }
    void printCalendar(){
        const char*m[12]={"January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"};
        int months[12]={31,28,31,30,31,30,31,31,30,31,30,31};
        if((year%400==0)||((year%4==0)&&(year%100!=0))){
            months[1]=29;
        }
        cout<<"-----------"<<m[month-1]<<","<<year<<"------------ \n\n";
        cout<<" Sun  Mon  Tue  Wed  Thu  Fri  Sat \n";
        int current=dayNumber();
        int k;
        for (k = 0; k < current; k++)
            cout << "     ";
        for (int j = 1; j <= months[month-1]; j++)
        {
            printf("%5d", j);
            if (++k > 6)
            {
                k = 0;
                printf("\n");
            }
        }
        if (k)
            printf("\n");
        current = k;
        return;
    }
};

Date Date::operator-(Date d2){
    Date diff;    
    diff.day=abs(getTotalDays()-d2.getTotalDays());
    return diff;
    }

Date Date::operator++(){
        if(day==31 && (month==1||month==3||month==5||month==7||month==8||month==10||month==12)){
            day-=30;
            if(month==12){
                month-=11;
            }else{
                month++;
            }
            if(month==1){
                year+=1;
            }
        }
        else if(day==30 && (month==4||month==6||month==9||month==11)){
            day-=29;
            month++;
        }
        else if(day==29 && month==2){
            day-=28;
            month++;
        }
        else if(day==28 && month==2 && year%4!=0){
            day-=27;
            month++;
        } else{
            day++;
        }
        return *this;
    }

Date Date::operator--(){
        if(day==1){
            if(month==5||month==7||month==8||month==10||month==12)
            {
                day+=29;
                month-=1;
            }
            else if(month==2||month==4||month==6||month==9||month==11)
            {
                day+=30;
                month-=1;
            }
            else if(month==3)
            {
                if(year%400==0||(year%4==0 && year%100!=0)){
                    day+=28;
                    month-=1;
                }else{
                    day+=27;
                    month-=1;
                }
            }
            else if(month==1)
            {
                month+=11;
                day+=30;
                year-=1;
            }
        }else{
            day--;
        }
        return *this;
    }

void displayMenu(){
    cout<<"-------------------------------------------------------\n";
    cout<<"             CALENDAR APPLICATION MENU\n";
    cout<<"-------------------------------------------------------\n";
    cout<<"A) Set Date\n";
    cout<<"B) Display Date (mm-dd-yyyy)\n";
    cout<<"C) Display Date (Weekday, Month, Day, Year)\n";
    cout<<"D) Display Future Date\n";
    cout<<"E) Display Previous Date\n";
    cout<<"F) Number Of Days Passed In Current Year\n";
    cout<<"G) Number Of Days Remaining In Current Year\n";
    cout<<"H) Compare Dates\n";
    cout<<"I) Increment Current Date\n";
    cout<<"J) Decrement Current Date\n";
    cout<<"K) Display Monthly Calendar\n";
    cout<<"L) Exit The Calendar\n\n";
    cout<<"Enter your choice: ";
}

int main(){

    Date d1,d2,diff;
    int m, d, y, M1, D1, Y1, numDays;
    char choice;
    system("clear");
    cout<<"\n\n\n\n\n\n\n";

    do{
        displayMenu();
        cin>>choice;
        while(toupper(choice)<'A'||toupper(choice)>'L')
        {
            cout<<"Please make a choice in the range of A through L: ";
            cin>>choice;
        }

        switch(choice)
        {
            case 'a':
            case 'A': system("clear");
                      cout<<"Choose a year: ";
                      cin>>y;
                      while(y<1753){
                        cout<<"Please type a valid year: ";
                        cin>>y;
                      }
                      d1.setYear(y);
                      cout<<"Choose a month: ";
                      cin>>m;
                      while(m>12||m<1){
                        cout<<"Please type a valid month: ";
                        cin>>m;
                      }
                      d1.setMonth(m);
                      cout<<"Choose a day: ";
                      cin>>d;
                      if(m==1||m==3||m==5||m==7||m==8||m==10||m==12){
                          while(d>31||d<1){
                              cout<<"Please type a valid day: ";
                              cin>>d;
                          }
                      }
                      if(m==4||m==6||m==9||m==11){
                          while(d>30||d<1){
                              cout<<"Please type a valid day: ";
                              cin>>d;
                          }
                      }
                      if((y%400==0)||((y%4==0)&&(y%100!=0))){
                          if(m==2){
                              while(d>29||d<1){
                                  cout<<"Please type a valid day: ";
                                  cin>>d;
                              }
                          }
                      }
                      if((y%4)!=0){
                          if(m==2){
                              while(d>28||d<1){
                                  cout<<"Please type a valid day: ";
                                  cin>>d;
                              }
                          }
                      }
                      d1.setDay(d);
                      cout<<"Done!\n\n";
                      break;
            case 'b':
            case 'B': system("clear");
                      d1.printDate();
                      break;
            case 'c':
            case 'C': system("clear");
                      cout<<"Date: ";
                      d1.printMonthName();
                      break;
            case 'd':
            case 'D': system("clear");
                      cout<<"Choose a number of days to add: ";
                      cin>>numDays;
                      d1.futureDate(numDays);
                      cout<<"The date in "<<numDays<<" days will be: \n";
                      d1.printMonthName();
                      cout<<"\n\n";
                      break;
            case 'e':
            case 'E': system("clear");
                      cout<<"Choose a number of days to subtract: ";
                      cin>>numDays;
                      d1.pastDate(numDays);
                      cout<<"The date "<<numDays<<" days ago was: \n";
                      d1.printMonthName();
                      cout<<"\n\n";
                      break;
            case 'f':
            case 'F': system("clear");
                      d1.dayIntoYear();
                      break;
            case 'g':
            case 'G': system("clear");
                      d1.daysRemaining();
                      break;
            case 'h':
            case 'H': system("clear");
                      cout<<"Choose a year: ";
                      cin>>Y1;
                      while(Y1<1753){
                        cout<<"Please type a valid year: ";
                        cin>>Y1;
                      }
                      d2.setYear(Y1);
                      cout<<"Choose a month: ";
                      cin>>M1;
                      while(M1>12||M1<1){
                        cout<<"Please type a valid month: ";
                        cin>>M1;
                      }
                      d2.setMonth(M1);
                      cout<<"Choose a day: ";
                      cin>>D1;
                      if(M1==1||M1==3||M1==5||M1==7||M1==8||M1==10||M1==12){
                          while(D1>31||D1<1){
                              cout<<"Please type a valid day: ";
                              cin>>D1;
                          }
                      }
                      if(M1==4||M1==6||M1==9||M1==11){
                          while(D1>30||D1<1){
                              cout<<"Please type a valid day: ";
                              cin>>D1;
                          }
                      }
                      if((Y1%400==0)||((Y1%4==0)&&(Y1%100!=0))){
                          if(M1==2){
                              while(D1>29||D1<1){
                                  cout<<"Please type a valid day: ";
                                  cin>>D1;
                              }
                          }
                      }
                      if((Y1%4)!=0){
                          if(M1==2){
                              while(D1>28||D1<1){
                                  cout<<"Please type a valid day: ";
                                  cin>>D1;
                              }
                          }
                      }
                      d2.setDay(D1);
                      diff=d1-d2;
                      if((y==Y1&&(m<M1||(m==M1 && d<D1)))||y<Y1){
                          cout<<"The date entered will be reached in "<<diff.getDay()<<" days!\n\n";
                      }else{
                          cout<<"The date entered has passed "<<diff.getDay()<<" days ago!\n\n";
                      }
                      break;
            case 'i':
            case 'I': system("clear");
                      ++d1;
                      cout<<"The next day is:\n";
                      d1.printMonthName();
                      break;
            case 'j':
            case 'J': system("clear");
                      if((d1.getYear()==1753) && (d1.getDay()==1) && (d1.getMonth()==1)){
                        cout<<"Date could not be decremented!\n";
                      }else{
                        --d1;
                        cout<<"The previous day was:\n";
                        d1.printMonthName();
                      }
                      break;
            case 'k':
            case 'K': system("clear");
                      d1.setDay(1);
                      d1.setMonth(1);
                      d1.setYear(1753);
                      cout<<"Choose a month: ";
                      cin>>m;
                      while(m>12||m<1){
                        cout<<"Please type a valid month: ";
                        cin>>m;
                      }
                      d1.setMonth(m);
                      cout<<"Choose a year: ";
                      cin>>y;
                      while(y<1753){
                        cout<<"Please type a valid year: ";
                        cin>>y;
                      }
                      d1.setYear(y);
                      cout<<"\n\n";
                      d1.printCalendar();
                      break;
        }

    } while(toupper(choice)!='L');
    cout<<"Goodbye! \n";
    return 0;
}