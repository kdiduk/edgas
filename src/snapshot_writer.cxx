#include "snapshot_writer.hxx"

#include <iostream>

#include "model.hxx"
#include "particle.hxx"


namespace edgas
{
    SnapshotWriter::SnapshotWriter(const std::string& filename)
    {
        outFile.open(filename);
        if (!outFile.is_open()) {
            std::cerr << "Error: Could not open file " << filename << " for writing snapshots." << std::endl;
            throw std::runtime_error("Failed to open snapshot file: " + filename);
        }

        outFile.precision(10);
        outFile << std::fixed;
    }

    SnapshotWriter::~SnapshotWriter()
    {
        outFile.close();
    }

    void SnapshotWriter::writeSnapshot(const Model& model)
    {
        outFile << model.globalTime << '\n';
        for (const auto& particle : model.particles) {
            outFile << particle.x << '\t' << particle.y << '\t'
                    << particle.vx << '\t' << particle.vy << "\n";
        }
        outFile.flush();
    }
}
