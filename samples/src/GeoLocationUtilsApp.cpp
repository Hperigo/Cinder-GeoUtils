#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"


#include "GeoUtils.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class GeoLocationUtilsApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    
    gl::TextureRef mMapTexture;
    
    
    geo::Coordinate _Sp {-23.5475, -46.6361};
    geo::Coordinate _Ldn {51.5085, -0.1257};
    
    vec2 mousePoint;
};

void GeoLocationUtilsApp::setup()
{
    
    mMapTexture = gl::Texture::create(loadImage(loadAsset("map.jpg")));
    geo::pixelSize = mMapTexture->getSize();
    
    setWindowSize(mMapTexture->getSize());
    
    mousePoint = vec2(mMapTexture->getSize()) * 0.5f;
}

void GeoLocationUtilsApp::mouseDown( MouseEvent event )
{
    
    mousePoint = event.getPos();
    
    
}

void GeoLocationUtilsApp::update()
{
}

void GeoLocationUtilsApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    
    gl::color(0.8f, 0.8f, 0.8f);
    gl::draw(mMapTexture);
    
    { // Draw Terminator
        
        vec2 size  = mMapTexture->getSize();
        
        float gamma = -5.0f;
        
        gl::color( Color::white() );
        Path2d terminatorPath;
        
        terminatorPath.moveTo(vec2(0, -10));
        
        auto v1 = geo::getTerminatorCoords(-180.0f, 0.0f, gamma);
        auto p1 = geo::coordinateToCartesian(v1);
        
        
        terminatorPath.lineTo(p1);
        
        for(int x = -180; x <= 180; x+=4){
            
            auto vv = geo::getTerminatorCoords(x, 0.0f, gamma);
            auto pp = geo::coordinateToCartesian(vv);
            terminatorPath.lineTo(pp);
        }
        
        auto v2 = geo::getTerminatorCoords(180.0f, 0.0f, gamma);
        
        auto p2 = geo::coordinateToCartesian(v2);
        terminatorPath.lineTo(p2);
        
        terminatorPath.lineTo(vec2(size.x, -10));
        
        terminatorPath.close();

        
        gl::color(0.0, 0.0, 0.0, 0.5);
        gl::drawSolid(terminatorPath);
        
    }
    
    
    { // Draw Cities
        
        //São Paulo
        gl::color(1.0f, 0.3f, 0.3f);
        vec2 spPoint = geo::coordinateToCartesian(_Sp);
        gl::drawSolidCircle( spPoint, 3 );
        
        
        //London
        gl::color(1.0f, 1.0f, 0.3f);
        vec2 lnd = geo::coordinateToCartesian(_Ldn);
        gl::drawSolidCircle( lnd, 3 );
        
        gl::drawLine(spPoint, lnd);
        
        float distance = geo::distanceCoordinate(_Sp, _Ldn);
        gl::drawString("São Paulo / London:\n" + to_string(distance) + "km",  ci::lerp<vec2>(spPoint, lnd, 0.5f));
    }
    
    {
        
        // Draw a mouse point and a coordinate point to check the math
        gl::color(0.3f, 0.3f, 1.0f);
        gl::drawSolidCircle(mousePoint, 10);
        
        geo::Coordinate mouseCoord = geo::cartesianToCoordinate( mousePoint );
        vec2 checkPoint = geo::coordinateToCartesian(mouseCoord);
        
        gl::color(1.0f, 1.0f, 1.0f);
        gl::drawSolidCircle(checkPoint, 5);
        
        vec2 spPoint = geo::coordinateToCartesian(_Sp);

        
        gl::drawLine(spPoint, checkPoint);
        
        float distance = geo::distanceCoordinate(_Sp, mouseCoord);
        gl::drawString("São Paulo / somewhere:" + to_string(distance) + "km",  ci::lerp<vec2>(spPoint, checkPoint, 0.5f));
        
        
        gl::drawString("Somewhere: Lat: " + to_string(mouseCoord.lat) + " Lon: " +  to_string(mouseCoord.lon),  checkPoint + vec2(10, 0));
    }
    
    
    

    
}

CINDER_APP( GeoLocationUtilsApp, RendererGl )
