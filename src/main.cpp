#include <Matrix.h>

int main()
{
    Matrix mat(32, 32);
    mat.print();
    std::cout << "FINISHING ... " << std::endl;

#if 0
    int row =7, col = 7;arr_size = 7;
    int depth = 2;
    int arr_minsize = 3;
    int arr_minsize1  = 1;
    int arr_outsize = 0;
    int arr_outsize1 = 2;
    Matrix in_matrix(7), kernel(3);

    arr_outsize = arr_size - (arr_minsize - 1);
    std::cout<<"size = " <<arr_outsize<<"\n";

    int in_matrix[depth][arr_size][arr_size]{};
    int kernel[arr_minsize1][arr_minsize][arr_minsize]{};
    int arrout[arr_outsize1][arr_outsize][arr_outsize]{};
    srand(time(nullptr));



    //initialization of the matrix arr
    for(int k = 0; k < depth; ++k) {
        for (int i = 0; i < arr_size; ++i) {
            for (int j = 0; j < arr_size; ++j) {
                arr[k][i][j] = (rand() % 9) + 0;
            }
        }
    }

    for(int k = 0; k < depth; ++k) {
        std::cout<<"\n";
        for (int i = 0; i < arr_size; ++i) {
            for (int j = 0; j < arr_size; ++j) {
                std::cout << arr[k][i][j]<< " ";
            }
            std::cout<<"\n";
        }
    }
    std::cout<<"\n\n";

    //initialization of the matrix kernel
    for (int k = 0; k < arr_minsize1; ++k) {
        for (int i = 0; i < arr_minsize; ++i) {
            for (int j = 0; j < arr_minsize; ++j) {
                kernel[k][i][j] = (rand() % 9) + 0;
            }
        }
    }

    for (int k = 0; k < arr_minsize1; ++k) {
        std::cout<<"\n";
        for (int i = 0; i < arr_minsize; ++i) {
            for (int j = 0; j < arr_minsize; ++j) {
                std::cout << kernel[k][i][j] << " ";
            }
            std::cout<<"\n";
        }
    }

    //Dot product
    for (int k = 0; k < depth; ++k) {
        for (int i = 0; i < arr_outsize; ++i) {
            for (int j = 0; j < arr_outsize; ++j) {

                int sum{}; 
                for (int a = 0; a < arr_minsize; ++a) {
                    for (int b = 0; b < arr_minsize; ++b ) {
                        sum += kernel[k][a][b] * arr[k][b+i][a+j];

                    }
                }
                arrout[k][i][j] = sum;
            }
        }
    }
    //print arrout

    for (int k = 0; k < arr_outsize1; ++k) {
        std::cout<<"\n";
        for (int i = 0; i < arr_outsize; ++i) {
            for (int j = 0; j < arr_outsize; ++j) {


                std::cout << arrout[k][i][j] <<" ";
            }
            std::cout<<"\n";
        }
    }
    /*
    //input file
    std::ofstream MyFile("filename.txt");

    for (int i = 0; i < arr_outsize; ++i) {
    for (int j = 0; j < arr_outsize; ++j) {
    MyFile << arrout[i][j]<<" ";
    }
    MyFile <<"\n";
    }

    MyFile.close();
    */

    return 0;
#endif
}
