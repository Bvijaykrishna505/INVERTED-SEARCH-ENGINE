#include "validate.h" // Include header file with function declarations and data structures
int hash_function(char *word) // Function to calculate hash index for a word
{
    int index; // Variable to store hash index
    if (isalpha(word[0])) // Check if first character is alphabetic
        index = tolower(word[0]) - 'a'; // Calculate index for alphabets (a=0, b=1, etc.)
    else // Handle non-alphabetic characters
        index = 26; // Assign index 26 for non-alphabetic characters
    return index; // Return calculated index
}

int update_database(Slist **head, main_node *hash_table[], char *file) // Function to update database from saved file
{
    FILE *fptr = fopen(file, "r"); // Open file in read mode
    if (fptr == NULL) // Check if file opening failed
    {
        printf("ERROR: Cannot open file %s\n", file); // Print error message
        return FAILURE; // Return failure
    }

    fseek(fptr, 0, SEEK_END); // Move file pointer to end of file
    long length = ftell(fptr); // Get file size
    fseek(fptr, 0, SEEK_SET); // Reset file pointer to beginning

    char *data = malloc(length + 2); // Allocate memory for file content
    fread(data, 1, length, fptr); // Read file content into buffer
    data[length] = '\0'; // Null terminate buffer
    fclose(fptr); // Close file
    if (data[length - 1] == '\n') // Check if last character is newline
    {
        data[length - 1] = '\0'; // Remove newline
        length--; // Decrement length
    }
    if (data[0] != '#' || data[length - 1] != '#') // Check if file starts and ends with '#'
    {
        printf("ERROR: File must start and end with '#'\n"); // Print error message
        free(data); // Free allocated memory
        return FAILURE; // Return failure
    }
    char *ptr = data + 1; // Skip first '#' character
    while (*ptr) // Process file content
    {
        char *end = strchr(ptr, '#'); // Find next '#' character
        if (!end) break; // Exit if no '#' found
        *end = '\0'; // Null terminate current entry

        int index; // Variable for hash index
        char word[27]; // Buffer for word
        if (sscanf(ptr, "%d;%26[^;];", &index, word) != 2) // Parse index and word
        {
            ptr = end + 1; // Move to next entry
            continue; // Skip to next iteration
        }

        char *fp = strchr(ptr, ';'); // Find first semicolon
        if (!fp) // Check if semicolon found
        { 
            ptr = end + 1; // Move to next entry
            continue; // Skip to next iteration
        }
        fp = strchr(fp + 1, ';'); // Find second semicolon
        if (!fp) // Check if semicolon found
        { 
            ptr = end + 1; // Move to next entry
            continue; // Skip to next iteration
        }
        fp++; // Move pointer past second semicolon

        while (*fp && fp < end) // Process file information entries
        {
            int wc = 0; // Variable for word count
            char fname[30] = {0}; // Buffer for filename
            int n = 0; // Variable for parsed length
            sscanf(fp, "%1d%29[^;]%n", &wc, fname, &n); // Parse word count and filename
            if (n == 0) break; // Exit if parsing failed
            fp += n; // Move pointer past parsed data
            if (*fp == ';') fp++; // Skip delimiter if present

            int hash_index = index; // Store hash index
            main_node *temp = hash_table[hash_index]; // Get main node at index
            main_node *found = NULL; // Pointer to found main node

            while (temp) // Search for existing main node with same word
            {
                if (strcmp(temp->word, word) == 0) // Compare words
                {
                    found = temp; // Store found node
                    break; // Exit loop
                }
                temp = temp->mainlink; // Move to next main node
            }

            if (found) // If word already exists in database
            {
                int exists = 0; // Flag to track if file exists
                for (int j = 0; j < found->file_count; j++) // Loop through files
                {
                    if (strcmp(found->file[j], fname) == 0) // Compare filenames
                    {
                        exists = 1; // Set flag if file exists
                        break; // Exit loop
                    }
                }

                if (!exists) // If file does not exist in main node
                {
                    strcpy(found->file[found->file_count], fname); // Copy filename to array
                    found->file_count++; // Increment file count

                    sub_node *new_sub = malloc(sizeof(sub_node)); // Allocate memory for new sub node
                    strcpy(new_sub->file_name, fname); // Copy filename to sub node
                    strcpy(new_sub->words, word); // Copy word to sub node
                    new_sub->word_count = wc; // Set word count
                    new_sub->link = found->link; // Link to existing sub nodes
                    found->link = new_sub; // Update main node link
                }
            }
            else // If word does not exist in database
            {
                main_node *new = malloc(sizeof(main_node)); // Allocate memory for new main node
                strcpy(new->word, word); // Copy word to main node
                new->file_count = 1; // Initialize file count
                strcpy(new->file[0], fname); // Copy filename to array
                new->link = NULL; // Set link to NULL
                sub_node *new_sub = malloc(sizeof(sub_node)); // Allocate memory for new sub node
                strcpy(new_sub->file_name, fname); // Copy filename to sub node
                strcpy(new_sub->words, word); // Copy word to sub node
                new_sub->word_count = wc; // Set word count
                new_sub->link = NULL; // Set link to NULL

                new->link = new_sub; // Link sub node to main node
                new->mainlink = hash_table[hash_index]; // Link to existing main nodes
                hash_table[hash_index] = new; // Update hash table
            }
            delete_file_from_list(head, fname); // Remove file from list if it exists
        }

        ptr = end + 1; // Move to next entry
    }
    
    free(data); // Free allocated memory
    if (*head != NULL) // Check if file list is not empty
    {
        create_database(*head, hash_table);  // Load remaining new files into hash table
    }

    printf("INFO : Data updated successfully\n"); // Print success message
    return SUCCESS; // Return success
}
void delete_file_from_list(Slist **head, char *filename) // Function to delete file from list
{
    Slist *temp = *head, *prev = NULL; // Pointers for current and previous nodes

    while (temp) // Traverse through list
    {
        if (strcmp(temp->file, filename) == 0) // Compare filenames
        {
            if (prev == NULL) // If node to delete is head
                *head = temp->link; // Update head to next node
            else // If node to delete is not head
                prev->link = temp->link; // Link previous node to next node
            free(temp); // Free deleted node memory
            return; // Return
        }
        prev = temp; // Update previous pointer
        temp = temp->link; // Move to next node
    }
}
