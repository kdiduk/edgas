#include <cmath>

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

TEST(ModelConstructor, PlacesParticlesAtGridPositions) {
    Config config{ .particleCount = 4, .particleRadius = 0.25, .particleMass = 1.0, .dimensionX = 10, .dimensionY = 10 };

    Model model(config);

    for (int i = 0; i < config.particleCount; ++i) {
        EXPECT_DOUBLE_EQ(model.particles[i].x, (i % config.dimensionX) + 0.5);
        EXPECT_DOUBLE_EQ(model.particles[i].y, (i % config.dimensionY) + 0.5);
    }
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
