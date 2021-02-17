#pragma once
#include <Matrix.h>
#include <FileReader.h>

#define OPTIONS_WIDTH 34
#define DESCRIPTION_WIDTH 110
#define PERIOD "  "

void help();
inline bool exists(const char * filename);
void handleOptions(int argc, char* argv[]);
void performConvolution(int matrix_idx, int kernel_idx, std::string filePath = "");
void storeResult(const std::string filePath, Json& json);

enum error_codes
{
    ERROR_OK,
    ERROR_OPEN_FILE,
    ERROR_FILE_NOT_EXIST,
    ERROR_IDX_OUT_OF_SCOPE,
};
