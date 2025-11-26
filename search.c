#include"validate.h" // Include header file with function declarations and data structures
 
int search_database(main_node* hash_table[]) // Function to search word in database
{
    char key[50]; // Buffer to store search word
    printf(COLOR_BOLD COLOR_MAGENTA "Enter the search word" COLOR_RESET " : " COLOR_CYAN); // Prompt for search word
    scanf("%s",key); // Read search word
    printf(COLOR_RESET); // Reset color
    int index,found=0; // Variables for hash index and found flag
    if (isalpha(key[0])) // Check if first character is alphabetic
    {
        index = tolower(key[0]) - 97; // Calculate index for alphabets (a=0, b=1, etc.)
    }
    else // Handle non-alphabetic characters
    {
        index = 26; // Assign index 26 for non-alphabetic characters
    }
    main_node* tempmain=hash_table[index]; // Get main node at calculated index
    while(tempmain!=NULL) // Traverse through main nodes at this index
    {
        if(strcmp(tempmain->word,key)==0) // Compare search word with main node word
        {
            found=1; // Set found flag
            sub_node*tempsub=tempmain->link; // Get first sub node
            printf("\n" COLOR_GREEN COLOR_BOLD "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" COLOR_RESET); // Print separator
            printf(COLOR_GREEN COLOR_BOLD "SEARCH RESULTS:" COLOR_RESET COLOR_CYAN " Word " COLOR_RESET COLOR_YELLOW COLOR_BOLD "\"%s\"" COLOR_RESET COLOR_GREEN " found in:\n" COLOR_RESET, tempmain->word); // Print header
            printf(COLOR_GREEN COLOR_BOLD "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" COLOR_RESET); // Print separator
            while(tempsub!=NULL) // Traverse through sub nodes
            {
                printf(COLOR_GREEN "  ✓ " COLOR_RESET COLOR_BOLD COLOR_CYAN "%s\n" COLOR_RESET, tempsub->file_name); // Print file where word found
                tempsub=tempsub->link; // Move to next sub node
            }
        }
        tempmain = tempmain->mainlink; // Move to next main node
    }
    if(!found) // If word not found
    {
        return FAILURE; // Return failure
    }
    return SUCCESS; // Return success
}