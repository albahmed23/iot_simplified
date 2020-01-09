# Simulate an IoT Device Sending Data

Using Python scripts and mqtt.eclipse.org server to simulate a device sending data. This is a good way to learn how devices send data to each other and it can also be a kick off to writing scripts that would analyze the data. 

The device is pretending to be a sound sensor that sends random data points every 10 seconds.

## Get Started

- Install python dependances:
    - paho-mqtt 1.5.0

    `pip install paho-mqtt`
    - matplotlib 3.1.2

    `pip install matplotlib`

### Make Data

Run the `make_data.py` script to start making data by publishing to the topic **sensor/sound**.

`python make_data.py`

### Get Data

Once data is being published to the topic, use `get_data.py` to subsribe to the topic and listen to data as they come in. In our case, we are saving the data in a csv file in the same folder as the get_data.py.

`python get_data.py`

### Read Data

In our case we called it `visualize_data.py` as we could plot the data using the matplotlib. You can do anything with the data at this point.

`python visualize_data.py`


> Please feel free to contact us if you have any questions or post an issue.