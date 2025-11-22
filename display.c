#include"validate.h" // Include header file with function declarations and data structures

int display_database(main_node* hash_table[]) // Function to display database contents
{
    size_t max_word_len = strlen("Word"); // Initialize maximum word length
    size_t max_file_len = strlen("File Name"); // Initialize maximum filename length
    int has_data = 0; // Flag to track if database has data

    for (int i = 0; i < 27; i++) // Loop through all hash table indices
    {
        main_node *tempmain = hash_table[i]; // Get main node at current index
        while (tempmain != NULL) // Traverse through main nodes
        {
            has_data = 1; // Set flag indicating data exists
            size_t word_len = strlen(tempmain->word); // Get length of current word
            if (word_len > max_word_len) // Check if current word length is greater
            {
                max_word_len = word_len; // Update maximum word length
            }

            sub_node *tempsub = tempmain->link; // Get first sub node
            while (tempsub != NULL) // Traverse through sub nodes
            {
                size_t file_len = strlen(tempsub->file_name); // Get length of current filename
                if (file_len > max_file_len) // Check if current filename length is greater
                {
                    max_file_len = file_len; // Update maximum filename length
                }
                tempsub = tempsub->link; // Move to next sub node
            }
            tempmain = tempmain->mainlink; // Move to next main node
        }
    }

    if (!has_data) // Check if database is empty
    {
        printf("INFO : Database is empty\n"); // Print empty database message
        return SUCCESS; // Return success
    }

    printf("%-5s | %-*s | %-10s | %-*s | %-10s\n", "Index", (int)max_word_len, "Word",
           "File Count", (int)max_file_len, "File Name", "Word Count"); // Print column headers

    int total_width = 5 + max_word_len + 10 + max_file_len + 10 + (4 * 3); // Calculate total table width
    for (int i = 0; i < total_width; i++) // Loop to print separator line
    {
        putchar('-'); // Print dash character
    }
    putchar('\n'); // Print newline

    for (int i = 0; i < 27; i++) // Loop through all hash table indices
    {
        main_node *tempmain = hash_table[i]; // Get main node at current index
        while (tempmain != NULL) // Traverse through main nodes
        {
            sub_node *tempsub = tempmain->link; // Get first sub node
            int first_entry = 1; // Flag for first entry in row

            while (tempsub != NULL) // Traverse through sub nodes
            {
                if (first_entry) // If first entry in row
                {
                    printf("%-5d | %-*s | %-10d | %-*s | %-10d\n",
                           i, (int)max_word_len, tempmain->word,
                           tempmain->file_count, (int)max_file_len,
                           tempsub->file_name, tempsub->word_count); // Print full row with all data
                    first_entry = 0; // Clear first entry flag
                }
                else // If subsequent entry in row
                {
                    printf("%-5s | %-*s | %-10s | %-*s | %-10d\n",
                           "", (int)max_word_len, "",
                           "", (int)max_file_len,
                           tempsub->file_name, tempsub->word_count); // Print row with only file info
                }
                tempsub = tempsub->link; // Move to next sub node
            }
            tempmain = tempmain->mainlink; // Move to next main node
        }
    }
    return SUCCESS; // Return success
}