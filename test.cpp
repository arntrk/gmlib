
#include <catch.hpp>

#include <BSplineBasis.h>
#include <vector>


/**
 * @brief Testing first order bspline basis function 
 * 
 * First order bspline basis is contains one basis function,
 * which is 1 for all values in the interval and 0 elsewere 
 */
TEST_CASE("BSpline basis function of 1st order", "[BSpline]")
{
  // constructing knot vector [0.0, 1.0]
  cad::KnotVector<double> knots(0.0, 1.0, 1); 
  cad::BSplineBasis<double>::Result result;

  cad::BSplineBasis<double> linear;

  // testing at t=0.0 which is inside [start, stop]
  result = linear(0.0, knots);
  REQUIRE(result.i == 0);
  REQUIRE(result.basis.size() == 1);
  REQUIRE(result.basis[0] == 1.0);

  result = linear(0.5, knots);
  REQUIRE(result.basis.size() == 1);
  REQUIRE(result.basis[0] == 1.0);

  result = linear(1.0, knots);
  REQUIRE(result.basis.size() == 1);
  REQUIRE(result.basis[0] == 1.0);

  // test that result is 0 outside interval
  result = linear(-1.0000001, knots);
  REQUIRE(result.basis.size() == 1);
  REQUIRE(result.basis[0] == 0.0);

  // test that result is 0 outside interval
  result = linear(1.0000001, knots);
  REQUIRE(result.basis.size() == 1);
  REQUIRE(result.basis[0] == 0.0);
}

TEST_CASE("BSpline basis function of 2st order", "[BSpline]")
{
  cad::KnotVector<double> knots(0.0, 1.0, 2);
  cad::BSplineBasis<double>::Result result;

  cad::BSplineBasis<double> basis;

  result = basis(0.0, knots);
  REQUIRE(result.i == 0);
  REQUIRE(result.basis.size() == 2);
  REQUIRE(result.basis[0] == 1.0);
  REQUIRE(result.basis[1] == 0.0);

  result = basis(0.5, knots);
  REQUIRE(result.basis[0] == 0.5);
  REQUIRE(result.basis[1] == 0.5);

  result = basis(1.0, knots);
  REQUIRE(result.basis[0] == 0.0);
  REQUIRE(result.basis[1] == 1.0);

  result = basis(-0.00000001, knots);
  REQUIRE(result.basis[0] == 0.0);
  REQUIRE(result.basis[1] == 0.0);

  result = basis(1.00000001, knots);
  REQUIRE(result.basis[0] == 0.0);
  REQUIRE(result.basis[1] == 0.0);

}

TEST_CASE("BSpline basis function of 3nd Order")
{
  cad::KnotVector<double> knots(0.0, 1.0, 3);
  cad::BSplineBasis<double>::Result result;

  cad::BSplineBasis<double> basis;

  result = basis(0.0, knots);
  REQUIRE(result.i == 0);
  REQUIRE(result.basis[0] == 1.0);
  REQUIRE(result.basis[1] == 0.0);
  REQUIRE(result.basis[2] == 0.0);

  result = basis(0.5, knots);
  REQUIRE(result.basis[0] == 0.25);
  REQUIRE(result.basis[1] == 0.5);
  REQUIRE(result.basis[2] == 0.25);

  result = basis(1.0, knots);
  REQUIRE(result.basis[0] == 0.0);
  REQUIRE(result.basis[1] == 0.0);
  REQUIRE(result.basis[2] == 1.0);
}

TEST_CASE("BSpline basis of 3 order with one internal knot")
{
  cad::KnotVector<double> knots(0.0, 1.0, 3); 
  cad::BSplineBasis<double>::Result result;
  cad::BSplineBasis<double> basis;

  knots.insert(0.5);

  result = basis(0.0, knots);
  REQUIRE(result.i == 0);
  REQUIRE(result.basis[0] == 1.0);
  REQUIRE(result.basis[1] == 0.0);
  REQUIRE(result.basis[2] == 0.0);

  result = basis(0.25, knots);
  REQUIRE(result.i == 0);
  REQUIRE(result.basis[0] == 0.25);
  REQUIRE(result.basis[1] == 0.625);
  REQUIRE(result.basis[2] == 0.125);

  result = basis(0.5, knots);
  REQUIRE(result.i == 1);
  REQUIRE(result.basis[0] == 0.5);
  REQUIRE(result.basis[1] == 0.5);
  REQUIRE(result.basis[2] == 0.0);

  result = basis(0.75, knots);
  REQUIRE(result.i == 1);
  REQUIRE(result.basis[0] == 0.125);
  REQUIRE(result.basis[1] == 0.625);
  REQUIRE(result.basis[2] == 0.25);

  result = basis(1.0, knots);
  REQUIRE(result.i == 1);
  REQUIRE(result.basis[0] == 0.0);
  REQUIRE(result.basis[1] == 0.0);
  REQUIRE(result.basis[2] == 1.0);
}


TEST_CASE("BSpline basis of 3 order with two internal knot")
{
  cad::KnotVector<double> knots(0.0, 1.0, 3);
  cad::BSplineBasis<double>::Result result;
  cad::BSplineBasis<double> basis;

  knots.insert(1.0 / 3.0);
  knots.insert(2.0 / 3.0);

  result = basis(0.0, knots);
  REQUIRE(result.i == 0);
  REQUIRE(result.basis[0] == 1.0);
  REQUIRE(result.basis[1] == 0.0);
  REQUIRE(result.basis[2] == 0.0);

  result = basis(0.25, knots);
  REQUIRE(result.i == 0);
  REQUIRE(result.basis[0] == 0.0625);
  REQUIRE(result.basis[1] == 0.65625);
  REQUIRE(result.basis[2] == 0.28125);

  result = basis(0.5, knots);
  REQUIRE(result.i == 1);
  //REQUIRE(result.basis[0] == 0.125);
  REQUIRE(result.basis[1] == 0.75);
  //REQUIRE(result.basis[2] == 0.125);

  result = basis(0.75, knots);
  REQUIRE(result.i == 2);
  REQUIRE(result.basis[0] == 0.28125);
  REQUIRE(result.basis[1] == 0.65625);
  //REQUIRE(result.basis[2] == 0.0625);

  result = basis(1.0, knots);
  REQUIRE(result.i == 2);
  REQUIRE(result.basis[0] == 0.0);
  REQUIRE(result.basis[1] == 0.0);
  REQUIRE(result.basis[2] == 1.0);
}

