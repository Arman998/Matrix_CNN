#include <Matrix.h>
#include <FileReader.h>

void outResultToFile(const std::string file_name, Json& json);
void cnn(int matrix_idx, int kernel_idx);

void outResultToFile(const std::string file_name, Json& json)
{
    std::ofstream json_file(file_name, std::ios::out | std::ofstream::app);
    if (json_file.is_open()) {
        json_file << std::setw(4) << json;
    }
    else {
        std::cout<<"Unable to open the file: " << file_name;
    }
    json_file.close();
}

void cnn(int matrix_idx, int kernel_idx)
{

    FileReader* reader = FileReader::getInstance();
    if (matrix_idx >= reader->matrices.size()) {
        std::cout << "The provided matrix index: "<< matrix_idx <<"is not exist" << std::endl;
        return;
    }
    if (matrix_idx >= reader->matrices.size()) {
        std::cout << "The provided kernel index: "<< kernel_idx <<"is not exist" << std::endl;
    }
    Matrix mat = *(reader->matrices[matrix_idx].get());
    Matrix krn = *(reader->kernels[kernel_idx].get());
    Matrix cnn_mat = mat.doCNN(krn);
    cnn_mat.print();

    char file_name[100];
    std::sprintf(file_name, "result_%d_%d.json", matrix_idx, kernel_idx);
    Json j_object = reader->matrixToJson(std::make_shared<Matrix>(cnn_mat));
    outResultToFile(file_name, j_object);
}

int main()
{

    FileReader* reader = FileReader::getInstance();

    // std::shared_ptr<Matrix> mat1(new Matrix(32, 32));
    // std::shared_ptr<Matrix> mat2(new Matrix(17, 17));
    // std::shared_ptr<Matrix> mat3(new Matrix(9, 9));
    // std::shared_ptr<Matrix> mat4(new Matrix(15, 15));
    // reader->matrices.push_back(mat1);
    // reader->matrices.push_back(mat2);
    // reader->matrices.push_back(mat3);
    // reader->matrices.push_back(mat4);
    // reader->storeMatrices();

    // std::shared_ptr<Matrix> krn1(new Matrix(5, 5));
    // std::shared_ptr<Matrix> krn2(new Matrix(4, 4));
    // std::shared_ptr<Matrix> krn3(new Matrix(3, 3));
    // reader->kernels.push_back(krn1);
    // reader->kernels.push_back(krn2);
    // reader->kernels.push_back(krn3);
    // reader->storeKernels();


    reader->loadMatrices();
    reader->loadKernels();
    cnn(0, 0);
    std::cout << "######################################################################################################" << std::endl;
    cnn(3, 1);





    // Convolution over all matrices with the first kernel
    /*
    for (auto& mat: reader->matrices) {
        mat->print();
        std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" <<std::endl;
        Matrix k = *(reader->kernels[0].get());
        k.print();
        std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" <<std::endl;
        Matrix cnn_mat = mat->doCNN(k);
        cnn_mat.print();
        Json j_object = reader->matrixToJson(std::make_shared<Matrix>(cnn_mat));
        outResultToFile("result.json", j_object);

    }
    */




/*    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "================================================================================"<< std::endl;
    std::cout << "===================================== 3D ======================================="<< std::endl;
    std::cout << "================================================================================"<< std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::vector<Matrix> matrix3D(3);
    std::vector<Matrix> filter3D(3);
    std::vector<Matrix> product3D;
    for (int i = 0; i < matrix3D.size(); ++i) {
        matrix3D[i] = Matrix(32, 32);
        filter3D[i] = Matrix(7, 7);

        product3D.push_back(matrix3D[i].doCNN(filter3D[i]));
        std::cout << "===================================" << i <<"========================================="<< std::endl;
        product3D[i].print();
        std::cout << "===================================" << i <<"========================================="<< std::endl;
    }
    */
    return 0;
}
