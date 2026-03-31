#include <gtest/gtest.h>

#include "collisions.hxx"

using namespace edgas;


TEST(timeToParticleCollision,
        ReturnsInfinity_WhenParticlesHaveSameLocalTimeAndAreMovingApart) {
    Particle p1{ .x = 2, .y = 0, .vx = 1, .vy = 0, .radius = 0.5, .mass = 1, .t = 0.0 };
    Particle p2{ .x = 1, .y = 0, .vx = -1, .vy = 0, .radius = 0.5, .mass = 1, .t = 0.0 };

    double time = collisions::timeToParticleCollision(p1, p2);

    EXPECT_DOUBLE_EQ(time, std::numeric_limits<double>::infinity());
}


TEST(timeToParticleCollision,
        ReturnsCollisionTime_WhenParticlesHaveSameLocalTimeAndAreMovingTowardsEachOther) {
    Particle p1{ .x = 0, .y = 0, .vx = 1, .vy = 0, .radius = 0.5, .mass = 1, .t = 0.0 };
    Particle p2{ .x = 2, .y = 0, .vx = -1, .vy = 0, .radius = 0.5, .mass = 1, .t = 0.0 };

    double time = collisions::timeToParticleCollision(p1, p2);
    EXPECT_DOUBLE_EQ(time, 0.5);
}


TEST(timeToParticleCollision,
        ReturnsCollisionTime_WhenParticlesAreOrthogonalAndMovingTowardsEachOther) {
    Particle p1{ .x = 0, .y = 0, .vx = 1, .vy = 0, .radius = 0.5, .mass = 1, .t = 0.0 };
    Particle p2{ .x = 2, .y = 3, .vx = 0, .vy = -1, .radius = 0.5, .mass = 1, .t = 0.0 };

    auto time = collisions::timeToParticleCollision(p1, p2);
    EXPECT_DOUBLE_EQ(time, 2.0);
}


TEST(timeToParticleCollision,
        ReturnsNoCollision_WhenParticlesAreOrthogonalAndMovingTowardsEachOtherAndDontTouch) {
    Particle p1{ .x = 0.5, .y = 0, .vx = 1, .vy = 0, .radius = 0.5, .mass = 1, .t = 0.0 };
    Particle p2{ .x = 2, .y = 3, .vx = 0, .vy = -1, .radius = 0.5, .mass = 1, .t = 0.0 };

    auto time = collisions::timeToParticleCollision(p1, p2);
    EXPECT_DOUBLE_EQ(time, std::numeric_limits<double>::infinity());
}

TEST(timeToParticleCollision,
        particlesHaveDistinctLocalTimesAndShouldCollide) {
    Particle p1{ .x = 0, .y = 0, .vx = 1, .vy = 0, .radius = 0.5, .mass = 1, .t = 1.0 };
    Particle p2{ .x = 4, .y = 0, .vx = -1, .vy = 0, .radius = 0.5, .mass = 1, .t = 2.0 };

    double time = collisions::timeToParticleCollision(p1, p2);
    EXPECT_DOUBLE_EQ(time, 3.0); // p2.t + 1.0
}


TEST(collideParticles,
        particlesWithSameMassAndSpeedCollideTowardsEachOtherOnlyAsisX)
{
    Particle p1{ .x = 0, .y = 0, .vx = 1, .vy = 0, .radius = 0.5, .mass = 1, .t = 0.0 };
    Particle p2{ .x = 1, .y = 0, .vx = -1, .vy = 0, .radius = 0.5, .mass = 1, .t = 0.0 };

    collisions::collideParticles(p1, p2);

    EXPECT_NEAR(p1.vx, -1.0, 1e-8);
    EXPECT_NEAR(p1.vy, 0.0, 1e-8);

    EXPECT_NEAR(p2.vx, 1.0, 1e-8);
    EXPECT_NEAR(p2.vy, 0.0, 1e-8);
}


TEST(collideParticles,
        particlesWithSameMassAndSpeedCollideTowardsEachOtherDiagonally)
{
    Particle p1{ .x = 0, .y = 0, .vx = 1, .vy = 1, .radius = 0.5, .mass = 1, .t = 0.0 };
    Particle p2{ .x = sin(M_PI / 4), .y = sin(M_PI / 4), .vx = -1, .vy = -1, .radius = 0.5, .mass = 1, .t = 0.0 };

    collisions::collideParticles(p1, p2);

    EXPECT_NEAR(p1.vx, -1.0, 1e-8);
    EXPECT_NEAR(p1.vy, -1.0, 1e-8);

    EXPECT_NEAR(p2.vx, 1.0, 1e-8);
    EXPECT_NEAR(p2.vy, 1.0, 1e-8);
}


TEST(collideParticles,
        particleCollideWithStationaryParticle)
{
    Particle p1{ .x = 0, .y = 0, .vx = 1, .vy = 0, .radius = 0.5, .mass = 1, .t = 0.0 };
    Particle p2{ .x = 1, .y = 0, .vx = 0, .vy = 0, .radius = 0.5, .mass = 1, .t = 0.0 };

    collisions::collideParticles(p1, p2);

    EXPECT_NEAR(p1.vx, 0.0, 1e-8);
    EXPECT_NEAR(p1.vy, 0.0, 1e-8);

    EXPECT_NEAR(p2.vx, 1.0, 1e-8);
    EXPECT_NEAR(p2.vy, 0.0, 1e-8);
}


TEST(collideParticles,
        particlesAreOrthogonalAndMovingTowardsEachOther) {
    Particle p1{ .x = 0, .y = 0, .vx = 1, .vy = 0, .radius = 0.5, .mass = 1, .t = 0.0 };
    Particle p2{ .x = sin(M_PI/4.0), .y = sin(M_PI/4.0), .vx = 0, .vy = -1, .radius = 0.5, .mass = 1, .t = 0.0 };

    collisions::collideParticles(p1, p2);

    EXPECT_NEAR(p1.vx, 0.0, 1e-8);
    EXPECT_NEAR(p1.vy, -1.0, 1e-8);

    EXPECT_NEAR(p2.vx, 1.0, 1e-8);
    EXPECT_NEAR(p2.vy, 0.0, 1e-8);
}

// EOF