#include <gtest/gtest.h>

#include "collisions.hxx"

TEST(timeToParticleCollision, 
        ReturnsInfinity_WhenParticlesHaveSameLocalTimeAndAreMovingApart) {
    edgas::Particle p1{ .x = 2, .y = 0, .vx = 1, .vy = 0, .radius = 0.5, .mass = 1, .t = 0.0 };
    edgas::Particle p2{ .x = 1, .y = 0, .vx = -1, .vy = 0, .radius = 0.5, .mass = 1, .t = 0.0 };

    double time = edgas::collisions::timeToParticleCollision(p1, p2);

    EXPECT_DOUBLE_EQ(time, std::numeric_limits<double>::infinity());
}

TEST(timeToParticleCollision, 
        ReturnsCollisionTime_WhenParticlesHaveSameLocalTimeAndAreMovingTowardsEachOther) {
    edgas::Particle p1{ .x = 0, .y = 0, .vx = 1, .vy = 0, .radius = 0.5, .mass = 1, .t = 0.0 };
    edgas::Particle p2{ .x = 2, .y = 0, .vx = -1, .vy = 0, .radius = 0.5, .mass = 1, .t = 0.0 };

    double time = edgas::collisions::timeToParticleCollision(p1, p2);
    EXPECT_DOUBLE_EQ(time, 0.5);
}

// EOF