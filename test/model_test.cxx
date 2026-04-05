#include <cmath>
#include <set>

#include <gtest/gtest.h>

#include "config.hxx"
#include "model.hxx"

using namespace edgas;


TEST(ModelConstructor, SetsDimensionsAndParticleCount) {
    Config config{ .particleCount = 4, .particleRadius = 0.25, .particleMass = 1.0, .dimensionX = 10, .dimensionY = 10 };

    Model model(config);

    EXPECT_EQ(model.dimensionX, 10);
    EXPECT_EQ(model.dimensionY, 10);
    EXPECT_EQ(model.nparticles, 4);
}

TEST(ModelConstructor, CreatesCorrectNumberOfParticles) {
    Config config{ .particleCount = 5, .particleRadius = 0.25, .particleMass = 1.0, .dimensionX = 10, .dimensionY = 10 };

    Model model(config);

    EXPECT_EQ(static_cast<int>(model.particles.size()), 5);
}

TEST(ModelConstructor, InitializesParticleRadiusAndMass) {
    Config config{ .particleCount = 3, .particleRadius = 0.3, .particleMass = 2.5, .dimensionX = 10, .dimensionY = 10 };

    Model model(config);

    for (const auto& p : model.particles) {
        EXPECT_DOUBLE_EQ(p.radius, 0.3);
        EXPECT_DOUBLE_EQ(p.mass, 2.5);
    }
}

TEST(ModelConstructor, PlacesParticlesAtGridCellCenters) {
    Config config{ .particleCount = 6, .particleRadius = 0.25, .particleMass = 1.0, .dimensionX = 4, .dimensionY = 3 };

    Model model(config);

    for (const auto& p : model.particles) {
        double cellX = p.x - 0.5;
        double cellY = p.y - 0.5;
        EXPECT_NEAR(cellX, std::round(cellX), 1e-10);
        EXPECT_NEAR(cellY, std::round(cellY), 1e-10);
        EXPECT_GE(cellX, 0);
        EXPECT_LT(cellX, config.dimensionX);
        EXPECT_GE(cellY, 0);
        EXPECT_LT(cellY, config.dimensionY);
    }
}

TEST(ModelConstructor, PlacesParticlesInUniqueCells) {
    Config config{ .particleCount = 8, .particleRadius = 0.25, .particleMass = 1.0, .dimensionX = 4, .dimensionY = 3 };

    Model model(config);

    std::set<std::pair<int, int>> cells;
    for (const auto& p : model.particles) {
        int cx = static_cast<int>(p.x - 0.5);
        int cy = static_cast<int>(p.y - 0.5);
        cells.insert({cx, cy});
    }
    EXPECT_EQ(cells.size(), static_cast<size_t>(config.particleCount));
}

TEST(ModelConstructor, InitializesVelocityWithUnitMagnitude) {
    Config config{ .particleCount = 10, .particleRadius = 0.25, .particleMass = 1.0, .dimensionX = 10, .dimensionY = 10 };

    Model model(config);

    for (const auto& p : model.particles) {
        double speed = std::sqrt(p.vx * p.vx + p.vy * p.vy);
        EXPECT_NEAR(speed, 1.0, 1e-10);
    }
}

TEST(ModelConstructor, InitializesGlobalTimeToZero) {
    Config config{ .particleCount = 2, .particleRadius = 0.25, .particleMass = 1.0, .dimensionX = 10, .dimensionY = 10 };

    Model model(config);

    EXPECT_DOUBLE_EQ(model.globalTime, 0.0);
}

TEST(ModelConstructor, InitializesParticleLocalTimeToZero) {
    Config config{ .particleCount = 3, .particleRadius = 0.25, .particleMass = 1.0, .dimensionX = 10, .dimensionY = 10 };

    Model model(config);

    for (const auto& p : model.particles) {
        EXPECT_DOUBLE_EQ(p.t, 0.0);
    }
}

// EOF
