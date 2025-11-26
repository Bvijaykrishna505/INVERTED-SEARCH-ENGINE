#include"validate.h" // Include header file with function declarations and data structures

int extntion(char*filename) // Function to check file extension
{
    const char *ext = strrchr(filename, '.');  // Find last occurrence of '.' in filename
    if (ext != NULL && strcmp(ext, ".txt") == 0) // Check if extension is .txt
    {
        return SUCCESS; // Return success if .txt extension found
    }
    else // If extension is not .txt
    {
        printf(COLOR_RED "✗ ERROR:" COLOR_RESET " File " COLOR_CYAN "%s" COLOR_RESET " is not a .txt file\n",filename); // Print error message
        return FAILURE; // Return failure
    }
}
int empty(char*filename) // Function to check if file is empty
{
    FILE *fp=fopen(filename,"r"); // Open file in read mode
    if(fp==NULL) // Check if file opening failed
    {
        printf(COLOR_RED "✗ ERROR:" COLOR_RESET " Cannot open file " COLOR_CYAN "--> %s\n" COLOR_RESET,filename); // Print error message
        return FAILURE; // Return failure
    }
    fseek(fp,0,SEEK_END); // Move file pointer to end of file
    long size=ftell(fp); // Get file size
    fclose(fp); // Close file
    if(size==0) // Check if file size is zero
    {
        printf(COLOR_YELLOW "⚠ WARNING:" COLOR_RESET " No content present in file " COLOR_CYAN "%s\n" COLOR_RESET,filename); // Print error message
       return FAILURE; // Return failure
    }
    return SUCCESS; // Return success if file is not empty
}
int insert_at_last(Slist **head,char *file) // Function to insert file at end of linked list
{
    Slist *new=malloc(sizeof(Slist)); // Allocate memory for new node
    if(new==NULL) // Check if memory allocation failed
    {
        return FAILURE; // Return failure
    }
    strcpy(new->file,file); // Copy filename to new node
    new->link=NULL; // Set link to NULL
    if(*head==NULL) // Check if list is empty
    {
        *head=new; // Set head to new node
        return SUCCESS; // Return success
    }
    Slist *temp=*head; // Start from head
    while(temp->link!=NULL) // Traverse to last node
    {
        temp=temp->link; // Move to next node
    }
    temp->link=new; // Link new node to last node
    return SUCCESS; // Return success
}
int duplicate(Slist *head,char *filename) // Function to check for duplicate filename
{
    while(head!=NULL) // Traverse through list
    {
        if(strcmp(head->file,filename)==0) // Compare filename with current node
        {
            return FAILURE; // Return failure if duplicate found
        }
        head=head->link; // Move to next node
    }
    return SUCCESS; // Return success if no duplicate found
}
void print_list(Slist *head) // Function to print file list
{
    if (head == NULL) // Check if list is empty
    {
        printf(COLOR_YELLOW "⚠ List is empty\n" COLOR_RESET); // Print empty list message
        return; // Return
    }

    size_t max_len = 0; // Variable to store maximum filename length
    Slist *temp = head; // Start from head
    while (temp != NULL) // Traverse through list
    {
        size_t len = strlen(temp->file); // Get length of current filename
        if (len > max_len) // Check if current length is greater
        {
            max_len = len; // Update maximum length
        }
        temp = temp->link; // Move to next node
    }
    
    // Ensure minimum width for better alignment
    if (max_len < 8) max_len = 8; // Minimum filename column width
    
    printf("\n" COLOR_CYAN COLOR_BOLD "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" COLOR_RESET); // Print separator
    printf(COLOR_CYAN COLOR_BOLD "              FILES CURRENTLY IN THE LIST\n" COLOR_RESET); // Print header
    printf(COLOR_CYAN COLOR_BOLD "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" COLOR_RESET); // Print separator
    printf(COLOR_YELLOW COLOR_BOLD "  No." COLOR_RESET COLOR_CYAN " │ " COLOR_RESET COLOR_GREEN COLOR_BOLD "%-*s\n" COLOR_RESET, (int)max_len, "File Name"); // Print column headers
    printf(COLOR_CYAN "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" COLOR_RESET); // Print separator

    int index = 1; // Initialize index counter
    temp = head; // Start from head
    while (temp != NULL) // Traverse through list
    {
        printf(COLOR_YELLOW "  %-3d" COLOR_RESET COLOR_CYAN " │ " COLOR_RESET COLOR_CYAN "%-*s\n" COLOR_RESET, index++, (int)max_len, temp->file); // Print file entry with index
        temp = temp->link; // Move to next node
    }
    printf("\n");
}
