#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int minute = 0;
    int hour = 11;
    int date = 5;
    int year = 2020;
    while (1){
        minute += 1;
        if (minute == 60) {
            hour += 1;
            minute = 0;
        }
        if (hour == 24){
            date += 1;
            hour = 0;
        }
        printf("%d : %d : %d : %d\n", year, date, hour, minute);
        sleep(1);
    }
    
    return 0;
}
