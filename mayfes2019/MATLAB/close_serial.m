
    clear cam;
    release(videoPlayer);
    release(pointTracker);
    release(faceDetector);


arduino = serial("/dev/ttyACM0");
fclose(arduino);
delete(arduino);
clear arduino;