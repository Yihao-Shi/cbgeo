#include <limits>

#include "Eigen/Dense"
#include "catch.hpp"
#include "json.hpp"

#include "material/linear_elastic.h"

//! \brief Check linearelastic class
TEST_CASE("LinearElastic is checked", "[material][linear_elastic]") {
  // Tolerance
  const double Tolerance = 1.E-7;

  //! Check for id = 0
  SECTION("LinearElastic id is zero") {
    const unsigned id = 0;
    auto material = std::make_shared<mpm::LinearElastic>(id);
    REQUIRE(material->id() == 0);
  }

  SECTION("LinearElastic id is positive") {
    //! Check for id is a positive value
    const unsigned id = std::numeric_limits<unsigned>::max();
    auto material = std::make_shared<mpm::LinearElastic>(id);
    REQUIRE(material->id() == std::numeric_limits<unsigned>::max());
  }

  //! Read material properties
  SECTION("LinearElastic material properties") {
    const unsigned id = 0;
    auto material = std::make_shared<mpm::LinearElastic>(id);
    REQUIRE(material->id() == 0);

    // Initialise material
    Json jmaterial;
    jmaterial["youngs_modulus"] = 1.0E+7;
    jmaterial["poisson_ratio"] = 0.3;

    material->properties(jmaterial);

    // Calculate modulus values
    const double K = 8333333.333333333;
    const double G = 3846153.846153846;
    const double a1 = 13461538.461566667;
    const double a2 = 5769230.769166667;

    mpm::Material::Matrix6x6 de = material->elastic_tensor();
    REQUIRE(de(0,0) ==  Approx(a1).epsilon(Tolerance));
    REQUIRE(de(0,1) ==  Approx(a2).epsilon(Tolerance));
    REQUIRE(de(0,2) ==  Approx(a2).epsilon(Tolerance));
    REQUIRE(de(0,3) ==  Approx(0.).epsilon(Tolerance));
    REQUIRE(de(0,4) ==  Approx(0.).epsilon(Tolerance));
    REQUIRE(de(0,5) ==  Approx(0.).epsilon(Tolerance));
    
    REQUIRE(de(1,0) ==  Approx(a2).epsilon(Tolerance));
    REQUIRE(de(1,1) ==  Approx(a1).epsilon(Tolerance));
    REQUIRE(de(1,2) ==  Approx(a2).epsilon(Tolerance));
    REQUIRE(de(1,3) ==  Approx(0.).epsilon(Tolerance));
    REQUIRE(de(1,4) ==  Approx(0.).epsilon(Tolerance));
    REQUIRE(de(1,5) ==  Approx(0.).epsilon(Tolerance));
    
    REQUIRE(de(2,0) ==  Approx(a2).epsilon(Tolerance));
    REQUIRE(de(2,1) ==  Approx(a2).epsilon(Tolerance));
    REQUIRE(de(2,2) ==  Approx(a1).epsilon(Tolerance));
    REQUIRE(de(2,3) ==  Approx(0.).epsilon(Tolerance));
    REQUIRE(de(2,4) ==  Approx(0.).epsilon(Tolerance));
    REQUIRE(de(2,5) ==  Approx(0.).epsilon(Tolerance));
    
    REQUIRE(de(3,0) ==  Approx(0.).epsilon(Tolerance));
    REQUIRE(de(3,1) ==  Approx(0.).epsilon(Tolerance));
    REQUIRE(de(3,2) ==  Approx(0.).epsilon(Tolerance));
    REQUIRE(de(3,3) ==  Approx(G).epsilon(Tolerance));
    REQUIRE(de(3,4) ==  Approx(0.).epsilon(Tolerance));
    REQUIRE(de(3,5) ==  Approx(0.).epsilon(Tolerance));

    REQUIRE(de(4,0) ==  Approx(0.).epsilon(Tolerance));
    REQUIRE(de(4,1) ==  Approx(0.).epsilon(Tolerance));
    REQUIRE(de(4,2) ==  Approx(0.).epsilon(Tolerance));
    REQUIRE(de(4,3) ==  Approx(0.).epsilon(Tolerance));
    REQUIRE(de(4,4) ==  Approx(G).epsilon(Tolerance));
    REQUIRE(de(4,5) ==  Approx(0.).epsilon(Tolerance));

    REQUIRE(de(5,0) ==  Approx(0.).epsilon(Tolerance));
    REQUIRE(de(5,1) ==  Approx(0.).epsilon(Tolerance));
    REQUIRE(de(5,2) ==  Approx(0.).epsilon(Tolerance));
    REQUIRE(de(5,3) ==  Approx(0.).epsilon(Tolerance));
    REQUIRE(de(5,4) ==  Approx(0.).epsilon(Tolerance));
    REQUIRE(de(5,5) ==  Approx(G).epsilon(Tolerance));

  }

}
