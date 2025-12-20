-- select all records based on date
SELECT * FROM radar_logs
    WHERE DATE(timestamp) = '2025-12-20';

-- select all records based on time
SELECT * FROM radar_logs
    WHERE TIME(timestamp) BETWEEN '14:00:00' AND '15:00:00';

-- select all records from the last x hour/s
SELECT * FROM radar_logs
    WHERE timestamp > datetime('now', '-1 hours');

-- select all records based on date and time
SELECT * FROM radar_logs
    WHERE DATE(timestamp) = '2025-12-20'
    AND TIME(timestamp) BETWEEN '14:00:00' AND '15:00:00';