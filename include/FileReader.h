#include <Matrix.h>
#include <json.h>
#include <string>
#include <memory>

#define MATRICES_FILE "matrix.json"
#define KERNELS_FILE "kernel.json"

using Json = nlohmann::json;

class FileReader
{
    public:
        FileReader(const FileReader&) = delete;
        FileReader(FileReader&&) = delete;
        FileReader& operator=(const FileReader&) = delete;
        FileReader& operator=(FileReader&&) = delete;

        static FileReader* getInstance();
        ~FileReader() = default;

        bool readJsonFile(const std::string file_name);
        void loadMatrices();
        void loadKernels();
        void storeMatrices();
        void storeKernels();
        Json matrixToJson(std::shared_ptr<Matrix> matrix);
        std::shared_ptr<Matrix> jsonToMatrix(Json& json);

        Json json_objects;
        std::vector<std::shared_ptr<Matrix>> matrices;
        std::vector<std::shared_ptr<Matrix>> kernels;

    private:
        FileReader();
        static FileReader* instance;

};
