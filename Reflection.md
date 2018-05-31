# PID Control Project

## Introduction

  The requirement of this project was to implement a PID controller which takes in as inputs the vehicle's velocity and the Cross-Track-Error. This also required parameter tuning to come up with optimal parameters.

## Approach

Followed the approach as discussed in the previous lesson and also followed this document for manual parameter tuning. http://smithcsrobot.weebly.com/uploads/6/0/9/5/60954939/pid_control_document.pdf

As per the above document Started with all the parameters as 0. Then stepwize did the following.

1. Increase Kp slowly. Started with .1 and went all the way to .2, however at .2 the osciallations were pretty huge and the vehicle would drop off. So after this I stared decreasing the Kp value and set it to .125, since the oscillations were not bad enough and the vehicle would stay on track.

2. After this I introduced the Kd parameter, to counter the oscillations. I initiated Kd to 3.0 and this resulted in decrease in the oscillations and stable driving at low throttle. Basically I could have ended this project here if I had to just drive at 0.3 throttle.

3. The vehicle was still having issues around the corners though. And also sometimes maintaining the center line. So I introduced a small Ki to start with, and as a result saw much better centering and performance around the turns.

4. Now I started increasing the throttle, however the performance would be very bad as the speed decreased. Just as we brake when we are near a curve or the vehicle is not controllable, it was clear that I need to decrease speed with increasing cte, if I wanted to stabilize the evhicle again.For this reason I also added a PID controller on throttle. I set the parameters, Kp -> 0.35 and Ki -> 0.0 and Kd-> 0.05.

5. At this point the vehicle was able to drive on the loop without falling out. For further optimization I decided to use twiddle. I implemented twiddle as suggested in the lessons. I ran twiddle alternatively on the throttle and steer PID's. And this way I was able to reach the final set of parameters.

# Importance of parameters

1. Kp contributes to the proportional steering response for the cte. This has the most strongest effect on reducing the error and bringing back the vehicle on the requisite track. [Checkout the video with Kp set to 0.](https://github.com/amrosebirani/CarND-PID-Control-Project/blob/master/videos/Video_without_Kp.mov) 

2. Kd contributes in stabilising the oscillations across the center line. If we remove this by setting it to 0, the vehicles oscillates a lot and ultimately drops out of the track. [Checkout the video with Kd set to 0 .](https://github.com/amrosebirani/CarND-PID-Control-Project/blob/master/videos/Video_Without_Kd.mov)

3. Ki counters other systemic errors like steering drift, but also generally smoothens the performance around curves etc. If we remove it we can see that the car constantly overshoots around curves and generally loses the track. [Checkout the video with Ki set to 0.](https://github.com/amrosebirani/CarND-PID-Control-Project/blob/master/videos/Video_without_Ki.mov)
