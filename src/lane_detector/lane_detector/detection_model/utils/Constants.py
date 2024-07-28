import numpy as np

class ThresholdConstants:
    LOWER_THRESHOLD = 150
    UPPER_THRESHOLD = 255

class CannyConstants:
    LOWER_THRESHOLD = 380
    UPPER_THRESHOLD = 500

class CropConstants:
    LOWER_BOUND = 0.11764705882
    UPPER_BOUND = 0.42352941176

class HoughConstants:
    RHO = 1 # Distance resolution of the accumulator, pixels 
    THETA_DIVISOR = 180 # Angle resolution of the accumulator, radians
    THRESHOLD = 30 # lines with intersections less than this are rejected
    MIN_LENGTH = 20 # Line segments shorter than this are rejected
    MAX_GAP = 5 # Gap between points on the same line to link them

class ColorConstants:

    LOWER_H = 21
    LOWER_S = 4
    LOWER_V = 75

    UPPER_H = 60
    UPPER_S = 255
    UPPER_V = 255

    LOWER_HSV = np.array([
        LOWER_H,
        LOWER_S,
        LOWER_V
    ])

    UPPER_HSV = np.array([
        UPPER_H,
        UPPER_S,
        UPPER_V
    ])

class GaussianConstants:
    KERNEL = 5