#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	directoryName = "/Users/samfriedman/Pictures/small/";
    newFileName = "tl_";
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofDrawBitmapString("Press spacebar to open an image, \"s\" to save the processed output", 20, 15);
	
	for (unsigned int i=0; i<loadedImages.size(); i++){
		loadedImages[i].draw(0, i*160 + 20);

	}
	
	for (unsigned int i=0; i<processedImages.size(); i++){
		processedImages[i].draw(processedImages[i].getWidth()+5, i*160 + 20);
	}


	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == 'd'){
        dir.listDir(directoryName);
        dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
        
        processedImages.clear();
        loadedImages.clear();
        
        // you can now iterate through the files and load them into the ofImage vector
        for(int i = 0; i < (int)dir.size(); i++){
            //Load the selected image
            ofImage image;
            int lastindex = dir.getPath(i).find_last_of(".");
            string rawname = dir.getPath(i).substr(0, lastindex);
            
            image.loadImage(dir.getPath(i));
            image.resize(128, 160);
            loadedImages.push_back(image);
            
            //Make some short variables
            int w = image.getWidth();
            int h = image.getHeight();
            
            //Make a new image to save manipulation by copying the source
            ofImage processedImage = image;
            
            //Walk through the pixels
            for (int y = 0; y < h; y++){
                for (int x = 0; x < w; x++){
                    
                    //Capture the colors for the row
                    ofColor color = image.getColor(x, y);
                    processedImage.setColor(x, y, color);
                }
            }
            //Store the processed image
            processedImages.push_back(processedImage);\
            processedImages[i].saveImage(dir.getOriginalDirectory()+newFileName+ofToString(i)+".bmp");

        }

    }
	if (key == ' '){
		
		//Open the Open File Dialog
		ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a jpg or png"); 
		//Check if the user opened a file
		if (openFileResult.bSuccess){
			
			ofLogVerbose("User selected a file");
			
			//We have a file, check it and process it
			processOpenFileSelection(openFileResult);
			
		}else {
			ofLogVerbose("User hit cancel");
		}
	}
	
	if (key == 's'){
		
		if (processedImages.size()==0){
			//User is trying to save without anything to output - bail
			return;
		}
		
		//
		ofFileDialogResult saveFileResult = ofSystemSaveDialog(ofGetTimestampString() + ".bmp" , "Save your file as a bitmap");
		if (saveFileResult.bSuccess){
			processedImages[0].saveImage(saveFileResult.filePath);
		}
	}
	
	
}

//Sort function for stl::sort http://www.cplusplus.com/reference/algorithm/sort/
bool sortColorFunction (ofColor i,ofColor j) { 
	return (i.getBrightness()<j.getBrightness()); 
}


void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult){
	
	ofLogVerbose("getName(): "  + openFileResult.getName());
	ofLogVerbose("getPath(): "  + openFileResult.getPath());
	
	ofFile file (openFileResult.getPath()); 
	
	if (file.exists()){
		//Limiting this example to one image so we delete previous ones
		processedImages.clear();
		loadedImages.clear();
		
		ofLogVerbose("The file exists - now checking the type via file extension");
		string fileExtension = ofToUpper(file.getExtension());
		
		//We only want images
		if (fileExtension == "JPG" || fileExtension == "PNG" || fileExtension == "BMP" || fileExtension == "GIF") {
			
			//Save the file extension to use when we save out
			originalFileExtension = fileExtension;
			
			//Load the selected image
			ofImage image;
			image.loadImage(openFileResult.getPath());
			image.resize(128, 160);
			loadedImages.push_back(image);
			
			//Make some short variables 
			int w = image.getWidth();
			int h = image.getHeight();
			
			//Make a new image to save manipulation by copying the source
			ofImage processedImage = image;
			
			//Walk through the pixels
			for (int y = 0; y < h; y++){
				for (int x = 0; x < w; x++){
					
					//Capture the colors for the row
					ofColor color = image.getColor(x, y); 
					processedImage.setColor(x, y, color);
				}
			}
			//Store the processed image
			processedImages.push_back(processedImage);
		}
        ofLogVerbose("The file has been copied.");

	}
	
}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	
}
