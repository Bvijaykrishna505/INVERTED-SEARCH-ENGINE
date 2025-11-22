#include "validate.h" // Include header file with function declarations and data structures

static int add_word_to_hash(const char *word, const char *filename, main_node *hash_table[]) // Static function to add word to hash table
{
    if (word[0] == '\0') // Check if word is empty
    {
        return SUCCESS; // Return success for empty word
    }

    int index; // Variable to store hash index
    if (isalpha(word[0])) // Check if first character is alphabetic
    {
        index = tolower(word[0]) - 'a'; // Calculate index for alphabets (0-25)
    }
    else // Handle non-alphabetic characters
    {
        index = 26; // Assign index 26 for non-alphabetic characters
    }

    main_node *hashtemp = hash_table[index]; // Get the main node at calculated index
    main_node *prev_main = NULL; // Pointer to track previous main node

    if (hashtemp == NULL) // Check if hash table slot is empty
    {
        main_node *Main = malloc(sizeof(main_node)); // Allocate memory for new main node
        if (Main == NULL) // Check if memory allocation failed
        {
            return FAILURE; // Return failure if allocation failed
        }
        strcpy(Main->word, word); // Copy word to main node
        Main->file_count = 1; // Initialize file count to 1
        Main->mainlink = NULL; // Set main link to NULL

        sub_node *Sub = malloc(sizeof(sub_node)); // Allocate memory for sub node
        if (Sub == NULL) // Check if memory allocation failed
        {
            return FAILURE; // Return failure if allocation failed
        }
        strcpy(Sub->words, word); // Copy word to sub node
        strcpy(Sub->file_name, filename); // Copy filename to sub node
        Sub->word_count = 1; // Initialize word count to 1
        Sub->link = NULL; // Set sub node link to NULL

        Main->link = Sub; // Link sub node to main node
        hash_table[index] = Main; // Store main node in hash table
        return SUCCESS; // Return success
    }

    int found = 0; // Flag to track if word was found

    while (hashtemp != NULL) // Traverse through main nodes at this index
    {
        if (strcmp(hashtemp->word, word) == 0) // Check if word matches existing main node
        {
            sub_node *sub = hashtemp->link; // Get first sub node
            sub_node *prev = NULL; // Pointer to track previous sub node

            while (sub != NULL) // Traverse through sub nodes
            {
                if (strcmp(sub->file_name, filename) == 0) // Check if filename matches
                {
                    sub->word_count += 1; // Increment word count for existing file
                    found = 1; // Set found flag
                    break; // Exit loop
                }
                prev = sub; // Update previous pointer
                sub = sub->link; // Move to next sub node
            }

            if (!found) // If file not found in sub nodes
            {
                sub_node *Sub = malloc(sizeof(sub_node)); // Allocate memory for new sub node
                if (Sub == NULL) return FAILURE; // Return failure if allocation failed

                strcpy(Sub->words, word); // Copy word to new sub node
                strcpy(Sub->file_name, filename); // Copy filename to new sub node
                Sub->word_count = 1; // Initialize word count to 1
                Sub->link = NULL; // Set link to NULL

                if (prev == NULL) // If no previous sub node exists
                    hashtemp->link = Sub; // Link new sub node to main node
                else // If previous sub node exists
                    prev->link = Sub; // Link new sub node after previous

                hashtemp->file_count += 1; // Increment file count in main node
            }

            found = 1; // Set found flag
            break; // Exit loop
        }

        prev_main = hashtemp; // Update previous main node pointer
        hashtemp = hashtemp->mainlink; // Move to next main node
    }

    if (!found && prev_main != NULL && hashtemp == NULL) // If word not found and we reached end of list
    {
        main_node *Main = malloc(sizeof(main_node)); // Allocate memory for new main node
        if (Main == NULL) // Check if memory allocation failed
        {
            return FAILURE; // Return failure if allocation failed
        }
        strcpy(Main->word, word); // Copy word to main node
        Main->file_count = 1; // Initialize file count to 1
        Main->mainlink = NULL; // Set main link to NULL

        sub_node *Sub = malloc(sizeof(sub_node)); // Allocate memory for new sub node
        if (Sub == NULL) // Check if memory allocation failed
        {
            return FAILURE; // Return failure if allocation failed
        }
        strcpy(Sub->words, word); // Copy word to sub node
        strcpy(Sub->file_name, filename); // Copy filename to sub node
        Sub->word_count = 1; // Initialize word count to 1
        Sub->link = NULL; // Set link to NULL

        Main->link = Sub; // Link sub node to main node
        prev_main->mainlink = Main; // Link new main node after previous main node
    }

    return SUCCESS; // Return success
}

int create_database(Slist *head, main_node *hash_table[]) // Function to create database from file list
{
    Slist *temp = head; // Start with head of file list
    while (temp != NULL) // Traverse through all files
    {
        FILE *fp = fopen(temp->file, "r"); // Open file in read mode
        if (fp == NULL) // Check if file opening failed
        {
            printf("Error opening file %s \n",temp->file); // Print error message
            temp = temp->link; // Move to next file
            continue; // Skip to next iteration
        }

        fseek(fp, 0, SEEK_SET); // Reset file pointer to beginning
        char buffer[100]; // Buffer to store words

        while (fscanf(fp, "%99s", buffer) == 1) // Read words from file
        {
            char *ptr = buffer; // Pointer to traverse buffer
            while (*ptr != '\0') // Process each character in buffer
            {
                while (*ptr != '\0' && !isalnum((unsigned char)*ptr)) // Skip non-alphanumeric characters
                {
                    ptr++; // Move to next character
                }

                if (*ptr == '\0') // If end of string reached
                {
                    break; // Exit loop
                }

                char word[100]; // Array to store extracted word
                int idx = 0; // Index for word array

                while (*ptr != '\0' && isalnum((unsigned char)*ptr) && idx < 99) // Extract alphanumeric characters
                {
                    word[idx++] = *ptr; // Store character in word array
                    ptr++; // Move to next character
                }
                word[idx] = '\0'; // Null terminate word

                if (add_word_to_hash(word, temp->file, hash_table) == FAILURE) // Add word to hash table
                {
                    fclose(fp); // Close file
                    return FAILURE; // Return failure
                }
            }
        }

        fclose(fp); // Close file
        temp = temp->link; // Move to next file in list
    }
    return SUCCESS; // Return success
}
