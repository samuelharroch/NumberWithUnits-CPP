
#include <iostream>
#include <string>
#include <map>
#include "NumberWithUnits.hpp"

using namespace std;

const double TOLERANCE = 0.0001;

namespace ariel{

        static map<string, map<string, double>> units_table;


        NumberWithUnits::NumberWithUnits(const double num, const string& units):
        num(num), units(units)
        {
            if ( units_table.find(units)== units_table.end()){
                throw invalid_argument{"We don't know about this unit"};
            }
        }


        void NumberWithUnits::read_units(std::istream& units_file){
            
            string equal;
            string unit1;
            string unit2;
            double one = 0;
            double num = 0;

            while(units_file >> one >> unit1 >> equal >> num >> unit2){
                
                units_table[unit1][unit2] = num;
                units_table[unit2][unit1] = 1/num;

                /*unit1 other convertions*/
                for(auto &pair : units_table[unit2]){
                    double u = units_table[unit1][unit2]*pair.second; //from unit1 to pair.first
                    units_table[unit1][pair.first] = u;
                    units_table[pair.first][unit1] = 1/u; 
                }

                /*unit2 other convertions*/
                for(auto &pair : units_table[unit1]){
                    double u = units_table[unit2][unit1]*pair.second; //from unit2 to pair.first
                    units_table[unit2][pair.first] = u;
                    units_table[pair.first][unit2] = 1/u; 
                }
            }
            
        }

        
        /*private method convertion */
        double NumberWithUnits::convert(double num, const string &unit1, const string &unit2 )  {
            if(unit1==unit2){
                return num; 
            }
            if (units_table[unit1].find(unit2)!=units_table[unit1].end()){   
                return num*units_table[unit1][unit2];
            }
            throw invalid_argument{"Cannot convert from "+ unit1 +"to "+unit2};
        }
        //----------------------------------
        // unary operator
        //----------------------------------

        // Minus -
        NumberWithUnits NumberWithUnits::operator+() const {
            return NumberWithUnits(this->num , this->units);
        }
        //plus + 
        NumberWithUnits NumberWithUnits::operator-() const {
            return NumberWithUnits(-(this->num) , this->units);
        }

        //----------------------------------------
        // binary operators
        //----------------------------------------
        NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& other) const{
            double new_num = this->convert(other.num, other.units, this->units) + this->num;
            return NumberWithUnits(new_num, this->units);
        }

        NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits& other) const{
            double new_num = this->num - this->convert(other.num, other.units, this->units);
            return NumberWithUnits(new_num, this->units);
        }

        NumberWithUnits NumberWithUnits::operator*(const double n) const {
            return NumberWithUnits(this->num* n, this->units);
        }

        //friend func 
        NumberWithUnits operator*( const double n,  const NumberWithUnits& other){
            // friend func can get to private members object
            return NumberWithUnits(other.num* n, other.units);
        }

        /*reference return func*/
        NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits& other) {
            this->num += convert(other.num, other.units, this->units);
            return *this;
        }

        NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& other) {
            this->num -= convert(other.num, other.units, this->units);
            return *this;
        }

        NumberWithUnits& NumberWithUnits::operator*=(const double n) {
            this->num *= n;
            return *this;
        }

        

        // prefix increment and discrement :
        NumberWithUnits& NumberWithUnits::operator++() {
            ++(this->num);
            return *this;
        }
        NumberWithUnits& NumberWithUnits::operator--() {
            --(this->num);
            return *this;
        }

        // postfix increment:
        NumberWithUnits NumberWithUnits::operator++(int dummy_flag_for_postfix_increment) {
            
            return NumberWithUnits(this->num++, this->units);
        }
        NumberWithUnits NumberWithUnits::operator--(int dummy_flag_for_postfix_increment) {
            return NumberWithUnits(this->num--, this->units);
        }

        int NumberWithUnits::compareTo(const NumberWithUnits& other) const {

            double diff = this->num - convert(other.num, other.units, this->units);
            if (diff> TOLERANCE){
                return 1;
            } 
            if  (diff < -TOLERANCE){
                return -1;
            }
            
            return 0;
        }

        //-----------------
        // bool binary operators 
        //-----------------

        bool NumberWithUnits::operator>(const NumberWithUnits& other) const {
            return compareTo(other) == 1;
        }
        bool NumberWithUnits::operator>=(const NumberWithUnits& other) const {
            return compareTo(other) >= 0;
        }
        bool NumberWithUnits::operator<(const NumberWithUnits& other) const {
            return compareTo(other) == -1;
        }
        bool NumberWithUnits::operator<=(const NumberWithUnits& other) const {
            return compareTo(other) <= 0;
        }
        bool NumberWithUnits::operator==(const NumberWithUnits& other) const {
            return compareTo(other) == 0;
        }
        bool NumberWithUnits::operator!=(const NumberWithUnits& other) const {
            return compareTo(other) != 0;
        }

         //----------------------------------
        // friend global IO operators
        //----------------------------------
        ostream& operator<< (std::ostream& output, const NumberWithUnits& unit_num){
            output << unit_num.num <<"["<< unit_num.units<< "]";
            return output;
        }

        static istream& getAndCheckNextCharIs(istream& input, char expectedChar) {
            char actualChar = 0 ;
            input >> actualChar;
            if (!input) {return input;}

            if (actualChar!=expectedChar) {
                // failbit is for format error
                input.setstate(ios::failbit);
            }
            return input;
        }

        istream& operator>> (std::istream& input , NumberWithUnits& num){

            double new_num = 0;
            string new_units;

            ios::pos_type startPosition = input.tellg();

            if ( (!(input >> new_num))                 ||
            (!getAndCheckNextCharIs(input,'['))  ||
            (!(input >> new_units)) ) {

                // rewind on error
                auto errorState = input.rdstate(); // remember error state
                input.clear(); // clear error so seekg will work
                input.seekg(startPosition); // rewind
                input.clear(errorState); 

            }
            else{
                unsigned int index = new_units.length()-1;

                if (new_units.at(index)!=']'){
                    string buffer;
                    input >> buffer;
                    new_units += buffer;
                }

                index = new_units.length()-1;
                new_units = new_units.substr(0,index);   
                
                if ( units_table.find(new_units)== units_table.end()){
                    throw invalid_argument{"We don't know about this unit"};
                }

                num.num=new_num;
                num.units= new_units;
            }
            
            return input;
        
        }

       
        NumberWithUnits::~NumberWithUnits(){}
}