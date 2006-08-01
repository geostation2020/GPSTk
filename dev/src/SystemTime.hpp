#pragma ident "$Id$"


#ifndef GPSTK_SYSTEMTIME_HPP
#define GPSTK_SYSTEMTIME_HPP

//============================================================================
//
//  This file is part of GPSTk, the GPS Toolkit.
//
//  The GPSTk is free software; you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published
//  by the Free Software Foundation; either version 2.1 of the License, or
//  any later version.
//
//  The GPSTk is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with GPSTk; if not, write to the Free Software Foundation,
//  Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//  
//  Copyright 2004, The University of Texas at Austin
//
//============================================================================

#include "UnixTime.hpp"

namespace gpstk
{
      /**
       * This class reads the current system time and stores it in
       * a UnixTime.
       */
   class SystemTime
      : public UnixTime
   {
   public:
         /**
          * @defgroup stbo SystemTime Basic Operations
          */
         //@{
      
         /**
          * Default Constructor.
          * Reads the system clock for the current system time.
          */
      SystemTime()
         throw()
      {
         check();
      }
      
         /** 
          * Copy Constructor.
          * @param right a reference to the SystemTime object to copy
          */
      SystemTime( const SystemTime& right )
         throw()
            : UnixTime( right )
      {}
      
         /**
          * Alternate Copy Constructor.
          * Takes a const TimeTag reference and copies its contents via
          * conversion to CommonTime.
          * @param right a const reference to the BasicTime object to copy
          * @throw InvalidRequest on over-/under-flow
          */
      SystemTime( const TimeTag& right )
         throw( gpstk::InvalidRequest )
      { 
         convertFromCommonTime( right.convertToCommonTime() ); 
      }
      
         /** 
          * Alternate Copy Constructor.
          * Takes a const CommonTime reference and copies its contents via
          * the convertFromCommonTime method.
          * @param right a const reference to the CommonTime object to copy
          * @throw InvalidRequest on over-/under-flow
          */
      SystemTime( const CommonTime& right )
         throw( InvalidRequest )
            : UnixTime( right )
      {}

         /** 
          * Assignment Operator.
          * @param right a const reference to the SystemTime to copy
          * @return a reference to this SystemTime
          */
      SystemTime& operator=( const SystemTime& right )
         throw();     
      
         /// Virtual Destructor.
      virtual ~SystemTime()
         throw()
      {}
         //@}

         /** 
          * Check the system clock and set this object to the current time.
          * @return a reference to this SystemTime
          */
      SystemTime& check() 
         throw();
   };

}

#endif // GPSTK_SYSTEMTIME_HPP
