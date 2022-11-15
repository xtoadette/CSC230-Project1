/*
 Name:  Stephanie Contino
 Date:  9/20/22
 File Name: Project1.cpp
 Description: This program reads a text file of a word search grid and searches the grid for a word given by user input.  The
            grid is stored in an input array, and the found location is stored in an output array.
 */
#include <iostream>
#include <fstream>

using namespace std;

//global variables
int nrows;
int ncols;
char* input;
char* output;

//initGame- reads in file and creates array of characters
bool initGame(string filename)
{
    ifstream fin(filename);
    
    //check if file was found
    if (!fin.is_open())
    {
        cout << filename << " not found" << endl;
        return false;
    }
    
    fin >> nrows;
    fin >> ncols;
    
    input = new char[nrows*ncols];
    output = new char[nrows*ncols];
    
    for (int i = 0; i < nrows*ncols; i++)
    {
        fin >> input[i];
        output[i] = '-';
    }
    
    return true;
}

//printGrid- prints the one dimensional array as a grid
void printGrid(char output[])
{
    //nested for loop to print grid
    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
        {
            cout << output[i*ncols+j] << " ";
        }
        cout << endl;
    }
}

//isWordAtInput- finds the input word in the array of chars
bool isWordAtInput(string word, int r, int c, int rincr, int cincr)
{
    int i = 0;
    int len = word.length();
    
    //checks first character before moving on
    if (word.at(i) == input[r * ncols + c])
    {
        r += rincr;
        c += cincr;
        
        //checks next characters until the end of the word
        for (i = 1; i < len; i++)
        {
            //error checks input
            if (c < 0 || c >= ncols)
            {
                break;
            }
            else if (r < 0 || r >= nrows)
            {
                break;
            }
            else if (word.at(i) != input[r * ncols + c])
            {
                break;
            }
            else
            {
                r += rincr;
                c += cincr;
            }
        }
        
        //returns true if the loop was successfully completed
        if (i == len)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    //if everything failed
    else
    {
        return false;
    }
}

//setWordAtOutput- moves the found word to the output grid
void setWordAtOutput(string word, int r, int c, int rincr, int cincr)
{
    for (int i = 0; i < word.length(); i++)
    {
        char a = word[i];
        output[r * ncols + c] = a;
        r += rincr;
        c += cincr;
    }
}

//findWord- locates the word by looping in each direction
void findWord(string word)
{
    //North
    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
        {
            if (isWordAtInput(word, i, j, -1, 0))
                setWordAtOutput(word, i, j, -1, 0);
        }
    }
    
    //South
    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
        {
            if (isWordAtInput(word, i, j, 1, 0))
                setWordAtOutput(word, i, j, 1, 0);
        }
    }
    
    //East
    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
        {
            if (isWordAtInput(word, i, j, 0, 1))
                setWordAtOutput(word, i, j, 0, 1);
        }
    }
    
    //West
    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
        {
            if (isWordAtInput(word, i, j, 0, -1))
            setWordAtOutput(word, i, j, 0, -1);
        }
    }
    
    //Southwest
    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
        {
            if (isWordAtInput(word, i, j, 1, -1))
                setWordAtOutput(word, i, j, 1, -1);
        }
    }
    
    //Southeast
    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
        {
            if (isWordAtInput(word, i, j, 1, 1))
                setWordAtOutput(word, i, j, 1, 1);
        }
    }
    
    //Northwest
    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
        {
            if (isWordAtInput(word, i, j, -1, -1))
                setWordAtOutput(word, i, j, -1, -1);
        }
    }
    
    //Northeast
    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
        {
            if (isWordAtInput(word, i, j, -1, 1))
                setWordAtOutput(word, i, j, -1, 1);
        }
    }
    
}

//main- runs the program
int main(int argc, char* argv[]) {
    string filename(argv[1]);
    
    if (!initGame(filename)) { return -1; }
        printGrid(input);
    
    for (int i=2; i<argc; ++i) {
        string word(argv[i]);
        cout << "Searching for " << word << endl;
        findWord(word);
    }
    
    printGrid(output);
    delete input;
    delete output;
}
