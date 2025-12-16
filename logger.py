import serial
import sqlite3
from datetime import datetime

# -------- SERIAL SETUP --------
PORT = "COM5"     # CHANGE to your Arduino UNO COM port
BAUD = 115200

try:
    ser = serial.Serial(PORT, BAUD, timeout=1)
    print(f"Connected to {PORT} at {BAUD} baud")
except Exception as e:
    print(f"Error connecting to serial port: {e}")
    exit(1)

# -------- SQLITE SETUP --------
conn = sqlite3.connect("radar_logs.db")
cursor = conn.cursor()

cursor.execute("""
CREATE TABLE IF NOT EXISTS radar_logs (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    timestamp TEXT,
    angle INTEGER,
    distance INTEGER,
    mode INTEGER,
    buzzer_active INTEGER
)
""")

conn.commit()
print("Database initialized: radar_logs.db")
print("Logging started...\n")

# -------- MAIN LOOP --------
try:
    while True:
        line = ser.readline().decode(errors="ignore").strip()

        if not line:
            continue

        try:
            # Expected format: angle,distance,mode,buzzer
            parts = line.split(",")
            
            if len(parts) != 4:
                print(f"Invalid format: {line}")
                continue

            angle = int(parts[0])
            distance = int(parts[1])
            mode = int(parts[2])
            buzzer = int(parts[3])

            timestamp = datetime.now().isoformat()

            cursor.execute(
                "INSERT INTO radar_logs (timestamp, angle, distance, mode, buzzer_active) VALUES (?, ?, ?, ?, ?)",
                (timestamp, angle, distance, mode, buzzer)
            )

            conn.commit()

            mode_str = "MANUAL" if mode == 1 else "AUTO"
            buzzer_str = "ON" if buzzer == 1 else "OFF"
            distance_str = f"{distance}cm" if distance != -1 else "OUT OF RANGE"

            print(f"[{timestamp}] Angle: {angle}° | Distance: {distance_str} | Mode: {mode_str} | Buzzer: {buzzer_str}")
            
        except ValueError as e:
            print(f"Parse error: {line} → {e}")

except KeyboardInterrupt:
    print("\n\nLogging stopped by user")
    
finally:
    ser.close()
    conn.close()
    print("Resources cleaned up")
