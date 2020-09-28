import numpy as np
import cv2
import RPi.GPIO as GPIO
from time import sleep

STOP  = 0
FORWARD  = 1
BACKWORD = 2

CH1 = 0
CH2 = 1

OUTPUT = 1
INPUT = 0

HIGH = 1
LOW = 0

ENA = 26

IN1 = 19  
IN2 = 13 

SET = 8

def setPinConfig(EN, INA, INB):        
    GPIO.setup(EN, GPIO.OUT)
    GPIO.setup(INA, GPIO.OUT)
    GPIO.setup(INB, GPIO.OUT)
    
    pwm = GPIO.PWM(EN, 100) 
    
    pwm.start(0) 
    return pwm


def setMotorContorl(pwm, INA, INB, speed, stat):

    
    pwm.ChangeDutyCycle(speed)  
    
    if stat == FORWARD:
        GPIO.output(INA, HIGH)
        GPIO.output(INB, LOW)
        
    
    elif stat == BACKWORD:
        GPIO.output(INA, LOW)
        GPIO.output(INB, LOW)
        
    
    elif stat == STOP:
        GPIO.output(INA, HIGH)
        GPIO.output(INB, HIGH)

        
GPIO.setmode(GPIO.BCM)
      

pwmA = setPinConfig(ENA, IN1, IN2)

def setMotor(ch, speed, stat):
    if ch == CH1:
        setMotorContorl(pwmA, IN1, IN2, speed, stat)

faceCascade = cv2.CascadeClassifier('SideFace.xml')
 

def detect(gray,frame):
 
    global SET  
    faces = faceCascade.detectMultiScale(gray, scaleFactor=1.05, minNeighbors=5, minSize=(100, 100), flags=cv2.CASCADE_SCALE_IMAGE)
 
    for (x, y, w, h) in faces:

        cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)
        print(x,y)

        if x>200 and x<270 and SET!=9 and y>120 :          
            setMotor(CH1, 100, FORWARD)
            sleep(8)
            setMotor(CH1, 100, STOP)
            SET = 9
            sleep(180)
        
        elif x>270 and SET!=9 and y>100: 
            setMotor(CH1, 100, FORWARD)
            sleep(8)
            setMotor(CH1, 100, STOP)
            SET = 9
            sleep(180)
        
        elif SET!=8 and x<180 and y<130:
            setMotor(CH1, 100, BACKWORD)
            sleep(8)
            setMotor(CH1, 100, STOP)
            SET = 8
            sleep(180)
 
    return frame
 

video_capture = cv2.VideoCapture(0)
 
while True:

    _, frame = video_capture.read()

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
 

    canvas = detect(gray, frame)

    cv2.imshow("CheckOnDisplay", canvas)
 

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


video_capture.release()
cv2.destroyAllWindows()
