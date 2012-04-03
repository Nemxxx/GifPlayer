/*
 *  textApp.cpp 
 *  GifPlayer made with OpenFrameworks
 *
 *  Created by Nicolas Boillot on 02/03/12.
 *  Using ofxGifDecoder by Jesus Gollonet
 *  Copyright 2012 fluaten. All rights reserved.
 */


#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofBackground(0,0,0);
	
	screenWidth		= ofGetScreenWidth(); 
	screenHeight	= ofGetScreenHeight();
	
	
	
	ofSetVerticalSync(true);
	
	#ifndef WIN32 // If mac search inside app for start gif else in folder data
	ofSetDataPathRoot("../Resources/");
	#endif
	bool success = dcd.decode("loader.gif");
	if (success) { gifs.push_back(dcd.getFile()); }
 	
	gifnumb = 0;
	gifnumbmax = 1;

	fpsToGiftime = 160; // Factor to transform Gif time in approximative fps
	
	gifW = gifs[gifnumb].getWidth(); // Gif width
	gifH = gifs[gifnumb].getHeight(); // Gif height
	
	ofSetWindowShape(gifW, gifH); 
	ofSetWindowPosition((screenWidth/2)- (gifW/2), (screenHeight/2)-(gifH/2));
	
	numFrame = gifs[gifnumb].getNumFrames()-1; // Gif n¡ of images

	gifD = gifs[gifnumb].getDuration(); // Gif duration  / example : 0.08
	framerate = (int)(gifD * fpsToGiftime); // Transform Gif time in approximative fps
	ofSetFrameRate(framerate);
	printf("FPS %i",framerate);
		
	

}

//--------------------------------------------------------------
void testApp::update(){ 
	
	//ofSetWindowTitle("Gif Player " + ofToString(ofGetFrameRate()));
	
	ofSetWindowTitle("Gif Player");
	
	if (!frameStop) { // Stop
		
	// Next frame
	LoopNum++; 
	
	// Loop gif
	if (LoopNum > numFrame ) { LoopNum = 0; }
	
	// Reverse play

	if (reverse) { frameNo = numFrame - LoopNum; 
	} else { frameNo = LoopNum; }

	}
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofBackground(0,0,0);
		
	if (ofGetWindowMode() == OF_WINDOW) {
		
		gifs[gifnumb].drawFrame(frameNo, 0, 0, gifW, gifH);		
		
	} else { // Fullscreen gif ratio
	
		if ( ((float)gifW/(float)gifH) <= ((float)screenWidth/(float)screenHeight) ) {
			
			SizescreenWidth = (gifW*screenHeight)/gifH;
			SizescreenHeight = screenHeight;
			XresizeScreenWidth = (screenWidth/2) - (SizescreenWidth/2);
			YresizeScreenHeight = 0;

		} else {
			
			SizescreenWidth = screenWidth;
			SizescreenHeight = (gifH*screenWidth)/gifW;
			XresizeScreenWidth = 0;
			YresizeScreenHeight = (screenHeight/2) - (SizescreenHeight/2);	
		}
		
		gifs[gifnumb].drawFrame(frameNo, XresizeScreenWidth, YresizeScreenHeight, SizescreenWidth, SizescreenHeight);
	
	} 
	
	if (gifnumb == 0) {
		ofSetHexColor(0xffffff);
		ofDrawBitmapString(" GifPlayer 0.1 (github.com/fluaten) \n\n Drag GIF files into this window", 10, 20); 
		ofDrawBitmapString(" Press SPACE to go fullscreen \n Press LEFT or RIGHT to navigate \n Press UP or DOWN to change fps \n Press X to stop, C or V to skip \n Press R to reverse animation \n Press J to M to change framerate \n Press B to capture screen", 10, 200);
	}
		
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    switch (key) {
			
		case OF_KEY_RIGHT: // Next gif
			if (gifnumbmax>1) { 
			gifnumb++;
			if (gifnumb >= gifnumbmax) { gifnumb = 1;}
			gifW = gifs[gifnumb].getWidth();
			gifH = gifs[gifnumb].getHeight();
			numFrame = gifs[gifnumb].getNumFrames()-1;
			if (ofGetWindowMode() == OF_WINDOW) { 
				ofSetWindowShape(gifW, gifH); 
				ofSetWindowPosition((screenWidth/2)- (gifW/2), (screenHeight/2)-(gifH/2));
			} 
			}
			break;	
		case OF_KEY_LEFT: // Previous gif
			if (gifnumbmax>1) {
			gifnumb--;
			if (gifnumb<1) { gifnumb = gifnumbmax-1;}
			gifW = gifs[gifnumb].getWidth();
			gifH = gifs[gifnumb].getHeight();
			numFrame = gifs[gifnumb].getNumFrames()-1;
			if (ofGetWindowMode() == OF_WINDOW) { 
				ofSetWindowShape(gifW, gifH); 
				ofSetWindowPosition((screenWidth/2)-(gifW/2), (screenHeight/2)-(gifH/2));
			} 
			}	
			break;	
		
		case 'r': // Reverse play
			reverse = !reverse;
			break;
		case 'x': // Stop
			frameStop = !frameStop; 
			break;			
		case 'c':  // Stop Frame + 1
			frameNo++;
			if (frameNo > numFrame ) frameNo = 0;
			break;	
		case 'v': // Stop Frame - 1
			frameNo--;
			if (frameNo < 0 ) frameNo = numFrame;  
			break;		
		
		case OF_KEY_DOWN: // fps -
			framerate--;
			if (framerate < 1) framerate = 0;
			ofSetFrameRate(framerate);
			break;
		case OF_KEY_UP: // fps +
			framerate++;
			if (framerate > 200) framerate = 200;
			ofSetFrameRate(framerate);
			break;	
			
		case 'j': // fps 12
			ofSetFrameRate(12);
			break;
		case 'k': // fps 17
			ofSetFrameRate(17);
			break;
		case 'l': // fps 25
			ofSetFrameRate(25);
			break;
		case 'm': // fps 300
			ofSetFrameRate(300);
			break;
			
		case 'f': 	
		case ' ': // Fullscreen mode
			ofToggleFullscreen();
			gifW = gifs[gifnumb].getWidth();
			gifH = gifs[gifnumb].getHeight();	
			if (ofGetWindowMode() == OF_WINDOW) {
				ofShowCursor();
				ofSetWindowShape(gifW, gifH);
				ofSetWindowPosition((screenWidth/2)- (gifW/2), (screenHeight/2)-(gifH/2));
			}  else { 	ofHideCursor(); }	
			break;
			
		case 'b': // Save Gif frame to PNG
		#ifndef WIN32 // If mac export image next to the app
		ofSaveScreen("../../../GifExport_" + filename() + ".png");	
		#else // If win or linux then export in data folder	
		ofSaveScreen("GifExport_" + filename() + ".png");
		#endif
			break;
			
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
   
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo info){ 
	
    if( info.files.size() > 0 ){ // Add gif(s) by drag and drop
		
	for(int k = 0; k < info.files.size(); k++){

		bool success = dcd.decode(info.files[k]);
		if (success) {
			gifs.push_back(dcd.getFile());
			gifnumb++;
			gifnumbmax++;
			gifW = gifs[gifnumb].getWidth();
			gifH = gifs[gifnumb].getHeight();	
			if (ofGetWindowMode() == OF_WINDOW) { ofSetWindowShape(gifW, gifH); 
			ofSetWindowPosition((screenWidth/2)-(gifW/2), (screenHeight/2)-(gifH/2));
			}
			numFrame = gifs[gifnumb].getNumFrames()-1; // Gif n¡ of images
			gifD = gifs[gifnumb].getDuration(); // Gif duration  / example : 0.08
			framerate = (int)(gifD * fpsToGiftime); // Transform Gif time in approximative fps
			ofSetFrameRate(framerate);
		}
		
	}
		
		
	}
	
	
}

//--------------------------------------------------------------
void testApp::exit(){ 
    
}

//--------------------------------------------------------------
string testApp::filename() {
	
	if (ofGetMonth()<=9) {
		month = "0"+ ofToString(ofGetMonth());
	} else {
		month = ofToString(ofGetMonth());
	}
	
	if (ofGetDay()<=9) {
		day = "0"+ ofToString(ofGetDay());
	} else {
		day = ofToString(ofGetDay());
	}
	
	if (ofGetHours()<=9) {
		GetHours = "0"+ ofToString(ofGetHours());
	} else {
		GetHours = ofToString(ofGetHours());
	}
	
	if (ofGetMinutes()<=9) {
		GetMinutes = "0"+ ofToString(ofGetMinutes());
	} else {
		GetMinutes = ofToString(ofGetMinutes());
	}
	
	if (ofGetSeconds()<=9) {
		GetSeconds = "0"+ ofToString(ofGetSeconds());
	} else {
		GetSeconds = ofToString(ofGetSeconds());
	}
	
	string currentfile = 
	ofToString(ofGetYear()) + "."
	+ month			+ "." 
	+ day			+ "."
	+ GetHours		+ "h"
	+ GetMinutes	+ "m" 
	+ GetSeconds	+ "s";
	
	return currentfile;
	
}


