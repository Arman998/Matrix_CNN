#include <helper.h>

int main(int argc , char* argv[])
{
    handleOptions(argc, argv);
    return 0;

    FileReader* reader = FileReader::getInstance();
    reader->loadMatrices();
    reader->loadKernels();
    doCNN(2, 2);
    std::cout << "######################################################################################################" << std::endl;
    doCNN(1, 1);
    return 0;
}
