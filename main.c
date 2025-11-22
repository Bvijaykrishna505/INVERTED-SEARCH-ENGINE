//PROJECTION DESCRIPTION 
//NAME: VIJAY KRISHNA 
//PROJECT NAME: INVERTED SEARCH ENGINE
// DESCRIPTION: An inverted search system that indexes words from multiple files using a hash table and linked lists. // Project description
//              It quickly retrieves the files in which a searched word appears. // Additional description
//DATE:10/11/2025 
#include"validate.h" // Include header file with function declarations and data structures

main_node *hash_table[27]; // Global hash table array with 27 indices (a-z + non-alphabetic)
int main(int argc,char*argv[]) // Main function with command line arguments
{
    if(argc<2) // Check if command line arguments are provided
    {
        printf("The arguments are <./a.out> <fil1.txt> ----<file.txt>\n"); // Print usage message
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
            printf("INFO : %s is duplicate file\n",argv[i]); // Print duplicate file message
            continue; // Skip to next file if duplicate
        }
        if(insert_at_last(&head,argv[i])==FAILURE) // Insert file at end of linked list
        {
            continue; // Skip to next file if insertion fails
        }
        printf("INFO : Success %s added to the linked list\n",argv[i]); // Print success message
        print_list(head); // Print the current file list
    }
    
    int option,flag=0,count=0; // Variables for menu option, create database flag, and update count
    while(1) // Infinite loop for menu
    {
        printf("1.create database\n2.Display database\n3.update database\n4.search\n5.save database\n6.exit\n"); // Print menu options
        printf("Enter the option : "); // Prompt for option
        scanf("%d",&option); // Read user option
        switch(option) // Switch based on user option
        {
            case 1: // Option to create database
                if(flag==0) // Check if database not created yet
                {
                     flag=1; // Set flag to indicate database created
                    if(create_database(head,hash_table)==SUCCESS) // Create database from file list
                    {
                        printf("INFO :file added to database successfully\n"); // Print success message
                    }
                    else // If database creation failed
                    {
                        printf("INFO : file not added to database successfully\n"); // Print failure message
                    }
                    break; // Exit switch
                }
                else // If database already created
                {
                    printf("ERROR : create database is already completed\n"); // Print error message
                }
                break; // Exit switch
            case 2: // Option to display database
                if(display_database(hash_table)==SUCCESS) // Display database contents
                {
                    printf("INFO : Data displayed successfully\n"); // Print success message
                }
                else // If display failed
                {
                    printf("INFO : Data not displayed \n"); // Print failure message
                }
                break; // Exit switch
            case 3: // Option to update database
                char str1[10]; // Buffer to store filename
                printf("Enter file name: "); // Prompt for filename
                scanf("%s",str1); // Read filename
                if(extntion(str1)==FAILURE) // Check file extension
                {
                    continue; // Skip if extension invalid
                }
                if( flag==1) // If create database already done
                {
                    printf("ERROR : create database completed update database not possible\n"); // Print error message
                }
                else if(count==1) // If update already done
                {
                    printf("ERROR : update  database completed  again update database not possible\n"); // Print error message
                }
                else // If update is allowed
                {
                    count=1; // Set count to indicate update done
                    if(update_database(&head,hash_table,str1)==SUCCESS) // Update database with saved file
                    {
                        printf("INFO : Data updated successfully\n"); // Print success message
                    }
                    else // If update failed
                    {
                        printf("INFO : Data not updated\n"); // Print failure message
                    }
                    break; // Exit switch
                }
                break; // Exit switch
            case 4: // Option to search database
                if(search_database(hash_table)==SUCCESS) // Search for word in database
                {
                    printf("INFO  : search completed successfully\n"); // Print success message
                }
                else // If search failed
                {
                    printf("INFO : Data not found \n"); // Print not found message
                }
                break; // Exit switch
            case 5: // Option to save database
                char str[10]; // Buffer to store filename
                printf("Enter file name: "); // Prompt for filename
                scanf("%s",str); // Read filename
                if(extntion(str)==FAILURE) // Check file extension
                {
                    continue; // Skip if extension invalid
                }
                if(save_database(hash_table,str)==SUCCESS) // Save database to file
                {
                    printf("INFO : Data saved successfully\n"); // Print success message
                }
                else // If save failed
                { 
                    printf("INFO : Data not saved\n"); // Print failure message
                }
                break; // Exit switch
            case 6: // Option to exit
                printf("Exit .....\n"); // Print exit message
                return SUCCESS; // Return success
            default: // Invalid option
                printf("INFO : Invalid option. Try again.\n"); // Print error message
                break; // Exit switch
        }
    }
}