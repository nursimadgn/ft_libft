*This project has been created as part of the 42 curriculum by seldogan.*

# Libft

## Description
Libft is the first project in the 42 curriculum. The goal is to create a custom static C library (libft.a) by reimplementing standard C library (libc) functions along with additional utility functions for memory, string, file descriptor manipulation, and dynamic linked list data structures.

---

## Instructions

### Compilation & Makefile Rules
The library compiles into a static library named `libft.a` using `cc` with `-Wall -Wextra -Werror` flags:

- **make** Compiles all .c files to .o files(generates) and generates libft.a.

- **make clean**: Removes all compiled object (.o) files.

- **make fclean**: Removes all object files and libft.a.

- **make re**: Cleans everything and rebuilds the library from scratch.

### Usage in a C Project
1. Create a `main.c` file and include the header:

#include "libft.h"

```c
int main(void)
{
    ft_putendl_fd("Hello, 42!", 1);
    return (0);
}
```
2. Compile your test code directly with the static library:

cc main.c libft.a && ./a.out

---

## Functions Overview

### Part 1 - Libc Functions
Re-implementations of standard C library functions conforming strictly to system man pages:

| Function | Prototype | Description |
| :--- | :--- | :--- |
| **ft_isalpha** | int ft_isalpha(int c); | Checks for an alphabetic character. |
| **ft_isdigit** | int ft_isdigit(int c); | Checks for a digit (0 through 9). |
| **ft_isalnum** | int ft_isalnum(int c); | Checks for an alphanumeric character. |
| **ft_isascii** | int ft_isascii(int c); | Checks whether a character fits into the ASCII set. |
| **ft_isprint** | int ft_isprint(int c); | Checks for any printable character including space. |
| **ft_strlen** | size_t ft_strlen(const char *s); | Computes the length of a string. |
| **ft_memset** | void *ft_memset(void *b, int c, size_t len); | Fills memory with a constant byte. |
| **ft_bzero** | void ft_bzero(void *s, size_t n); | Zeroes a byte string. |
| **ft_memcpy** | void *ft_memcpy(void *dst, const void *src, size_t n); | Copies a memory area. |
| **ft_memmove** | void *ft_memmove(void *dst, const void *src, size_t len); | Safely copies memory handling overlapping areas. |
| **ft_strlcpy** | size_t ft_strlcpy(char *dst, const char *src, size_t dstsize); | Size-bounded string copy. |
| **ft_strlcat** | size_t ft_strlcat(char *dst, const char *src, size_t dstsize); | Size-bounded string concatenation. |
| **ft_toupper** | int ft_toupper(int c); | Converts a lower-case letter to upper-case. |
| **ft_tolower** | int ft_tolower(int c); | Converts an upper-case letter to lower-case. |
| **ft_strchr** | char *ft_strchr(const char *s, int c); | Locates the first occurrence of a character in a string. |
| **ft_strrchr** | char *ft_strrchr(const char *s, int c); | Locates the last occurrence of a character in a string. |
| **ft_strncmp** | int ft_strncmp(const char *s1, const char *s2, size_t n); | Compares two strings up to a specified number of characters. |
| **ft_memchr** | void *ft_memchr(const void *s, int c, size_t n); | Scans memory for a specific byte. |
| **ft_memcmp** | int ft_memcmp(const void *s1, const void *s2, size_t n); | Compares two memory areas. |
| **ft_strnstr** | char *ft_strnstr(const char *haystack, const char *needle, size_t len); | Locates a substring in a string within length bounds. |
| **ft_atoi** | int ft_atoi(const char *str); | Converts the initial portion of a string to an integer. |
| **ft_calloc** | void *ft_calloc(size_t count, size_t size); | Allocates memory and sets all allocated bytes to zero. |
| **ft_strdup** | char *ft_strdup(const char *s1); | Duplicates a string using dynamic memory allocation. |

---

### Part 2 - Additional Functions
Utility functions not included in the standard libc or implemented in a specific format:

| Function | Prototype | Description |
| :--- | :--- | :--- |
| **ft_substr** | char *ft_substr(char const *s, unsigned int start, size_t len); | Allocates and returns a substring from a string. |
| **ft_strjoin** | char *ft_strjoin(char const *s1, char const *s2); | Concatenates two strings into a newly allocated string. |
| **ft_strtrim** | char *ft_strtrim(char const *s1, char const *set); | Trims specified characters from the beginning and end of a string. |
| **ft_split** | char **ft_split(char const *s, char c); | Splits a string into an array of strings using a delimiter character. |
| **ft_itoa** | char *ft_itoa(int n); | Converts an integer into a null-terminated string. |
| **ft_strmapi** | char *ft_strmapi(char const *s, char (*f)(unsigned int, char)); | Applies a function to characters of a string to create a new string. |
| **ft_striteri** | void ft_striteri(char *s, void (*f)(unsigned int, char*)); | Applies a function to each character of a string in-place. |
| **ft_putchar_fd** | void ft_putchar_fd(char c, int fd); | Outputs a character to a given file descriptor. |
| **ft_putstr_fd** | void ft_putstr_fd(char *s, int fd); | Outputs a string to a given file descriptor. |
| **ft_putendl_fd** | void ft_putendl_fd(char *s, int fd); | Outputs a string followed by a newline to a file descriptor. |
| **ft_putnbr_fd** | void ft_putnbr_fd(int n, int fd); | Outputs an integer to a given file descriptor. |

---

### Part 3 - Linked List Functions (Bonus)
Functions using the t_list structure to easily manipulate singly linked list data structures:

| Function | Prototype | Description |
| :--- | :--- | :--- |
| **ft_lstnew** | t_list *ft_lstnew(void *content); | Allocates memory and creates a new list node. |
| **ft_lstadd_front** | void ft_lstadd_front(t_list **lst, t_list *new); | Adds a new node at the beginning of the list. |
| **ft_lstsize** | unsigned int ft_lstsize(t_list *lst); | Counts the number of nodes in the list. |
| **ft_lstlast** | t_list *ft_lstlast(t_list *lst); | Returns the last node of the list. |
| **ft_lstadd_back** | void ft_lstadd_back(t_list **lst, t_list *new); | Adds a new node at the end of the list. |
| **ft_lstdelone** | void ft_lstdelone(t_list *lst, void (*del)(void *)); | Frees a single node's content and its own memory. |
| **ft_lstclear** | void ft_lstclear(t_list **lst, void (*del)(void *)); | Deletes and frees a given node and all its successors. |
| **ft_lstiter** | void ft_lstiter(t_list *lst, void (*f)(void *)); | Iterates a list and applies a function to each node's content. |
| **ft_lstmap** | t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *)); | Iterates a list and creates a new list from function results. |

---

## Resources & References

### Classic Documentation & Online Guides
- **Linux Manual Pages (man 3)** – Primary reference for standard libc behavior and return values.
- **[GeeksforGeeks - Singly Linked List in C](https://www.geeksforgeeks.org/c/linked-list-in-c/)** – Guide on node creation, pointer linking, and dynamic memory allocation.
- **[C Tutor / PythonTutor](https://pythontutor.com/c.html)** – Memory visualizer used to trace Stack vs. Heap allocation step-by-step.
- **[Stack Overflow](https://stackoverflow.com/)** – Stack Overflow - Consulted for understanding underlying algorithms, resolving complex edge cases, and memory    management.
- **YouTube Tutorials & Walkthroughs** – YouTube Tutorials & Walkthroughs - Referenced for understanding complex data structures, pointer operations, and Makefile concepts.

### AI Collaboration & Learning
- Al as a Technical Partner - Used strictly for learning and understanding concepts:
- Learning pointer logic and memory operations.
- Creating test cases for edge limits and memory leaks.
- Organizing study notes and speeding up Markdown documentation.

### Testing Tools & Checkers
- **[libft-tester (tamerakdeniz)](https://github.com/tamerakdeniz/libft-tester)** –  Tester for edge cases and memory leaks.
- **[Libft Tester (Sfabi28)](https://github.com/Sfabi28/libft_tester)** – Tester for edge cases and memory leaks.

---

## 📖 Deep Dives & Personal Study Notes

For in-depth explanations of low-level C mechanics, data type & parameter selection, sign-extension traps, and linked list diagrams:
👉 **[Read Detailed Study Notes (NOTES.md)](./not.md)**