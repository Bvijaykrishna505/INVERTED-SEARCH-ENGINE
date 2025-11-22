#include"validate.h" // Include header file with function declarations and data structures
int save_database(main_node* hash_table[],char *file) // Function to save database to file
{
    FILE*fptr=fopen(file,"w"); // Open file in write mode
    if(fptr==NULL) // Check if file opening failed
    {
        return FAILURE; // Return failure
    }
    for(int i=0;i<27;i++) // Loop through all hash table indices
    {
        main_node* tempmain=hash_table[i]; // Get main node at current index
        if(tempmain==NULL) // Check if index is empty
        { 
            continue; // Skip to next index
        }
        while(tempmain!=NULL) // Traverse through main nodes at this index
        {
            fprintf(fptr,"#%d;%s;%d;",i,tempmain->word,tempmain->file_count); // Write index, word, and file count
            sub_node*tempsub=tempmain->link; // Get first sub node
            while(tempsub!=NULL) // Traverse through sub nodes
            {
                fprintf(fptr,"%s;%d",tempsub->file_name,tempsub->word_count); // Write filename and word count
                tempsub=tempsub->link; // Move to next sub node
            }
            fprintf(fptr, "#\n");  // Write end marker for word entry
            tempmain=tempmain->mainlink; // Move to next main node
        }
    }
    fclose(fptr); // Close file
    return SUCCESS; // Return success
}