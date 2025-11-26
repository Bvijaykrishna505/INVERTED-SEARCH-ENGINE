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
        printf("\n" COLOR_YELLOW COLOR_BOLD "⚠ WARNING: Database is empty!\n" COLOR_RESET); // Print empty database message
        return SUCCESS; // Return success
    }

    // Ensure minimum column widths for better formatting
    if (max_word_len < 4) max_word_len = 4; // Set minimum word length
    if (max_file_len < 9) max_file_len = 9; // Set minimum file length

    // Define fixed column widths for proper alignment
    int index_width = 7; // Width for Index column (to fit "  XXX")
    int word_width = (int)max_word_len; // Width for Word column
    int file_count_width = 12; // Width for File Count column
    int file_name_width = (int)max_file_len; // Width for File Name column
    int word_count_width = 12; // Width for Word Count column
    
    // Calculate total width for separator line
    int total_width = index_width + 3 + word_width + 3 + file_count_width + 3 + file_name_width + 3 + word_count_width; // 3 for " │ " separators

    printf("\n" COLOR_CYAN COLOR_BOLD); // Start separator
    for (int i = 0; i < total_width; i++) printf("━"); // Print separator line matching table width
    printf(COLOR_RESET "\n");
    printf(COLOR_CYAN COLOR_BOLD "                              DATABASE CONTENTS\n" COLOR_RESET); // Print header
    printf(COLOR_CYAN COLOR_BOLD); // Start separator
    for (int i = 0; i < total_width; i++) printf("━"); // Print separator line matching table width
    printf(COLOR_RESET "\n");
    
    // Print column headers with fixed widths
    printf(COLOR_YELLOW COLOR_BOLD "%-*s" COLOR_RESET COLOR_CYAN " │ " COLOR_RESET COLOR_GREEN COLOR_BOLD "%-*s" COLOR_RESET COLOR_CYAN " │ " COLOR_RESET COLOR_MAGENTA COLOR_BOLD "%-*s" COLOR_RESET COLOR_CYAN " │ " COLOR_RESET COLOR_BLUE COLOR_BOLD "%-*s" COLOR_RESET COLOR_CYAN " │ " COLOR_RESET COLOR_WHITE COLOR_BOLD "%-*s\n" COLOR_RESET,
           index_width, "Index", word_width, "Word", file_count_width, "File Count", file_name_width, "File Name", word_count_width, "Word Count");
    
    printf(COLOR_CYAN); // Start separator
    for (int i = 0; i < total_width; i++) printf("━"); // Print separator line matching table width
    printf(COLOR_RESET "\n");

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
                    printf(COLOR_YELLOW "%-*d" COLOR_RESET COLOR_CYAN " │ " COLOR_RESET COLOR_GREEN "%-*s" COLOR_RESET COLOR_CYAN " │ " COLOR_RESET COLOR_MAGENTA "%-*d" COLOR_RESET COLOR_CYAN " │ " COLOR_RESET COLOR_BLUE "%-*s" COLOR_RESET COLOR_CYAN " │ " COLOR_RESET COLOR_WHITE "%-*d\n" COLOR_RESET,
                           index_width, i, 
                           word_width, tempmain->word,
                           file_count_width, tempmain->file_count, 
                           file_name_width, tempsub->file_name, 
                           word_count_width, tempsub->word_count); // Print full row with all data
                    first_entry = 0; // Clear first entry flag
                }
                else // If subsequent entry in row
                {
                    printf("%-*s" COLOR_CYAN " │ " COLOR_RESET "%-*s" COLOR_RESET COLOR_CYAN " │ " COLOR_RESET "%-*s" COLOR_RESET COLOR_CYAN " │ " COLOR_RESET COLOR_BLUE "%-*s" COLOR_RESET COLOR_CYAN " │ " COLOR_RESET COLOR_WHITE "%-*d\n" COLOR_RESET,
                           index_width, "", // Empty index
                           word_width, "", // Empty word
                           file_count_width, "", // Empty file count
                           file_name_width, tempsub->file_name, 
                           word_count_width, tempsub->word_count); // Print row with only file info
                }
                tempsub = tempsub->link; // Move to next sub node
            }
            tempmain = tempmain->mainlink; // Move to next main node
        }
    }
    return SUCCESS; // Return success
}