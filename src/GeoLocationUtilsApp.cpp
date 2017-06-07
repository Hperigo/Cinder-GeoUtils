#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class GeoLocationUtilsApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void GeoLocationUtilsApp::setup()
{
}

void GeoLocationUtilsApp::mouseDown( MouseEvent event )
{
}

void GeoLocationUtilsApp::update()
{
}

void GeoLocationUtilsApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( GeoLocationUtilsApp, RendererGl )
