/** @file song_analyzer.c
 *  @brief A small program to analyze songs data.
 *  @author Mike Z.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Juan G.
 *  @author STUDENT_NAME
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define MAX_LINE_LEN 80

/**
 * @brief Serves as an incremental counter for navigating the list.
 *
 * @param p The pointer of the node to print.
 * @param arg The pointer of the index.
 *
 */
void inccounter(node_t *p, void *arg){
    int *ip = (int *)arg;
    (*ip)++;
}

/**
 * @brief Allows to print out the content of a node.
 *
 * @param p The pointer of the node to print.
 * @param arg The format of the string.
 *
 */
void print_node(node_t *p, void *arg){
    char *fmt = (char *)arg;
    printf(fmt, p->artist);
}

/**
 * @brief Allows to print each node in the list.
 *
 * @param l The first node in the list
 *
 */
void analysis(node_t *l){
    int len = 0;
    apply(l, inccounter, &len);
    printf("Number of words: %d\n", len);
    apply(l, print_node, "%s\n");
}
/**
 * @brief free the space of the linked list
 *
 * @param head The first node in the list
 *
 */
void free_linked_list(node_t* head){
    node_t* buffer;
   while (head != NULL){
       buffer = head;//make the buffer equal to the head to make sure we can access the next node
       head = head->next;//head become the next node
       free(buffer);
    }
}
/**
 * structure argc_information is to save all the passed in command arguments
 */
struct argc_information{
    char file_name[MAX_LINE_LEN];
    int display;
    char sort_method[MAX_LINE_LEN];
}argc_information;
/**
 * structure song_info is a tmp pocketto save all the information of one song
 */
struct song_info{
    char *artist;
    int popularity;
    char *song;
    int year;
    double energy;
    double danceability;
}song_info;
/**
 * @brief fetch the command args and save into argc_information type variable.
 *
 * @param argv The argv array
 *
 */
struct argc_information fetch_the_info(char *argv[]){
    struct argc_information info;//To crate a agrc_info type variable to save the data and return
    char buffer[MAX_LINE_LEN];// The command line arguments are all string type, save the display in string buffer
    strncpy(info.sort_method, argv[1]+9, MAX_LINE_LEN);//strnpy will pipe the data in to the destiantion variable after the given index
    strncpy(buffer, argv[2]+10, MAX_LINE_LEN);
    strncpy(info.file_name, argv[3]+8, MAX_LINE_LEN);
    info.display = atoi(buffer);//Use the atoi() from <stdlib.h> to save the int type display to the info.display
    return info;
}
/**
 * @brief will read the file and put the song in sorted order in to a linked_list
 *
 * @param file the file name
 * @param linked_list the list will save the songs
 * @param sort_method the sort method of the list
 *
 */
node_t* read_file(char* file, node_t* linked_list, char* sort_method){
    FILE *fp = fopen(file, "r");
    int extend_max_line_len = 10 * MAX_LINE_LEN;//the constant MAX_LINE_LEN is not large enough
    char* txt_line_pointer;//use to count once a line
    struct song_info pocket_for_node;//temp space to save a song info that will be save in the node 
    txt_line_pointer = (char*)malloc(sizeof(char) * extend_max_line_len);
    fgets(txt_line_pointer, extend_max_line_len, fp);//To skip the first subjects name line
    while(fgets(txt_line_pointer, extend_max_line_len, fp) != NULL){
        char all_content_copy[extend_max_line_len];
        strcpy(all_content_copy,txt_line_pointer);
        char* rest_info = all_content_copy;
        char* one_line_token;
        int colmun_fetch_counter = 0;//To check is the one_line_token at the column we need to fetch the information 
        while((one_line_token = strtok_r(rest_info, ",", &rest_info))){
            switch(colmun_fetch_counter){//fecth the information at the specific column
                case 0:
                    pocket_for_node.artist = one_line_token;
                    break;
                case 1:
                    pocket_for_node.song = one_line_token;
                    break;
                case 5:
                    pocket_for_node.popularity = atoi(one_line_token);
                    break;
                case 7:
                    pocket_for_node.energy = atof(one_line_token);
                    colmun_fetch_counter = 0;//when the case 7 is triggered, all the info we need for this line of the song have gotten, reset the counter to 0
                    node_t *node = new_node(pocket_for_node.artist, pocket_for_node.popularity, pocket_for_node.song, pocket_for_node.year, pocket_for_node.energy, pocket_for_node.danceability);//pipe the info in the pocket to a new node
                    linked_list = add_inorder(linked_list, node, sort_method);//add the new node to the linked_list and resort the linked list
                    break;
                case 4:
                    pocket_for_node.year = atoi(one_line_token);
                    break;
                case 6:
                    pocket_for_node.danceability = atof(one_line_token);
                    break;
            }
            colmun_fetch_counter++;
        }

    }
    free(txt_line_pointer);
    fclose(fp);
    return linked_list;

}
/**
 * @brief will generate a csv file within the display numbers of the song by the sort method
 * @param sorted_link_list the sorted linked list
 * @param display the number of the song needs to be displayed
 * @param sort_method the sort method of the list
 *
 */
void generate_csv_file(node_t *sorted_link_list, int display, char* sort_method){
    FILE* output = fopen("output.csv", "w");
    fprintf(output, "%s,%s,%s,%s\n","artist", "song","year", sort_method);//generate the first line of the subject in the file
    node_t *sorted_link_list_copy = sorted_link_list;//make a copy of the linked list to make sure the orign list won't be modefied
    if(strcmp(sort_method, "popularity") == 0){
        for(int i = 0; i < display; i++){
            fprintf(output, "%s,%s,%d,%d\n", sorted_link_list_copy->artist, sorted_link_list_copy->song, sorted_link_list_copy->year, sorted_link_list_copy->popularity);
            sorted_link_list_copy = sorted_link_list_copy->next;
        }

    }
    if(strcmp(sort_method, "energy") == 0){
        for(int i = 0; i < display; i++){
            fprintf(output, "%s,%s,%d,%g\n", sorted_link_list_copy->artist, sorted_link_list_copy->song, sorted_link_list_copy->year, sorted_link_list_copy->energy);
            sorted_link_list_copy = sorted_link_list_copy->next;
        }

    }
    if(strcmp(sort_method, "danceability") == 0){
        for(int i = 0; i < display; i++){
            fprintf(output, "%s,%s,%d,%g\n", sorted_link_list_copy->artist, sorted_link_list_copy->song, sorted_link_list_copy->year, sorted_link_list_copy->danceability);
            sorted_link_list_copy = sorted_link_list_copy->next;
        }
        
    }
    fclose(output); 
}


/**
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int main(int argc, char *argv[]){
    if(argc < 4){
        printf("The command is not correct\n");
        return 1;
    }else{
        struct argc_information args_info = fetch_the_info(argv);//fetch the command arguments into one type
        char file_names_copy[MAX_LINE_LEN];
        strcpy(file_names_copy,args_info.file_name);
        char* rest_line = file_names_copy;
        char* file_name_token;
        node_t* sorted_song_list = NULL;
        int count = 0;
        while((file_name_token = strtok_r(rest_line, ",", &rest_line))){//read the file name once a time 
            sorted_song_list = read_file(file_name_token, sorted_song_list, args_info.sort_method);
            count++;
        }
       generate_csv_file(sorted_song_list, args_info.display, args_info.sort_method);
       free_linked_list(sorted_song_list);//free the list we crated in the end

    }
    exit(0);
}
