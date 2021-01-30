#include <FileReader.h>

FileReader* FileReader::instance = nullptr;

FileReader::FileReader() {}

FileReader* FileReader::getInstance()
{
    if (instance == nullptr) {
        instance = new FileReader();
    }
    return instance;
}

bool FileReader::readJsonFile(const std::string file_name)
{
    std::cout<<"file_name: " << file_name;
    if (MATRICES_FILE != file_name && KERNELS_FILE != file_name) {
        std::cout << "Error: Unknown file name is specified" << std::endl;
        return false;
    }

    std::ifstream json_file(file_name, std::ios::in);
    if(json_file.is_open() && !(json_file.peek() == std::ifstream::traits_type::eof())) {
        json_objects.clear();
        json_file >> json_objects;
    }
    else {
        std::cout<<"Unable to open json_file";
        return false;
    }
    json_file.close();
    return true;
}

void FileReader::loadMatrices()
{
    if (readJsonFile(MATRICES_FILE)) {
        matrices.clear();
        for (auto& obj: json_objects) {
            matrices.push_back(jsonToMatrix(obj));
        }
    }
}

void FileReader::loadKernels()
{
    if (readJsonFile(KERNELS_FILE)) {
        kernels.clear();
        for (auto& obj: json_objects) {
            kernels.push_back(jsonToMatrix(obj));
        }
    }
}

void FileReader::storeMatrices()
{
    json_objects.clear();
    for (auto& mat: matrices) {
        json_objects.push_back(matrixToJson(mat));
    }

    std::ofstream json_file(MATRICES_FILE, std::ios::out | std::ofstream::trunc);
    if (json_file.is_open()) {
        json_file << std::setw(4) << json_objects;
    }
    else {
        std::cout<<"Unable to open file";
    }
}

void FileReader::storeKernels()
{
    json_objects.clear();
    for (auto& mat: kernels) {
        json_objects.push_back(matrixToJson(mat));
    }

    std::ofstream json_file(KERNELS_FILE, std::ios::out | std::ofstream::trunc);
    if (json_file.is_open()) {
        json_file << std::setw(4) << json_objects;
    }
    else {
        std::cout<<"Unable to open file";
    }
}

Json FileReader::matrixToJson(std::shared_ptr<Matrix> matrix)
{
    Json json;
    json["row_size"] = matrix.get()->getRowSize();
    json["column_size"] = matrix.get()->getColumnSize();
    json["matrix2D"] = matrix.get()->matrix2D;
    return json;
}

std::shared_ptr<Matrix> FileReader::jsonToMatrix(Json& json)
{
    int row = json["row_size"].get<int>();
    int col = json["column_size"].get<int>();
    std::shared_ptr<Matrix> matrix(new Matrix(row, col));
    matrix->matrix2D = json["matrix2D"].get<std::vector<std::vector<int>>>();
    return matrix;
}