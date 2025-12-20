-- select all records where buzzer is on (1)
SELECT * FROM radar_logs
    WHERE buzzer_active = 1;

-- select all records where buzzer is off (0)
SELECT * FROM radar_logs
    WHERE buzzer_active = 0;