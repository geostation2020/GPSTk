#include <iostream>
#include "TestUtil.hpp"
#include "OrbAlmGen.hpp"
#include "CivilTime.hpp"
#include "GPSWeekSecond.hpp"

using namespace std;

/** Threshold for how much different our velocities can be between
 * being computed directly via svXvt and computed via differencing
 * svXvt positions over time. */
double velDiffThresh = 0.0008;


class OrbAlmGen_T
{
public:
   unsigned testSvXvt();
};


unsigned OrbAlmGen_T ::
testSvXvt()
{
   TUDEF("OrbAlmGen", "svXvt");
      // Hard code orbital parameters mostly so we can copy and paste
      // the data into other similar tests with minimal changes.
   gpstk::OrbAlmGen oe;
   oe.M0       = -.136404614938e+01;
   oe.ecc      =  .146582192974e-01;
   oe.A        =  .515359719276e+04 * .515359719276e+04;
   oe.AHalf    =  .515359719276e+04;
   oe.OMEGA0   = -.296605403382e+01;
   oe.deltai   =  .941587707856e+00 - (0.3*gpstk::PI);
   oe.i0       =  .941587707856e+00;
   oe.w        = -.224753761329e+01;
   oe.OMEGAdot = -.804390648956e-08;
   gpstk::CommonTime toa =
      gpstk::CivilTime(2015,7,19,1,59,28.0,gpstk::TimeSystem::GPS);
   oe.loadWeekNumber(toa);
   oe.af0      =  .579084269702e-03;
   oe.af1      =  .227373675443e-11;
   oe.health   = 0;
   oe.subjectSV= gpstk::SatID(2, gpstk::SatelliteSystem::GPS);
   oe.ctToe    = gpstk::GPSWeekSecond(1854,.716800000000e+04);
   oe.dataLoadedFlag = true;
      // iode .700000000000e+01
      // codes on L2 .100000000000e+01
      // L2 P data .000000000000e+00
      // sv accuracy .240000000000e+01
      // tgd -.204890966415e-07
      // iodc .700000000000e+01
      // xmit time .360000000000e+04
      // fit int .400000000000e+01
   bool testFailed = false;
   try
   {
         // first compute Xvt
      static const unsigned SECONDS = 7200;
      gpstk::Xvt zeroth_array[SECONDS];
      for (unsigned ii = 0; ii < SECONDS; ii++)
      {
         zeroth_array[ii] = oe.svXvt(toa + ii);
      }
         // then compute first derivative of position, i.e. velocity
      gpstk::Triple deriv[SECONDS];
      double h = 1; // time step size in seconds
      for (unsigned ii = 0; ii < SECONDS; ii++)
      {
         if (ii == 0)
         {
            deriv[ii] = (1/h)*(-1.5*zeroth_array[ii].getPos() +
                               2.0*zeroth_array[ii+1].getPos() -
                               0.5*zeroth_array[ii+2].getPos());
         }
         else if ((ii == 1) || (ii == (SECONDS-2)))
         {
            deriv[ii] = (1/h)*(-0.5*zeroth_array[ii-1].getPos() +
                               0.5*zeroth_array[ii+1].getPos());
         }
         else if (ii == (SECONDS-1))
         {
            deriv[ii] = (1/h)*(0.5*zeroth_array[ii-2].getPos() -
                               2.0*zeroth_array[ii-1].getPos() +
                               1.5*zeroth_array[ii].getPos());
         }
         else
         {
            deriv[ii] = (1/h)*((1.0/12.0)*zeroth_array[ii-2].getPos() -
                               (2.0/3.0)*zeroth_array[ii-1].getPos() +
                               (2.0/3.0)*zeroth_array[ii+1].getPos() -
                               (1.0/12.0)*zeroth_array[ii+2].getPos());
         }
      }
         // then check the difference between derived and computed velocity
      for (unsigned ii = 0; ii < SECONDS; ii++)
      {
         double derivedMag = deriv[ii].mag();
         double computedMag = zeroth_array[ii].getVel().mag();
            // If you want to print the data e.g. to plot, uncomment
            // this stream output statement and comment out tbe break
            // statement below.
            // Just don't check it in that way, please.
            // cerr << ii << " " << (computedMag - derivedMag) << endl;
         if (fabs(computedMag - derivedMag) > velDiffThresh)
         {
               // no sense in printing 7200 success/fail messages.
            testFailed = true;
            break;
         }
      }
      if (testFailed)
      {
         TUFAIL("computed velocity is significantly different from derived"
                " velocity");
      }
      else
      {
         TUPASS("velocity check");
      }
   }
   catch (gpstk::Exception& exc)
   {
      cerr << exc;
      TUFAIL("Exception");
   }
   catch (...)
   {
      TUFAIL("Exception");
   }
   TURETURN();
}


int main()
{
   unsigned total = 0;
   OrbAlmGen_T testClass;
   total += testClass.testSvXvt();

   cout << "Total Failures for " << __FILE__ << ": " << total << endl;
   return total;
}
