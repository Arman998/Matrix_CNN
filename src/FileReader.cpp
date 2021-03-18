#include <FileReader.h>
#include <assert.h>
FileReader* FileReader::instance = nullptr;

FileReader* FileReader::getInstance()
{
    if (instance == nullptr) {
        try {
            instance = new FileReader();
        } catch (const std::bad_alloc& err) {
            std::cout << "Memory allocation failed: " << err.what() << std::endl;
        }
    }
    assert(instance != nullptr);
    return instance;
}

/*
 The function is to load the kernels or matrices from json file into the json 
 object. The parameter file_name should specify either matrices.json or 
 kernels.js on file.
*/
bool FileReader::readJsonFile(const std::string file_name)
{
    if (MATRICES_FILE != file_name && KERNELS_FILE != file_name) {
        std::cout << "Error: Unknown file name \"" << file_name << "\" is specified" << std::endl;
        return false;
    }

    std::ifstream json_file(file_name, std::ios::in);
    if (json_file.is_open() && !(json_file.peek() == std::ifstream::traits_type::eof())) {
        json_objects.clear();
        json_file >> json_objects;
    }
    else {
        std::cout<<"Unable to open \"" << file_name << "\" file!" << std::endl;
        return false;
    }
    json_file.close();
    return true;
}

/*
 Load the matrices json data from file into the json object;
*/
void FileReader::loadMatrices()
{
    if (readJsonFile(MATRICES_FILE)) {
        matrices.clear();
        for (auto& obj: json_objects) {
            matrices.push_back(jsonToMatrix(obj));
        }
    }
}

/*
 Load the kernels json data from file into the json object;
*/
void FileReader::loadKernels()
{
    if (readJsonFile(KERNELS_FILE)) {
        kernels.clear();
        for (auto& obj: json_objects) {
            kernels.push_back(jsonToMatrix(obj));
        }
    }
}

/*
 Store the generated matrices data into the json file;
*/
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
        std::cout<<"Unable to open the \"" << MATRICES_FILE << "\" file" << std::endl;
    }
}


/*
 Store the generated kernels data into the json file
*/
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
        std::cout<<"Unable to open the \"" << KERNELS_FILE << "\" file" << std::endl;
    }
}

/*
 The function will be regenerate the matrices and kernels data based on provided
 CLI options. The option -M must be soecified to generate matrices file.The -K
 option must be specified to generate kernels file. the both matrices and
 kernels files will be regenerated if both of -M and -K options are specified.

*/

void FileReader::regenerateMatrices(bool opt_mat, bool opt_krn, int count)
{

    if (opt_mat || ! opt_krn) {

        int idx = 0;
        while (idx < count) {
            std::cout << "Please enter the dimensions for the matrix" << (idx + 1) << ": ";
            int row = 0, col = 0;
            std::cin >> row >> col;
            assert (row > 1);
            assert (col > 1);
            std::shared_ptr<Matrix> mat = allocateMemMatrix(row, col);
            assert(nullptr != mat);
            matrices.push_back(mat);
            ++idx;
        }
        storeMatrices();
    }

    if (opt_krn) {
        int idx = 0;
        while (idx < count) {
            std::cout << "Please enter the dimensions for the kernel" << (idx + 1) << ": ";
            int row = 0, col = 0;
            std::cin >> row >> col;
            assert (row > 1);
            assert (col > 1);
            std::shared_ptr<Matrix> krn = allocateMemMatrix(row, col);
            assert(nullptr != krn);
            kernels.push_back(krn);
            ++idx;
        }
        storeKernels();
    }
}
/*
 The function writes the matrices to the file in Json format
*/
Json FileReader::matrixToJson(std::shared_ptr<Matrix> matrix)
{
    Json json;
    json["row_size"] = matrix.get()->getRowSize();
    json["column_size"] = matrix.get()->getColumnSize();
    json["matrix2D"] = matrix.get()->getMatrix2D();
    return json;
}
/*
 The function reads the matrix written in json format from the file and assigns
 it to the matrix 
*/
std::shared_ptr<Matrix> FileReader::jsonToMatrix(Json& json)
{
    int row = json["row_size"].get<int>();
    int col = json["column_size"].get<int>();
    std::shared_ptr<Matrix> matrix = allocateMemMatrix(row, col);
    matrix->setMatrix2D(json["matrix2D"].get<std::vector<std::vector<int>>>());
    return matrix;
}

const Matrix& FileReader::getMatrixAt(int index) const
{
    return *this->matrices[index].get();
}

const Matrix& FileReader::getKernelAt(int index) const
{
    return *this->kernels[index].get();
}

int FileReader::matricesSize()
{
    return matrices.size();
}

int FileReader::kernelsSize()
{
    return kernels.size();
}
/*
 The function checks for memory and returns if available
*/

std::shared_ptr<Matrix> FileReader::allocateMemMatrix(int row, int col)
{
    std::shared_ptr<Matrix> mat(nullptr);
    try {
        mat = std::shared_ptr<Matrix> (new Matrix(row, col));
    } catch (const std::bad_alloc& err) {
        std::cout << "Memory allocation failed: " << err.what() << std::endl;
    }
    assert(nullptr != mat);
    return mat;
}
