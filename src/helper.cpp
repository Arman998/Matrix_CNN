#include <helper.h>
#include <getopt.h>

/*
 * USAGE: <path_to>/matrix_cnn [OPTIONS]...
 * The following options are supported:
 *
 * 	-R, --regenerate                 Regenerate matrices
 * 	                                  the -M option will be choosen by default if there is not specified,
 * 	                                  which file must be regenerated(matrices or kernels)!
 *
 * 	-M, --matrices                   Choose the 'matrices.json' file to be generated, if the --regenerate option is specified!
 *
 * 	-K, --kernels                    Choose the 'kernels.json' file to be generated, if the --regenerate option is specified!
 *
 * 	-C, --count <value>              Provide the number of matrices that must be genearated!
 * 	                                  Default value to generate matrices is 5!
 * 	                                  The dimensions of each matrix must be provided separately from CLI
 *
 * 	-O, --output <file_path>         Store the result matrix into the file provided by the option.
 * 	                                  The result.json file will be created in the current working directory,
 * 	                                  if there is not provided the output file!
 *
 * 	--do_cnn <-m> value <-k> value   Do convolution operation on matrix with id: -m matrix_id, by the kernel with id: -k kernel_id
 * 	                                  Note: the -m and -k options with their values are mandatory options!
 *
 * Examples of usage:
 * 	./matrix_cnn --regenerate -K --count 5
 * 	./matrix_cnn --do_cnn -m 3 -k 2 -O /home/workspace/output.json
*/
void help()
{
    std::cout << "USAGE: <path_to>/matrix_cnn [OPTIONS]... " << std::endl;
    std::cout << "The following options are supported:" << std::endl;

    std::cout << std::endl;
    std::cout << std::left << std::setw(OPTIONS_WIDTH)
        << "\t-R, --regenerate" << std::setw(DESCRIPTION_WIDTH)
        << "Regenerate matrices"<< std::endl
        << "\t" << std::setw(OPTIONS_WIDTH) << PERIOD << std::setw(DESCRIPTION_WIDTH)
        << "the -M option will be choosen by default if there is not specified,"<< std::endl
        << "\t" << std::setw(OPTIONS_WIDTH) << PERIOD << std::setw(DESCRIPTION_WIDTH)
        << "which file must be regenerated(matrices or kernels)!"<< std::endl
        << "\t" << std::setw(OPTIONS_WIDTH) << PERIOD << std::setw(DESCRIPTION_WIDTH)
        << "both of files will be generated if both of -M and -K options are specified"<< std::endl;

    std::cout << std::endl;
    std::cout << std::left << std::setw(OPTIONS_WIDTH)
        << "\t-M, --matrices" << std::setw(DESCRIPTION_WIDTH)
        << "Choose the 'matrices.json' file to be generated, if the --regenerate option is specified!"<< std::endl;

    std::cout << std::endl;
    std::cout << std::left << std::setw(OPTIONS_WIDTH)
        << "\t-K, --kernels" << std::setw(DESCRIPTION_WIDTH)
        << "Choose the 'kernels.json' file to be generated, if the --regenerate option is specified!"<< std::endl;

    std::cout << std::endl;
    std::cout << std::left << std::setw(OPTIONS_WIDTH)
        << "\t-C, --count <value>" << std::setw(DESCRIPTION_WIDTH)
        << "Provide the number of matrices that must be genearated!"<< std::endl
        << "\t" << std::setw(OPTIONS_WIDTH) << PERIOD << std::setw(DESCRIPTION_WIDTH)
        << "Default value to generate matrices is 5."<< std::endl
        << "\t" << std::setw(OPTIONS_WIDTH) << PERIOD << std::setw(DESCRIPTION_WIDTH)
        << "The dimensions of each matrix must be provided separately from CLI" << std::endl;

    std::cout << std::endl;
    std::cout << std::left << std::setw(OPTIONS_WIDTH)
        << "\t-O, --output <file_path>" << std::setw(DESCRIPTION_WIDTH)
        << "Store the result matrix into the file provided by the option."<< std::endl
        << "\t" << std::setw(OPTIONS_WIDTH) << PERIOD << std::setw(DESCRIPTION_WIDTH)
        << "The result.json file will be created in the current working directory,"<< std::endl
        << "\t" << std::setw(OPTIONS_WIDTH) << PERIOD << std::setw(DESCRIPTION_WIDTH)
        << "if there is not provided the output file!"<< std::endl;

    std::cout << std::endl;
    std::cout << std::left << std::setw(OPTIONS_WIDTH)
        << "\t--do_cnn <-m> value <-k> value" << std::setw(DESCRIPTION_WIDTH)
        << "Do convolution operation on matrix with id: -m matrix_id, by the kernel with id: -k kernel_id"<< std::endl
        << "\t" << std::setw(OPTIONS_WIDTH) << PERIOD << std::setw(DESCRIPTION_WIDTH)
        << "Note: the -m and -k options are mandatory options, and the arguments shuld be >= 1 number!"<< std::endl;

    std::cout << std::endl;
    std::cout << "Examples of usage:" << std::endl;
    std::cout << "\t./matrix_cnn --regenerate -K --count 5" << std::endl;
    std::cout << "\t./matrix_cnn --do_cnn -m 3 -k 2 -O /home/workspace/output.json" << std::endl;
}

inline bool exists(const char* filename)
{
    std::ifstream file(filename);
    return file.good();
}


void handleOptions(int argc, char* argv[])
{
    if (argc == 1) {
        help();
        exit(1);
	}

    int opt = -1;
    bool regenerate = false;
    bool opt_mat = false, opt_krn = false;
    int count = 5;
    bool do_cnn = false;
    int mat_idx = 0, krn_idx = 0;
    std::string filePath;

    const char* short_options = "RMKC:O:m:k:d";
    static struct option long_options[] = {
        {"regenerate", no_argument, nullptr, 'R'},
        {"matrices", no_argument, nullptr, 'M'},
        {"kernels", no_argument, nullptr, 'K'},
        {"count", required_argument, nullptr, 'C'},
        {"output", required_argument, nullptr, 'O'},
        {"do_cnn", no_argument, nullptr, 'd'},
        {nullptr, 0, nullptr, 0}
    };

    while ((opt = getopt_long(argc, argv, short_options, long_options, NULL)) != -1)
    {
        switch (opt)
        {
            case 'R':
                regenerate = true;
                break;
            case 'M':
                opt_mat = true;
                break;
            case 'K':
                opt_krn = true;
                break;
            case 'C': {
                    count = atoi(optarg);
                }
                break;
            case 'O':
                filePath = optarg;
                break;
            case 'm':
                mat_idx = atoi(optarg);
                break;
            case 'k':
                krn_idx = atoi(optarg);
                break;
            case 'd':
                do_cnn = true;
                break;
            case '?':
            default:
                std::cout << "Unknown option is specified!" << std::endl;
                help();
                break;
        }
    }

    FileReader* reader = FileReader::getInstance();
    if (regenerate) {
        reader->regenerateMatrices(opt_mat, opt_krn, count);
    }

    if (do_cnn) {
        if(mat_idx < 1 || krn_idx < 1) {
            help();
            return;
        }
        performConvolution(mat_idx - 1, krn_idx - 1, filePath);
    }
}

void performConvolution(int matrix_idx, int kernel_idx, std::string filePath)
{
    if(! exists(MATRICES_FILE)) {
        std::cout << "Faild to load the \"" << MATRICES_FILE << "\" file: File not found!" << std::endl;
        exit(ERROR_FILE_NOT_EXIST);
    }

    if(! exists(KERNELS_FILE)) {
        std::cout << "Faild to load the \"" << KERNELS_FILE << "\" file: File not found!" << std::endl;
        exit(ERROR_FILE_NOT_EXIST);
    }

    FileReader* reader = FileReader::getInstance();
    reader->loadMatrices();
    reader->loadKernels();

    assert(matrix_idx >= 0);
    assert(kernel_idx >= 0);
    if (matrix_idx >= reader->matricesSize()) {
        std::cout << "The provided matrix index: \""<< matrix_idx + 1<<"\" does not exist!" << std::endl;
        exit(ERROR_IDX_OUT_OF_SCOPE);
    }
    if (kernel_idx >= reader->kernelsSize()) {
        std::cout << "The provided kernel index: \""<< kernel_idx + 1<<"\" does not exist!" << std::endl;
        exit(ERROR_IDX_OUT_OF_SCOPE);
    }
    Matrix mat = reader->getMatrixAt(matrix_idx);
    Matrix krn = reader->getKernelAt(kernel_idx);
    Matrix cnn_mat = mat.doCNN(krn);
    //cnn_mat.print();

    Json j_object = reader->matrixToJson(std::make_shared<Matrix>(cnn_mat));
    if(filePath.empty()) {
        char name[100];
        std::sprintf(name, "result_%d_%d.json", matrix_idx + 1, kernel_idx + 1);
        filePath = name;
    }
    storeResult(filePath, j_object);
}


void storeResult(const std::string filePath, Json& json)
{
    std::ofstream json_file(filePath, std::ios::out | std::ofstream::trunc);
    if (json_file.is_open()) {
        json_file << std::setw(4) << json;
        json_file.close();
    } else {
        std::cout<<"Unable to open the file: " << filePath;
        exit(ERROR_OPEN_FILE);
    }
}

