//PROJECTION DESCRIPTION 
//NAME: VIJAY KRISHNA 
//PROJECT NAME: INVERTED SEARCH ENGINE
// DESCRIPTION: An inverted search system that indexes words from multiple files using a hash table and linked lists. // Project description
//              It quickly retrieves the files in which a searched word appears.
//DATE:10/11/2025 
#include"validate.h" // Include header file with function declarations and data structures

main_node *hash_table[27]; // Global hash table array with 27 indices (a-z + non-alphabetic)
int main(int argc,char*argv[]) // Main function with command line arguments
{
    if(argc<2) // Check if command line arguments are provided
    {
        printf(COLOR_RED "\n" COLOR_BOLD "ERROR: Missing command line arguments!\n" COLOR_RESET); // Print error message
        printf(COLOR_CYAN "Usage: <./a.out> <file1.txt> <file2.txt> ...\n\n" COLOR_RESET); // Print usage
        return FAILURE; // Return failure if no arguments
    }
    Slist*head=NULL; // Initialize file list head to NULL
    for(int i=1;i<argc;i++) // Loop through all command line arguments
    {
        if(extntion(argv[i])==FAILURE) // Check if file has .txt extension
        {
            continue; // Skip to next file if extension check fails
        }
        if(empty(argv[i])==FAILURE) // Check if file is not empty
        {
            continue; // Skip to next file if file is empty
        }
        if(duplicate(head,argv[i])==FAILURE) // Check if file is duplicate
        {
            printf(COLOR_YELLOW "⚠ " COLOR_RESET COLOR_YELLOW "WARNING:" COLOR_RESET " File " COLOR_CYAN "%s" COLOR_RESET " is a duplicate file\n",argv[i]); // Print duplicate file message
            continue; // Skip to next file if duplicate
        }
        if(insert_at_last(&head,argv[i])==FAILURE) // Insert file at end of linked list
        {
            continue; // Skip to next file if insertion fails
        }
        printf(COLOR_GREEN "✓ " COLOR_RESET COLOR_GREEN COLOR_BOLD "SUCCESS:" COLOR_RESET " File " COLOR_CYAN COLOR_BOLD "%s" COLOR_RESET " added to the linked list\n",argv[i]); // Print success message
        print_list(head); // Print the current file list
    }
    
    int option,flag=0,count=0; // Variables for menu option, create database flag, and update count
    while(1) // Infinite loop for menu
    {
        printf("\n" COLOR_CYAN COLOR_BOLD "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" COLOR_RESET); // Print separator line
        printf(COLOR_CYAN COLOR_BOLD "           INVERTED SEARCH ENGINE - MAIN MENU\n" COLOR_RESET); // Print menu title
        printf(COLOR_CYAN COLOR_BOLD "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" COLOR_RESET); // Print separator line
        printf("  " COLOR_YELLOW "1." COLOR_RESET COLOR_GREEN " Create Database\n" COLOR_RESET); // Print menu option
        printf("  " COLOR_YELLOW "2." COLOR_RESET COLOR_GREEN " Display Database\n" COLOR_RESET); // Print menu option
        printf("  " COLOR_YELLOW "3." COLOR_RESET COLOR_GREEN " Update Database\n" COLOR_RESET); // Print menu option
        printf("  " COLOR_YELLOW "4." COLOR_RESET COLOR_GREEN " Search Database\n" COLOR_RESET); // Print menu option
        printf("  " COLOR_YELLOW "5." COLOR_RESET COLOR_GREEN " Save Database\n" COLOR_RESET); // Print menu option
        printf("  " COLOR_YELLOW "6." COLOR_RESET COLOR_RED " Exit\n" COLOR_RESET); // Print menu option
        printf(COLOR_BOLD COLOR_MAGENTA "Enter your option" COLOR_RESET " : " COLOR_CYAN); // Prompt for option
        scanf("%d",&option); // Read user option
        printf(COLOR_RESET); // Reset color
        switch(option) // Switch based on user option
        {
            case 1: // Option to create database
                if(flag==0) // Check if database not created yet
                {
                     flag=1; // Set flag to indicate database created
                    if(create_database(head,hash_table)==SUCCESS) // Create database from file list
                    {
                        printf("\n" COLOR_GREEN COLOR_BOLD "✓ SUCCESS: Files added to database successfully!\n" COLOR_RESET); // Print success message
                    }
                    else // If database creation failed
                    {
                        printf("\n" COLOR_RED COLOR_BOLD "✗ FAILURE: Files not added to database successfully!\n" COLOR_RESET); // Print failure message
                    }
                    break; // Exit switch
                }
                else // If database already created
                {
                    printf("\n" COLOR_YELLOW COLOR_BOLD "⚠ WARNING: Database creation already completed!\n" COLOR_RESET); // Print warning message
                }
                break; // Exit switch
            case 2: // Option to display database
                if(display_database(hash_table)==SUCCESS) // Display database contents
                {
                    printf("\n" COLOR_GREEN "✓ Data displayed successfully\n" COLOR_RESET); // Print success message
                }
                else // If display failed
                {
                    printf("\n" COLOR_RED "✗ Data not displayed\n" COLOR_RESET); // Print failure message
                }
                break; // Exit switch
            case 3: // Option to update database
                char str1[10]; // Buffer to store filename
                printf(COLOR_BOLD COLOR_MAGENTA "Enter file name" COLOR_RESET " : " COLOR_CYAN); // Prompt for filename
                scanf("%s",str1); // Read filename
                printf(COLOR_RESET); // Reset color
                if(extntion(str1)==FAILURE) // Check file extension
                {
                    continue; // Skip if extension invalid
                }
                if( flag==1) // If create database already done
                {
                    printf("\n" COLOR_YELLOW COLOR_BOLD "⚠ WARNING: Database creation completed. Update not possible!\n" COLOR_RESET); // Print warning message
                }
                else if(count==1) // If update already done
                {
                    printf("\n" COLOR_YELLOW COLOR_BOLD "⚠ WARNING: Database update already completed!\n" COLOR_RESET); // Print warning message
                }
                else // If update is allowed
                {
                    count=1; // Set count to indicate update done
                    if(update_database(&head,hash_table,str1)==SUCCESS) // Update database with saved file
                    {
                        printf("\n" COLOR_GREEN "✓ Data updated successfully\n" COLOR_RESET); // Print success message
                    }
                    else // If update failed
                    {
                        printf("\n" COLOR_RED "✗ Data not updated\n" COLOR_RESET); // Print failure message
                    }
                    break; // Exit switch
                }
                break; // Exit switch
            case 4: // Option to search database
                if(search_database(hash_table)==SUCCESS) // Search for word in database
                {
                    printf("\n" COLOR_GREEN "✓ Search completed successfully\n" COLOR_RESET); // Print success message
                }
                else // If search failed
                {
                    printf("\n" COLOR_RED "✗ Word not found in database\n" COLOR_RESET); // Print not found message
                }
                break; // Exit switch
            case 5: // Option to save database
                char str[10]; // Buffer to store filename
                printf(COLOR_BOLD COLOR_MAGENTA "Enter file name" COLOR_RESET " : " COLOR_CYAN); // Prompt for filename
                scanf("%s",str); // Read filename
                printf(COLOR_RESET); // Reset color
                if(extntion(str)==FAILURE) // Check file extension
                {
                    continue; // Skip if extension invalid
                }
                if(save_database(hash_table,str)==SUCCESS) // Save database to file
                {
                    printf("\n" COLOR_GREEN COLOR_BOLD "✓ SUCCESS: Database saved to " COLOR_RESET COLOR_CYAN COLOR_BOLD "%s" COLOR_RESET COLOR_GREEN COLOR_BOLD " successfully!\n" COLOR_RESET, str); // Print success message
                }
                else // If save failed
                { 
                    printf("\n" COLOR_RED COLOR_BOLD "✗ FAILURE: Database not saved!\n" COLOR_RESET); // Print failure message
                }
                break; // Exit switch
            case 6: // Option to exit
                printf("\n" COLOR_CYAN COLOR_BOLD "Thank you for using Inverted Search Engine!\n" COLOR_RESET); // Print exit message
                printf(COLOR_YELLOW "Exiting...\n\n" COLOR_RESET); // Print exit message
                return SUCCESS; // Return success
            default: // Invalid option
                printf("\n" COLOR_RED COLOR_BOLD "✗ ERROR: Invalid option! Please try again.\n" COLOR_RESET); // Print error message
                break; // Exit switch
        }
    }
}