/*
 *  textApp.h 
 *  GifPlayer made with OpenFrameworks
 *
 *  Created by Nicolas Boillot on 02/03/12.
 *  Using ofxGifDecoder by Jesus Gollonet
 *  Copyright 2012 fluaten. All rights reserved.
 */



#ifndef _GIF_PLAYER
#define _GIF_PLAYER

#include "ofMain.h"
#include "ofxGifDecoder.h"
#include "ofxGifFile.h"

class testApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void exit();
	
	string filename();
	
	float gifD, fpsToGiftime;
	int gifW, gifH, numFrame, LoopNum, frameNo, framerate;
	int screenWidth,screenHeight, gifnumb; 
	int	XresizeScreenWidth, YresizeScreenHeight, SizescreenHeight, SizescreenWidth;
	string month,day,GetHours,GetMinutes, GetSeconds;
    int gifnumbmax, numFiles;
	bool reverse, frameStop, LoadingGif;

	ofxGifDecoder dcd;
	vector <ofxGifFile> gifs;

};

#endif
