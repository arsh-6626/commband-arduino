# Commband Project

## Introduction

We are living in an era of technological advancements, yet people with disabilities often rely on primitive methods of external help. The DTS (Disability Technology Solutions) system focuses on using open-source technology and smartphones to assist specially-abled individuals with modern yet affordable methods.

All components are built around Arduino microcontrollers and their interactions with a smartphone application built using MIT App Inventor.

---

## CommBand

CommBand is a gesture recognition device that uses an accelerometer to assist individuals with speech impairments or those who cannot use sign language. It aims to provide an alternative means of communication for people with conditions like cerebral palsy and Parkinson's Disease.

### Components Used
- **Arduino UNO**
- **HC-05 Bluetooth Module**
- **MPU6050 Accelerometer**

---

## Working Principle

The MPU6050 accelerometer is a micro-machined structure that can measure acceleration along the X, Y, and Z axes. The structure is suspended by polysilicon springs, allowing it to deflect when accelerated. This deflection changes the capacitance between fixed and suspended plates, and this change is proportional to the acceleration along each axis. The sensor processes these changes and outputs an analog voltage signal.

The roll and pitch values are calculated using the following equations:

- **Roll**: 
  \[
  \text{roll} = \arctan \left(\frac{a_y}{a_x}\right)
  \]

- **Pitch**:
  \[
  \text{pitch} = -\arctan \left(\frac{a_x}{\sqrt{a_y^2 + a_z^2}}\right)
  \]

- **Gesture Recognition**: The microcontroller processes these roll and pitch values to identify specific gestures. Once a gesture is recognized, the data is sent to a custom-made mobile app that outputs the corresponding message in text and audio format.

### Workflow
1. A gesture is performed.
2. The accelerometer detects changes in acceleration.
3. The microcontroller processes the data and sends it to the mobile app.
4. The app identifies the gesture and gives an audio message output.

---

## Merits
- **Cost-Effective**: The expected cost of production is less than 900 INR.
- **Open Source**: Easily upgradeable or customizable for various use cases.
- **Lightweight and Wearable**: Designed for easy use and comfort.

---

## Future Scope
1. Enhanced data analysis to increase the number of gestures.
2. Implementing machine learning for a wider range of gestures, potentially covering the entire alphabet series.
3. Improving precision to reduce the delay between gesture detection and audio output.

---

## Acknowledgments
This project is built using open-source technologies and aims to make communication more accessible for people with disabilities. Contributions and customizations are encouraged to further improve and expand the functionality of the system.
