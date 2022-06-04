# Photocell-Door-with-Arduino-and-face_recognition-Library
Photocell door that can be opened and closed according to face recognition. Project simply works like; </br>
</br>-Python side take video stream from ESP-32 CAMERA that streaming through wifi. </br>
-Uses face_recognition library to process captured faces in video stream and compare faces that registered in the system. If the faces match, Python send the name of registered person to Arduino through Serial Port. Arduino display it on the Lcd like "Welcome ...." and Open the door for 3 seconds.</br>
-When door is closing if there was a interrupt like puting something between door, door will reopen and stay opened until object removed.</br>
-Lastly if someone inside the door want's to get out. There is a sensor that tracks motion and when it detect motion it will open the door.


# Project-Images

</br>
<div style="display:flex;justify-content: space-evenly">
<img src="https://github.com/HarunResitKarahan/Photocell-Door-with-Arduino-and-face_recognition-Library/blob/main/Photocell-Door-Image1.jpeg" width="400">
<img src="https://github.com/HarunResitKarahan/Photocell-Door-with-Arduino-and-face_recognition-Library/blob/main/Photocell-Door-Image2.jpeg" width="400"></div>
</br>
