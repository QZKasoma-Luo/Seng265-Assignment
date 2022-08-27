/** @file event_manager.c
 *  @brief A pipes & filters program that uses conditionals, loops, and string processing tools in C to process iCalendar
 *  events and printing them in a user-friendly format.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Juan G.
 *  @author QingZe Luo
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief The maximum line length.
 *
 */
#define MAX_LINE_LEN 132

/**
 * Function: main
 * --------------
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */

/**
 * check_argument function checks if the numbrt of
 * arguments passing in from the shell is correct
 * as start_date, end_date and the filenames
 *
 */ 
int check_iCal_argument(int arugment_number);

/**
 * struct Date includes the date, month and year
 */ 
struct Date{
	int day;
	int month;
	int year;
}Date;

/**
 * struct Time includes hour, mins, and second
 */
struct Time{

	int hour;
	int mins;
	int sec;
}Time;

/*
 * The function month_format will turn the number into
 * the corresponding month in English
 */
char *month_format(int month);

/*
 * The read_file function will open the file and read it line by line
 * until is the end of the file and pass the mathced infromation to other 
 * function and close the file in the end
 */
int read_file(char file_name[MAX_LINE_LEN], struct Date start, struct Date end);

/*
 * The date compare function will compare the time to make sure the 
 * event is going to happen in the valid time, return 0 as true, 1 as false
 */
int date_time_compare(struct Date start, struct Date end, struct Date file_s, struct Date file_end);

/*
 * The print_readable_ical function will use the infromation that passed from the
 * read_file_function to print the valid form of the event
 */
void print_readable_iCal(struct Date file_start_d,struct Time start,struct Time end, char location[MAX_LINE_LEN], char summary[MAX_LINE_LEN]);

/*The rrule_situation function will only be called when the "rrule" was matched in the read_file function
 * and print the event recursivly 
 */
void rrule_situation(struct Date file_start_d,struct Date rrule_date, struct Date end_date, struct Time start,struct Time end, char location[MAX_LINE_LEN], char summary[MAX_LINE_LEN]);

/*
 * The correct _dash_line function will print the correct number of the dash line for
 * each event
 */
void correct_dash_line(int number);

int main(int argc, char *argv[]){
    // TODO: your code
    if(check_iCal_argument(argc)){

	 struct Date start;
	 struct Date end;

	sscanf(argv[1], "--start=%d/%d/%d",&start.year, &start.month, &start.day);
        sscanf(argv[2], "--end=%d/%d/%d", &end.year, &end.month, &end.day);
	

	
	char file_name[MAX_LINE_LEN];

	sscanf(argv[3], "--file=%s", file_name);
	
	read_file(file_name,start, end);

    }else{
	
	printf("\nBash Command error :the number of arguments are not correct\n");

	  }
    return 0;
}

int check_iCal_argument(int argument_number){
	
	int key = 2;

	if(key < argument_number){
		return 1;

	}else{
		return 0;

	}	


}

char *month_format(int month){
	char month_en[10] = {};
	char *mon_pointer = month_en;
	if(month == 1){
		strcpy(month_en, "January");
	
	}else if(month == 2){
		 strcpy(month_en, "February");
		
	}else if(month == 3){
		strcpy(month_en, "March");
		
	}else if(month == 4){
		strcpy(month_en, "April");
		
	}else if(month == 5){
		strcpy(month_en, "May");
	
	}else if(month == 6){
		strcpy(month_en, "June");
		
	}else if(month == 7){
		strcpy(month_en, "July");
	
	}else if(month == 8){
		strcpy(month_en, "August");
	}else if(month == 9){
		strcpy(month_en, "September");
	}else if(month == 10){
		strcpy(month_en, "October");
	}else if(month == 11){
		strcpy(month_en, "November");
	}else{
		strcpy(month_en, "December");
	}

	return mon_pointer;

}

int read_file(char file_name[MAX_LINE_LEN], struct Date start, struct Date end){

 	char buffer[MAX_LINE_LEN];
	
	FILE *fp = fopen(file_name, "r");

	if(fp == NULL){
		printf("\nCan't Open File \n");
		return 1;
	}

	struct Date file_start_date;
        struct Time file_start_time;

	struct Date file_end_date;
	struct Time file_end_time;

	char summary[MAX_LINE_LEN];
	char location[MAX_LINE_LEN];
	memset(summary, 0,sizeof(summary));
	memset(location, 0, sizeof(location));


	int count = 0;
	char old[50];
	char new[50];


	struct Date rrule_date;
	struct Time rrule_time;

	int RRULE = 0;
	int enter = 0;

	while(fgets(buffer, MAX_LINE_LEN,fp) != NULL){


		if(strncmp(buffer,"DTSTART", 7) == 0){

			sscanf(buffer, "DTSTART:%4d%2d%2dT%2d%2d%2d", &file_start_date.year,&file_start_date.month, &file_start_date.day, &file_start_time.hour, &file_start_time.mins, &file_start_time.sec);
																 
				
				                                                 

		}
		if(strncmp(buffer, "DTEND", 5) == 0){
	 
			sscanf(buffer, "DTEND:%4d%2d%2dT%2d%2d%2d", &file_end_date.year,&file_end_date.month, &file_end_date.day, &file_end_time.hour, &file_end_time.mins, &file_end_time.sec);
	
			
		}
		                          							            											                    
		if(strncmp(buffer, "RRULE", 5) == 0){
                         
                           sscanf(buffer, "RRULE:FREQ=WEEKLY;WKST=MO;UNTIL=%4d%2d%2dT%2d%2d%2d;BYDAY=TH", &rrule_date.year,&rrule_date.month, &rrule_date.day, &rrule_time.hour, &rrule_time.mins, &rrule_time.sec);
                           RRULE = 1;
				continue;

                }				

		if((date_time_compare( start, end, file_start_date, file_end_date)) || RRULE == 1){

			
			
			if(strncmp(buffer, "LOCATION", 8) == 0){

				sscanf(buffer, "LOCATION:%[^\n]", location);
			
			

				if(location[(strlen(location))- 1] == '\n'){

					location[(strlen(location)) - 1] = '\0';
				}
				
				count++;
				continue;
				
			}


			if(strncmp(buffer, "SUMMARY", 7) == 0){
				
				sscanf(buffer, "SUMMARY:%[^\n]", summary);

				 if(location[(strlen(summary))- 1] == '\n'){

					location[(strlen(summary)) - 1] = '\0';
				 }
				 count++;

			}

			
			

			if(count == 2|| RRULE == 1){

				if(RRULE == 1){

        				rrule_situation(file_start_date,rrule_date, file_end_date, file_start_time, file_end_time, location, summary);
					RRULE = 0;
					count = 0;
					continue;
				}

				sprintf(new, "%s %02d, %d",month_format(file_start_date.month), file_start_date.day, file_start_date.year );
				if(strcmp(new, old) != 0 || enter == 1){
					 printf("\n%s %02d, %d\n",month_format(file_start_date.month), file_start_date.day, file_start_date.year);
					correct_dash_line(strlen(new));
					enter = 0;
				}

				strcpy(old, new);

				print_readable_iCal(file_start_date,file_start_time,file_end_time,location, summary);
				count = 0;

			}

		}
	}
			

			
		
			

	fclose(fp);
	return 0;
		
}


void print_readable_iCal(struct Date file_start_d,struct Time start,struct Time end, char location[MAX_LINE_LEN], char summary[MAX_LINE_LEN]){
	
	
	 if(end.hour >= 12 && start.hour >= 12){

		 if(start.hour != 12){
		 	end.hour = end.hour - 12;
			start.hour = start.hour - 12;
		 }else if(start.hour == 12){

			end.hour = end.hour - 12;
		 }
		 printf("%2d:%02d PM to %2d:%02d PM: %s {{%s}}\n",  start.hour,  start.mins, end.hour, end.mins, summary,  location);

	 }else if (end.hour < 12 && start.hour < 12){
		
		 printf("%2d:%02d AM to %2d:%02d AM: %s {{%s}}\n",  start.hour,  start.mins, end.hour, end.mins, summary,  location);

	 }else if(start.hour < 12 && end.hour >= 12){

		 if(end.hour != 12){
			end.hour = end.hour - 12;
		 }
		printf("%2d:%02d AM to %2d:%02d PM: %s {{%s}}\n",  start.hour,  start.mins, end.hour, end.mins, summary,  location);

	 }


}

int date_time_compare(struct Date start, struct Date end, struct Date file_s, struct Date file_end){

	if(start.year <= file_s.year && end.year >= file_end.year && start.month <= file_s.month && end.month >= file_end.month && start.day <= file_s.day && end.day >= file_end.day){

		return 1;


	}else{

		return 0;
	}

	
	


}

void rrule_situation(struct Date file_start_d,struct Date rrule_date, struct Date end_date, struct Time start,struct Time end, char location[MAX_LINE_LEN], char summary[MAX_LINE_LEN]){

	int freq = 7;
	struct Date start_day_copy;
	start_day_copy.day = file_start_d.day;
	char str_len[MAX_LINE_LEN];
	
	
	sprintf(str_len, "%s %02d, %d",month_format(file_start_d.month), start_day_copy.day, file_start_d.year );
	if(rrule_date.year >= file_start_d.year && rrule_date.month >= file_start_d.month && rrule_date.day >= file_start_d.day){

			while(start_day_copy.day < rrule_date.day){
				
				printf("\n%s %02d, %d\n",month_format(file_start_d.month), start_day_copy.day, file_start_d.year);
				correct_dash_line(strlen(str_len));
			

				print_readable_iCal( start_day_copy, start,end, location,  summary);
				start_day_copy.day = start_day_copy.day + freq;

			}


	}



}

void correct_dash_line(int number){


	for(int i = 0; i < number; i++){

		if(i + 1 == number){


			printf("-\n");

			break;


		}
		printf("-");



	}
}







