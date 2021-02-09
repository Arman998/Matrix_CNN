#pragma once
#include <Matrix.h>
#include <FileReader.h>

#define OPTIONS_WIDTH 34
#define DESCRIPTION_WIDTH 110
#define PERIOD "  "

void help();
inline bool exists(const char * filename);
void handleOptions(int argc, char* argv[]);
void performConvolution(int matrix_idx, int kernel_idx);
void storeResult(const std::string file_name, Json& json);
