//
//  GeoUtils.hpp
//  CirculatorySys
//
//  Created by Henrique on 21/03/17.
//
//

#ifndef GeoUtils_h
#define GeoUtils_h

#include "cinder/Vector.h"


namespace geo {
    
    static cinder::vec2 pixelSize = ci::vec2(1920, 1080);
    
    
    class Coordinate{
    public:
        Coordinate(){
    
        }
        Coordinate(float latitude, float longitude ) : lat(latitude), lon(longitude){
            
            
        }
        
        Coordinate(const ci::vec2& latlon) : lat(latlon.x) , lon(latlon.y) {
            
            
            
        }
        
        float lat = 0;
        float lon = 0;
    };
    
    
    
    //!Translates a Latitude and Longitude to a Cartesian point in a equiretangular map
   inline ci::vec2 coordinateToCartesian(const Coordinate coordinate , ci::vec2 mapSize = pixelSize){
       
        float width = mapSize.x;
        float height = mapSize.y;
       
       auto y = (((coordinate.lat * -1) + 90) * (height/ 180));
       auto x = ((coordinate.lon + 180) * (width  / 360));
       
        return ci::vec2(x,y);
    }
    
    
    //!Translates a cartesian point to Latitude and Longitude
    inline Coordinate cartesianToCoordinate(const ci::vec2& point, ci::vec2 size = pixelSize){
        
        
        float width = size.x;
        float height = size.y;
        
        Coordinate coord;
       
        coord.lat = (point.y - height  * 0.5) / height  * -180;
        coord.lon = (point.x - width * 0.5) / width * 360;

        return coord;
    }
    
    //! Returns the distance between two coordinates
   inline double distanceCoordinate(const Coordinate& coordA, const Coordinate coordB){
        
        const double R = 6371e3; // metres
        double latA = ci::toRadians(coordA.lat); //lat1.toRadians();
        double latB = ci::toRadians(coordB.lat);
        double deltaLat = ci::toRadians(coordB.lat-coordA.lat);
        double deltaLong = ci::toRadians( coordB.lon -coordA.lon );
        
        
        double a = sin( deltaLat /2.0) * sin( deltaLat /2.0) +
        cos(latA) * cos(latB) *
        sin(deltaLong/2.0f) * sin(deltaLong/2.0);
       
        double c = 2.0 *  atan2(sqrt(a), sqrt(1.0 - a));
        double d = R * c;
       
        return d * 0.001; // in km
    }
    
    //! Returns a coordinate point in the terminator line
    inline Coordinate getTerminatorCoords(float lat, float lon, float gamma){
        
        Coordinate terminator;

        terminator.lat= glm::atan(gamma * std::sin( glm::radians(lat - lon ) )) * (180.0f / M_PI);
        terminator.lon = lat;
        
        return terminator;
    }
    
}// end of namespace

#endif /* GeoUtils_hpp */
