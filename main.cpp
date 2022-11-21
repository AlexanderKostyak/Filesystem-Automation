#include <string>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <fstream>
#include <stack>

//FILESYSTEM DOCUMENTATION For Programmatic Automation 
// 2022 Alexander Kostyak
//https://monkeylearn.com/blog/word-embeddings-transform-text-numbers/    Word2Vec, includes sample training data
//note:

    //Windows Filesystem has a max path length of 260 characters, frequently surpassed by some apps like OpenFOAM or Eclipse IDE
    //Irregular non-ASCII chars in foldernames and filenames will also throw exceptions in the stl filesystem utilization
    //the stl supported std::filesystem::recursive_directory_iterator works well in local directories but errors in drive scope
    //to capture all supported files, many try-catch blocks are used in conjunction with path vectors and manual recurison


/*The MIT License (MIT)
Copyright © 2022 Alexander Joseph Kostyak

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), 
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, 
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/


namespace fs =   std::filesystem;

void outputcontents(const fs::path, std::vector<fs::path>*) ;
void outputfilecontents(std::vector<fs::path>*);
std::string getfile(std::string);
void writetofile(std::string);
int counter,totalfolders,totalfiles = -1;

std::fstream file;

int main()
{
    fs::path pathname = "C:\\";
    std::vector<fs::path> *folders = new std::vector<fs::path>;

    file.open("FolderTree.txt", std::ios_base::out);
    outputcontents(pathname,folders);
    file.close();

    totalfolders = counter;
    counter = -1;
        std::system("CLS");
        std::cout << "Filesystem Automation has documented your filesystem folder paths for your entire PC" << std::endl <<
            "This information is used to evaluate your organization methods and serves as a backup for folder file locations" << std::endl << std::endl <<
            "FOLDERS SCANNED:   " << totalfolders << std::endl << std::endl << 
            "Filesystem Automation is now documenting individual file paths within the virtual folder paths collected" << std::endl << std::endl <<
            "CURRENT PATH LOCATION:   " << "C:" << std::endl << std::endl << "FILES SCANNED:   " << counter << std::endl;

    file.open("FileTree.txt", std::ios_base::out);
    outputfilecontents(folders);
    file.close();

    totalfiles = counter;
    counter = -1;
    std::system("CLS");
    std::cout << "Filesystem Automation has documented your filesystem folder paths for your entire PC" << std::endl <<
        "This information is used to evaluate your organization methods and serves as a backup for folder file locations" << std::endl << std::endl <<
        "FOLDERS SCANNED:   " << totalfolders << std::endl << std::endl <<
        "Filesystem Automation is now documenting individual file paths within the virtual folder paths collected" << std::endl << std::endl <<
        "FILES SCANNED:   " << totalfiles << std::endl << std::endl <<
        "Operation Completed, Proceed to Path Stack Vectorization and Neural Network Training" << std::endl << std::endl;

    std::cin.get();

    return 0;
}


void outputcontents(const fs::path pathwithcontents, std::vector<fs::path>* folders)
{
    std::error_code tmp;
    std::vector<std::string> files;
    std::vector<fs::path> thisdir;
    counter++;

    try
    {
        for (const auto& entry : fs::directory_iterator(pathwithcontents, fs::directory_options::skip_permission_denied, tmp))
        {
            if (entry.is_directory()) {
                folders->push_back(entry);
                thisdir.push_back(entry);
            }
        }
    }
    catch (const fs::filesystem_error& g)
    {
        std::cout << "err   " << g.code() << std::endl << g.path1() << std::endl << g.path2() << std::endl << g.what() << std::endl << std::endl;
        std::cout << tmp << tmp.message() << std::endl << tmp.value() << std::endl;
    }
    catch (const std::exception&)
    {

    }

    try
    {
        for (const fs::path dirpath : thisdir) {
            writetofile(dirpath.string());
            try
            {
                outputcontents(dirpath, folders);
            }
            catch (const fs::filesystem_error& g) {
                std::cout << "err   " << g.code() << std::endl << g.path1() << std::endl << g.path2() << std::endl << g.what() << std::endl << std::endl;
                std::cout << tmp << tmp.message() << std::endl << tmp.value() << std::endl;
            }
            catch (const std::exception&)
            {

            }
        }
    }
    catch (const fs::filesystem_error& g)
    {
        std::cout << "err   " << g.code() << std::endl << g.path1() << std::endl << g.path2() << std::endl << g.what() << std::endl << std::endl;
        std::cout << tmp << tmp.message() << std::endl << tmp.value() << std::endl;
    }
    catch (const std::exception&)
    {

    }
    
    if (counter % 1000 == 0){
        std::system("CLS");
        std::cout << "Filesystem Automation is now documenting your filesystem folder paths for your entire PC" << std::endl <<
            "This information is used to evaluate your organization methods and serves as a backup for existing folder locations" << std::endl << std::endl <<
            "CURRENT PATH LOCATION:   " << pathwithcontents << std::endl << std::endl << "FOLDERS SCANNED:   " << counter << std::endl;
    }
}

void outputfilecontents(std::vector<fs::path> *folders) {
    std::error_code tmp;

    try
    {
        int completed = 0;
        for (const auto& entry : *folders)
        {
            completed++;
            try
            {
                writetofile("FOLDER " + entry.string());
                counter++;
                for (const auto& fileentry : fs::directory_iterator(entry, fs::directory_options::skip_permission_denied, tmp))
                    
                    try {
                    counter++;
                    if (counter % 1000 == 0) {
                        std::system("CLS");
                        std::cout << "Filesystem Automation has documented your filesystem folder paths for your entire PC" << std::endl <<
                            "This information is used to evaluate your organization methods and serves as a backup for folder file locations" << std::endl << std::endl <<
                            "FOLDERS SCANNED:   " << totalfolders << std::endl << std::endl <<
                            "Filesystem Automation is now documenting individual file paths within the virtual folder paths collected" << std::endl << std::endl <<
                            "CURRENT PATH LOCATION:   " << fileentry.path().string() << std::endl << std::endl << "FILES SCANNED:   " << counter << std::endl <<
                            (int)(100*completed/folders->size()) << " % COMPLETE" << std::endl;
                    }
                    if (!fileentry.is_directory()) {
                        writetofile(fileentry.path().string());
                        //writetofile(fileentry.file_size...
                        }
                    }
                    catch (const fs::filesystem_error& g)
                    {
                        std::cout << "err   " << g.code() << std::endl << g.path1() << std::endl << g.path2() << std::endl << g.what() << std::endl << std::endl;
                        std::cout << tmp << tmp.message() << std::endl << tmp.value() << std::endl;
                    }
                    catch (const std::exception&)
                    {

                    }
            }
            catch (const std::exception&)
            {

            }
        }
    }
    catch (const fs::filesystem_error& g)
    {
        std::cout << "err   " << g.code() << std::endl << g.path1() << std::endl << g.path2() << std::endl << g.what() << std::endl << std::endl;
        std::cout << tmp << tmp.message() << std::endl << tmp.value() << std::endl;
    }
    catch (const std::exception&)
    {

    }
}


//Currently Unused in this script
std::string getfile(std::string filepath) {
    std::string parsed = "";
    int lastbackslash = 0;
    int parentbackslash = 0;
    int iter = 0;
    

    for (char stringpart : filepath) {
        parentbackslash = lastbackslash;
        if (stringpart == '\\')
            lastbackslash = iter;

        iter++;
    }
    return &filepath[parentbackslash+1];
}

//file is global
void writetofile(std::string pathstring) {
    
    if (file.is_open())
    {
        file << pathstring << std::endl;
    }

}
