### Directory structure

#### Glossary
 - kpc : It is file extension stands for kernel program character. This is kernel program which to be executed by compute
 	unit like gpu/cpu core. 
 
#### Library linking via GCC
 
 ```
 -llibrary
Search the library named library when linking.
It makes a difference where in the command you write this option; the linker searches processes libraries and object files in the order they are specified. Thus, `foo.o -lz bar.o' searches library `z' after file `foo.o' but before `bar.o'. If `bar.o' refers to functions in `z', those functions may not be loaded.

The linker searches a standard list of directories for the library, which is actually a file named `liblibrary.a'. The linker then uses this file as if it had been specified precisely by name.

The directories searched include several standard system directories plus any that you specify with `-L'.

Normally the files found this way are library files--archive files whose members are object files. The linker handles an archive file by scanning through it for members which define symbols that have so far been referenced but not defined. But if the file that is found is an ordinary object file, it is linked in the usual fashion. The only difference between using an `-l' option and specifying a file name is that `-l' surrounds library with `lib' and `.a' and searches several directories.
 ```
 
 With above knowledge and below location OpenCL in linux platform. You can use -lOpenCL to link opencl during compile time
 ```
 ubuntu@ubuntu:/usr/lib/aarch64-linux-gnu$ sudo ls libOpenCL.so 
libOpenCL.so
ubuntu@ubuntu:/usr/lib/aarch64-linux-gnu$ pwd
/usr/lib/aarch64-linux-gnu
 ```
 
Note: linking is different than including api of the library. One more thing that generall under /usr/lib or /usr/include is system
path hence you don't need to use -L to explicitly specify the path of linker library. 