#pragma ident "$Id: //depot/sgl/gpstk/dev/src/GPSWeekSecond.hpp#3 $"

#ifndef GPSTK_GPSWEEKSECOND_HPP
#define GPSTK_GPSWEEKSECOND_HPP

#include "TimeTag.hpp"

namespace gpstk
{
      /** 
       * This class encapsulates the "Full GPS Week and GPS 
       * Seconds-of-week" time representation.
       */
   class GPSWeekSecond : public TimeTag
   {
   public:
      static const std::string printChars;
      static const std::string defaultFormat;

         /** 
          * @defgroup gwsbo GPSWeekSecond Basic Operations
          * Default and Copy Constructors, Assignment Operator and Destructor.
          */
         //@{
         /**
          * Default Constructor.
          * All elements are initialized to zero.
          */
      GPSWeekSecond( int w = 0,
                     double s = 0. )
         throw()
            : week(w), sow(s)
      {}
      
         /**
          * Copy Constructor.
          * @param right a reference to the GPSWeekSecond object to copy
          */
      GPSWeekSecond( const GPSWeekSecond& right )
         throw()
            : week( right.week ), sow( right.sow )
      {}
      
         /**
          * Alternate Copy Constructor.
          * Takes a const TimeTag reference and copies its contents via
          * conversion to CommonTime.
          * @param right a const reference to the BasicTime object to copy
          * @throw InvalidRequest on over-/under-flow
          */
      GPSWeekSecond( const TimeTag& right )
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
      GPSWeekSecond( const CommonTime& right )
         throw( InvalidRequest )
      {
         convertFromCommonTime( right );
      }

         /** 
          * Assignment Operator.
          * @param right a const reference to the GPSWeekSecond to copy
          * @return a reference to this GPSWeekSecond
          */
      GPSWeekSecond& operator=( const GPSWeekSecond& right )
         throw();
      
         /// Virtual Destructor.
      virtual ~GPSWeekSecond()
         throw()
      {}
         //@}

         // The following functions are required by TimeTag.
      virtual CommonTime convertToCommonTime() const;

      virtual void convertFromCommonTime( const CommonTime& ct ) ;

         /// This function formats this time to a string.  The exceptions 
         /// thrown would only be due to problems parsing the fmt string.
      virtual std::string printf( const std::string& fmt ) const
         throw( gpstk::StringUtils::StringException );

         /**
          * Set this object using the information provided in \a info.
          * @param info the IdToValue object to which this object shall be set.
          * @return true if this object was successfully set using the 
          *  data in \a info, false if not.
          */
      virtual bool setFromInfo( const IdToValue& info )
         throw();
      
         /// Return a string containing the characters that this class
         /// understands when printing times.
      virtual std::string getPrintChars() const
         throw()
      { 
         return "Fg";
      }

         /// Return a string containing the default format to use in printing.
      virtual std::string getDefaultFormat() const
         throw()
      {
         return "%04F %g";
      }

      virtual bool isValid() const
         throw();

         /**
          * @defgroup gwsco GPSWeekSecond Comparison Operators
          * All comparison operators have a parameter "right" which corresponds
          *  to the GPSWeekSecond object to the right of the symbol.
          * All comparison operators are const and return true on success
          *  and false on failure.
          */
         //@{
      bool operator==( const GPSWeekSecond& right ) const
         throw();
      bool operator!=( const GPSWeekSecond& right ) const
         throw();
      bool operator<( const GPSWeekSecond& right ) const
         throw();
      bool operator>( const GPSWeekSecond& right ) const
         throw();
      bool operator<=( const GPSWeekSecond& right ) const
         throw();
      bool operator>=( const GPSWeekSecond& right ) const
         throw();
         //@}

      int week;
      double sow;
   };

}

#endif // GPSTK_GPSWEEKSECOND_HPP
