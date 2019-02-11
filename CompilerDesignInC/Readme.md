# Compiler Design in Visual C++
In this folder, all the source files are compatible with Visual C++

For e.g. In windows, we have to use

1. [scanf_s() instead of scanf()](http://faculty.edcc.edu/paul.bladek/CS131/scanf_s.htm)
2. fopen_s() instead of fopen()
3. gets_s() instead of gets() etc.
## Description
There are **3 sections**

1. [Header Files](https://github.com/sdc224/Compiler-Design-Programs/tree/master/CompilerDesignInC/Header%20Files)
2. [Implementations](https://github.com/sdc224/Compiler-Design-Programs/tree/master/CompilerDesignInC/Implementations)
3. [Main Functions](https://github.com/sdc224/Compiler-Design-Programs/tree/master/CompilerDesignInC/MainFunctions)

The folder structure inside Header Files and Implementations are same, for e.g., if Header Files contain Dfa, then Implementations must contain Nfa. For those developers who want to contribute us in our project, please follow the same rule, else pull requests may be invalidated.

**Header Files** contain all the header files that are used in this program(*additional header files*). Due to this kind of folder structure, the configuration files can be easily created and the additional include directories can be easily added.

**Implementations** contain the resource files, as well as the implementation of functions and other *extern variables*. So if anyone wants to see what's happening inside of the functions of header files, he/she should go to this directory.

**Main Function** is for lab purpose, it contain files that have main function, means presentaion file. Sorry, but it is still in development phase.

The **abc.txt** file is used for our testing, feel free to *change it as well as its extension*, it will work.
## Additional Words
Changes are always welcome, but please follow the rules in order to change or addition of any source or header files.

For VS users, please include all the files in your project(solution). I have not yet completed the development part of the .sln and .csproj file, so please do any changes if you want(by *cloning*).