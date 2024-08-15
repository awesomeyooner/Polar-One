import rclpy
from rclpy.node import Node
from geometry_msgs import Tra
from cv_bridge import CvBridge
import cv2 

class NodeManager(Node):

    def __init__(self):
        super().__init__('apriltag_detector')

        self.publisher = self.create_publisher(Image, 'apriltag/tf', 10)

        timer_period = 0.005 #seconds

        self.timer = self.create_timer(timer_period, self.timer_callback)

        self.capture = cv2.VideoCapture(0)

    def timer_callback(self):
        ret, frame = self.capture.read()

        mirrored_side = cv2.flip(frame, 0)
        normal = cv2.flip(mirrored_side, 1)

        if ret:
            self.publisher.publish(
                self.bridge.cv2_to_imgmsg(normal)
            )

def main(args=None):
    rclpy.init(args=args)
    node = NodeManager()

    rclpy.spin(node)

    node.destroy_node()

    node.capture.release()
    
    rclpy.shutdown()

if __name__ == '__main__':
    main()