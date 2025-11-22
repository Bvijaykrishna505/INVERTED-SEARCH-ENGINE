# INVERTED-SEARCH-ENGINE
🔍 Inverted Search using Singly Linked List &amp; Hash Table  This project implements an Inverted Search Engine in C using Singly Linked Lists and a Hash Table to index and search words across multiple text files. It demonstrates strong use of core Data Structures, including hashing, linked lists, file handling, and dynamic memory management.
## Algorithm Flow

### Database Creation Flow

```
START
  │
  ├─> For each file in list
  │     │
  │     ├─> Open file
  │     │
  │     ├─> Read tokens
  │     │
  │     ├─> Extract words
  │     │     │
  │     │     ├─> Calculate hash index
  │     │     │
  │     │     ├─> Search hash table
  │     │     │
  │     │     ├─> Word exists?
  │     │     │     │
  │     │     │     ├─> YES: Update count or add file
  │     │     │     │
  │     │     │     └─> NO: Create new node
  │     │     │
  │     └─> Close file
  │
  └─> END
```
📌 Project Overview

The program reads multiple text files and builds an Inverted Index, which maps each unique word to:
The files in which the word appears
How many times it appears in each file

The data is stored in:
✔️ Hash Table
Used for fast indexing (O(1) average lookup). Each hash index points to a singly linked list.

✔️ Singly Linked List
Stores the word, and a sub-list of file information containing:
File name
Word count in that file
This structure makes the search extremely efficient.

🎯 Features
✔️ Build an inverted index from multiple files
✔️ Uses hashing to store words efficiently
✔️ Words stored as a Singly Linked List at each hash index
✔️ For each word, maintain a file info list
✔️ Search quickly for any word
✔️ Display complete inverted index
✔️ Save & load index using a backup file
✔️ Clean modular design
✔️ Input validation and error handling

🛠️ Technologies & Concepts Used
C programming
Hash Table
Singly Linked Lists
File handling (fopen, fgets)
Dynamic memory allocation
Tokenization (string parsing)
Modular programming (separate .c files)

🧠 Learning Outcomes:
Implementation of Hashing
Singly Linked List operations
Linked list of linked lists (nested structure)
File parsing & tokenization
Modular programming
Designing efficient search systems
Building scalable index structures

how to run - gcc *.c 
./a.out (nfiles)
