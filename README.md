# Arduino Radar Project

A multi-component radar system that visualizes distance measurements and angles in real-time using Arduino, Processing, and Python.

## Project Structure

- **Radar1.ino & Radar2.ino**: Arduino sketches (Arduino Mega and Arduino UNO)
- **Radar_pde.pde**: Processing visualization application
- **logger.py**: Python data logger for SQLite database storage
- **Radar Circuit Diagram/**: Circuit schematics and design files

## System Overview

- **Arduino Mega**: Reads ultrasonic sensor data and controls servo motor
- **Arduino UNO**: Communicates with the Mega via serial
- **Processing**: Real-time radar visualization
- **Python Logger**: Records data to SQLite database

---

## Prerequisites

### Hardware
- Arduino Mega
- Arduino UNO
- HC-SR04 Ultrasonic Sensor
- Servo Motor
- Joystick Module
- USB cables

### Software
- Arduino IDE (https://www.arduino.cc/en/software)
- Processing (https://processing.org/download)
- Python 3.x (https://www.python.org/downloads)

### Python Dependencies
```bash
pip install pyserial
```

---

## Setup Instructions

### 1. Proteus Circuit Simulation (Optional)

To run the circuit simulation in Proteus:

1. Open Proteus Design Suite
2. Open `Radar Circuit Diagram/Radar Circuit Diagram.pdsprj`
3. Add Extra Libraries:
   - In Proteus, go to **Settings** → **Manage Paths**
   - Add the library path: `Radar Circuit Diagram/Extra Library/`
   - Alternatively, copy contents from `Extra Library/` to your Proteus default library folder
4. Compile and simulate the circuit design

### 2. Arduino Setup

1. **Upload to Arduino Mega**:
   - Open Arduino IDE
   - Select `Radar1/Radar1.ino`
   - Select Board: `Arduino Mega 2560`
   - Select the correct COM port
   - Click Upload

2. **Upload to Arduino UNO**:
   - Open Arduino IDE
   - Select `Radar2/Radar2.ino`
   - Select Board: `Arduino UNO`
   - Select the correct COM port
   - Click Upload

---

## Configuring COM Ports

### Find Your COM Ports
1. **Windows**: Open Device Manager → Ports (COM & LPT) → Note the COM numbers for each Arduino

### 2. Processing Configuration

Edit `Processing Code/Radar_pde.pde`:

Find this line (around line 22):
```java
myPort = new Serial(this, "COM6", 9600);
```

Replace `"COM6"` with your Arduino Mega COM port:
```java
myPort = new Serial(this, "COM3", 9600);  // Change COM6 to your port
```

**Note**: The baud rate `9600` matches `Serial.begin(9600)` in Radar1.ino

### 3. Python Logger Configuration

Edit `logger.py`:

Find this line (line 7):
```python
PORT = "COM5"     # CHANGE to your Arduino UNO COM port
```

Replace `"COM5"` with your Arduino UNO COM port:
```python
PORT = "COM4"     # Change to your port
```

**Note**: The baud rate `115200` matches `Serial1.begin(115200)` in Radar1.ino

---

## Running the Project

### Step 1: Start Arduino Devices
- Both Arduinos should be connected and programmed
- Open the serial monitor to verify data transmission

### Step 2: Start the Python Logger (Optional)
```bash
cd c:\Users\Ibrahim.ElTouny\Documents\Arduino\Radar
python logger.py
```

- The script will create/update `radar_logs.db` with sensor readings
- Press `Ctrl+C` to stop logging

### Step 3: Start Processing Visualization
1. Open Processing
2. Open `Processing Code/Radar_pde.pde`
3. Click the **Play** button (▶) to start the sketch
4. The radar visualization should appear in a new window

---

## Operation Modes

### Automatic Mode
- Servo continuously scans from left to right
- Distance measurements update in real-time

### Manual Mode
- Press the joystick button to toggle manual control
- Use joystick X-axis to control servo angle
- Real-time position updates

---

## Troubleshooting

### "COM Port Not Found"
- Verify USB cables are connected
- Check Device Manager for correct COM port numbers
- Update COM port values in Processing and Python files
- Restart Arduino IDE and Processing

### No Data in Processing
- Check Arduino Mega is powered and running
- Verify Processing COM port matches Arduino Mega's actual port
- Check Serial monitor to confirm data transmission at 9600 baud
- Ensure Arduino sketch uploaded successfully

### Python Logger Crashes
- Verify Python is installed: `python --version`
- Install pyserial: `pip install pyserial`
- Check Arduino UNO COM port in Python script
- Verify baud rate is 115200

### Data Not Logging to Database
- Ensure logger.py is running with Python 3
- Check write permissions in the Radar folder
- Verify `radar_logs.db` file is created
- Use SQLite viewer to inspect database

---

## Database Schema

The Python logger stores data in `radar_logs.db` with the following structure:

| Column | Type | Description |
|--------|------|-------------|
| id | INTEGER | Primary key |
| timestamp | TEXT | Recording timestamp |
| angle | INTEGER | Servo angle (0-180°) |
| distance | INTEGER | Measured distance (cm) |
| mode | INTEGER | 0=Automatic, 1=Manual |
| buzzer_active | INTEGER | Buzzer state |

---

## Quick Reference: COM Port Locations

| Component | File | Variable | Default |
|-----------|------|----------|---------|
| Arduino Mega → Processing | `Radar_pde.pde` | Line 22 | COM6 |
| Arduino UNO → Python | `logger.py` | Line 7 | COM5 |

---

## Support

For issues or questions, check:
1. Arduino IDE console for upload errors
2. Processing console for data reception errors
3. Command line output when running Python logger
4. Device Manager to verify COM ports

---

## License

This project is for educational and personal use.
