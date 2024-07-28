import cv2

def null_method(x):
    pass

def put_text(frame, text, x, y):
    cv2.putText(
            img = frame, 
            text = str(text), 
            org = (x, y), 
            fontFace = cv2.FONT_HERSHEY_SIMPLEX, 
            fontScale = 1,
            thickness = 3,
            lineType = cv2.LINE_AA,   
            color = (0, 0, 255)
        )

def draw_line(frame, x1, y1, x2, y2, color=(0, 0, 255)):
    cv2.line(
            frame, 
            (x1, y1),
            (x2, y2),
            color, 
            5
        )
    
def draw_line_slope(frame, slope, y_int, length, color=(0, 0, 255)):
    if slope == None or slope == 0:
        print("slope")
        return
    
    if y_int == None:
        print("y int")
        return

    x1 = (frame.shape[0] - y_int) / slope
    y1 = frame.shape[0]

    x2 = x1 + (-length / slope)
    y2 = frame.shape[0] - length

    draw_line(frame, int(x1), int(y1), int(x2), int(y2), color)
    
def get_best_fit(lines):
    """
    Returns the slope and the y intercept given a list of points defined as lines

        Parameters:
            lines: array of lines in the format: x1, y1, x2, y2

        Returns:
            slope: slope of the linear regression
            y_intercept: y intercept of the line
    """

    slope = 0
    y_intercept = 0

    n = len(lines) * 2

    sum_x = 0
    sum_y = 0
    sum_xy = 0
    sum_x_squared = 0

    for line in lines:
        for x1, y1, x2, y2 in line:
            sum_x += x1 + x2
            sum_y += y1 + y2

            sum_xy += (x1 * y1) + (x2 * y2)
            sum_x_squared += (x1 * x1) + (x2 * x2)
            
    if ((n * sum_x_squared) - (sum_x * sum_x)) != 0:
        slope = ((n * sum_xy) - (sum_x * sum_y)) / ((n * sum_x_squared) - (sum_x * sum_x))
        y_intercept = (sum_y - (slope * sum_x)) / n

    return slope, y_intercept

def filter_lines(lines):

    left_lines = []
    right_lines = []
    
    for line in lines:
        for x1, y1, x2, y2 in line:
            if x2 - x1 == 0:
                return left_lines, right_lines

            slope = (y2 - y1) / (x2 - x1)

            if(slope > 0):
                right_lines.append(line)
            
            elif(slope < 0):
                left_lines.append(line)

    return left_lines, right_lines
        

class Trackbar:

    def __init__(self, bar_name, frame_name, default, upper):
        self.bar_name = bar_name
        self.frame_name = frame_name
        self.upper = upper
        self.default = default

        cv2.createTrackbar(bar_name, frame_name, default, upper, null_method)

    def get(self):
        return cv2.getTrackbarPos(self.bar_name, self.frame_name)
    
    def get_percent(self):
        return self.get() / self.upper