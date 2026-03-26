#include "snapshot_writer.hxx"

#include <iostream>

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

        outFile << "time\tx\ty\tvx\tvy\n";
        outFile.precision(10);
        outFile << std::fixed;
    }

    SnapshotWriter::~SnapshotWriter()
    {
        outFile.close();
    }

    void SnapshotWriter::writeSnapshot(double time, const Particle& particle)
    {
        outFile << time << "\t" << particle.x << "\t" << particle.y << "\t"
                << particle.vx << "\t" << particle.vy << "\n";
    }
}
