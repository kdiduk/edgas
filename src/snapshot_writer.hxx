#ifndef EDGAS_SNAPSHOT_WRITER_HXX
#define EDGAS_SNAPSHOT_WRITER_HXX

#include <fstream>
#include <string>

namespace edgas
{
    struct Model;

    class SnapshotWriter {
    public:
        SnapshotWriter(const std::string& filename);
        ~SnapshotWriter();

        void writeSnapshot(const Model& model);
    
    private:
        std::ofstream outFile;
    };
}


#endif // EDGAS_SNAPSHOT_WRITER_HXX