-- Change datatype of status from an INTEGER to TINYINT
ALTER TABLE private_dms ADD COLUMN new_column_name TINYINT;
UPDATE private_dms SET new_column_name = CAST(status as TINYINT);
ALTER TABLE private_dms DROP COLUMN status;

ALTER TABLE private_dms ADD COLUMN status TINYINT;
UPDATE private_dms SET status = new_column_name;
ALTER TABLE private_dms DROP COLUMN new_column_name;
