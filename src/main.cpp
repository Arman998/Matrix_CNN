#include <Matrix.h>

int main()
{

    srand(time(nullptr));
    Matrix mat(32, 32);
    std::cout << "Displaying the main matrix" << std::endl;
    mat.print();
    std::cout << std::endl;

    Matrix aaa(5, 5);
    std::cout << "Displaying the filter matrix" << std::endl;
    aaa.print();
    std::cout << std::endl;

    std::cout << "Displaying the Convolution matrix" << std::endl;
    Matrix product = mat.doCNN(aaa);
    product.print();
    return 0;
}
