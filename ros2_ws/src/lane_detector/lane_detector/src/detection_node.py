import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image 
from sensor_msgs.msg import CompressedImage
from std_msgs.msg import Float64
from cv_bridge import CvBridge
import cv2 
from utils import Detector

class LaneDetector(Node):

    def __init__(self):
        super().__init__('lane_detector')

        self.frame_publisher = self.create_publisher(CompressedImage, 'detection/image_raw/compressed', 10)
        self.delta_publisher = self.create_publisher(Float64, 'detection/slope_delta', 10)

        self.subscription = self.create_subscription(Image, 'camera/image_raw', self.listener_callback, 10)

        self.bridge = CvBridge()

    def listener_callback(self, image):
        frame = self.bridge.imgmsg_to_cv2(image)
        
        try:
            output_frame, slope_delta = Detector.get_slope_delta(frame)
            # output_frame = Detector.binary_threshold(frame)
            # slope_delta = 0
        except:
            output_frame = frame
            slope_delta = 0
            print("failure")

        slope_msg = Float64()
        slope_msg.data = float(slope_delta)

        compressed_output = self.bridge.cv2_to_compressed_imgmsg(output_frame, 'jpg')

        self.frame_publisher.publish(compressed_output)
        self.delta_publisher.publish(slope_msg)



def main(args=None):
    rclpy.init(args=args)

    lane_detector = LaneDetector()

    rclpy.spin(lane_detector)

    lane_detector.destroy_node()

    rclpy.shutdown()

if __name__ == '__main__':
    main()