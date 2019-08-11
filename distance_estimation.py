import cv2
import numpy as np
import imutils


"""range for both to be mentioned in HSV"""
#orange is the colour of the ball
orange_low = [ , , ]
orange_high = [ , , ]

#green in the centre of the marker at the centre 
green_low = [ , , ]
green_high = [ , , ]

cap = cv2.VideoCapture(0)

while True:
    _ , frame = cap.read()
    frame = cv2.cvtColor(frame, cv2.cvtColor_BGR2HSV)
    orange = cv2.inRange(frame, orange_low, orange_high)
    green = cv2.inRange(frame, green_low, green_high)

    orange_cnts = cv2.findContours(orange.copy(), cv2.RETR_LIST, cv2.CHAIN_APPROX_NONE)
    orange_cnts = imutils.grab_contours(cnts)
    #o is the contour with maximum area out of all the contours
    o = max(orange_cnts, key = cv2.contourArea)

    #finding centre of contour, here the coordinates of centre is (cX,cY)
    M = cv2.moments(o)
	cX = int(M["m10"] / M["m00"])
	cY = int(M["m01"] / M["m00"])
    
    #Area of ball to be used for similarity
    orange_area = cv2.minEnclosingCircle(o)
    
    green_cnts = cv2.findContours(orange.copy(), cv2.RETR_LIST, cv2.CHAIN_APPROX_NONE)
    green_cnts = imutils.grab_contours(cnts)
    #g is the contour with maximum area out of all the contours
    g = max(green_cnts, key = cv2.contourArea)
    

""" now find out the area of the contour for a known distance from camera 
    say when the object is at 20cm distance from camera area of contour is
    A1 cm^2. Now for an unknown distance since we know area of the new contour
    say it is A2 cm^2. 

                Distance (unknown) = (20*A2)/A1 ; :: SIMILARITY OF AREAS

    This is not a strong logic for motion in 2 directions. Hence i strongly
    suggest using a camera for motion along x - axis and another for motion
    along y - axis """

#Another assumption is that the contour with the largest area is the required contour
    known_area = 
    distance_of_ball_from_camera = known_length*orange_area/known_area
    """Distance of ball from centre = root over((cX-x)^2 + (cY-y)^2) ; Here x and y are
    coordinates of centre i.e., the centre you have to define"""


