from setuptools import find_packages, setup
import os
from glob import glob

package_name = 'lane_detector'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob(os.path.join('launch', '*launch.[pxy][yma]*'))),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='dev',
    maintainer_email='awesomeyooner@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],

    entry_points={
        'console_scripts': [
            'camera_driver = lane_detector.camera_publisher.driver:main',
            'camera_compressor = lane_detector.camera_publisher.compressed:main',
            'detector_node = lane_detector.detection_model.detection_node:main',
        ],
    },
)
