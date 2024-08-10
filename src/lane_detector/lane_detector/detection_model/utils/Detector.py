import numpy as np
import cv2
from lane_detector.detection_model.utils.Constants import *
from lane_detector.detection_model.utils import Utility

def region_selection(image):
	# create an array of the same size as of the input image 
	mask = np.zeros_like(image) 
	# if you pass an image with more then one channel
	if len(image.shape) > 2:
		channel_count = image.shape[2]
		ignore_mask_color = (255,) * channel_count
	# our image only has one channel so it will go under "else"
	else:
		# color of the mask polygon (white)
		ignore_mask_color = 255
	# creating a polygon to focus only on the road in the picture
	# we have created this polygon in accordance to how the camera was placed
	rows, cols = image.shape[:2]
	bottom_left = [cols * 0.1, rows * 0.95]
	top_left	 = [cols * 0.4, rows * 0.6]
	bottom_right = [cols * 0.9, rows * 0.95]
	top_right = [cols * 0.6, rows * 0.6]
	vertices = np.array([[bottom_left, top_left, top_right, bottom_right]], dtype = np.int32)
	# filling the polygon with white color and generating the final mask
	cv2.fillPoly(mask, vertices, ignore_mask_color)
	# performing Bitwise AND on the input image and mask to get only the edges on the road
	masked_image = cv2.bitwise_and(image, mask)
	return masked_image

def crop_image(image, lower_bound, upper_bound):
	rounded_lower = int((1 - upper_bound) * image.shape[0])
	rounded_upper = int((1 - lower_bound) * image.shape[0])
	
	crop = image[rounded_lower:rounded_upper, 0:image.shape[1]]
	return crop

def hough_transform(image, rho = HoughConstants.RHO, theta = np.pi/HoughConstants.THETA_DIVISOR, threshold = HoughConstants.THRESHOLD, 	minLineLength = HoughConstants.MIN_LENGTH, maxLineGap = HoughConstants.MAX_GAP):
	"""
	Determine and cut the region of interest in the input image.
	Parameter:
		image: grayscale image which should be an output from the edge detector
	"""

	return cv2.HoughLinesP(
		image, 
		rho = rho, 
		theta = theta, 
		threshold = threshold,
		minLineLength = minLineLength, 
		maxLineGap = maxLineGap
	)

def draw_lines(image, lines, color=[255, 0, 0], thickness=12):
	"""
	draws the lines onto a frame given each line
	"""

	if lines is None:
		return
	
	lined_img = np.zeros_like(image)

	for line in lines:
		for x1, y1, x2, y2 in line:
			cv2.line(lined_img, (x1, y1), (x2, y2), color, thickness)

	return cv2.addWeighted(image, 1.0, lined_img, 1.0, 1.0)
	
def get_slope_delta(frame):
	
	#gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
	
	threshold = binary_threshold(frame)
	
	edges = canny_frame(threshold)
	
	lines = hough_transform(edges)

	lined_frame = draw_lines(frame, lines)

	if len(lines) != 0:
                 
		left_lines, right_lines = Utility.filter_lines(lines)

		l_slope, l_yint = Utility.get_best_fit(left_lines)
		r_slope, r_yint = Utility.get_best_fit(right_lines)

		slope_delta = abs(l_slope) - abs(r_slope)
		
		Utility.draw_line_slope(lined_frame, l_slope, l_yint, 900, (0, 255, 0))
		Utility.draw_line_slope(lined_frame, r_slope, r_yint, 900, (0, 0, 255))

		Utility.put_text(lined_frame, slope_delta, 200, 200)

	return lined_frame, slope_delta

def hsv_filter(frame, lower_bound, upper_bound):
	"""
	applies an HSV filter onto the given frame with a lower and upper bound, the pixels accepted will be shown in their 
	original color and the rejected ones will be black
	"""

	hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

	mask = cv2.inRange(hsv, lower_bound, upper_bound)

	result = cv2.bitwise_and(frame, frame, mask = mask)

	return result

def hsv_mask(frame, lower_bound, upper_bound):
	"""
	applies an HSV mask onto the given frame with a lower and upper bound, the pixels 
	accepted will be pure white and the rejected pixels will be pure black.
	"""
	hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

	mask = cv2.inRange(hsv, lower_bound, upper_bound)

	return mask

def binary_threshold(frame, lower_bound = ThresholdConstants.LOWER_THRESHOLD, upper_bound = ThresholdConstants.UPPER_THRESHOLD):

	threshold = cv2.threshold(
                frame, 
                lower_bound, 
                upper_bound, 
                cv2.THRESH_BINARY)[1] 
	
	return threshold

def canny_frame(image, lower = CannyConstants.LOWER_THRESHOLD, upper = CannyConstants.UPPER_THRESHOLD):
	"""
	returns the edges detected in the frame given a lower and upper threshold
	"""

	edges = cv2.Canny(
		image, 
		lower, 
		upper
	)

	return edges

def gaussian_blur(frame, kernel = GaussianConstants.KERNEL):
	blur = cv2.GaussianBlur(frame, (kernel, kernel), 0)

	return blur

