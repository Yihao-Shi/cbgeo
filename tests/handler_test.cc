// No-debase test
#include <limits>

#include <memory>

#include "Eigen/Dense"
#include "catch.hpp"

#include "handler.h"
#include "node.h"

//! \brief Check node handler class for 2D case
TEST_CASE("Node handler is checked for 2D case", "[nodehandler][2D]") {
  // Dimension
  const unsigned Dim = 2;
  // Tolerance
  const double Tolerance = 1.E-7;

  // Node 1
  mpm::Index id1 = 0;
  Eigen::Vector2d coords;
  coords.setZero();
  auto node1 = std::make_shared<mpm::Node<Dim>>(id1, coords);

  // Node 2
  mpm::Index id2 = 1;
  auto node2 = std::make_shared<mpm::Node<Dim>>(id2, coords);

  // Node handler
  auto nodehandler = std::make_shared<mpm::Handler<mpm::Node<Dim>>>();

  // Check insert node
  SECTION("Check insert node functionality") {
    // Insert node 1 and check status
    bool status1 = nodehandler->insert(node1);
    REQUIRE(status1 == true);
    // Insert node 2 and check status
    bool status2 = nodehandler->insert(node2->id(), node2);
    REQUIRE(status2 == true);
    // Check size of node hanlder
    REQUIRE(nodehandler->size() == 2);
  }

  // Check iterator
  SECTION("Check begin node iterator") {
    // Insert node 1
    nodehandler->insert(node1);
    // Insert node 2
    nodehandler->insert(node2);
    // Check size of node hanlder
    std::size_t counter = 0;
    for (auto itr = nodehandler->begin(); itr != nodehandler->end();
         ++itr) {
      auto coords = ((*itr).second)->coordinates();
      // Check if coordinates for each node is zero
      for (unsigned i = 0; i < coords.size(); ++i)
        REQUIRE(coords[i] == Approx(0.).epsilon(Tolerance));
      ++counter;
    }
    // Iterate over nodes and check if the number of nodes is good
    REQUIRE(counter == 2);
  }
}

//! \brief Check node handler class for 3D case
TEST_CASE("Node handler is checked for 3D case", "[nodehandler][3D]") {
  // Dimension
  const unsigned Dim = 3;
  // Tolerance
  const double Tolerance = 1.E-7;

  // Node 1
  mpm::Index id1 = 0;
  Eigen::Vector3d coords;
  coords.setZero();
  auto node1 = std::make_shared<mpm::Node<Dim>>(id1, coords);

  // Node 2
  mpm::Index id2 = 1;
  auto node2 = std::make_shared<mpm::Node<Dim>>(id2, coords);

  // Node handler
  auto nodehandler = std::make_shared<mpm::Handler<mpm::Node<Dim>>>();

  // Check insert node
  SECTION("Check insert node functionality") {
    // Insert node 1 and check status
    bool status1 = nodehandler->insert(node1);
    REQUIRE(status1 == true);
    // Insert node 2 and check status
    bool status2 = nodehandler->insert(node2->id(), node2);
    REQUIRE(status2 == true);
    // Check size of node hanlder
    REQUIRE(nodehandler->size() == 2);
  }

  // Check iterator
  SECTION("Check begin node iterator") {
    // Insert node 1
    nodehandler->insert(node1);
    // Insert node 2
    nodehandler->insert(node2);
    // Check size of node hanlder
    std::size_t counter = 0;
    for (auto itr = nodehandler->begin(); itr != nodehandler->end();
         ++itr) {
      auto coords = ((*itr).second)->coordinates();
      // Check if coordinates for each node is zero
      for (unsigned i = 0; i < coords.size(); ++i)
        REQUIRE(coords[i] == Approx(0.).epsilon(Tolerance));

      ++counter;
    }
    // Iterate over nodes and check if the number of nodes is good
    REQUIRE(counter == 2);
  }
}
