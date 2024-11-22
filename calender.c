#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
int anchor_day(int);
int doomsDay_date(int,int);
int leap_year(int);
char *month_day_words(int,int);
int day_of_week(int,int,int);
void print_calender(int,int);
int ends_on(int,int);
void print_year(int);
void today(void);

void author(){
    printf("\n__________________________________Author: Mark Emmanuel_________________________________");
}

int main(void){
    int day,date,month,year,option;
    printf("<-------------------------------------Options------------------------------------>\n");
    printf("\n1. Find day of the week\n");
    printf("2. Print a Months's Calender\n");
    printf("3. Print a Year's Calender\n");
    printf("4. When is Today\n");
    printf("\n____________________________________Enter Choice__________________________________\n");
    printf("\t\nChoice(1,2,3 or 4): ");
    scanf("%d",&option);
    if(option == 1){
        printf("\nEnter the Date(DD MM YY): ");
        scanf("%d %d %d",&date,&month,&year);
        day = day_of_week(date,month,year);
        printf("\t%d of %s %d is on a %s",date,month_day_words(-1,month),year,month_day_words(day,month));
        author();
    }else if(option == 2){
        date = 1;
        printf("Enter the Month and Year(MM YY): ");
        scanf("%d %d",&month,&year);
        day = day_of_week(date,month,year);
        printf("\n\t%s %d Calender\n\n",month_day_words(-1,month));
        print_calender(day,ends_on(month,year));
        author();
    }else if(option == 3){
        printf("\nEnter the Year: ");
        scanf("%d",&year);
        print_year(year);
        author();
    }else if(option == 4){
        today();
    }else{
        printf("Invalid Choice ");
    }
    return 0;
}

void today(void){
    SYSTEMTIME date;
    GetLocalTime(&date);
    printf("\nToday is %s %d %s %d\n\n",month_day_words(day_of_week(date.wDay,date.wMonth,date.wYear),-1),date.wDay,month_day_words(-1,date.wMonth),date.wYear);
    printf("\t%s %d\n",month_day_words(-1,date.wMonth),date.wYear);
    print_calender(day_of_week(date.wDay,date.wMonth,date.wYear),ends_on(date.wMonth,date.wYear));
    author();
}

void print_year(int year){
    for(int i = 1; i <= 12; i++){
            int day = day_of_week(1,i,year);
            int end = ends_on(i,year);
            printf("\n");
            printf("\t%s %d\n",month_day_words(-1,i),year);
            print_calender(day,end);
            printf("\n");
    }
}

void print_calender(int day,int end){
    int date = 0;
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 3; j++){
            printf("%c",month_day_words(i,-1)[j]);
        }
        printf("  ");
    }
    printf("\n");
   for(int i = 0; i < 5; i++){
        for(int j = 0; j < 7; j++){
            if(date == end){
                return;
            }
            if(j < day){
                printf("     ");
            }else{
                printf("%2d   ",++date);
                day = -1;
            }
        }
        printf("\n");
   }
}

int day_of_week(int date,int month,int year){
    static int day;
    int Q,R,P;
    int last2 = year - ((year/100) * 100);
    Q = last2 / 12;
    R = last2 % 12;
    P = R / 4;
    
    int doomsDay = anchor_day(year) + Q + R + P;
    int difference = abs(date - doomsDay_date(month,year));
    if(doomsDay_date(month,year) - date > 0){
        day = (doomsDay - difference) % 7;
    }else if(doomsDay_date(month,year) - date < 0){
        day = (doomsDay + difference) % 7;
    }else{
        day = doomsDay % 7;
    }
    while(day < 0){
        day += 7;
    }
    return day;
}

int anchor_day(int year){
    int sequence[] = {10,11,12,13};
    for(int i = 0; i < 4; i++){
        if(((year/100) - sequence[i]) % 4 == 0){
            if(i == 0){
                return 5;
            }else if(i == 1){
                return 3;
            }else if(i == 2){
                return 2;
            }else{
                return 0;
            }
        }
    }
}

int leap_year(int year){
    if((year % 4 == 0) && year % 100 != 0){
            return 1;
        }else if(year % 4 == 0 && year % 100 == 0 && year % 400 == 0){
            return 1;
        }else{
            return 0;
        }
}

int doomsDay_date(int month,int year){
    int dates[] = {3,28,14,4,9,6,11,8,5,10,7,12};
    if(month == 1 || month == 2){
        if(leap_year(year)){
            return ++dates[month-1];
        }else{
            return dates[month-1];
        }
    }
    return dates[month-1];
}
char *month_day_words(int day,int month){
    char *months[] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
    char *days[] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
    if(day == -1){
        return months[month-1];
    }else{
        return days[day];
    }
}

int ends_on(int month,int year){
    if(month == 2){
        if(leap_year(year)){
            return 29;
        }else{
            return 28;
        }
    }else if(month == 9 || month == 4 || month == 6 || month == 11){
        return 30;
    }else{
        return 31;
    }
}