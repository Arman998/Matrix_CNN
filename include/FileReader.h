#include <Matrix.h>
#include <json.h>
#include <string>
#include <memory>

#define MATRICES_FILE "matrices.json"
#define KERNELS_FILE "kernels.json"

using Json = nlohmann::json;

class FileReader
{
    public:
        FileReader(const FileReader&) = delete; // copy ctor
        FileReader(FileReader&&) = delete;      // move ctor
        FileReader& operator=(const FileReader&) = delete; // copy assignment
        FileReader& operator=(FileReader&&) = delete;      // move assignment

        static FileReader* getInstance();
        ~FileReader() = default;

        // Read json file into the json_objects
        bool readJsonFile(const std::string file_name);
        void loadMatrices();
        void loadKernels();
        void storeMatrices();
        void storeKernels();
        void regenerateMatrices(bool opt_mat, bool opt_krn, int count);
        Json matrixToJson(std::shared_ptr<Matrix> matrix);
        std::shared_ptr<Matrix> jsonToMatrix(Json& json);


        Json json_objects;
        std::vector<std::shared_ptr<Matrix>> matrices;
        std::vector<std::shared_ptr<Matrix>> kernels;

    private:
        FileReader() {};
        static FileReader* instance;

};
