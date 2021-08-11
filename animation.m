%% Video Recording
% Note: here, I determine the frame rate based on the number of frames and
% the desired duration.  Alternatively, you can set the frame rate, and let 
% the duration vary.
data = csvread('animation.csv');

vidStr = 'trajectories';    %Name of video file to be saved
nFrames = 300;    %Number of frames
duration = 15; %Video duration [Seconds]

vidObj = VideoWriter(vidStr,'MPEG-4');  %Create video object, .mp4
vidObj.FrameRate = 20;   %Set frame rate
  % Set video quality to max
   %Open video object for editing
open(vidObj);
randX = data(:,1); randY = data(:,2);
chaseX = data(:,3); chaseY = data(:,4);
folX = data(:,5); folY = data(:,6);
for j = 1:nFrames
    % Plot something in this loop. Each loop iteration becomes a frame in
    % the video.
    
    if chaseX(j) > 0 
        plot(chaseX(j),chaseY(j),'r.'); 
        
    end
    if folX(j) > 0
        plot(folX(j),folY(j),'g.');
    end
    hold on; axis equal;
    plot(randX(j),randY(j),'b.');plot(data(j,7),data(j,8),'k.');
    plot(data(j,9),data(j,10),'m.');

    drawnow % Force plot to update before code advances
    writeVideo(vidObj,getframe(gcf));
end


close(vidObj);  %Close the video object, so you can open it outside of MATLAB