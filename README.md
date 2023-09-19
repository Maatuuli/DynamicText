# DynamicText
Core (DynamicText, text functions, stdlib-wrapper) for Web Development in C.

Project goals:

* web development in compiled programming languages like the C programming language
* basic set of functions for programming easily a website
* usage of FastCGI or CGI
  * CGI and FastCGI are part of most web spaces for just $5 per month
  * execute your compiled web sites without the need to have an own web server
* usage of tools and best practices for defensive programming in error-prone programming languages
  * unit tests with good equivalence partitioning
  * usage of an address santizer tools to avoid not allowed read or write actions in memory
  * writing own functions with low cyclomatic complexity for easy maintenance
  * strict exit during wrong usage of own functions with detailed error logging (origin .c-filename + line number)
  * usage of CppCheck and Splint tool for static code analysis
  * high code coverage for own functions with lcov tool
* showing the ratio between source code for the production code and unit tests
  * ratio 1:4
  * so for 1 production code line I need 4 additional lines of code to test it
* statistics for the amount of allocation, reallocation and free calls
* "One-file compilation" approach with multi *.c file structure: You compile the whole website with one GCC bash line.
