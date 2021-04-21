
#include <iostream>
#include <string>
#include "NumberWithUnits.hpp"

using namespace std;

namespace ariel{

        NumberWithUnits::NumberWithUnits(const double num, const string& units){}

        NumberWithUnits::NumberWithUnits(){}

        void NumberWithUnits::read_units(std::istream& units_file){
            int x=3;
        }

        //----------------------------------
        // unary operator
        //----------------------------------

        // Minus -
        NumberWithUnits NumberWithUnits::operator-() const {
            return NumberWithUnits();
        }
        //plus + 
        NumberWithUnits NumberWithUnits::operator+() const {
            return NumberWithUnits();
        }

        //----------------------------------------
        // binary operators
        //----------------------------------------
        NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& other) const{
            return NumberWithUnits();
        }

        NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits& other) const{
            return NumberWithUnits();
        }

        NumberWithUnits NumberWithUnits::operator*(const double n) const {
            return NumberWithUnits();
        }

        //friend func 
        NumberWithUnits operator*( const double n,  const NumberWithUnits& other){
            return NumberWithUnits();
        }

        NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits& other) {
            return *this;
        }

        NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& other) {
            return *this;
        }

        NumberWithUnits& NumberWithUnits::operator*=(const double n) {
            return *this;
        }

        

        // prefix increment and discrement :
        NumberWithUnits& NumberWithUnits::operator++() {
            return *this;
        }
        NumberWithUnits& NumberWithUnits::operator--() {
            return *this;
        }

        // postfix increment:
        NumberWithUnits NumberWithUnits::operator++(int dummy_flag_for_postfix_increment) {
            return NumberWithUnits();
        }
        NumberWithUnits NumberWithUnits::operator--(int dummy_flag_for_postfix_increment) {
            return NumberWithUnits();
        }

        //-----------------
        // bool binary operators 
        //-----------------

        bool NumberWithUnits::operator>(const NumberWithUnits& other) const {
            return true;
        }
        bool NumberWithUnits::operator>=(const NumberWithUnits& other) const {
            return true;
        }
        bool NumberWithUnits::operator<(const NumberWithUnits& other) const {
            return true;
        }
        bool NumberWithUnits::operator<=(const NumberWithUnits& other) const {
            return true;
        }
        bool NumberWithUnits::operator==(const NumberWithUnits& other) const {
            return true;
        }
        bool NumberWithUnits::operator!=(const NumberWithUnits& other) const {
            return true;
        }

         //----------------------------------
        // friend global IO operators
        //----------------------------------
        ostream& operator<< (std::ostream& output, const NumberWithUnits& num){
            return output;
        }
        istream& operator>> (std::istream& input , NumberWithUnits& num){
            return input;
        }

        NumberWithUnits::~NumberWithUnits(){}
}