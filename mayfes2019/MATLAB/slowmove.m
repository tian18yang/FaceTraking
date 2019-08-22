clear cam;

L = 1;

l = 10;
d = 40;
theta4 = 0;
phi = [-90,45,0];
theta = [phi_to_theta(phi),0];
ft = finaladjustment(theta);

runLoop = 1;
numPts = 0;

faceDetector = vision.CascadeObjectDetector();
pointTracker = vision.PointTracker('MaxBidirectionalError', 2);
cam = webcam();
videoFrame = snapshot(cam);
frameSize = size(videoFrame);
videoPlayer = vision.VideoPlayer('Position', [100 100 [frameSize(1), frameSize(2)]+30]);

fwrite(arduino,['H','4',theta(4),10]);
fwrite(arduino,['H','3',theta(3),10]);
fwrite(arduino,['H','2',theta(2),10]);
fwrite(arduino,['H','1',theta(1),10]);

tic;
while(toc<5)
end

phi = [90,45,0];
theta = [phi_to_theta(phi),0];
ft = finaladjustment(theta);
fwrite(arduino,['H','4',thera(4),1]);
fwrite(arduino,['H','3',ftheta(3),1]);
fwrite(arduino,['H','2',theta(2),1]);
fwrite(arduino,['H','1',theta(1),1]);

ffclog=[];
fplog=[];
bcplog=[];
finalthetalog=[];

%step(videoPlayer, videoFrame);

    %arduino = serial("/dev/ttyACM0");
    %fopen(arduino);
    while runLoop
        
        
        
        found = 0;
        originalvideoFrame = snapshot(cam);
        videoFrame = imresize(originalvideoFrame,0.5);
        videoFrame = fliplr(permute(videoFrame,[2,1,3]));
        frameSize = size(videoFrame);
        videoFrameGray = rgb2gray(videoFrame);
        
        if numPts < 10
            
            % Detection mode.
            bbox = faceDetector.step(videoFrameGray);
            bbox2=zeros(0,4);
            for i = 1:size(bbox,1)
                if bbox(i,3)>80
                    bbox2=bbox(i,:);
                end
            end
            bbox=bbox2;
        
            if ~isempty(bbox)
                % Find corner points inside the detected region.
                points = detectMinEigenFeatures(videoFrameGray, 'ROI', bbox(1, :));
                sizebbox=bbox(1,3);
            
            % Re-initialize the point tracker.
                xyPoints = points.Location;
                numPts = size(xyPoints,1);
                release(pointTracker);
                initialize(pointTracker, xyPoints, videoFrameGray);
            
            % Save a copy of the points.
                oldPoints = xyPoints;
            
            % Convert the rectangle represented as [x, y, w, h] into an
            % M-by-2 matrix of [x,y] coordinates of the four corners. This
            % is needed to be able to transform the bounding box to display
            % the orientation of the face.
                bboxPoints = bbox2points(bbox(1, :));
                found = 1;
            
            % Convert the box corners into the [x1 y1 x2 y2 x3 y3 x4 y4] 
            % format required by insertShape.
                bboxPolygon = reshape(bboxPoints', 1, []);
            
            % Display a bounding box around the detected face.
                videoFrame = insertShape(videoFrame, 'Polygon', bboxPolygon, 'LineWidth', 3);
            
            % Display detected corners.
                videoFrame = insertMarker(videoFrame, xyPoints, '+', 'Color', 'white');
            end
        
        else
        % Tracking mode.
            [xyPoints, isFound] = step(pointTracker, videoFrameGray);
            visiblePoints = xyPoints(isFound, :);
            oldInliers = oldPoints(isFound, :);
                
            numPts = size(visiblePoints, 1);       
        
            if numPts >= 10
            % Estimate the geometric transformation between the old points
            % and the new points.
                [xform, oldInliers, visiblePoints] = estimateGeometricTransform(...
                    oldInliers, visiblePoints, 'similarity', 'MaxDistance', 4);            
            
            % Apply the transformation to the bounding box.
                bboxPoints = transformPointsForward(xform, bboxPoints);
                found = 1;
            
            % Convert the box corners into the [x1 y1 x2 y2 x3 y3 x4 y4] 
            % format required by insertShape.
                bboxPolygon = reshape(bboxPoints', 1, []);            
            
            % Display a bounding box around the face being tracked.
                videoFrame = insertShape(videoFrame, 'Polygon', bboxPolygon, 'LineWidth', 3);
            
            % Display tracked points.
                videoFrame = insertMarker(videoFrame, visiblePoints, '+', 'Color', 'white');
            
            % Reset the points.
                oldPoints = visiblePoints;
                setPoints(pointTracker, oldPoints);
            end

        end
        
    % Display the annotated video frame using the video player object.
        %step(videoPlayer, videoFrame);
        

    % Check whether the video player window has been closed.
        %runLoop = isOpen(videoPlayer);
        
        
        if found==1
            L=0;
            ffc = facefromcamera(bboxPoints,frameSize,phi(3),theta4);
            fp  = face_position(phi,ffc,l,theta4);
            bcp = best_camera_position(fp,d,l,ffc(3))
            
            %phi = theta_to_phi(bcp(1:3));
        
        
            face_dy = (bboxPoints(1,2) + bboxPoints(2,2) + bboxPoints(3,2) + bboxPoints(4,2))/4-frameSize(1)/2;
            face_dx = (bboxPoints(1,1) + bboxPoints(3,1))/2 - frameSize(2)/2;
            if(face_dy<200)
                face_dy=0;
            end
            %bcp(3)=theta(3)-face_dy*0.0001;
            bcp(4)=theta4-face_dx*0.01;
            
            a=2;
        
            final_theta = finaladjustment(bcp);
        
            %{
            fwrite(arduino,double(['H','1',final_theta(1),20]));
            fwrite(arduino,double(['H','2',final_theta(2),20]));
            fwrite(arduino,double(['H','3',final_theta(3),10]));
            fwrite(arduino,double(['H','4',90,20]));
            %}
            
            Text = [fp(1) fp(2) fp(3) phi(3)];
            videoFrame = insertText(videoFrame,[1 100;1 200;1 300;1 400],Text,'FontSize',30);
            %videoFrame = insertText(videoFrame,[100,400],strcat('size = ',num2str(sizebbox)),'FontSize',30);
            videoPlayer(videoFrame);
            tic;
            %{
            while 1
                
                while arduino.BytesAvailable<2
                    if(toc>0.5)
                        break;
                    end
                end
                if(toc>0.5)
                    break;
                end
                index = fread(arduino,1,'uchar');
                if index==201
                    theta(1)=fread(arduino,1,'uchar')+15;
                end
                if index==202
                    theta(2)=fread(arduino,1)+40;
                end
                if index==203
                    theta(3)=90-fread(arduino,1);
                end
                if index==204
                    theta4=fread(arduino,1)-90;
                    break;
                end
                flushinput(arduino);
            end
            %}
        end
        
        runLoop = isOpen(videoPlayer) || L;
        
    end

% Clean up.
    clear cam;
    release(videoPlayer);
    release(pointTracker);
    release(faceDetector);