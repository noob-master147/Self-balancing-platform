import cv2
import imutils


"""range for both to be mentioned in HSV"""
#orange is the colour of the ball
orange_low = (5,50,50)
orange_high = (15,255,255)

cap = cv2.VideoCapture(0)

while True:
    _ , frame = cap.read()
    frame = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
    orange = cv2.inRange(frame, orange_low, orange_high)
    try:
        cnts = cv2.findContours(orange.copy(), cv2.RETR_LIST, cv2.CHAIN_APPROX_NONE)
        orange_cnts = imutils.grab_contours(cnts)

        cnt = cnts[0]
        M = cv2.moments(cnt)
        cx = int(M['m10']/M['m00'])
        cy = int(M['m01']/M['m00'])

        cv2.circle(frame,(cx,cy),7,(255,0,0),-1)
        cv2.imshow("orange",frame)
        #orange.shape[0] = hieght in pixels
        #1 px = 0.026458333 cm
        #Area of screen (cm) = orange.shape[0]*orange.shape[1]*0.026458333
        
        Area_cv = orange.shape[0]*orange.shape[1]*((0.026458333)**2)
        #print(Area_cv)
        Area_platform = 22.4*22.4
        centre_y = (orange.shape[0])/2
        centre_x = (orange.shape[1])/2

        dist_cv = (((cx-centre_x)**2 - (cy-centre_y)**2)**(0.5))*0.026458333

        #The actual distance of the ball from the centre
        dist_platform = (dist_cv*(Area_cv/Area_platform))
        print(dist_platform)

        key = cv2.waitKey(1)
        #space to exit
        if key == 32:
            break
    except:
        cv2.imshow("orange",orange)
        key = cv2.waitKey(1)
        if key == 32:
            break
        


	
    
    


