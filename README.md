# DynamicText
Core (DynamicText, text functions, stdlib-wrapper) for Web Development in C.

Project goals:

* web development in compiled programming languages like the C programming language
* basic set of functions for programming easily a website
* usage of FastCGI or CGI
  * cloud servers are available for just $5 per month
  * execute your compiled web sites with nginx and spawn-fcgi
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

![alt chart__lines_of_code](https://github.com/Maatuuli/DynamicText/blob/main/chart___lines_of_code.jpg?raw=true)

![alt code_coverage_overview](https://github.com/Maatuuli/DynamicText/blob/main/code_coverage.png?raw=true)
