clear;
a = arduino('COM4', 'Uno', 'Libraries', 'Ultrasonic');
sensor=ultrasonic(a, 'D5', 'D3');
distance = readDistance(sensor)*100
time=readEchoTime(sensor)
clear;