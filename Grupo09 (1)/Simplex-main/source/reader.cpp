#include <eigen3/Eigen/Dense>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "simplex.h"

std::string read_compressed_mps(std::string str)
{
    std::string s = "./build/decomp ";
    s += str;
    s += " > ";
    std::string filename = "tests/decompressed/";

    int idx = str.size() - 1;
    char q = str[idx];

    while (q != '/') {
        idx--;
        q = str[idx];
    }

    filename += str.substr(idx + 1, str.size() - (idx + 1));

    s += filename;

    if (system(s.c_str()))
        exit(1);

    return filename;
}

void read_mps(std::string str)
{

    std::string s = "python3 build/p.py ";
    s += str;
    s += " > build/out.txt";
    std::cout << s;
    if (system(s.c_str()))
        exit(1);
}

Simplex Simplex::Reader::Read()
{

    char ans;
    std::string path;

    std::cout << "Do you want to read entry from mps or compressed mps file?"
              << "(c/y/n/h) [h for help.]\n";
    std::cin >> ans;

   
    switch (ans) {
    case 'c':
        std::cout << "Insert path to file" << std::endl;
        std::cin >> path;
        path = read_compressed_mps(path);
        read_mps(path);
        return ReadMatrix("build/out.txt");
        break;
    case 'y':
        std::cout << "Insert path to file" << std::endl;
        std::cin >> path;
        read_mps(path);
        return ReadMatrix("build/out.txt");
        break;
    case 'h':
         std::cout << "This program solves a lp problem using two phase Simplex "
                  << "and Bland's rule.\nThe file containing the lp can be a "
                     "compressed mps ("
                  << "c)\nregular mps (y)\nor txt specific format (n).\nAlso, the path must be"
                     " in the format:\n/home/user/.../file"
                     "\nTherefore\n";
        return Read();
    case 'n' :
        std::cout << "Insert path to file" << std::endl;
        std::cin >> path; 
        break;
    default :
        std::cout << "Invalid Option\n";
        return Read();
    }

    return ReadMatrix(path);
}

Simplex Simplex::Reader::ReadMatrix(const std::string path)
{
    Simplex s = Simplex();
    file_d.open(path, std::ios_base::in);
    int rows, cols; // restrictions, variables

    if (file_d.is_open()) {
        file_d >> rows >> cols;
    } else {
        std::cout << "Invalid path to file" << std::endl;
        exit(2);
    }

    std::vector<float> matrix_entries; // holds the integers to become matrix
    std::vector<float> cost_fnt;       // holds the integers to become matrix

    ReadLineFiletoVec(cost_fnt);
    ReadLineFiletoVec(cost_fnt);
    for (int i = 0; i <= rows + 1; i++) { // reads the cost and then n rows
        ReadLineFiletoVec(matrix_entries);
    }

    MatrixXf T = Eigen::Map<Matrix<float, Dynamic, Dynamic, Eigen::RowMajor>>(
        matrix_entries.data(), rows, cols + 1); // converts array to row matrix

    MatrixXf cst = Eigen::Map<Matrix<float, Dynamic, Dynamic, Eigen::RowMajor>>(
        cost_fnt.data(), 1, cols); // converts array to row matrix
    s.c = cst.row(0);
    s.b = T.col(cols);
    s.A = T.block(0, 0, rows, cols);

    s.restrictions = rows;
    s.variables = cols;

    return s;
}

void Simplex::Reader::ReadLineFiletoVec(std::vector<float> &vec)
{
    std::string matrix_row;   // current line from file
    std::string matrix_entry; // parsed integer from matrix_row
    getline(file_d, matrix_row);

    std::stringstream matrixRowStringStream(matrix_row);
    while (getline(matrixRowStringStream, matrix_entry, ' '))
    // parses int separated by space
    {
        vec.push_back(stof(matrix_entry)); // adds int to vector
    }
}
