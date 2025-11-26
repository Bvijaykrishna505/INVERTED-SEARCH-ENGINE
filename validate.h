#ifndef VALIDATE_H // Header guard start
#define VALIDATE_H // Define header guard

#include<stdio.h> // Standard input/output library
#include<stdlib.h> // Standard library for memory allocation
#include<stdarg.h> // Variable argument macros
#include<string.h> // String manipulation functions
#include<ctype.h> // Character classification functions

#define SUCCESS 0 // Success status code
#define FAILURE -1 // Failure status code

// ANSI Color codes for terminal output
#define COLOR_RESET "\033[0m" // Reset color
#define COLOR_RED "\033[1;31m" // Red color for errors
#define COLOR_GREEN "\033[1;32m" // Green color for success
#define COLOR_YELLOW "\033[1;33m" // Yellow color for warnings
#define COLOR_BLUE "\033[1;34m" // Blue color for info
#define COLOR_MAGENTA "\033[1;35m" // Magenta color
#define COLOR_CYAN "\033[1;36m" // Cyan color for highlights
#define COLOR_WHITE "\033[1;37m" // White color
#define COLOR_BOLD "\033[1m" // Bold text
#define COLOR_UNDERLINE "\033[4m" // Underline text

typedef struct sub // Structure definition for sub node (stores file-specific word information)
{
    char words[100]; // Array to store word
    int word_count; // Count of word occurrences in file
    char file_name[25]; // Array to store filename
	struct sub *link; // Pointer to next sub node
}sub_node; // Type name for sub node structure
typedef struct single // Structure definition for single linked list node (stores file list)
{
	char file[30]; // Array to store filename
	struct single *link; // Pointer to next node
}Slist; // Type name for single linked list node
typedef struct hash // Structure definition for hash table
{
    int index; // Hash table index
    struct main *link; // Pointer to main node
}Hash; // Type name for hash structure
typedef struct main // Structure definition for main node (stores word information)
{
	int file_count; // Number of files containing the word
    char word[27]; // Array to store word
    char file[20][30]; // 2D array to store filenames
	struct sub *link; // Pointer to sub node
    struct main *mainlink; // Pointer to next main node
}main_node; // Type name for main node structure

int extntion(char*filename); // Function to check file extension
int empty(char*filename); // Function to check if file is empty
int insert_at_last(Slist **head,char *file); // Function to insert file at end of list
void print_list(Slist *head); // Function to print file list
int duplicate(Slist *head,char *filename); // Function to check for duplicate filename
int create_database(Slist*head,main_node* hash_table[]); // Function to create database from file list
int display_database(main_node* hash_table[]); // Function to display database contents
int save_database(main_node* hash_table[],char *file); // Function to save database to file
int search_database(main_node* hash_table[]); // Function to search word in database
int update_database(Slist **head, main_node *hash_table[], char *file); // Function to update database from saved file
void delete_file_from_list(Slist **head,  char *filename); // Function to delete file from list
int hash_function( char *word); // Function to calculate hash index
#endif // Header guard end