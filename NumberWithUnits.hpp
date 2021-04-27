#include <string>
#include <iostream>

namespace ariel{

    class NumberWithUnits
    {
    private:

        double num;
        std::string units;
        static double convert(double num, const std::string &unit1, const std::string &unit2 ) ;
        int compareTo(const NumberWithUnits& other) const ;

    public:

        NumberWithUnits(const double num, const std::string& units);   

        static void read_units(std::istream& units_file);

        //----------------------------------
        // unary operator
        //----------------------------------

        // Minus -
        NumberWithUnits operator-() const ;
        //plus + 
        NumberWithUnits operator+() const ;

        //----------------------------------------
        // binary operators
        //----------------------------------------
        NumberWithUnits operator+(const NumberWithUnits& other) const;

        NumberWithUnits operator-(const NumberWithUnits& other) const;


        NumberWithUnits& operator+=(const NumberWithUnits& other) ;

        NumberWithUnits& operator-=(const NumberWithUnits& other) ;

        //----------------------------------------
        // Mult operators
        //----------------------------------------
        NumberWithUnits operator*(const double n) const ;

        friend NumberWithUnits operator*( const double n,  const NumberWithUnits& other);

        NumberWithUnits& operator*=(const double n) ;

        

        // prefix increment and discrement :
        NumberWithUnits& operator++() ;
        NumberWithUnits& operator--() ;

        // postfix increment:
        NumberWithUnits operator++(int dummy_flag_for_postfix_increment) ;
        NumberWithUnits operator--(int dummy_flag_for_postfix_increment) ;

        //-----------------
        // bool binary operators 
        //-----------------

        bool operator>(const NumberWithUnits& other) const ;
        bool operator>=(const NumberWithUnits& other) const ;
        bool operator<(const NumberWithUnits& other) const ;
        bool operator<=(const NumberWithUnits& other) const ;
        bool operator==(const NumberWithUnits& other) const ;
        bool operator!=(const NumberWithUnits& other) const ;

         //----------------------------------
        // friend global IO operators
        //----------------------------------
        friend std::ostream& operator<< (std::ostream& output, const NumberWithUnits& num);
        friend std::istream& operator>> (std::istream& input , NumberWithUnits& num);

        ~NumberWithUnits();
    };
    
    
}