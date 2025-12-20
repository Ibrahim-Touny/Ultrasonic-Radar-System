-- select all records where mode is automatic (0)
SELECT * FROM radar_logs
    WHERE mode = 0;

-- select all records where mode is manual (1)
SELECT * FROM radar_logs
    WHERE mode = 1;