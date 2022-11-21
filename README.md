# Filesystem-Automation
std:filesystem C++20 functions for filesystem analysis

the C++20 std::filesystem::recursive_directory_iterator can be used to browse a filetree as well.  It rarely works without throwing exceptions on an entire filesystem.  This script uses a traditional loop and ignores unusual files that throw errors, documenting your entire system's foldertree and filetree respectively.<br>

It takes a few minutes on my SSD, but would be much slower on a mechanical disk.  You may change the drive letter according to your preferred disk.  You must also have the C++20 compiler flag, the filesystem namespace was only recently introduced expiramentally in C++14.  It does include other functions to deduce file types, sizes, modification times, basic file operations, permissions, etc.<br>

I found rooting through filenames with ctrl+f was particularly more helpful than windows search in many cases.  I saw potential here for word-vector based automation in file organization.  If you want a more visual analysis of your drive utilization, I strongly recommend wiztree:<br>
https://diskanalyzer.com/
